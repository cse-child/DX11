#include "Framework.h"

CardManager::CardManager()
{
	LoadCardTextures();
	CreateCards(10);

	ShuffleCard();
}

CardManager::~CardManager()
{
	for (Card* card : cards)
		delete card;
	cards.clear();
}

void CardManager::Update()
{
	for (Card* card : cards)
		card->Update();
}

void CardManager::Render()
{
	for (Card* card : cards)
		card->Render();
}

void CardManager::CreateCards(UINT puzzleLevel)
{
	UINT totalCardNum = puzzleLevel * PAIR_NUM;

	/* ��� ���ϱ� */
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

	Vector2 size = Texture::Add(cardTextures[0])->GetSize() * CARD_SCALE; // ī�� ������

	Vector2 totalHalfSize = size * Vector2(width, height) * 0.5f;
	Vector2 startOffset = Vector2(CENTER_X, CENTER_Y) - totalHalfSize + size * 0.5f;

	// ī�� ���� �ʱ�ȭ
	cardBoard.resize(height);
	for (vector<Card*>& cards : cardBoard)
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
			card->SetCoord(x, y);

			cards.push_back(card);

			cardBoard[y][x] = card;
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
		int random1 = Random(0, cards.size());
		int random2 = Random(0, cards.size());

		SwapCard(random1, random2);
	}
}

void CardManager::SwapCard(int n1, int n2)
{
	Vector2 temp = cards[n1]->Position();
	cards[n1]->Position() = cards[n2]->Position();
	cards[n2]->Position() = temp;

	POINT tempCoord = cards[n1]->pos;
	cards[n1]->pos = cards[n2]->pos;
	cards[n2]->pos = tempCoord;

	POINT pos1 = cards[n1]->pos;
	POINT pos2 = cards[n2]->pos;
	Card* tempCard = cardBoard[pos1.y][pos1.x];
	cardBoard[pos1.y][pos1.x] = cardBoard[pos2.y][pos2.x];
	cardBoard[pos2.y][pos2.x] = tempCard;
}

void CardManager::SelectCard(Card* selectCard)
{
	if (firstSelectCard == nullptr)
	{
		firstSelectCard = selectCard;
		return;
	}
	secondSelectCard = selectCard;

	DeleteMatchCard();

	firstSelectCard = nullptr;
	secondSelectCard = nullptr;
}

void CardManager::DeleteMatchCard()
{
	if (!IsSameCard()) return;

	if (IsSameLine(firstSelectCard->pos, secondSelectCard->pos))
	{
		firstSelectCard->SetActive(false);
		secondSelectCard->SetActive(false);
		return;
	}

	if (IsDigeud(firstSelectCard->pos, secondSelectCard->pos))
	{
		firstSelectCard->SetActive(false);
		secondSelectCard->SetActive(false);
		return;
	}
}

bool CardManager::IsSameCard()
{
	if (firstSelectCard == secondSelectCard)
	{
		MessageBox(hWnd, L"���� ī�� �Դϴ�.", L"Error", MB_OK);
		return false;
	}

	if(firstSelectCard->key == secondSelectCard->key)
		return true;

	MessageBox(hWnd, L"ī�尡 ��ġ���� �ʽ��ϴ�.", L"Error", MB_OK);
	return false;
}

/* �� ī�尡 ���� ���ο� �ִ��� �Ǵ� & �� ���� ��ֹ��� ���� �Ǵ� */
bool CardManager::IsSameLine(POINT pos1, POINT pos2)
{
	if(pos1.x != pos2.x && pos1.y != pos2.y)
		return false;
	
	if (pos1.x == pos2.x) // ���� ���� �ִ� ���
	{
		int minPos = min(pos1.y, pos2.y);
		int maxPos = max(pos1.y, pos2.y);

		for (int y = minPos + 1; y < maxPos; y++)
		{
			if (cardBoard[y][pos1.x]->Active())
				return false;
		}
	}

	if (pos1.y == pos2.y) // ���� �࿡ �ִ� ���
	{
		int minPos = min(pos1.x, pos2.x);
		int maxPos = max(pos1.x, pos2.x);

		for (int x = minPos + 1; x < maxPos; x++)
		{
			if (cardBoard[pos1.y][x]->Active())
				return false;
		}
	}
	return true;
}

