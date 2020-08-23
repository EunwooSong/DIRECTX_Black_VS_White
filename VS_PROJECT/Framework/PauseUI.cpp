#include "pch.h"
#include "PauseUI.h"


PauseUI::PauseUI() : isNeed(false), time(0.0f) , startAnim(true), done(false)
{
	se = new SoundEvent();
	startUI = new StartUI();

	FWSOUND->loadFile(L"Resources/AudioClips/GameScene.mp3", se);
	FWSOUND->PlaySoundEvent(se);

	startUI->SetPosition(1280/2, 720/2);

	FWAPP->timeScale = 1.0f;
	
}


PauseUI::~PauseUI()
{
	FWSOUND->StopSoundEvent(se);
}

void PauseUI::Show()
{
	bg = new GameObject(L"Resources/PauseUI.png");
	bt = new Button(L"Resources/Btn_GoToMaIn.png ", false);

	bg->SetPosition(1280 / 2, 720 / 2);
	bt->SetPosition(1280 / 2, 720 / 2 + 30);

	bt->goMain = true;

	scene->PushBackUI(bg);
	scene->PushBackUI(bt);
}

void PauseUI::Off()
{
	//버튼과 배경 삭제
	scene->Destroy(bg);
	scene->Destroy(bt);
}

void PauseUI::OnUpdate() {
	time += FWAPP->DeltaTime();

	if (!done) {
		scene->PushBackUI(startUI);
		startUI->SwapAnimation(startUI->startAnim);
		done = true;
	}

	if (time > 2.0f + 1.0f && startAnim) {
		puts("test");
		scene->Destroy(startUI);
		startAnim = false;
	}

	if (FWINPUT->GetKeyDown(VK_ESCAPE)) {
		isNeed = !isNeed;

		if (isNeed) {
			Show();
			FWAPP->timeScale = 0.0f;
			puts("Show");

		}

		else {
			Off();
			FWAPP->timeScale = 1.0f;
			puts("Off");
		}
	}
}
