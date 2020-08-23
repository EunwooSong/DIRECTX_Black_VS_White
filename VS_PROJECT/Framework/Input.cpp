#include "pch.h"
#include "Input.h"


Input::Input()
{
}


Input::~Input()
{
}

Input* Input::GetInstance()
{
	static Input i;
	return &i;
}

int Input::GetMouseX()
{
	return mouseX;
}

int Input::GetMouseY()
{
	return mouseY;
}

bool Input::GetKeyDown(int vk)
{
	return (GetMyKeyState(vk) == 1) ? true : false;
}

bool Input::GetKeyPressed(int vk)
{
	return (GetMyKeyState(vk) == 2) ? true : false;
}

bool Input::GetKeyUp(int vk)
{
	return (GetMyKeyState(vk) == -1) ? true : false;
}


void Input::UpdateKeyState()
{
	for (int i = 0; i < 256; i++)
	{
		lkey[i] = rkey[i];
		rkey[i] = GetAsyncKeyState(i) & 0x8000;
	}
}

int Input::GetMyKeyState(int vk)
{
	if (lkey[vk] && rkey[vk]) return 2; //�Ʊ �������� ���ݵ� ���������� ��
	if (!lkey[vk] && rkey[vk]) return 1; //�Ʊ�� �ƴ����� ������ ����������
	if (lkey[vk] && !rkey[vk]) return -1; //������ ������
	return 0;
}