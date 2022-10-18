#include "Framework.h"
#include "PuzzleScene.h"

PuzzleScene::PuzzleScene()
{
	CardManager::Get();
}

PuzzleScene::~PuzzleScene()
{
	CardManager::Delete();
}

void PuzzleScene::Update()
{
	CardManager::Get()->Update();
}

void PuzzleScene::Render()
{
	CardManager::Get()->Render();
}

void PuzzleScene::PostRender()
{
}
