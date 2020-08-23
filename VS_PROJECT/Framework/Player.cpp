#include "pch.h"
#include "Player.h"
#include "MainScene.h"
//White
//a - ����
//d - ������
//g - �⺻ ����
//h - ��� ű

//Black
//left - ����
//right - ������
//keypad2 - �⺻ ����
//keypad3 - ��� ű

Player::Player(bool isBlack, float moveSpeed, float attackDelay, float dropKickDelay, float moveDir, float _moveDelay) :
	moveSpeed(moveSpeed), attackDelay(attackDelay), moveDir(moveDir), isBlack(isBlack), isAttacking(false), hp(100.0f), 
	knockBackGab(150.0f), dropKickDelay(dropKickDelay), jumpSpeed(300.0f), jumpSpeedGab(350.0f), gameOver(false),
	isPunchAttack(false), isDropKick(false)
{
	SetAnimation(_moveDelay, attackDelay); 
	specialAttackSound = new SoundEvent();
	defaultAttackSound = new SoundEvent();

	FWSOUND->loadFile(L"Resources/AudioClips/SpecialAttack.wav", specialAttackSound);
	FWSOUND->loadFile(L"Resources/AudioClips/DefaultAttack.wav", defaultAttackSound);
}


Player::~Player()
{
}

void Player::SetAnimation(float _moveDelay, float _attackDelay)
{
	//��
	if (isBlack) {
		moveAnimation = new Animation(this, _moveDelay);	//3 > 2 > 1 > 3 > . . . �ݺ�
		moveAnimation->PushBackSprite(L"Resources/Black/Walk_3.png");
		moveAnimation->PushBackSprite(L"Resources/Black/Walk_2.png");
		moveAnimation->PushBackSprite(L"Resources/Black/Walk_1.png");

		attackAnimation = new Animation(this, _attackDelay);	//attack (delay ��. . .) Idle -> �̵� ����
		attackAnimation->PushBackSprite(L"Resources/Black/Attack.png");
		attackAnimation->PushBackSprite(L"Resources/Black/Idle.png");

		idleAnimation = new Animation(this, 0.0f);
		idleAnimation->PushBackSprite(L"Resources/Black/Idle.png");

		dropKickAnimation = new Animation(this, dropKickDelay/3);
		dropKickAnimation->PushBackSprite(L"Resources/Black/Jump_1.png");
		dropKickAnimation->PushBackSprite(L"Resources/Black/Jump_2.png");
		dropKickAnimation->PushBackSprite(L"Resources/Black/Jump_3.png");

		dropKickAnimationFinal = new Animation(this, 0.0f);
		dropKickAnimationFinal->PushBackSprite(L"Resources/Black/Jump_4.png");

		SwapAnimation(idleAnimation);
		SetColliderByScale();
	}
	//��
	else {
		moveAnimation = new Animation(this, _moveDelay);	//3 > 2 > 1 > 3 > . . . �ݺ�
		moveAnimation->PushBackSprite(L"Resources/White/Walk_3.png");
		moveAnimation->PushBackSprite(L"Resources/White/Walk_2.png");
		moveAnimation->PushBackSprite(L"Resources/White/Walk_1.png");

		attackAnimation = new Animation(this, _attackDelay);	//attack (delay ��. . .) Idle -> �̵� ����
		attackAnimation->PushBackSprite(L"Resources/White/Attack.png");
		attackAnimation->PushBackSprite(L"Resources/White/Idle.png");

		idleAnimation = new Animation(this, 0.0f);
		idleAnimation->PushBackSprite(L"Resources/White/Idle.png");

		dropKickAnimation = new Animation(this, dropKickDelay / 3);
		dropKickAnimation->PushBackSprite(L"Resources/White/Jump_1.png");
		dropKickAnimation->PushBackSprite(L"Resources/White/Jump_2.png");
		dropKickAnimation->PushBackSprite(L"Resources/White/Jump_3.png");

		dropKickAnimationFinal = new Animation(this, 0.0f);
		dropKickAnimationFinal->PushBackSprite(L"Resources/White/Jump_4.png");

		SwapAnimation(idleAnimation);
		SetColliderByScale();
	}
	
}


void Player::OnUpdate()
{
	time += FWAPP->DeltaTime();

	UpdateAnimation();

	if(!KnockBack())
		if (!isAttacking)
			Move();

	if (currentJumpSpeed != 0.0f) {
		currentJumpSpeed += -jumpSpeedGab * FWAPP->DeltaTime();

		pos.y -= currentJumpSpeed * FWAPP->DeltaTime();
		pos.x += -scale.x * moveSpeed * FWAPP->DeltaTime() * 2.0f;
	}
	
	//������ �����ٴ� ��ȣ�� ������ 2�ʵ� ����ȭ������
	if (gameOver) {
		if (time > 2.0f) {
			FWAPP->ChangeScene(new MainScene());
		}
	}

	Attack();
}

void Player::OnLateUpdate()
{
	if (this->col->Intersected(target)) {
		if (isAttacking && canGiveDamage) {
			if (attackType == defaultAttack) {
				if (isBlack)
					puts("White Hit");
				else
					puts("Black Hit");

				//���̻� �������� ���� �ʵ��� ����
				canGiveDamage = false;

				//�˹� ���� �߰��Ͽ� �˹� ����, �˹�ÿ��� �̵� x
				target->knockBackDir = -this->scale.x;
				target->knockBackSpeed = 200.0f;

				if (target->Hit(10.0f)) {
					puts("Die!");
				}
			}

			else if (attackType == specialAttack) {
				if (isBlack)
					puts("White Special Hit");
				else
					puts("Black Special Hit");

				canGiveDamage = false;

				target->knockBackDir = -this->scale.x;
				target->knockBackSpeed = 300.0f;

				if (target->Hit(35.0f)) {
					puts("Die!");
				}
			}
		}
	}

	if (this->pos.y > groundYPos) {
		currentJumpSpeed = 0.0f;
		pos.y = groundYPos;
		isDropKick = false;
	}

	if (this->pos.x < 124.0f || this->pos.x > 1157.0f) {
		Die();
	}
}

