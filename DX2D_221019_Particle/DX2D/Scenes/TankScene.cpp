#include "Framework.h"
#include "TankScene.h"

TankScene::TankScene()
{
	map = new GameTileMap("TextData/Stage1.map");
	map->SetMapPos(Vector2(50, 50));

	aStar = new AStar(map);

	tank = new Tank();
	tank->Position() = { 150,130 };
	tank->Update();
}

TankScene::~TankScene()
{
	delete map;
	delete aStar;
	delete tank;
}

void TankScene::Update()
{	
	if (KEY_DOWN(VK_LBUTTON))
	{
		int start = aStar->FindCloseNode(tank->Position());
		int end = aStar->FindCloseNode(mousePos);

		aStar->GetPath(start, end, tank->GetPath());
	}

	//map->PushObject(tank->GetCollider());

	map->Update();
	tank->Update();
}

void TankScene::Render()
{
	map->Render();
	aStar->Render();
	tank->Render();
}

void TankScene::PostRender()
{
}
