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
	void TankMove();
	void MonsterMove();
	
	void CollisionTankAndMonster();

private:
	GameTileMap* map;
	AStar* aStar;

	Tank* tank;
	Monster* monster;
};