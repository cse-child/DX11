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

	Vector2 screenPos = CAM->WorldToScreen(localPosition);

	if (screenPos.x < -size.x || screenPos.x > WIN_WIDTH + size.x)
		isActive = false;
	if (screenPos.y < -size.y || screenPos.y > WIN_HEIGHT + size.y)
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
