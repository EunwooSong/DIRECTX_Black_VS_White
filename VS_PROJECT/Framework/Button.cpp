#include "pch.h"
#include "Button.h"

//이를 캔버스에서 생성
Button::Button(const wchar_t * uri, bool goGame) : GameObject(uri), goGame(goGame)
{
	se = new SoundEvent();
	SetColliderByScale();

	if (goGame) {
		FWSOUND->loadFile(L"Resources/AudioClips/MainScene.mp3", se);
		FWSOUND->PlaySoundEvent(se);
	}
		
}

Button::~Button()
{
}

void Button::OnUpdate() {
	if (FWINPUT->GetKeyDown(VK_LBUTTON)) {
		if (col->Intersected(FWINPUT->GetMouseX(), FWINPUT->GetMouseY())) {
			if (goMain)
				FWAPP->ChangeScene(new MainScene());

			else if (goGame) {
				FWSOUND->StopSoundEvent(se);
				FWAPP->ChangeScene(new GameScene());
			}
				
		}
	}


}
