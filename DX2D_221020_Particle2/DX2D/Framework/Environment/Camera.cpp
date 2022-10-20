#include "Framework.h"

Camera::Camera()
{
	viewBuffer = new MatrixBuffer();
	viewBuffer->SetVS(1);
}

Camera::~Camera()
{
	delete viewBuffer;
}

void Camera::Update()
{
	if (target)
		FollowMode();
	else
		FreeMode();

	SetView();
}

void Camera::GUIRender()
{
	ImGui::Text("Camera Option");
	ImGui::Text("Position(X : %d, Y : %d)", 
		(int)localPosition.x, (int)localPosition.y);
	ImGui::SliderFloat("Cam Speed", &speed, 0, 500);
}

void Camera::SetView()
{
	UpdateWorld();

	view = XMMatrixInverse(nullptr, world);

	viewBuffer->Set(view);
	viewBuffer->SetVS(1);
}

// 스크린 좌표 -> 월드 좌표
Vector2 Camera::ScreenToWorld(Vector2 pos)
{
	return pos * world;
}

// 월드 좌표 -> 스크린 좌표
Vector2 Camera::WorldToScreen(Vector2 pos)
{
	return pos * view; // world의 역행렬
}

void Camera::FreeMode()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS('W'))
			localPosition.y += speed * DELTA;
		if (KEY_PRESS('S'))
			localPosition.y -= speed * DELTA;
		if (KEY_PRESS('A'))
			localPosition.x -= speed * DELTA;
		if (KEY_PRESS('D'))
			localPosition.x += speed * DELTA;
	}
	FixPosition(localPosition);
}

void Camera::FollowMode()
{
	Vector2 targetPos = target->GlobalPosition() - targetOffset;
	
	FixPosition(targetPos);

	localPosition = Lerp(localPosition, targetPos, speed * DELTA);
}

void Camera::FixPosition(Vector2& position)
{
	if (position.x < leftBottom.x)
		position.x = leftBottom.x;

	if (position.x > rightTop.x - WIN_WIDTH)
		position.x = rightTop.x - WIN_WIDTH;

	if (position.y < leftBottom.y)
		position.y = leftBottom.y;
				 
	if (position.y > rightTop.y - WIN_HEIGHT)
		position.y = rightTop.y - WIN_HEIGHT;
}
