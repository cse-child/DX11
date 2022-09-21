#pragma once

class Bullet : public Rect
{
public:
	Bullet();
	~Bullet();

	void Update();

	void Fire(Vector2 pos, Vector2 direction);

private:
	float speed = 3.0f;

	Vector2 direction;
};