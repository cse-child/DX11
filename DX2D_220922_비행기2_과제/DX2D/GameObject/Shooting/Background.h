#pragma once

class Background : public Texture
{
public:
	Background();
	~Background();

	void Update();
	void Render();
	
private:
	Quad* bgs[2];

	float speed = 50.0f;
};