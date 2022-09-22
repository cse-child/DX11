#include "Framework.h"

Plane::Plane()
	:Texture(L"Textures/Shooting/plane.png"), Quad({100, 100})
{
	tag = "Plane";
	Position() = { CENTER_X, CENTER_Y };

	BulletManager::Get()->CreateBullets(50);
}

Plane::~Plane()
{
	BulletManager::Delete;
}

void Plane::Update()
{
	Move();
	Fire();

	UpdateWorld();
	BulletManager::Get()->Update();
}

void Plane::Render()
{
	Texture::Render();
	Quad::Render();
	BulletManager::Get()->Render();
}

void Plane::PostRender()
{
	RenderUI();
}

void Plane::Move()
{
	if (KEY_PRESS('W'))
	{
		Position().y += speed * DELTA;
		if (Top() >= WIN_HEIGHT)
			Position().y = WIN_HEIGHT - Half().y;
	}
	if (KEY_PRESS('S'))
	{
		Position().y -= speed * DELTA;
		if (Bottom() <= 0)
			Position().y = Half().y;
	}
	if (KEY_PRESS('A'))
	{
		Position().x -= speed * DELTA;
		if (Left() <= 0)
			Position().x = Half().x;
	}
	if (KEY_PRESS('D'))
	{
		Position().x += speed * DELTA;
		if (Right() >= WIN_WIDTH)
			Position().x = WIN_WIDTH - Half().x;
	}

	Rotation().z = atan2(mousePos.y - Position().y, mousePos.x - Position().x) - XMConvertToRadians(90);
}

void Plane::Fire()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 direction = Vector2(mousePos) - Position();

		BulletManager::Get()->Fire(Position(), direction.Normalized());
	}
}
