#pragma once

class ThiefCard : public Button
{
private:
	friend class ThiefCardManager;

	enum CardType
	{
		PLAYER, COMPUTER
	};

public:
	ThiefCard(wstring textureFile);
	~ThiefCard();

	void Update();

private:
	void OnClick();
	void SetCardNum();

private:
	wstring key;

	UINT cardNum;

	CardType cardType;

	float nonePos;
	float overPos;

	bool isDebugMode = false;
	bool isSelected = false;

};