#include "Framework.h"

ThiefCardManager::ThiefCardManager()
{
	LoadCardTextures();
	CreateCards();
	HandOutCards();
	CheckEraseComputerCard();
	SortComputerCards();
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

void ThiefCardManager::NextTurn()
{
	if (playerCards.size() == 0)
	{
		MessageBox(hWnd, L"Player가 승리하였습니다!", L"WIN", MB_OK);
		PostQuitMessage(0);
		return;
	}
	else if (computerCards.size() == 0)
	{
		MessageBox(hWnd, L"Player가 패배하였습니다..", L"LOSE", MB_OK);
		PostQuitMessage(0);
		return;
	}

	if (!isBringCard)
	{
		MessageBox(hWnd, L"상대의 카드 한 장을 뽑아야 턴을 넘길 수 있습니다.", L"PICK THE CARD", MB_OK);
		return;
	}
	else
	{
		// Computer -> Player 랜덤 카드 뽑기
		UINT randomIdx = Random(0, playerCards.size());
		ThiefCard* randomPlayerCard = playerCards[randomIdx];

		// player card -> computer card 변경
		randomPlayerCard->cardType = ThiefCard::COMPUTER;
		if(!isDebugMode)
			randomPlayerCard->SetTexture(Texture::Add(L"Textures/Trump_Back.png"));
		randomPlayerCard->SetObject(randomPlayerCard);
		randomPlayerCard->SetObjEvent(bind(&ThiefCardManager::BringComputerCard, this, placeholders::_1));

		computerCards.push_back(randomPlayerCard);

		playerCards.erase(playerCards.begin() + randomIdx);

		CheckEraseComputerCard();
		SortComputerCards();

		isBringCard = false;
	}
}

void ThiefCardManager::SortPlayerCards()
{
	float overlapRate = 0.5f;
	float totalHalfSize = cardSize.x * playerCards.size() * 0.5f * overlapRate;
	Vector2 startOffset = { CENTER_X - totalHalfSize, cardSize.y };

	for (UINT i = 0; i < playerCards.size(); i++)
	{
		Vector2 pos = { startOffset.x + i * cardSize.x * overlapRate , startOffset.y };
		playerCards[i]->Position() = pos;
		playerCards[i]->nonePos = pos.y;
		playerCards[i]->overPos = pos.y + cardSize.y * 0.5f;
	}
}

void ThiefCardManager::SwapCards()
{
	for (UINT i = 0; i < SWAP_COUNT; i++)
	{
		UINT randomI = Random(0, playerCards.size());
		UINT randomJ = Random(0, playerCards.size());

		ThiefCard* temp = playerCards[randomI];
		playerCards[randomI] = playerCards[randomJ];
		playerCards[randomJ] = temp;
	}
	SortPlayerCards();

	for (UINT i = 0; i < SWAP_COUNT; i++)
	{
		UINT randomI = Random(0, computerCards.size());
		UINT randomJ = Random(0, computerCards.size());

		ThiefCard* temp = computerCards[randomI];
		computerCards[randomI] = computerCards[randomJ];
		computerCards[randomJ] = temp;
	}
	SortComputerCards();
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

		if (isHide) // Computer Card
		{
			cards[i]->SetTexture(Texture::Add(L"Textures/Trump_Back.png"));
			cards[i]->overPos = pos.y -cardSize.y * 0.5f;
			cards[i]->cardType = ThiefCard::COMPUTER;
			cards[i]->SetObject(cards[i]);
			cards[i]->SetObjEvent(bind(&ThiefCardManager::BringComputerCard, this, placeholders::_1));
		}
	}
}

void ThiefCardManager::CheckSameCardNum()
{
	if (firstSelectCard->cardNum != secondSelectCard->cardNum) return;
	
	// 같은 숫자 카드면 삭제
	playerCards.erase(remove(playerCards.begin(), playerCards.end(), firstSelectCard), playerCards.end());
	playerCards.erase(remove(playerCards.begin(), playerCards.end(), secondSelectCard), playerCards.end());
}

/* 컴퓨터 카드에서 같은 숫자들 자동으로 지우기 */
void ThiefCardManager::CheckEraseComputerCard()
{
	bool isErase = false;

	for (ThiefCard* i : computerCards)
	{
		for (ThiefCard* j : computerCards)
		{
			if ((i->key != j->key) && (i->cardNum == j->cardNum) && (i->Active() && j->Active()))
			{
				i->SetActive(false);
				j->SetActive(false);
				break;
			}
		}
	}
	 
	for (int i = computerCards.size() - 1; i >= 0; i--)
	{
		if (!computerCards[i]->Active())
			computerCards.erase(remove(computerCards.begin(), computerCards.end(), computerCards[i]), computerCards.end());
	}	
}

void ThiefCardManager::ComputerDebugMode()
{
	if (KEY_DOWN(VK_F1))
	{
		if (!isDebugMode)
		{
			for (ThiefCard* card : computerCards)
				card->SetTexture(Texture::Add(card->key));
			
			isDebugMode = true;
		}
		else
		{
			for (ThiefCard* card : computerCards)
				card->SetTexture(Texture::Add(L"Textures/Trump_Back.png"));
			
			isDebugMode = false;
		}
	}
}

void ThiefCardManager::BringComputerCard(void* bringCard)
{
	ThiefCard* card = (ThiefCard*)bringCard;

	if (!isBringCard)
	{
		card->cardType = ThiefCard::PLAYER;
		card->SetTexture(Texture::Add(card->key));
		card->SetObjEvent(nullptr);
		playerCards.push_back(card);
		computerCards.erase(remove(computerCards.begin(), computerCards.end(), card), computerCards.end()); // vector 특정 원소 지우기
		isBringCard = true;

		SortPlayerCards();
	}
	else
	{
		MessageBox(hWnd, L"한 턴에 한 장의 카드만 가져올 수 있습니다.", L"WARNING", MB_OK);
	}
}

void ThiefCardManager::SortComputerCards()
{
	float overlapRate = 0.5f;
	float totalHalfSize = cardSize.x * computerCards.size() * 0.5f * overlapRate;
	Vector2 startOffset = { CENTER_X - totalHalfSize, WIN_HEIGHT - cardSize.y };

	for (UINT i = 0; i < computerCards.size(); i++)
	{
		Vector2 pos = { startOffset.x + i * cardSize.x * overlapRate , startOffset.y };
		computerCards[i]->Position() = pos;
		computerCards[i]->nonePos = pos.y;
		computerCards[i]->overPos = pos.y - cardSize.y * 0.5f;
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
