#pragma once

class Tank : public AnimObject
{
public:
	Tank();
	~Tank();

	void Update();
	void Render();

	Collider* GetCollider() { return collider; }

private:
	void Control();

private:
	float moveSpeed = 200.0f;
	float rotSpeed = 3.0f;

	Collider* collider;
};