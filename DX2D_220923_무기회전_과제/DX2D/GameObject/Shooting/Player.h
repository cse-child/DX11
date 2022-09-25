#pragma once

class Player : public Quad
{
public:
	Player();
	~Player();

	void Update();
	void Render();
	void RenderUI();

private:
	void MoveControl();

private:
	float moveSpeed = 300.0f;

};