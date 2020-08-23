#pragma once
#include "GameObject.h"
#include "Player.h"
#include "GameScene.h"

class PlayerHpUI :
	public GameObject
{
public:
	PlayerHpUI(const wchar_t * uri);
	~PlayerHpUI();

	Player * targetHp;

	void OnUpdate();
};

