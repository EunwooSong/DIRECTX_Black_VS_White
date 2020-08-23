#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Button.h"
class GameScene : 
	public Scene
{
public:
	GameScene();
	~GameScene();

	void Initialize();

public:
	bool isUse;
	bool isPlayed;
};

