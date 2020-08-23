#pragma once
#include "GameObject.h"
#include "Animation.h"

class StartUI :
	public GameObject
{
public:
	Animation * startAnim;

	StartUI();
	~StartUI();

	void OnUpdate();
};

