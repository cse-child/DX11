#pragma once

class ThiefCardManager : public Singleton<ThiefCardManager>
{
public:
	ThiefCardManager();
	~ThiefCardManager();

	void Update();
	void Render();

	void SelectCard(ThiefCard* selectCard);

private:
	void LoadCardTextures();
	void CreateCards();
	void HandOutCards();
	void SetLandomCards(vector<ThiefCard*>& cards, float height, bool isHide = false);
	void CheckSameCardNum();

	void ComputerDebugMode();

private:
	vector<ThiefCard*> totalCards;
	vector<ThiefCard*> playerCards;
	vector<ThiefCard*> computerCards;

	vector<wstring> cardTextures;

	ThiefCard* firstSelectCard = nullptr;
	ThiefCard* secondSelectCard = nullptr;

	Vector2 cardSize;

	UINT totalCardCount = 0;

};


// 구현할거
// 1. 정렬 버튼
// 2. 턴 끝내기 버튼 
// 3. 상대방 카드 뽑아오기
// 4. 컴퓨터 AI 기능 구현