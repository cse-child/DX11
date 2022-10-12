#include "Framework.h"
#include "ShootingScene.h"

ShootingScene::ShootingScene()
{
	bg = new Quad(L"Textures/test.jpg");
	bg->Scale() *= 4;
	bg->UpdateWorld();

	CAM->SetLeftBottom(bg->Size() * bg->Scale() * -0.5f);
	CAM->SetRightTop(bg->Size() * bg->Scale() * 0.5f);

	cursor = new Quad(L"Textures/Shooting/cursor.png");

	plane = new Plane();
	BulletManager::Get();

	CAM->SetTarget(plane);

	EffectManager::Get()->Add("fire", 50,
		L"Textures/Effect/groundFire.png", Vector2(37, 1), 1, true);
	EffectManager::Get()->Add("exp", 50,
		L"Textures/Effect/explosion.png", Vector2(5, 3), 1, false);

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

	if (KEY_DOWN(VK_LBUTTON))
		EffectManager::Get()->Play("fire", cursor->Position());

	if (KEY_DOWN(VK_RBUTTON))
		EffectManager::Get()->Play("exp", cursor->Position());

	plane->Update();
	BulletManager::Get()->Update();

	EffectManager::Get()->Update();
}

void ShootingScene::Render()
{
	bg->Render();

	plane->Render();
	BulletManager::Get()->Render();

	cursor->Render();

	EffectManager::Get()->Render();
}

void ShootingScene::PostRender()
{
	plane->RenderUI();
}