bool Player::KnockBack()
{
	if(knockBackSpeed <= 0.0f)
		return false;

	//�˹� ����
	knockBackSpeed -= knockBackGab * FWAPP->DeltaTime();
	pos.x += knockBackDir * knockBackSpeed * FWAPP->DeltaTime();

	return true;
}

void Player::Move()
{
	if (isBlack) {
		if (FWINPUT->GetKeyPressed(VK_LEFT)) {
			moveDir = -1.0f;
			scale.x = -moveDir;
		}

		else if (FWINPUT->GetKeyPressed(VK_RIGHT)) {
			moveDir = 1.0f;
			scale.x = -moveDir;
		}

		else
			moveDir = 0.0f;

		if (moveDir != 0.0f)
			currentAnimation = moveAnimation;

		else
			currentAnimation = idleAnimation;

		pos.x += moveDir * moveSpeed * FWAPP->DeltaTime();	//�÷��̾� �̵�
	}

	else {
		if (FWINPUT->GetKeyPressed('A')) {
			moveDir = -1.0f;
			scale.x = -moveDir;
		}

		else if (FWINPUT->GetKeyPressed('D')) {
			moveDir = 1.0f;
			scale.x = -moveDir;
		}

		else
			moveDir = 0.0f;

		if (moveDir != 0.0f)
			currentAnimation = moveAnimation;

		else
			currentAnimation = idleAnimation;

		pos.x += moveDir * moveSpeed * FWAPP->DeltaTime();	//�÷��̾� �̵�
	}
}

void Player::Attack()
{
	if (isBlack) {
		if (FWINPUT->GetKeyDown(VK_NUMPAD2) && time > attackDelay && !isAttacking) {
			puts("Player(black) is Attacking!");
			DefaultAttack();
		}

		else if (isDropKick) {
			if (time > dropKickDelay / 3 * 2 + 1.0f) {
				SwapAnimation(dropKickAnimationFinal);
			}
			else if (time > dropKickDelay / 3 * 2 && !canGiveDamage) {
				currentJumpSpeed = jumpSpeed;
				canGiveDamage = true;
			}
		}

		else if (FWINPUT->GetKeyDown(VK_NUMPAD3) && time > dropKickDelay && !isAttacking) {
			puts("Player(black) is Special Attacking!");
			SpecialAttack();
		}

		else if (isPunchAttack) {
			if (time > attackDelay) { 
				isAttacking = false;
				canGiveDamage = false;
			}
		}
		else if (!isDropKick) {
			isAttacking = false;
			canGiveDamage = false;
		}
	}

	else {
		if (FWINPUT->GetKeyDown('G') && time > attackDelay && !isAttacking) {
			puts("Player(black) is Attacking!");
			DefaultAttack();
		}

		else if (isDropKick) {
			if (time > dropKickDelay / 3 * 2 + 1.0f) {
				SwapAnimation(dropKickAnimationFinal);
			}
			else if (time > dropKickDelay / 3 * 2 && !canGiveDamage) {
				currentJumpSpeed = jumpSpeed;
				canGiveDamage = true;
			}
		}

		else if (FWINPUT->GetKeyDown('H') && time > dropKickDelay && !isAttacking) {
			puts("Player(black) is Special Attacking!");
			SpecialAttack();
		}

		else if (isPunchAttack) {
			if (time > attackDelay) {
				isAttacking = false;
				canGiveDamage = false;
			}
		}
		else if (!isDropKick) {
			isAttacking = false;
			canGiveDamage = false;
		}
	}
}

void Player::Die()
{
	static bool end = false;

	if (!gameOver && end) 
		end = false;

	else if(end)
		return;

	if (isBlack && !end) {
		printf("WhiteWin \n");
		GameObject * ww = new GameObject(L"Resources/White_Win.png");
		ww->SetPosition(1280 / 2, 720 / 2);
		scene->PushBackUI(ww);
		time = 0.0f;
	}

	else if(!end) {
		printf("BlackWin \n");
		GameObject * bw = new GameObject(L"Resources/Black_Win.png");
		bw->SetPosition(1280 / 2, 720 / 2);
		scene->PushBackUI(bw);
		time = 0.0f;
	}

	gameOver = true;
	target->gameOver = true;
	end = true;
}

void Player::DefaultAttack() {
	attackType = defaultAttack;	//��ų�� ���� �������� �ٸ��� �ϱ� ����
	time = 0.0f;

	SwapAnimation(attackAnimation);
	
	isPunchAttack = true;
	isAttacking = true;
	canGiveDamage = true;
}

void Player::SpecialAttack()
{
	attackType = specialAttack;
	time = 0.0f;

	SwapAnimation(dropKickAnimation);
	isDropKick = true;
	isAttacking = true;
}

bool Player::Hit(float damage)
{
	hp -= damage;

	if (target->attackType == defaultAttack)
		FWSOUND->PlaySoundEvent(defaultAttackSound);

	else if(target->attackType == specialAttack)
		FWSOUND->PlaySoundEvent(specialAttackSound);

	if (hp <= 0.0f) {
		hp = 0.0f;
		return true;
	}

	return false;
}
