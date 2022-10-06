#include "Framework.h"

ThiefCardManager::ThiefCardManager()
{
	LoadCardTextures();
	CreateCards();
	HandOutCards();
}

ThiefCardManager::~ThiefCardManager()
{
	for (ThiefCard* card : totalCards)
		delete card;
	totalCards.clear();
	for (ThiefCard* card : playerCards)
		delete card;
	totalCards.clear();
	for (ThiefCard* card : computerCards)
		delete card;
	totalCards.clear();
}

void ThiefCardManager::Update()
{
	ComputerDebugMode();

	for (ThiefCard* card : playerCards)
		card->Update();

	for (ThiefCard* card : computerCards)
		card->Update();
}

void ThiefCardManager::Render()
{
	for (ThiefCard* card : playerCards)
		card->Render();

	for (ThiefCard* card : computerCards)
		card->Render();
}

void ThiefCardManager::SelectCard(ThiefCard* selectCard)
{
	if (selectCard->cardType == ThiefCard::COMPUTER) return;

	if (firstSelectCard == nullptr)
	{
		firstSelectCard = selectCard;
		firstSelectCard->isSelected = true;
		return;
	}
	
	if (firstSelectCard == selectCard) return;

	secondSelectCard = selectCard;
	secondSelectCard->isSelected = true;

	CheckSameCardNum();

	firstSelectCard->isSelected = false;
	secondSelectCard->isSelected = false;
	firstSelectCard = nullptr;
	secondSelectCard = nullptr;
}

void ThiefCardManager::CreateCards()
{
	totalCards.resize(totalCardCount);

	for (UINT i = 0; i < totalCardCount; i++)
	{
		totalCards[i] = new ThiefCard(cardTextures[i]);
	}
}

/* 플레이어와 컴퓨터에게 카드를 랜덤으로 나눠주기 */
void ThiefCardManager::HandOutCards()
{
	playerCards.resize(Random(totalCardCount / 2, totalCardCount / 2 + 2));
	computerCards.resize(totalCardCount - playerCards.size());

	SetLandomCards(playerCards, cardSize.y);
	SetLandomCards(computerCards, WIN_HEIGHT - cardSize.y, true);
}

void ThiefCardManager::SetLandomCards(vector<ThiefCard*>& cards, float height, bool isHide)
{
	float overlapRate = 0.5f;
	float totalHalfSize = cardSize.x * playerCards.size() * 0.5f * overlapRate;
	Vector2 startOffset = { CENTER_X - totalHalfSize, height };

	for (UINT i = 0; i < cards.size(); i++)
	{
		UINT randomIdx = Random(0, totalCards.size());
		cards[i] = totalCards[randomIdx];
		totalCards.erase(totalCards.begin() + randomIdx);

		Vector2 pos = { startOffset.x + i * cardSize.x * overlapRate , startOffset.y };
		cards[i]->Position() = pos;
		cards[i]->nonePos = pos.y;
		cards[i]->overPos = pos.y + cardSize.y * 0.5f;
		cards[i]->cardType = ThiefCard::PLAYER;

		if (isHide)
		{
			cards[i]->SetTexture(Texture::Add(L"Textures/Trump_Back.png"));
			cards[i]->overPos = pos.y -cardSize.y * 0.5f;
			cards[i]->cardType = ThiefCard::COMPUTER;
		}
	}
}

void ThiefCardManager::CheckSameCardNum()
{
	if (firstSelectCard->cardNum != secondSelectCard->cardNum) return;
	
	firstSelectCard->SetActive(false);
	secondSelectCard->SetActive(false);
}

void ThiefCardManager::ComputerDebugMode()
{
	if (KEY_DOWN(VK_F1))
	{
		for (ThiefCard* card : computerCards)
		{
			if (!card->isDebugMode)
			{
				card->SetTexture(Texture::Add(card->key));
				card->isDebugMode = true;
			}
			else
			{
				card->SetTexture(Texture::Add(L"Textures/Trump_Back.png"));
				card->isDebugMode = false;
			}
		}
	}
}

void ThiefCardManager::LoadCardTextures()
{
	WIN32_FIND_DATA findData;

	HANDLE handle;
	bool result = true;
	handle = FindFirstFile(L"Textures/Cards/*.png", &findData);

	wstring fileName;

	while (result)
	{
		fileName = L"Textures/Cards/";
		fileName += findData.cFileName;

		cardTextures.push_back(fileName);

		result = FindNextFile(handle, &findData);
	}

	totalCardCount = cardTextures.size();
	cardSize = Texture::Add(cardTextures[0])->GetSize();
}
