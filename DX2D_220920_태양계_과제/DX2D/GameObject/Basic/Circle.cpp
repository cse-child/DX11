#include "Framework.h"
#include "Circle.h"

Circle::Circle(Float2 pos, float size, Float3 color, Float3 color2)
{
	vertexShader = new VertexShader(L"Shaders/VertexColor.hlsl");
	pixelShader = new PixelShader(L"Shaders/PixelColor.hlsl");

	vertices.emplace_back(pos.x, pos.y, color.x, color.y, color.z);
	for (UINT i = 0; i <= 350; i++)
	{
		vertices.emplace_back(cosf(i * XM_PI / 180) * size + pos.x, -sinf(i * XM_PI / 180) * size + pos.y, color2.x, color2.y, color2.z);
	}

	for (UINT i = 1; i < vertices.size()-1; i++)
	{
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i+1);
	}

	vertexBuffer = new VertexBuffer(vertices.data(),
		sizeof(VertexColor), vertices.size());

	indexBuffer = new IndexBuffer(indices.data(), indices.size());
}

Circle::~Circle()
{
	delete vertexShader;
	delete pixelShader;
	delete vertexBuffer;
	delete indexBuffer;
}

void Circle::Render()
{
	vertexBuffer->Set();
	indexBuffer->Set();

	vertexShader->Set();
	pixelShader->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}
