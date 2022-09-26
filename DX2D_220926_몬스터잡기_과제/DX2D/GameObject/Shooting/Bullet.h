#pragma once

class Bullet : public Quad
{
public:
	Bullet();
	~Bullet();

	void Update();
	void Render();

	void Fire(Vector2 pos, Vector2 direction);

	Collider* GetCollider() { return collider; }

private:
	float speed = 400.0f;
	Vector2 direction;

	Collider* collider;

};