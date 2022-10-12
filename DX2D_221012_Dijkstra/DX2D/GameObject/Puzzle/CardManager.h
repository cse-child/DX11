#pragma once

class CardManager : public Singleton<CardManager>
{
private:
	struct EmptyDir
	{
		bool up;
		bool down;
		bool right;
		bool left;
	};

	const UINT PAIR_NUM = 4;
	const float CARD_SCALE = 0.5f;
	const UINT SHUFFLE = 50;

public:
	CardManager();
	~CardManager();

	void Update();
	void Render();

	void SelectCard(Card* selectCard);

private:
	void CreateCards(UINT puzzleLevel);
	void LoadCardTextures();

	void ShuffleCard();
	void SwapCard(int n1, int n2);
	
	void DeleteMatchCard();

	bool IsSameCard();
	bool IsSameLine(POINT pos1, POINT pos2);
	bool IsSameLineIncludeSelf(POINT pos1, POINT pos2);
	bool IsDigeud(POINT pos1, POINT pos2); 
	EmptyDir GetEmptyDir(POINT pos);

private:
	vector<Card*> cards;
	vector<vector<Card*>> cardBoard;
	vector<wstring> cardTextures; // 카드 경로 저장

	Card* firstSelectCard = nullptr;
	Card* secondSelectCard = nullptr;

	UINT width = 0;
	UINT height = 0;
};