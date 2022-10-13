#pragma once

class Rect : public Transform
{
public:
	Rect(Float2 pos, Float2 size);
	~Rect();

	void Render();

	void SetColor(Float3 color);

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	MatrixBuffer* worldBuffer;

	vector<VertexColor> vertices;
	vector<UINT> indices;
};