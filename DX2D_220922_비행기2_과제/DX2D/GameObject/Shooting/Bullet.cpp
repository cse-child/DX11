#include "Framework.h"
#include "Bullet.h"

Bullet::Bullet()
	:Texture(L"Textures/Shooting/bullet.png"), Quad({30, 30})
{
	isActive = false;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Position() += direction * speed * DELTA;

	if (Left() <= 0 || Right() >= WIN_WIDTH)
		isActive = false;
	if (Bottom() <= 0 || Top() >= WIN_HEIGHT)
		isActive = false;

	UpdateWorld();
}

void Bullet::Render()
{
	Texture::Render();
	Quad::Render();
}

void Bullet::Fire(Vector2 pos, Vector2 direction)
{
	isActive = true;
	Position() = pos;
	this->direction = direction;
	Rotation().z = atan2(mousePos.y - Position().y, mousePos.x - Position().x) - XMConvertToRadians(90);
}
