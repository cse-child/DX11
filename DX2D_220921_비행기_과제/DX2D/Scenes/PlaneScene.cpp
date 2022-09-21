#include "Framework.h"
#include "PlaneScene.h"

PlaneScene::PlaneScene()
{
	plane = new Triangle({ 0, 0 }, 50);
	plane->Position() = { CENTER_X, CENTER_Y };
	plane->SetTag("Plane");

	BulletManager::Get()->CreateBullets(10);
}

PlaneScene::~PlaneScene()
{
	delete plane;
	BulletManager::Delete();
}

void PlaneScene::Update()
{
	plane->Update();
	BulletManager::Get()->Update();
}

void PlaneScene::Render()
{
	plane->Render();
	BulletManager::Get()->Render();
}

void PlaneScene::PostRender()
{
	plane->RenderUI();
}
