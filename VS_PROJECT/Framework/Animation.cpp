#include "pch.h"
#include "Animation.h"


Animation::Animation(GameObject * target, float delay) : target(target), timer(0.0f), delay(delay)
{
}

Animation::~Animation()
{
}

void Animation::PushBackSprite(const wchar_t* uri)
{
	Sprite* s = nullptr;
	if (FAILED(Graphic::LoadBitmapFromFile(FWAPP->GetCurrentScene(), uri, 0, 0, s)))
	{
		printf("�ִϸ��̼� �̹��� �ε� ����: %sȮ�ιٶ�\n", uri);
	}
	else 
	{
		if (sprites.empty())
		{
			sprites.push_back(s);
			currentSprite = sprites.begin();
		}
		else
			sprites.push_back(s);
	}
}

void Animation::UpdateAnimation()
{
	if (sprites.empty())
	{
		printf("�ִϸ��̼��� �����ϴ�.\n");
		return;
	}

	timer += FWAPP->DeltaTime();

	if (timer >= delay)
	{
		timer = 0.0f;
		++currentSprite;

		if (currentSprite == sprites.end())
		{
			currentSprite = sprites.begin();
		}
		
		target->sprite = *currentSprite;
	}
}
