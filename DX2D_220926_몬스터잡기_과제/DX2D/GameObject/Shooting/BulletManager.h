#pragma once

class BulletManager : public Singleton<BulletManager>
{
private:
	const UINT MAX_BULLET = 50;

public:
	BulletManager();
	~BulletManager();

	void Update();
	void Render();

	void Fire(Vector2 pos, Vector2 direction);

	vector<Bullet*> GetBullets() { return bullets; }

private:
	vector<Bullet*> bullets;
};