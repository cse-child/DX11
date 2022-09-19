#include "Framework.h"
#include "Shape.h"

Shape::Shape(float size, int num, float x, float y)
	:size(size), polygonNum(num), x(x), y(y)
{
	vertexShader = new VertexShader(L"Shaders/Tutorial.hlsl");
	pixelShader = new PixelShader(L"Shaders/Tutorial.hlsl");

	DrawShape();
}

Shape::~Shape()
{
	delete vertexShader;
	delete pixelShader;
	delete vertexBuffer;
}

void Shape::Render()
{
	vertexBuffer->Set();

	vertexShader->Set();
	pixelShader->Set();

	DC->Draw(vertices.size(), 0);
}

void Shape::DrawShape()
{
	for (UINT i = 0; i < polygonNum; i++)
	{
		vertices.emplace_back(x, y, 1, 0.9, 0.89);
		vertices.emplace_back(0.57f * cosf((i+1) * XM_2PI / polygonNum) * size + x, sinf((i + 1) * XM_2PI / polygonNum) * size + y, 0.98, 0.76, 0.76);
		vertices.emplace_back(0.57f * cosf(i * XM_2PI / polygonNum) * size + x, sinf(i * XM_2PI / polygonNum) * size + y, 0.89, 0.61, 0.76);
	}

	vertexBuffer = new VertexBuffer(vertices.data(),
		sizeof(VertexColor), vertices.size());
}
