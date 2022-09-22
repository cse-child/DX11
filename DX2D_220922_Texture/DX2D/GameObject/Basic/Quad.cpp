#include "Framework.h"

Quad::Quad(Vector2 size, Vector2 pos)
{
	vertexShader = new VertexShader(L"Shaders/VertexUV.hlsl");
	pixelShader = new PixelShader(L"Shaders/PixelUV.hlsl");

	float left = pos.x - size.x * 0.5f;
	float right = pos.x + size.x * 0.5f;
	float top = pos.y + size.y * 0.5f;
	float bottom = pos.y - size.y * 0.5f;

	vertices.emplace_back(left, top, 0, 0);
	vertices.emplace_back(right, top, 1, 0);
	vertices.emplace_back(left, bottom, 0, 1);
	vertices.emplace_back(right, bottom, 1, 1);

	indices = { 0, 1, 2, 2, 1, 3 };

	vertexBuffer = new VertexBuffer(vertices.data(),
		sizeof(Vertex), vertices.size());

	indexBuffer = new IndexBuffer(indices.data(), indices.size());

	worldBuffer = new MatrixBuffer();
}

Quad::~Quad()
{
	delete vertexShader;
	delete pixelShader;
	delete vertexBuffer;
	delete indexBuffer;
	delete worldBuffer;
}

void Quad::Render()
{
	worldBuffer->Set(world);
	worldBuffer->SetVS(0);

	vertexBuffer->Set();
	indexBuffer->Set();

	vertexShader->Set();
	pixelShader->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}