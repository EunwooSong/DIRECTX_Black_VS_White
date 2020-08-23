#include "pch.h"
#include "StartUI.h"


StartUI::StartUI()
{
	startAnim = new Animation(this, 2/4.0f);
	puts("test");
	startAnim->PushBackSprite(L"Resources/3.png");
	startAnim->PushBackSprite(L"Resources/3.png");
	startAnim->PushBackSprite(L"Resources/2.png");
	startAnim->PushBackSprite(L"Resources/1.png");
	startAnim->PushBackSprite(L"Resources/Go.png");
	startAnim->PushBackSprite(L"Resources/Go.png");
	puts("comp");
}


StartUI::~StartUI()
{
}

void StartUI::OnUpdate()
{
	UpdateAnimation();
}
