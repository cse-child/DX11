#include "Framework.h"
#include "ShootingScene.h"

ShootingScene::ShootingScene()
{
	plane = new Plane();
	enemies.resize(ENEMY_COUNT);
	for (Enemy*& enemy : enemies)
		enemy = new Enemy(plane);
	BulletManager::Get();
}

ShootingScene::~ShootingScene()
{
	delete plane;
	for (Enemy* enemy : enemies)
		delete enemy;
	BulletManager::Delete();
}

void ShootingScene::Update()
{
	EnemySpawn();
	CollisionEnemyAndBullet();

	plane->Update();
	for (Enemy* enemy : enemies)
		enemy->Update();
	BulletManager::Get()->Update();
}

void ShootingScene::Render()
{
	plane->Render();
	for (Enemy* enemy : enemies)
		enemy->Render();
	BulletManager::Get()->Render();
}

void ShootingScene::PostRender()
{
	plane->RenderUI();
}

void ShootingScene::EnemySpawn()
{
	playTime += DELTA;

	if (playTime > spawnTime)
	{
		for (Enemy* enemy : enemies)
		{
			if (!enemy->Active())
			{
				enemy->Spawn();
				playTime = 0.0f;
				break;
			}
		}
	}
}

void ShootingScene::CollisionEnemyAndBullet()
{
	vector<Bullet*> bullets = BulletManager::Get()->GetBullets();

	for (Enemy* enemy : enemies)
	{
		for (Bullet* bullet : bullets)
		{
			if (!bullet->Active()) continue;

			if (enemy->CircleCollision(bullet->GetCollider()))
			{
				enemy->SetActive(false);
				bullet->SetActive(false);
			}
		}
	}
}
