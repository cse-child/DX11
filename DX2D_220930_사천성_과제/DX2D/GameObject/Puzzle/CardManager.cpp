#include "Framework.h"

CardManager::CardManager()
{
	LoadCardTextures();
	CreateCards(3);

	ShuffleCard();
}

CardManager::~CardManager()
{
	for (Cards cards : cardBoard)
	{
		for (Card* card : cards)
			delete card;
		cards.clear();
	}
	cardBoard.clear();
	
}

void CardManager::Update()
{
	if (selectCard.size() == SELECT_COUNT)
		CheckCard();

	for (Cards cards : cardBoard)
	{
		for (Card* card : cards)
			card->Update();
	}
}

void CardManager::Render()
{
	for (Cards cards : cardBoard)
	{
		for (Card* card : cards)
			card->Render();
	}
}

void CardManager::CreateCards(UINT puzzleLevel)
{
	UINT totalCardNum = puzzleLevel * PAIR_NUM;

	/* Width x Height Ȳ�ݺ� ���ϱ� - ��� ���ϱ� */
	vector<UINT> divisors;
	for (int i = 1; i <= totalCardNum; i++)
	{
		if (totalCardNum % i == 0)
			divisors.push_back(i);
	}

	// ����� ������ Ȧ����� ��� ����� ũ�� ����
	UINT temp = divisors.size() / 2;

	if (divisors.size() % 2 == 1)
	{
		width = divisors[temp];
		height = divisors[temp];
	}
	else // ����� ������ ¦����� ��� ��ġ�� �� ���� ũ�� ����
	{
		width = divisors[temp];
		height = divisors[temp-1];
	}

	/* ȭ�鿡 ī�� ��ġ�ϱ� */
	Vector2 size = Texture::Add(cardTextures[0])->GetSize() * CARD_SCALE; // ī�� ������

	Vector2 totalHalfSize = size * Vector2(width, height) * 0.5f;
	Vector2 startOffset = Vector2(CENTER_X, CENTER_Y) - totalHalfSize + size * 0.5f;

	/* ī�� ���� �ʱ�ȭ */
	cardBoard.resize(height);
	for (Cards& cards : cardBoard)
		cards.resize(width);

	for (UINT y = 0; y < height; y++)
	{
		for (UINT x = 0; x < width; x++)
		{
			Vector2 pos = startOffset + Vector2(x, y) * size;
			
			// ī�� �ε��� (2����->1����)
			UINT index = (y * width + x) / PAIR_NUM;
			Card* card = new Card(cardTextures[index]);
			card->Position() = pos;
			card->Scale() *= CARD_SCALE;
			card->SetObjEvent(bind(&CardManager::OnClickButtonEvent, this, placeholders::_1));
			
			// �迭 index�� �����ؼ� ����
			// (0,0) (0,1) (0,2) ...
			// (1,0) (1,1) (1,2) ...
			card->Info().pos = { (int)((height - 1) - y), (int)x };
			
			// [height][width]
			cardBoard[card->Info().pos.x][card->Info().pos.y] = card;
		}
	}
}

void CardManager::LoadCardTextures()
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
}

void CardManager::ShuffleCard()
{
	for (int i = 0; i < SHUFFLE; i++)
	{
		POINT randomPos1 = { Random(0, height), Random(0, width) };
		POINT randomPos2 = { Random(0, height), Random(0, width) };

		SwapCard(randomPos1, randomPos2);
	}
}

void CardManager::SwapCard(POINT pos1, POINT pos2)
{
	// ȭ�鿡 ��µ� Pixel Position ����
	Vector2 temp = cardBoard[pos1.x][pos1.y]->Position();
	cardBoard[pos1.x][pos1.y]->Position() = cardBoard[pos2.x][pos2.y]->Position();
	cardBoard[pos2.x][pos2.y]->Position() = temp;

	// ī���� Index ���� ����
	POINT temp2 = cardBoard[pos1.x][pos1.y]->Info().pos;
	cardBoard[pos1.x][pos1.y]->Info().pos = cardBoard[pos2.x][pos2.y]->Info().pos;
	cardBoard[pos2.x][pos2.y]->Info().pos = temp2;
}

void CardManager::OnClickButtonEvent(void* card)
{
	if (card == nullptr) return;
	if (selectCard.size() == SELECT_COUNT) return;

	Card* sCard = (Card*)card;

	if (selectCard.size() > 0)
	{
		if (selectCard[0] == sCard) // ���� ī��� vector�� ����X
			return;
	}

	sCard->Selected() = true;
	
	selectCard.push_back(sCard);
}

void CardManager::CheckCard()
{
	// �׸��� ������ ���Ž�� ����
	if (selectCard[0]->Info().key == selectCard[1]->Info().key)
	{
		POINT start = selectCard[0]->Info().pos;
		POINT end = selectCard[1]->Info().pos;

		// �� ī�尡 ������ �����ڸ��� ��ġ�� ��� - ����ڸ��� ������� ���� ����
		//if ((start.x == end.x) && (start.x == 0 || start.x == height - 1) ||
		//	(start.y == end.y) && (start.y == 0 || start.y == width-1))
		//{
		//	RemoveCard(true);
		//	return;
		//}

		// �� ī�尡 ������ ��ġ�� ���
		if ((start.x == end.x && abs(start.y - end.y) == 1) || 
			(start.y == end.y && abs(start.x - end.x) == 1))
		{
			RemoveCard(true);
			return;
		}

		// ��� Ž��..
		POINT diff = {start.x - end.x, start.y - end.y}; // �� ���� �� �Ÿ�
		bool same[2] = { false, false };

		while (start.x == end.x && start.y == end.y) // ���������� �������� ������ Ž�� ����
		{
			start.x++; // ������ 1ȸ �̵�
			if (cardBoard[start.x][start.y]->Active() == false) // �̵��� �ڸ��� ����ִٸ�
			{
				if (start.x == end.x)
					same[0] = true;
			}

			if (same[0]) // �� �̵��� �����ٸ� (?,x)
			{
				start.y++; // 
			}

			// �̵��� �ڸ��� �����ִٸ�(�ٸ� ī�尡 �ִٸ�)
		}
		
	}


	RemoveCard(false);
}

void CardManager::RemoveCard(bool result)
{
	if (result) // ī�带 ���� �� �ִ� ��쿡�� �����
	{
		selectCard[0]->SetActive(false);
		selectCard[1]->SetActive(false);
	}

	// ī�� �˻簡 ������ �ʱ�ȭ
	selectCard[0]->Selected() = false;
	selectCard[1]->Selected() = false;

	selectCard.clear();
}
