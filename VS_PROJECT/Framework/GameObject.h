#pragma once
#include "Scene.h"
#include "BoxCollider.h"
#include "Animation.h"

class Scene;
class BoxCollider;
class Animation;

struct Sprite;

typedef D2D_POINT_2F Point;
typedef D2D_RECT_F Rect;
typedef D2D_COLOR_F Color;
struct Rotation{
	float angle;	//Degree�� ����մϴ�. Radian�� �ƴմϴ�.
	Point pivot;	//ȸ�� �߽�
};

class GameObject
{
public:
	GameObject();
	GameObject(const wchar_t* uri);
	virtual ~GameObject();

	virtual void OnUpdate();
	virtual void OnLateUpdate();
	virtual void OnDestroy();

	void SetPosition(float x, float y);
	void SetRotation(float angle, float pivotX, float pivotY);	//degree
	void SetScale(float x, float y);
	void SetColliderByScale();	//������ ��ȭ�� �ݶ��̴� ����

public:
	Point pos;
	Rotation rot;
	Point scale;
	Point size;   //�̹��� ������
	string name;
	BoxCollider* col;
	Sprite* sprite;
	float alpha;
	bool _isDestroyed;
	bool isActive;
	Scene* scene;

public:
	Animation* currentAnimation;
	void SwapAnimation(Animation* nextAnim);
	void UpdateAnimation();

};

