#pragma once

class Monster : public AnimObject
{
private:
	const float DETECT_RANGE = 200.0f;

	enum State
	{
		WAKE_UP, SLEEP
	};

public:
	Monster();
	~Monster();

	void Update();
	void Render();

	Collider* GetCollider() { return collider; }

	vector<Vector2>& GetPath() { return path; }

private:
	void MovePath();

private:
	Collider* collider;

	vector<Vector2> path;
	
	float moveSpeed = 150.0f;
};