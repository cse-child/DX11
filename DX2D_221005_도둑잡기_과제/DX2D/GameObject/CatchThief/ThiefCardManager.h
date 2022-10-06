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


// �����Ұ�
// 1. ���� ��ư
// 2. �� ������ ��ư 
// 3. ���� ī�� �̾ƿ���
// 4. ��ǻ�� AI ��� ����