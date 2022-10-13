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

	monster = new Monster();
	monster->Position() = { 625, 625 };
	monster->Update();

	EffectManager::Get()->Add("exp", 1, L"Textures/Effect/explosion.png", Vector2(5, 3));
}

TankScene::~TankScene()
{
	delete map;
	delete aStar;
	delete tank;
	delete monster;
}

void TankScene::Update()
{	
	if (!tank->Active()) return;

	TankMove();
	MonsterMove();
	CollisionTankAndMonster();

	//map->PushObject(tank->GetCollider());
	//map->Update();

	tank->Update();
	monster->Update();
}

void TankScene::Render()
{
	map->Render();
	aStar->Render();

	tank->Render();
	monster->Render();
}

void TankScene::PostRender()
{
}

void TankScene::TankMove()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		int start = aStar->FindCloseNode(tank->Position());
		int end = aStar->FindCloseNode(mousePos);

		aStar->GetPath(start, end, tank->GetPath());
	}
}

void TankScene::MonsterMove()
{
	if (Vector2::Distance(tank->Position(), monster->Position()) < 200.0f && monster->GetPath().empty())
	{
		int start = aStar->FindCloseNode(monster->Position());
		int end = aStar->FindCloseNode(tank->Position());

		aStar->GetPath(start, end, monster->GetPath());
	}
}

void TankScene::CollisionTankAndMonster()
{
	if (tank->GetCollider()->IsRectCollision((RectCollider*)monster->GetCollider()))
	{
		EffectManager::Get()->Play("exp", tank->GlobalPosition());
		tank->SetActive(false);
	}
}
