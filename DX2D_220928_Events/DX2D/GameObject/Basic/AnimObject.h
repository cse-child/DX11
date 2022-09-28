#pragma once

class AnimObject : public Transform
{
public:
	AnimObject();
	~AnimObject();

	void Update();
	void Render();

	void SetColor(float r, float g, float b, float a = 1.0f);

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	MatrixBuffer* worldBuffer;
	ColorBuffer* colorBuffer;

protected:
	map<int, Clip*> clips;
	Clip* curClip = nullptr;
};