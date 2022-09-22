#pragma once

class Plane : public Texture, public Quad
{
public:
	Plane();
	~Plane();

	void Update();
	void Render();
	void PostRender();

private:
	void Move();
	void Fire();

private:
	float speed = 300.0f;
};