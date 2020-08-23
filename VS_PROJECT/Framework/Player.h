#pragma once
#include "GameObject.h"
#include "SoundEvent.h"
#include "Sound.h"

class Player :
	public GameObject
{
public:
	Player(bool isBlack, float moveSpeed, float attackDelay, float dropKickDelay,float moveDir, float _moveDelay);
	~Player();

	Animation * moveAnimation;
	Animation * attackAnimation;
	Animation * dropKickAnimation;
	Animation * idleAnimation;
	Animation * dropKickAnimationFinal;

	SoundEvent * specialAttackSound;
	SoundEvent * defaultAttackSound;

	void SetAnimation(float _moveDelay, float _attackDelay);	//animation 설정
	void Move();
	void Attack();
	void Die();

	void DefaultAttack();
	void SpecialAttack();

	bool KnockBack();
	bool Hit(float damage);

	void OnUpdate();
	void OnLateUpdate();

public :
	Player *target;

	float hp;			//Hp 정보를 PlayerHpUI로 보내어 UI에서 처리 -> 나누기 100 / 기본은 100.0f
	float knockBackDir;
	float knockBackSpeed;
	float groundYPos;	//바닥 포지션으로 바닥 충돌 처리

	bool gameOver;
	bool isAttacking;	//공격중임에는 이동 제한을 위함

private:
	float time;			//시간, 쿨타임을 위함
	bool isBlack;		//검은색 플레이어인지 확인
	bool canGiveDamage;	//데미지를 한번만 주도록

	typedef enum AttackType
	{
		defaultAttack, specialAttack
	};

	AttackType attackType;
	float moveDir;		//이동 방향
	float moveSpeed;	//이동 속도
	float knockBackGab;	//감소는 고정

	//기본 공격
	bool isPunchAttack;
	float attackDelay;	//공격 속도
	
	//Drop Kick - 관련 함수
	bool isDropKick;
	float dropKickDelay;//Drop Kick Delay
	float jumpSpeed;
	float currentJumpSpeed;
	float jumpSpeedGab;

	
};
