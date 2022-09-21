#pragma once

class BulletManager : public Singleton<BulletManager>
{
public:
	BulletManager();
	~BulletManager();

	void Update();
	void Render();

	void Fire(Vector2 pos, Vector2 direction);

	void CreateBullets(UINT poolingCount);

private:
	vector<Bullet*> bullets;

};