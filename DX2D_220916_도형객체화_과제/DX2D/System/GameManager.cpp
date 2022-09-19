#include "Framework.h"

#include "Scenes/TutorialScene.h"
#include "Scenes/DrawShapeScene.h"

GameManager::GameManager()
{
	Create();

	//scene = new TutorialScene();
	scene = new DrowShapeScene();
}

GameManager::~GameManager()
{
	delete scene;

	Delete();
}

void GameManager::Update()
{
	Keyboard::Get()->Update();
	Timer::Get()->Update();

	scene->Update();
}

void GameManager::Render()
{
	scene->Render();
	scene->PostRender();
}

void GameManager::Create()
{
	Keyboard::Get();
	Timer::Get();
	Device::Get();
}

void GameManager::Delete()
{
	Keyboard::Delete();
	Timer::Delete();
	Device::Delete();
}
