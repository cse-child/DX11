#include "Framework.h"
#include "TankScene.h"

TankScene::TankScene()
{
	map = new GameTileMap("TextData/Stage1.map");
	map->SetMapPos(Vector2(50, 50));

	tank = new Tank();
	tank->Position() = { 150,130 };
	tank->Update();
}

TankScene::~TankScene()
{
	delete map;
	delete tank;
}

void TankScene::Update()
{	
	map->PushObject(tank->GetCollider());

	map->Update();
	tank->Update();
}

void TankScene::Render()
{
	map->Render();
	tank->Render();
}

void TankScene::PostRender()
{
}
