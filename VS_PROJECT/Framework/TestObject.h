#pragma once
#include "GameObject.h"
class TestObject :
	public GameObject
{
public:
	TestObject();
	~TestObject();

	Animation* walkAnimation;
	Animation* jumpAnimation;

	void OnUpdate();
};

