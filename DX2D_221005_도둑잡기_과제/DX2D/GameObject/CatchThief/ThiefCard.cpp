#include "Framework.h"

ThiefCard::ThiefCard(wstring textureFile)
	:Button(textureFile, true), key(textureFile)
{
	SetCardNum();
	SetEvent(bind(&ThiefCard::OnClick, this));
}

ThiefCard::~ThiefCard()
{
}

void ThiefCard::Update()
{
	switch (state)
	{
	case Button::NONE:
		if(!isSelected)
			localPosition.y = nonePos;
		break;
	case Button::DOWN:
		break;
	case Button::OVER:
		localPosition.y = overPos;
		break;
	}

	Button::Update();
}

void ThiefCard::OnClick()
{
	ThiefCardManager::Get()->SelectCard(this);
}

void ThiefCard::SetCardNum()
{
	string num = ToString(key);
	if (num == "Textures/Cards/Trump_Joker.png")
	{
		cardNum = 99;
		return;
	}
	num = num.substr(num.find_first_of('(')+1, 2);
	
	if (num[1] == ')')
		cardNum = num[0] - '0';
	else
		cardNum = stoi(num);
}
