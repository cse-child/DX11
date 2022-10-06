#include "Framework.h"

Button::Button(wstring textureFile)
	:Quad(textureFile)
{
	collider = new RectCollider({ size.x*0.5f, size.y*3 });
	collider->SetParent(this);
}

Button::~Button()
{
	delete collider;
}

void Button::Update()
{
	if (!isActive) return;

	if (collider->IsPointCollision(mousePos))
	{
		if (KEY_DOWN(VK_LBUTTON))
			isDownCheck = true;

		if (KEY_PRESS(VK_LBUTTON))
			state = DOWN;
		else
			state = OVER;

		if (isDownCheck && KEY_UP(VK_LBUTTON))
		{
			if (event != nullptr)
				event();

			isDownCheck = false;
		}
	}
	else
	{
		state = NONE;

		if (KEY_UP(VK_LBUTTON))
			isDownCheck = false;
	}

	collider->UpdateWorld();
	UpdateWorld();
}

void Button::Render()
{
	if (!isActive) return;

	Quad::Render();
	//collider->Render();
}
