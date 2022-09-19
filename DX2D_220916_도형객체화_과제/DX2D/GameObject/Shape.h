#pragma once

class Shape
{
public:
	Shape(float size, int num, float x, float y);
	~Shape();

	void Render();

private:
	void DrawShape();

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	VertexBuffer* vertexBuffer;

	vector<VertexColor> vertices;

	float x, y;
	float size;
	float polygonNum;
};