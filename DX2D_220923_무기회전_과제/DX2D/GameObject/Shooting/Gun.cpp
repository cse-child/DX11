#include "Framework.h"
#include "Gun.h"

Gun::Gun()
	:Quad(L"Textures/Weapon/gun.png")
{
	//localPosition = { CENTER_X, CENTER_Y };
	localPosition = { 30, -10 };
	localScale *= 0.3f;
}

Gun::~Gun()
{
}

void Gun::Update()
{
	if (KEY_PRESS('W'))
		localRotation.z -= rotSpeed * DELTA;
	if (KEY_PRESS('S'))
		localRotation.z += rotSpeed * DELTA;

	if (KEY_DOWN(VK_SPACE))
	{
		//Vector2 firePos = localPosition + Right() * 0.5f + Vector2{30, 10};
		//Vector2 firePos = localPosition + Right() * 30 + Up() * 10;
		Vector2 firePos = GlobalPosition() + Right() * 30 + Up() * 10;
		BulletManager::Get()->Fire(firePos, Right());
	}

	UpdateWorld();
}

void Gun::Render()
{
	Quad::Render();
}
