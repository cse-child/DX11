#pragma once

class TileScene : public Scene
{
public:
	TileScene();
	~TileScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void ClickSampleBtn(void* sampleBtn);

private:
	void CreateSample();

	void Save();
	void Load();

private:
	Vector2 sampleTileSize = { 50,50 };

	vector<Button*> sampleBtns;

	TileMap* tileMap;

	wstring selectSampleFile;

	Quad* selectSample = nullptr;

	string projectPath;
};