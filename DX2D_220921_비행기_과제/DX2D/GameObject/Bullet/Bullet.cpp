#include "Framework.h"

Bullet::Bullet()
	:Rect({ 0,0 }, { 30,30 })
{
	isActive = false;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Position() += direction * speed * DELTA;

	if (Position().x < 0 || Position().x > WIN_WIDTH)
		isActive = false;
	if (Position().y < 0 || Position().y > WIN_HEIGHT)
		isActive = false;

	UpdateWorld();
}

void Bullet::Fire(Vector2 pos, Vector2 direction)
{
	isActive = true;
	Position() = pos;
	this->direction = direction;
}
