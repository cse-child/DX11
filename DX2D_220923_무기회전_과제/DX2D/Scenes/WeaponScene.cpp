#include "Framework.h"
#include "WeaponScene.h"

WeaponScene::WeaponScene()
{
	player = new Player();
	gun = new Gun();
	BulletManager::Get();

	gun->SetParent(player);
}

WeaponScene::~WeaponScene()
{
	delete player;
	delete gun;
	BulletManager::Delete();
}

void WeaponScene::Update()
{
	player->Update();
	gun->Update();
	BulletManager::Get()->Update();
}

void WeaponScene::Render()
{
	player->Render();
	BulletManager::Get()->Render();
	gun->Render();
}

void WeaponScene::PostRender()
{
	player->RenderUI();
}
