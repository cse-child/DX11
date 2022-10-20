#include "Framework.h"

GameTileMap::GameTileMap(string file)
{
	Load(file);
}

GameTileMap::~GameTileMap()
{
	for (Quad* tile : bgTiles)
		delete tile;
	bgTiles.clear();

	for (Tile* tile : objTiles)
		delete tile;
	objTiles.clear();
}

void GameTileMap::Update()
{
	//for (Tile* tile : objTiles)
	//	tile->Update();
}

void GameTileMap::Render()
{
	for (Quad* tile : bgTiles)
		tile->Render();

	for (Tile* tile : objTiles)
		tile->Render();
}

void GameTileMap::SetMapPos(Vector2 pos)
{
	localPosition = pos;
	UpdateWorld();

	for (Quad* tile : bgTiles)
		tile->UpdateWorld();

	for (Tile* tile : objTiles)
		tile->Update();
}

void GameTileMap::PushObject(Collider* collider)
{
	for (Tile* tile : objTiles)
	{
		tile->GetCollider()->PushCollider(collider);
	}
}

// 반환을 안하고 참조형으로 저장해서 효율이 좋음
void GameTileMap::GetNodes(vector<Node*>& nodes)
{
	for (Quad* tile : bgTiles)
	{
		Vector2 tilePos = tile->GlobalPosition();
		Node* node = new Node(tilePos, nodes.size());

		for (Tile* obj : objTiles)
		{
			Vector2 objPos = obj->GlobalPosition();
			if (objPos == tilePos)
			{
				node->SetState(Node::OBSTACLE);
			}
		}
		nodes.push_back(node);
	}
}

void GameTileMap::Load(string file)
{
	BinaryReader* reader = new BinaryReader(file);

	width = reader->UInt();
	height = reader->UInt();

	UINT size = reader->UInt();

	bgTiles.resize(size);

	for (Quad*& tile : bgTiles)
	{
		Tile::Data data;
		data.textureFile = reader->WString();
		data.pos.x = reader->Float();
		data.pos.y = reader->Float();
		data.angle = reader->Float();
		data.type = (Tile::Type)reader->Int();

		tile = new Quad(data.textureFile);
		tile->Position() = data.pos;
		tile->Rotation().z = data.angle;
		tile->SetParent(this);
		tile->UpdateWorld();
	}

	size = reader->UInt();

	objTiles.resize(size);

	for (Tile*& tile : objTiles)
	{
		Tile::Data data;
		data.textureFile = reader->WString();
		data.pos.x = reader->Float();
		data.pos.y = reader->Float();
		data.angle = reader->Float();
		data.type = (Tile::Type)reader->Int();

		tile = new Tile(data);
		tile->SetParent(this);
		tile->UpdateWorld();
	}
	delete reader;
}
