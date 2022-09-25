#include "Framework.h"

BulletManager::BulletManager()
{
	bullets.resize(MAX_BULLET);

	for (Bullet*& bullet : bullets)
	{
		bullet = new Bullet();
	}
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
		bullet->Update();
}

void BulletManager::Render()
{
	for (Bullet* bullet : bullets)
		bullet->Render();

	bullets[0]->RenderUI();
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
