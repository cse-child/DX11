#include "Framework.h"

Bullet::Bullet()
	//:Quad(L"Textures/Shooting/playerBullet2.png")
	:Quad(L"Textures/Weapon/bullet.png")
{
	isActive = false;
	localScale *= 0.5f;
}

Bullet::~Bullet()
{
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
}

void Bullet::Render()
{
	if (!isActive) return;

	Quad::Render();
}

void Bullet::Fire(Vector2 pos, Vector2 direction)
{
	isActive = true;
	localPosition = pos;
	this->direction = direction;

	localRotation.z = direction.Angle() ;
}
