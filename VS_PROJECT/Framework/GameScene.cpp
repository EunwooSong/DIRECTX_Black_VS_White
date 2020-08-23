#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "PlayerHpUI.h"
#include "PauseUI.h"
GameScene::GameScene() : isUse(false), isPlayed(false)
{
}


GameScene::~GameScene()
{
}

void GameScene::Initialize() {
	GameObject * bg = new GameObject(L"Resources/BattleStage.png");
	GameObject * vs = new GameObject(L"Resources/VS.png");
	PauseUI * pui = new PauseUI();

	bg->SetPosition(1280 / 2, 720 / 2);
	vs->SetPosition(1280 / 2, 50);

	PushBackGameObject(bg);
	PushBackGameObject(pui);
	//bool isBlack, float moveSpeed, float attackDelay, float dropKickDelay,float moveDir, float _moveDelay, float _attackDelay
	Player * playerBlack = new Player(true, 125.0f, 1.0f, 3.0f, 0.0f, 0.1f);
	PlayerHpUI * playerBlackHpUI = new PlayerHpUI(L"Resources/Black/Hp_UI.png");
	playerBlack->SetPosition(1280 / 2 + 200, 720 / 2 + 100);

	//UI Set
	playerBlackHpUI->targetHp = playerBlack;
	playerBlackHpUI->SetPosition(1280 / 2 + 50, 50);

	Player * playerWhite = new Player(false, 125.0f, 1.0f, 3.0f, 0.0f, 0.1f);
	PlayerHpUI * playerWhiteHpUI = new PlayerHpUI(L"Resources/White/Hp_UI.png");
	playerWhite->SetPosition(1280 / 2 - 200, 720 / 2 + 100);

	//UI Set
	playerWhiteHpUI->targetHp = playerWhite;
	playerWhiteHpUI->SetPosition(1280 / 2 - 50, 50);

	//서로 충돌 타겟 설정
	playerBlack->target = playerWhite;
	playerWhite->target = playerBlack;

	//최하 Y pos? 설정
	playerBlack->groundYPos = 720 / 2 + 95;
	playerWhite->groundYPos = 720 / 2 + 95;

	PushBackGameObject(playerWhite);
	PushBackGameObject(playerBlack);

	//ui 추가
	PushBackUI(vs);
	PushBackUI(playerBlackHpUI);
	PushBackUI(playerWhiteHpUI);

	isPlayed = true;
}