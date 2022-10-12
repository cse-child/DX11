#pragma once

class Tank : public AnimObject
{
public:
	Tank();
	~Tank();

	void Update();
	void Render();

	Collider* GetCollider() { return collider; }

	void SetPath(vector<Vector2> path) { this->path = path; }

private:
	void Control();
	void MovePath();

private:
	float moveSpeed = 200.0f;
	float rotSpeed = 3.0f;

	Collider* collider;

	vector<Vector2> path;
};