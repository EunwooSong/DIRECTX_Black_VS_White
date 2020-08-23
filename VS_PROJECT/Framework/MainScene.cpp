#include "pch.h"
#include "MainScene.h"

MainScene::MainScene()
{
}


MainScene::~MainScene()
{
}

void MainScene::Initialize()
{
	GameObject * bg = new GameObject(L"Resources/MainScene.png");
	Button * bt = new Button(L"Resources/Btn_StartGame.png", true);

	bg->SetPosition(1280/2, 720/2);
	bt->SetPosition(1280/2, 720/2);
	PushBackUI(bg);
	PushBackUI(bt);
}
