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

	/* Width x Height 황금비 구하기 - 약수 구하기 */
	vector<UINT> divisors;
	for (int i = 1; i <= totalCardNum; i++)
	{
		if (totalCardNum % i == 0)
			divisors.push_back(i);
	}

	// 약수의 개수가 홀수라면 가운데 약수로 크기 지정
	UINT temp = divisors.size() / 2;

	if (divisors.size() % 2 == 1)
	{
		width = divisors[temp];
		height = divisors[temp];
	}
	else // 약수의 개수가 짝수라면 가운데 위치한 두 수로 크기 지정
	{
		width = divisors[temp];
		height = divisors[temp-1];
	}

	/* 화면에 카드 배치하기 */
	Vector2 size = Texture::Add(cardTextures[0])->GetSize() * CARD_SCALE; // 카드 사이즈

	Vector2 totalHalfSize = size * Vector2(width, height) * 0.5f;
	Vector2 startOffset = Vector2(CENTER_X, CENTER_Y) - totalHalfSize + size * 0.5f;

	/* 카드 보드 초기화 */
	cardBoard.resize(height);
	for (Cards& cards : cardBoard)
		cards.resize(width);

	for (UINT y = 0; y < height; y++)
	{
		for (UINT x = 0; x < width; x++)
		{
			Vector2 pos = startOffset + Vector2(x, y) * size;
			
			// 카드 인덱스 (2차원->1차원)
			UINT index = (y * width + x) / PAIR_NUM;
			Card* card = new Card(cardTextures[index]);
			card->Position() = pos;
			card->Scale() *= CARD_SCALE;
			card->SetObjEvent(bind(&CardManager::OnClickButtonEvent, this, placeholders::_1));
			
			// 배열 index로 변경해서 저장
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
	// 화면에 출력될 Pixel Position 변경
	Vector2 temp = cardBoard[pos1.x][pos1.y]->Position();
	cardBoard[pos1.x][pos1.y]->Position() = cardBoard[pos2.x][pos2.y]->Position();
	cardBoard[pos2.x][pos2.y]->Position() = temp;

	// 카드의 Index 정보 변경
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
		if (selectCard[0] == sCard) // 같은 카드는 vector에 저장X
			return;
	}

	sCard->Selected() = true;
	
	selectCard.push_back(sCard);
}

void CardManager::CheckCard()
{
	// 그림이 같으면 경로탐색 시작
	if (selectCard[0]->Info().key == selectCard[1]->Info().key)
	{
		POINT start = selectCard[0]->Info().pos;
		POINT end = selectCard[1]->Info().pos;

		// 두 카드가 동일한 가장자리에 위치한 경우 - 어느자리에 상관없이 삭제 가능
		//if ((start.x == end.x) && (start.x == 0 || start.x == height - 1) ||
		//	(start.y == end.y) && (start.y == 0 || start.y == width-1))
		//{
		//	RemoveCard(true);
		//	return;
		//}

		// 두 카드가 나란히 위치한 경우
		if ((start.x == end.x && abs(start.y - end.y) == 1) || 
			(start.y == end.y && abs(start.x - end.x) == 1))
		{
			RemoveCard(true);
			return;
		}

		// 경로 탐색..
		POINT diff = {start.x - end.x, start.y - end.y}; // 두 지점 간 거리
		bool same[2] = { false, false };

		while (start.x == end.x && start.y == end.y) // 시작지점과 끝지점이 같으면 탐색 종료
		{
			start.x++; // 오른쪽 1회 이동
			if (cardBoard[start.x][start.y]->Active() == false) // 이동한 자리가 비어있다면
			{
				if (start.x == end.x)
					same[0] = true;
			}

			if (same[0]) // 열 이동이 끝났다면 (?,x)
			{
				start.y++; // 
			}

			// 이동한 자리가 막혀있다면(다른 카드가 있다면)
		}
		
	}


	RemoveCard(false);
}

void CardManager::RemoveCard(bool result)
{
	if (result) // 카드를 지울 수 있는 경우에만 지우기
	{
		selectCard[0]->SetActive(false);
		selectCard[1]->SetActive(false);
	}

	// 카드 검사가 끝나면 초기화
	selectCard[0]->Selected() = false;
	selectCard[1]->Selected() = false;

	selectCard.clear();
}
