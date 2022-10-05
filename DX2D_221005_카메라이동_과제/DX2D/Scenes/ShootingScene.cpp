#include "Framework.h"
#include "ShootingScene.h"

ShootingScene::ShootingScene()
{
	bg = new Quad(L"Textures/test.jpg");
	bg->Position() = { CENTER_X, CENTER_Y };
	bg->Scale() *= 4;
	bg->UpdateWorld();

	cursor = new Quad(L"Textures/Shooting/cursor.png");

	plane = new Plane();
	BulletManager::Get();

	CAM->SetTarget(plane);
	CAM->SetCamBgSize(bg->Size());
	
	//ShowCursor(false);
}

ShootingScene::~ShootingScene()
{
	delete bg;
	delete cursor;
	delete plane;
	BulletManager::Delete();
}

void ShootingScene::Update()
{
	cursor->Position() = CAM->ScreenToWorld(mousePos);
	cursor->UpdateWorld();

	plane->Update();
	BulletManager::Get()->Update();
}

void ShootingScene::Render()
{
	bg->Render();

	plane->Render();
	BulletManager::Get()->Render();

	cursor->Render();
}

void ShootingScene::PostRender()
{
	plane->RenderUI();
}
