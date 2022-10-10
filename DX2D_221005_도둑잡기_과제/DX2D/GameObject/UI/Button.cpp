#include "Framework.h"

Button::Button(wstring textureFile, bool isCard)
	:Quad(textureFile)
{
	if(isCard)
		collider = new RectCollider({ size.x*0.5f, size.y*3 });
	else
		collider = new RectCollider(size);

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
			if (objEvent != nullptr)
			{
				objEvent(object);
			}

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

	if(ThiefCardManager::Get()->IsDebugMode())
		collider->Render();
}

void Button::ButtonColorUpdate()
{
	switch (state)
	{
	case Button::NONE:
		GetColorBuffer()->Set(noneColor);
		break;
	case Button::DOWN:
		GetColorBuffer()->Set(downColor);
		break;
	case Button::OVER:
		GetColorBuffer()->Set(overColor);
		break;
	}
}
