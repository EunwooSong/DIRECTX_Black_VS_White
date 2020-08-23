#include "pch.h"
#include "TestObject.h"


TestObject::TestObject()
{
	walkAnimation = new Animation(this, 0.3f);
	walkAnimation->PushBackSprite(L"1.png");
	walkAnimation->PushBackSprite(L"2.png");
	walkAnimation->PushBackSprite(L"3.png");
	currentAnimation = walkAnimation;

	jumpAnimation = new Animation(this, 0.5f);
	jumpAnimation->PushBackSprite(L"bullet.png");
	jumpAnimation->PushBackSprite(L"player.png");
}


TestObject::~TestObject()
{
	SAFE_DELETE(walkAnimation);
}

void TestObject::OnUpdate()
{
	UpdateAnimation();

	if (FWINPUT->GetKeyDown(VK_SPACE))
	{
		SwapAnimation(jumpAnimation);
	}
}