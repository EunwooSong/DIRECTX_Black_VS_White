#include "pch.h"
#include "Application.h"
#include "Input.h"
#include "Procedure.h"
#include "Audio.h"


Application::Application() : hwnd(NULL), graphic(NULL), changeSceneCalled(false), currentScene(NULL), timeScale(1.0f)
{

}


Application::~Application()
{
}

Application * Application::GetInstance()
{
	static Application app;
	return &app;
}

void Application::Run(const wchar_t * title, int width, int height, bool isFullscreen, Scene * firstScene)
{
	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			if (SUCCEEDED(Initialize(title, width, height, isFullscreen, firstScene)))
			{
				RunMessageLoop();
				Uninitialize();
			}
		}
		CoUninitialize();
	}
}

HRESULT Application::Initialize(const wchar_t* title, int width, int height, bool isFullscreen, Scene* firstScene)
{
	HRESULT hr;

	graphic = Graphic::GetInstance();
	graphic->width = width;
	graphic->height = height;
	graphic->isFullScreen = isFullscreen;
	hr = CreateFrame(title, width, height, isFullscreen);				//������ Ŭ���� ��� �� �ʱ�ȭ
	if (FAILED(hr))
		return E_FAIL;

	hr = graphic->CreateDeviceIndependentResources();	//��ġ ������ �ڿ� ����
	if (FAILED(hr))
		return E_FAIL;

	hr = graphic->CreateDeviceResources();	//��ġ ������ �ڿ� ����
	if (FAILED(hr))
		return E_FAIL;

	Audio::GetInstance()->Initialize();

	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	currentScene = firstScene;
	currentScene->Initialize();

	return S_OK;
}
void Application::RunMessageLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		UpdateTime();
		graphic->Render();
		FWAPP->currentScene->Update();
		if (changeSceneCalled)
		{
			LateChangeScene();
		}
		FWAPP->currentScene->LateUpdate();
		FWINPUT->UpdateKeyState();
	}
}

void Application::Uninitialize()
{
	DeleteScenes();
	graphic->DiscardDeviceIndependentResources();
	Audio::GetInstance()->Uninitialize();
}

void Application::DeleteScenes()
{
	SAFE_DELETE(currentScene);
	SAFE_DELETE(nextScene);
}

HWND Application::GetHWND()
{
	return hwnd;
}


HRESULT Application::CreateFrame(const wchar_t* title, int width, int height, bool isFullscreen)
{
	//������ Ŭ���� �ʱ�ȭ
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbSize = sizeof(WNDCLASSEX);			//cbSize�� �ʱ�ȭ
	wcex.style = CS_HREDRAW | CS_VREDRAW;		//ȭ�� ũ�� �ٲ� ������ �ٽ� �׸� �� (��,Ⱦ)
	wcex.lpfnWndProc = Procedure::WndProc;	//������ ���ν��� �Լ� ���
	wcex.cbClsExtra = 0;						//���� ���� ��� x
	wcex.cbWndExtra = 0;						//���� ���� ��� X
	wcex.hInstance = GetModuleHandle(NULL);		//hInstance
	wcex.hbrBackground = NULL;					//��� �� ����
	wcex.lpszMenuName = NULL;					//�޴� ���� x
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);	//���콺 Ŀ�� ����
	wcex.lpszClassName = title;		//������Ŭ�����̸�

	//������ Ŭ������ �ü���� ���
	if (!RegisterClassEx(&wcex))
	{
		printf("failed");
		return 0;
	}

	//������ ���� �ϱ� ���� ����
	int wx, wy;
	RECT windowRect = { 0, };
	DWORD style, exstyle;
	if (isFullscreen)
	{
		wx = wy = 0L;
		windowRect.right = GetSystemMetrics(SM_CXSCREEN);
		windowRect.bottom = GetSystemMetrics(SM_CYSCREEN);
		style = WS_SYSMENU | WS_POPUP;
		exstyle = WS_EX_TOPMOST;
	}
	else
	{
		wx = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
		wy = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

		windowRect.right = width;
		windowRect.bottom = height;
		style = WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_CAPTION;		//CW_USEDEFAULT
		exstyle = NULL;
	}

	//������ ����
	AdjustWindowRectEx(&windowRect, style, FALSE, exstyle);

	//������ ����
	hwnd = CreateWindowEx(exstyle,title, title, style,
		wx, wy, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
		NULL, NULL, wcex.hInstance, NULL);

	//GetWindowRect �Ἥ ������ ũ�� ������ �� ����
	if (hwnd == NULL)
	{
		printf("CreateWindowEx Failed\n");
		return E_FAIL;
	}
	else
	{
		return S_OK;
	}
}

Scene * Application::GetCurrentScene()
{
	return currentScene;
}

float Application::DeltaTime()
{
	return deltaTime * timeScale;
}

void Application::ChangeScene(Scene* nextScene)
{
	changeSceneCalled = true;
	this->nextScene = nextScene;
}

void Application::Exit()
{
	PostQuitMessage(0);
}

void Application::LateChangeScene()
{
	changeSceneCalled = false;

	//���� �� ����
	SAFE_DELETE(currentScene);

	//���� �� ����
	currentScene = nextScene;
	graphic->CreateDeviceResources();
	currentScene->Initialize();
	nextScene = nullptr;
}

void Application::UpdateTime()
{
	static DWORD oldTime = timeGetTime();   //������ �ð�(temp����)

	DWORD curTime = timeGetTime();      //���� �ð�
	deltaTime = (curTime - oldTime)*0.001f;

	oldTime = curTime;
}
