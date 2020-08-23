#pragma once
#include "GameObject.h"
#include "Button.h"
#include "SoundEvent.h"
#include "Sound.h"
#include "StartUI.h"
//버튼을 지움, 배경을 지움, 필요하면 생성 아니면 다시 지움
class PauseUI :
	public GameObject
{
public:
	PauseUI();
	~PauseUI();

	SoundEvent * se;
	GameObject * bg;
	StartUI * startUI;
	Button * bt;
	
	void Show();
	void Off();
	void OnUpdate();

private :
	float time;
	bool isNeed;
	bool done;
	bool startAnim;
};

