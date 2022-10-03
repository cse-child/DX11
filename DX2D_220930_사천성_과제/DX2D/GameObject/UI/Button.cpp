#include "Framework.h"

Button::Button(wstring textureFile)
	:Quad(textureFile)
{
	collider = new RectCollider(size);
	collider->SetParent(this);

	SetPixelShader(Shader::AddPS(L"Shaders/PixelOutline.hlsl"));
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
				ExcuteObjEvent(this);

			isDownCheck = false;
		}
	}
	else
	{
		state = NONE;

		if (KEY_UP(VK_LBUTTON))
			isDownCheck = false;
	}

	switch (state)
	{
	case Button::NONE:
		if(!isSelected)
			GetColorBuffer()->Set(noneColor);
		else
			GetColorBuffer()->Set(selectColor);
		break;
	case Button::DOWN:
		//SetPixelShader(Shader::AddPS(L"Shaders/PixelUV.hlsl"));
		//GetColorBuffer()->Set(downColor);
		break;
	case Button::OVER:
		GetColorBuffer()->Set(overColor);
		break;
	}

	collider->UpdateWorld();
	UpdateWorld();
}

void Button::Redner()
{
	if (!isActive) return;

	Quad::Render();
	collider->Render();
}
