#pragma once

class GameTileMap : public Transform
{
public:
	GameTileMap(string file);
	~GameTileMap();

	void Update();
	void Render();

	void SetMapPos(Vector2 pos);

	void PushObject(Collider* collider);

private:
	void Load(string file);

private:
	UINT width, height;

	Vector2 tileSize;

	vector<Quad*> bgTiles;
	vector<Tile*> objTiles;
};