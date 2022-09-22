#include "Framework.h"

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
	for (Bullet* bullet : bullets)
		delete bullet;
	bullets.clear();
}

void BulletManager::Update()
{
	for (Bullet* bullet : bullets)
	{
		if (bullet->Active())
			bullet->Update();
	}
}

void BulletManager::Render()
{
	for (Bullet* bullet : bullets)
	{
		if (bullet->Active())
			bullet->Render();
	}
}

void BulletManager::Fire(Vector2 pos, Vector2 direction)
{
	for (Bullet* bullet : bullets)
	{
		if (!bullet->Active())
		{
			bullet->Fire(pos, direction);
			return;
		}
	}
}

void BulletManager::CreateBullets(UINT poolingCount)
{
	bullets.resize(poolingCount);

	for (Bullet*& bullet : bullets)
	{
		bullet = new Bullet();
	}
}
