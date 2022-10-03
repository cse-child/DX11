#include "Framework.h"

Card::Card(wstring textureFile)
	:Button(textureFile)
{
	info.key = textureFile;
}

Card::~Card()
{
}

void Card::Update()
{
	if (!isActive) return;

	Button::Update();
}

void Card::Render()
{
	if (!isActive) return;

	Button::Render();
}
