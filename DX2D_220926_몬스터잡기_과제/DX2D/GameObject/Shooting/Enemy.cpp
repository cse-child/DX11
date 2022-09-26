#include "Framework.h"

Enemy::Enemy(Quad* target)
	:Quad(L"Textures/Shooting/rectEnemy.png"), target(target)
{
	isActive = false;
	
	//localPosition = { CENTER_X * 0.5f, CENTER_Y * 0.5f };

	collider = new CircleCollider(size.x * 0.5f);
	collider->SetParent(this);
}

Enemy::~Enemy()
{
	delete collider;
}

void Enemy::Update()
{
	if (!isActive) return;

	localPosition += direction * moveSpeed * DELTA;

	if (localPosition.x < -size.x || localPosition.x > WIN_WIDTH + size.x)
		isActive = false;
	if (localPosition.y < -size.y || localPosition.y > WIN_HEIGHT + size.y)
		isActive = false;

	UpdateWorld();
	collider->UpdateWorld();
}

void Enemy::Render()
{
	if (!isActive) return;

	Quad::Render();
	collider->Render();
}

void Enemy::Spawn()
{
	isActive = true;
	
	localPosition = { (float)(rand() % WIN_WIDTH), (float)(rand() % WIN_HEIGHT) };
	Rotation().z = atan2f(target->Position().y - localPosition.y, target->Position().x - localPosition.x);
	direction = (target->Position() - localPosition).Normalize();
	//UpdateWorld();
}

bool Enemy::CircleCollision(Collider* target)
{
	if (!isActive) return false;
	if (target == nullptr) return false;

	if (collider->IsCircleCollision((CircleCollider*)target))
	{
		return true;
	}
	return false;
}
