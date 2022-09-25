#include "Framework.h"

Player::Player()
	:Quad(L"Textures/Weapon/robot.png")
{
	localPosition = { CENTER_X, CENTER_Y };
}

Player::~Player()
{
}

void Player::Update()
{
	MoveControl();

	UpdateWorld();
}

void Player::Render()
{
	Quad::Render();
}

void Player::RenderUI()
{
	ImGui::Text("Plane Info");
	ImGui::SliderFloat("MoveSpeed", &moveSpeed, 0, 500);
}

void Player::MoveControl()
{
	if (KEY_PRESS(VK_LEFT))
		localPosition -= Right() * moveSpeed * DELTA;
	if (KEY_PRESS(VK_RIGHT))
		localPosition += Right() * moveSpeed * DELTA;
	if(KEY_PRESS(VK_UP))
		localPosition += Up() * moveSpeed * DELTA;
	if (KEY_PRESS(VK_DOWN))
		localPosition -= Up() * moveSpeed * DELTA;
}
