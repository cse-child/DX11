#include "Framework.h"

Bullet::Bullet()
	:Quad(L"Textures/Shooting/playerBullet2.png")
{
	isActive = false;

	collider = new CircleCollider(Size().x * 0.5f);
	collider->SetParent(this);
}

Bullet::~Bullet()
{
	delete collider;
}

void Bullet::Update()
{
	if (!isActive) return;

	localPosition += direction * speed * DELTA;

	if (localPosition.x < -size.x || localPosition.x > WIN_WIDTH + size.x)
		isActive = false;
	if (localPosition.y < -size.y || localPosition.y > WIN_HEIGHT + size.y)
		isActive = false;

	UpdateWorld();
	collider->UpdateWorld();
}

void Bullet::Render()
{
	if (!isActive) return;

	Quad::Render();
	collider->Render();
}

void Bullet::Fire(Vector2 pos, Vector2 direction)
{
	isActive = true;
	localPosition = pos;
	this->direction = direction;

	localRotation.z = direction.Angle() - XM_PIDIV2;
}
