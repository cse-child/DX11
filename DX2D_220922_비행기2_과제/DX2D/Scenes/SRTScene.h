#pragma once

class SRTScene : public Scene
{
public:
	SRTScene();
	~SRTScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Rect* rect;

	MatrixBuffer* worldBuffer;
	//XMFLOAT4X4 world;
	Matrix world, world2;

	Float2 position;
	Float2 scale;
	float angle, angle2; // z√‡ »∏¿¸

	Float2 pivot;

};