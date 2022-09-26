#pragma once

class Enemy : public Quad
{
public:
	Enemy(Quad* target);
	~Enemy();

	void Update();
	void Render();

	void Spawn();

	bool CircleCollision(Collider* target);

private:
	Vector2 direction;

	float moveSpeed = 100.0f;

	Collider* collider;

	Quad* target;
};