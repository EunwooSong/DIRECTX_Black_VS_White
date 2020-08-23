#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "MainScene.h"
#include "GameScene.h"
#include "SoundEvent.h"
#include "Sound.h"

class Button :
	public GameObject
{
public:
	Button(const wchar_t * uri, bool goGame);
	~Button();

	SoundEvent * se;

	bool goMain;
	bool goGame;

	void OnUpdate();
};



