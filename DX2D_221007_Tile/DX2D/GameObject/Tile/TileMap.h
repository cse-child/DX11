#pragma once

class TileMap : public Transform
{
public:
	TileMap(UINT width, UINT height);
	~TileMap();

	void Update();
	void Render();

	void ClickTile(Quad* selectSample, Tile::Type type);

	void Save(string file);
	void Load(string file);

private:
	void CreateTile();

	void SetBGTile(wstring file, float angle);
	void SetOBJTile(wstring file, float angle);

	void ClearBGTile();

private:
	UINT width, height;

	vector<Tile*> bgTiles;
	vector<Tile*> objTiles;

	Vector2 tileSize;
};