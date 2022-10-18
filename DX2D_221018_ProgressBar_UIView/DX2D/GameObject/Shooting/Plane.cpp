#include "Framework.h"

Plane::Plane()
	:Quad(L"Textures/Shooting/player.png")
{
	localPosition = { CENTER_X, CENTER_Y };

	hpBar = new ProgressBar(L"Textures/UI/hp_bar.png", 
		L"Textures/UI/hp_bar_BG.png", 100);

	hpBar->Position() = { 100, WIN_HEIGHT - 100 };
	hpBar->UpdateWorld();
}

Plane::~Plane()
{
	delete hpBar;
}

void Plane::Update()
{
	//Vector2 screenPos = { 100, WIN_HEIGHT - 100 };
	//hpBar->Position() = CAM->ScreenToWorld(screenPos);

	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 firePos = localPosition + Up() * size.y * 0.5f;
		
		Vector2 cursorPos = CAM->ScreenToWorld(mousePos);
		Vector2 direction = (cursorPos - firePos).Normalize();
		
		BulletManager::Get()->Fire(firePos, direction);
		//BulletManager::Get()->Fire(firePos, Up());
	}

	if (KEY_DOWN(VK_RBUTTON))
	{
		curHp -= 10.0f;

		hpBar->SetAmount(curHp);
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
	hpBar->Render();

	ImGui::Text("Plane Info");
	ImGui::SliderFloat("MoveSpeed", &moveSpeed, 0, 500);
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
	
	//localRotation.z = atan2f(localPosition.y - mousePos.y, localPosition.x - mousePos.x) + XMConvertToRadians(90);
}
