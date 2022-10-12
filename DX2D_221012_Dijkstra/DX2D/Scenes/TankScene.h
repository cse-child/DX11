#pragma once

class TankScene : public Scene
{
public:
	TankScene();
	~TankScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	GameTileMap* map;

	Tank* tank;
};