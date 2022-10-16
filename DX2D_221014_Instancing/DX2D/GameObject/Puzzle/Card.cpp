#include "Framework.h"

Card::Card(wstring textureFile)
	:Button(textureFile), key(textureFile)
{
	SetEvent(bind(&Card::OnClick, this));
}

Card::~Card()
{
}

void Card::OnClick()
{
	CardManager::Get()->SelectCard(this);
}
