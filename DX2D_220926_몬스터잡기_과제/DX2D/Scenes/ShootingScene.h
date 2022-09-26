#pragma once

class ShootingScene : public Scene
{
private:
	const UINT ENEMY_COUNT = 10;

public:
	ShootingScene();
	~ShootingScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	void EnemySpawn();
	void CollisionEnemyAndBullet();

private:
	Plane* plane;

	vector<Enemy*> enemies;

	float playTime = 0.0f;
	float spawnTime = 2.0f;
};