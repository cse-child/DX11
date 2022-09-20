#include "Framework.h"

Rect::Rect(Float2 pos, Float2 size)
{
	vertexShader = new VertexShader(L"Shaders/VertexColor.hlsl");
	pixelShader = new PixelShader(L"Shaders/PixelColor.hlsl");

	float left = pos.x - size.x * 0.5f;
	float right = pos.x + size.x * 0.5f;
	float top = pos.y + size.y * 0.5f;
	float bottom = pos.y - size.y * 0.5f;

	vertices.emplace_back(left,top, 1, 0, 0);
	vertices.emplace_back(right, top, 0, 1, 0);
	vertices.emplace_back(left, bottom, 0, 0, 1);
	vertices.emplace_back(right, bottom, 1, 1, 0);

	indices = { 0, 1, 2, 2, 1, 3 };

	vertexBuffer = new VertexBuffer(vertices.data(),
		sizeof(VertexColor), vertices.size());

	indexBuffer = new IndexBuffer(indices.data(), indices.size());
}

Rect::~Rect()
{
	delete vertexShader;
	delete pixelShader;
	delete vertexBuffer;
	delete indexBuffer;
}

void Rect::Render()
{
	vertexBuffer->Set();
	indexBuffer->Set();

	vertexShader->Set();
	pixelShader->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}
