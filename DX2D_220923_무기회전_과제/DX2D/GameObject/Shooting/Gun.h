#pragma once

class Gun : public Quad
{
public:
	Gun();
	~Gun();

	void Update();
	void Render();

private:
	float rotSpeed = 5.0f;
};