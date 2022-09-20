#include "Framework.h"

#include "Scenes/TutorialScene.h"
#include "Scenes/SRTScene.h"

GameManager::GameManager()
{
	Create();
	CreateProjection();

	//scene = new TutorialScene();
	scene = new SRTScene();
}

GameManager::~GameManager()
{
	delete scene;
	delete view;
	delete projection;

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

void GameManager::CreateProjection()
{
	view = new MatrixBuffer();
	projection = new MatrixBuffer();

	Matrix orthographic = XMMatrixOrthographicOffCenterLH(
		0.0f, WIN_WIDTH, 0.0f, WIN_HEIGHT, -1.0f, 1.0f);

	projection->Set(orthographic);

	view->SetVS(1);
	projection->SetVS(2);
}
