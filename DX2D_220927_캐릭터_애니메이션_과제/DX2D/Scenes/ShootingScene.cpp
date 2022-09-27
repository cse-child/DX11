#include "Framework.h"
#include "ShootingScene.h"

ShootingScene::ShootingScene()
{
	plane = new Plane();
	BulletManager::Get();
}

ShootingScene::~ShootingScene()
{
	delete plane;
	BulletManager::Delete();
}

void ShootingScene::Update()
{
	plane->Update();
	BulletManager::Get()->Update();
}

void ShootingScene::Render()
{
	plane->Render();
	BulletManager::Get()->Render();
}

void ShootingScene::PostRender()
{
	plane->RenderUI();
}
