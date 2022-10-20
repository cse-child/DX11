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
	float moveSpeed = 200.0f;
	float rotSpeed = 5.0f;

	float maxHp = 100.0f;
	float curHp = 100.0f;

	ProgressBar* hpBar;
};