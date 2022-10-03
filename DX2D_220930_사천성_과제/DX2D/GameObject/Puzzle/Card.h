#pragma once

struct CardInfo
{
	wstring key;
	POINT pos;
};

class Card : public Button
{
public:
	Card(wstring textureFile);
	~Card();

	void Update();
	void Render();

	bool& Selected() { return isSelected; }
	
	CardInfo& Info() { return info; }

private:
	CardInfo info;
};