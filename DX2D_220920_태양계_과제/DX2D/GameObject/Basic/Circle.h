#pragma once

class Circle
{
public:
	Circle(Float2 pos, float size, Float3 color, Float3 color2);
	~Circle();

	void Render();

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	vector<VertexColor> vertices;
	vector<UINT> indices;
};