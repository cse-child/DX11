#include "Framework.h"
#include "CatchingThiefScene.h"

CatchingThiefScene::CatchingThiefScene()
{
	bg = new Quad(L"Textures/card_bg.jpg");
	bg->Resize({ WIN_WIDTH, WIN_HEIGHT }, { CENTER_X, CENTER_Y });
	bg->UpdateWorld();

	ThiefCardManager::Get();
}

CatchingThiefScene::~CatchingThiefScene()
{
	delete bg;
	ThiefCardManager::Delete();
}

void CatchingThiefScene::Update()
{
	ThiefCardManager::Get()->Update();
}

void CatchingThiefScene::Render()
{
	bg->Render();
	ThiefCardManager::Get()->Render();
}

void CatchingThiefScene::PostRender()
{
}
