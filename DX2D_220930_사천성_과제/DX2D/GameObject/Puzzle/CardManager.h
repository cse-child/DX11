#pragma once

class CardManager : public Singleton<CardManager>
{
private:
	const UINT PAIR_NUM = 4;
	const float CARD_SCALE = 0.5f;
	const UINT SHUFFLE = 50;
	const UINT SELECT_COUNT = 2;

public:
	CardManager();
	~CardManager();

	void Update();
	void Render();

private:
	void CreateCards(UINT puzzleLevel);
	void LoadCardTextures();

	void ShuffleCard();
	void SwapCard(POINT pos1, POINT pos2);

	void OnClickButtonEvent(void* card);

	void CheckCard();

	void RemoveCard(bool result);
	
private:
	//vector<Card*> cards;
	typedef vector<Card*> Cards;
	vector<Cards> cardBoard;
	vector<wstring> cardTextures; // 카드 경로 저장

	vector<Card*> selectCard;

	UINT width = 0;
	UINT height = 0;
};