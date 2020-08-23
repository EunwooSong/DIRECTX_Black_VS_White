#include "pch.h"
#include <iostream>
#include "Application.h"
#include "GameScene.h"
#include "TestScene.h"
#include "MainScene.h"
int main()
{
	FWAPP->Run(L"연습", 1280, 720, false, new MainScene());

	return 0;
}

//0716변경점:
//1. delete를 모두 SAFE_DELETE로 변경		(오류 방지)
//2. App->Init의 소멸자 호출을 함수로 변경	(프로그램 종료시 비트맵 릴리즈 안되는 오류 해결)
//3. GameObject SetXXX 추가					(편의성, SetPosition, SetRotation, SetScale)
//4. GameObject SetColliderByScale 추가		(편의성, SetScale 호출시 SetColliderByScale도 함께 호출됨)
//5. Scene PushBackXXX 조건 추가			(텅 빈 게임오브젝트 생성시 오류 해결)
//6. Graphic LoadBitmap	수정				(같은 이미지 여러번 로드시 문제 해결)