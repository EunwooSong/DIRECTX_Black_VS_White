#pragma once
#include "GameObject.h"
#include "Button.h"
#include "SoundEvent.h"
#include "Sound.h"
#include "StartUI.h"
//��ư�� ����, ����� ����, �ʿ��ϸ� ���� �ƴϸ� �ٽ� ����
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

