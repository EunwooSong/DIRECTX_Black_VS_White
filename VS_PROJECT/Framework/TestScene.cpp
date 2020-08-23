#include "pch.h"
#include "TestScene.h"
#include "TestObject.h"

TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
	TestObject* t = new TestObject();
	PushBackGameObject(t);
	t->SetPosition(300.0f, 400.0f);
}
