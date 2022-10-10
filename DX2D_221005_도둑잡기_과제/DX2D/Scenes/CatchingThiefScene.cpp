#include "Framework.h"
#include "CatchingThiefScene.h"

CatchingThiefScene::CatchingThiefScene()
{
	bg = new Quad(L"Textures/card_bg.jpg");
	bg->Resize({ WIN_WIDTH, WIN_HEIGHT }, { CENTER_X, CENTER_Y });
	bg->UpdateWorld();

	noneCursor = Texture::Add(L"Textures/hand_cursor.png");
	clickCursor = Texture::Add(L"Textures/hand_cursor_click.png");

	cursor = new Quad(noneCursor);
	ShowCursor(false);

	ThiefCardManager::Get();

	nextTurnBtn = new Button(L"Textures/Button-Next.png");
	nextTurnBtn->Position() = { WIN_WIDTH - 75, 130 };
	nextTurnBtn->SetEvent(bind(&ThiefCardManager::NextTurn, ThiefCardManager::Get()));

	sortBtn = new Button(L"Textures/Button-Sort.png");
	sortBtn->Position() = { WIN_WIDTH - 110, 75 };
	sortBtn->SetEvent(bind(&ThiefCardManager::SortPlayerCards, ThiefCardManager::Get()));

	swapBtn = new Button(L"Textures/Button-Swap.png");
	swapBtn->Position() = { WIN_WIDTH - 40, 75 };
	swapBtn->SetEvent(bind(&ThiefCardManager::SwapCards, ThiefCardManager::Get()));
}

CatchingThiefScene::~CatchingThiefScene()
{
	delete bg;
	delete cursor;
	ThiefCardManager::Delete();
	delete nextTurnBtn;
	delete sortBtn;
	delete swapBtn;
}

void CatchingThiefScene::Update()
{
	cursor->Position() = mousePos;

	if (KEY_PRESS(VK_LBUTTON))
		cursor->SetTexture(clickCursor);
	else
		cursor->SetTexture(noneCursor);

	nextTurnBtn->Update();
	nextTurnBtn->ButtonColorUpdate();
	sortBtn->Update();
	sortBtn->ButtonColorUpdate();
	swapBtn->Update();
	swapBtn->ButtonColorUpdate();

	cursor->UpdateWorld();
	ThiefCardManager::Get()->Update();
}

void CatchingThiefScene::Render()
{
	bg->Render();
	ThiefCardManager::Get()->Render();

	nextTurnBtn->Render();
	sortBtn->Render();
	swapBtn->Render();

	cursor->Render();
}

void CatchingThiefScene::PostRender()
{
}
