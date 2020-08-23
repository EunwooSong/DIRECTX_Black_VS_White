#include "pch.h"
#include "PlayerHpUI.h"

PlayerHpUI::PlayerHpUI(const wchar_t * uri) : GameObject(uri)
{
}

PlayerHpUI::~PlayerHpUI()
{
}

void PlayerHpUI::OnUpdate()
{
	scale.x = targetHp->hp / 100.0f;

	if (targetHp->hp <= 0.0f) {
		targetHp->Die();
	}
}