bool CardManager::IsSameLineIncludeSelf(POINT pos1, POINT pos2)
{
	if (pos1.x != pos2.x && pos1.y != pos2.y)
		return false;

	if (pos1.x == pos2.x) // ���� ���� �ִ� ���
	{
		int minPos = min(pos1.y, pos2.y);
		int maxPos = max(pos1.y, pos2.y);

		for (int y = minPos; y <= maxPos; y++)
		{
			if (cardBoard[y][pos1.x]->Active())
				return false;
		}
	}

	if (pos1.y == pos2.y) // ���� �࿡ �ִ� ���
	{
		int minPos = min(pos1.x, pos2.x);
		int maxPos = max(pos1.x, pos2.x);

		for (int x = minPos; x <= maxPos; x++)
		{
			if (cardBoard[pos1.y][x]->Active())
				return false;
		}
	}
	return true;
}

/* ��(���) �ڷ� ���� ��� + Z, �� */
bool CardManager::IsDigeud(POINT pos1, POINT pos2)
{
	EmptyDir result1 = GetEmptyDir(pos1);
	EmptyDir result2 = GetEmptyDir(pos2);

	// ���� �������� �ո� ��� ū ����� ���� - ������ ������
	if (result1.up && result2.up)
		return true;
	if (result1.down && result2.down)
		return true;
	if (result1.left && result2.left)
		return true;
	if (result1.right && result2.right)
		return true;

	// 2. ��ֹ��� �־ ���� ����ڷ� ������ ���
	// Right
	for (int x = pos1.x + 1; x < width; x++)
	{
		POINT pos = { x, pos1.y };

		if (cardBoard[pos.y][pos.x]->Active()) // �������� �����ִ�.
			break;

		if (IsSameLine(pos, pos2))
			return true;

		POINT temp = { x, pos2.y };
		
		if (IsSameLineIncludeSelf(pos, temp))
		{
			if(IsSameLine(pos2, temp))
				return true;
		}
	}

	// Left
	for (int x = pos1.x - 1; x >= 0; x--)
	{
		POINT pos = { x, pos1.y };

		if (cardBoard[pos.y][pos.x]->Active()) 
			break;

		if (IsSameLine(pos, pos2))
			return true;

		POINT temp = { x, pos2.y };
		if (IsSameLineIncludeSelf(pos, temp))
		{
			if (IsSameLine(pos2, temp))
				return true;
		}
	}

	// Up
	for (int y = pos1.y + 1; y < height; y++)
	{
		POINT pos = { pos1.x, y };

		if (cardBoard[pos.y][pos.x]->Active())
			break;

		if (IsSameLine(pos, pos2))
			return true;

		POINT temp = { pos2.x, y };
		if (IsSameLineIncludeSelf(pos, temp))
		{
			if (IsSameLine(pos2, temp))
				return true;
		}
	}

	// Down
	for (int y = pos1.y - 1; y >= 0; y--)
	{
		POINT pos = { pos1.x, y };

		if (cardBoard[pos.y][pos.x]->Active())
			break;

		if (IsSameLine(pos, pos2))
			return true;

		POINT temp = { pos2.x, y };
		if (IsSameLineIncludeSelf(pos, temp))
		{
			if (IsSameLine(pos2, temp))
				return true;
		}
	}
	return false;
}

/* ���� ī��� ���� �����¿� ��������� �շ��ִ��� �˻� */
CardManager::EmptyDir CardManager::GetEmptyDir(POINT pos)
{
	EmptyDir result;

	// Right
	if (pos.x == width - 1) // �ܰ��ΰ�?
		result.right = true;
	else // ��ĭ�� �̵��ϸ� �˻�
	{
		result.right = true;
		for (int x = pos.x + 1; x < width; x++)
		{
			if (cardBoard[pos.y][x]->Active())
				result.right = false;
		}
	}

	// Left
	if (pos.x == 0)
		result.left = true;
	else
	{
		result.left = true;
		for (int x = pos.x - 1; x >= 0; x--)
		{
			if (cardBoard[pos.y][x]->Active())
				result.left = false;
		}
	}

	// Up
	if (pos.y == height - 1) 
		result.up = true;
	else
	{
		result.up = true;
		for (int y = pos.y + 1; y < height; y++)
		{
			if (cardBoard[y][pos.x]->Active())
				result.up = false;
		}
	}
	// Down
	if (pos.y == 0) 
		result.down = true;
	else
	{
		result.down = true;
		for (int y = pos.y - 1; y >= 0; y--)
		{
			if (cardBoard[y][pos.x]->Active())
				result.down = false;
		}
	}
	return result;
}
