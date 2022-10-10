#pragma once

class ThiefCardManager : public Singleton<ThiefCardManager>
{
private:
	const UINT SWAP_COUNT = 30;

public:
	ThiefCardManager();
	~ThiefCardManager();

	void Update();
	void Render();

	void SelectCard(ThiefCard* selectCard);

	void NextTurn();
	void SortPlayerCards();
	void SwapCards();

	bool IsDebugMode() { return isDebugMode; }

private:
	void LoadCardTextures();
	void CreateCards();

	void HandOutCards();
	void SetLandomCards(vector<ThiefCard*>& cards, float height, bool isHide = false);

	void CheckSameCardNum();
	void CheckEraseComputerCard();

	void ComputerDebugMode();

	void BringComputerCard(void* bringCard);
	
	void SortComputerCards();


private:
	vector<ThiefCard*> totalCards;
	vector<ThiefCard*> playerCards;
	vector<ThiefCard*> computerCards;

	vector<wstring> cardTextures;

	ThiefCard* firstSelectCard = nullptr;
	ThiefCard* secondSelectCard = nullptr;

	Vector2 cardSize;

	UINT totalCardCount = 0;

	bool isDebugMode = false;
	bool isBringCard = false;
};