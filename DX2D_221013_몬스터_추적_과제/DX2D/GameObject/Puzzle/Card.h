#pragma once

class Card : public Button
{
private:
	friend class CardManager;

public:
	Card(wstring textureFile);
	~Card();

	void SetCoord(int x, int y) { pos = { x,y }; }

private:
	void OnClick();

private:
	wstring key;

	POINT pos;
};