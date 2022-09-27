#include "Framework.h"

Plane::Plane()
	:Quad(L"Textures/Shooting/player.png")
{
	localPosition = { CENTER_X, CENTER_Y };
}

Plane::~Plane()
{
}

void Plane::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 firePos = localPosition + Up() * size.y * 0.5f;
		//Vector2 direction = (mousePos - firePos).Normalize();
		//
		//BulletManager::Get()->Fire(firePos, direction);
		BulletManager::Get()->Fire(firePos, Up());
	}

	MoveControl();

	UpdateWorld();
}

void Plane::Render()
{
	Quad::Render();
}

void Plane::RenderUI()
{
	ImGui::Text("Plane Info");
	ImGui::SliderFloat("MoveSpeed", &moveSpeed, 0, 100);
	ImGui::SliderFloat("RotSpeed", &rotSpeed, 0, 20);
}

void Plane::MoveControl()
{
	if (KEY_PRESS('A'))
		localRotation.z -= rotSpeed * DELTA;
	if (KEY_PRESS('D'))
		localRotation.z += rotSpeed * DELTA;

	if (KEY_PRESS('W'))
		localPosition += Up() * moveSpeed * DELTA;
	if (KEY_PRESS('S'))
		localPosition -= Up() * moveSpeed * DELTA;
}
