#pragma once

class Transform
{
public:
	Transform(Float2 position = {0,0}, Float2 scale = {1,1}, float angle = 0.0f);
	~Transform();

	void Set();

	Float2& Pos() { return position; }
	float& Angle() { return angle; }

	Matrix& GetWorld() { return world; }

private:
	Float2 position;
	Float2 scale = { 1, 1 };
	float angle = 0.0f;

	Matrix world;
};