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

	void SetAnimation(float _moveDelay, float _attackDelay);	//animation ����
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

	float hp;			//Hp ������ PlayerHpUI�� ������ UI���� ó�� -> ������ 100 / �⺻�� 100.0f
	float knockBackDir;
	float knockBackSpeed;
	float groundYPos;	//�ٴ� ���������� �ٴ� �浹 ó��

	bool gameOver;
	bool isAttacking;	//�������ӿ��� �̵� ������ ����

private:
	float time;			//�ð�, ��Ÿ���� ����
	bool isBlack;		//������ �÷��̾����� Ȯ��
	bool canGiveDamage;	//�������� �ѹ��� �ֵ���

	typedef enum AttackType
	{
		defaultAttack, specialAttack
	};

	AttackType attackType;
	float moveDir;		//�̵� ����
	float moveSpeed;	//�̵� �ӵ�
	float knockBackGab;	//���Ҵ� ����

	//�⺻ ����
	bool isPunchAttack;
	float attackDelay;	//���� �ӵ�
	
	//Drop Kick - ���� �Լ�
	bool isDropKick;
	float dropKickDelay;//Drop Kick Delay
	float jumpSpeed;
	float currentJumpSpeed;
	float jumpSpeedGab;

	
};
