#pragma once

class Plane : public Quad
{
public:
	Plane();
	~Plane();

	void Update();
	void Render();
	void RenderUI();

private:
	void MoveControl();

private:
	float moveSpeed = 100.0f;
	float rotSpeed = 5.0f;
};