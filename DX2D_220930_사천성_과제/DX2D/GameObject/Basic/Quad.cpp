#include "Framework.h"

Quad::Quad(wstring file, Vector2 startUV, Vector2 endUV, Vector2 pos)
	:startUV(startUV), endUV(endUV)
{
	texture = Texture::Add(file);

	size = texture->GetSize();

	float left = pos.x - size.x * 0.5f;
	float right = pos.x + size.x * 0.5f;
	float top = pos.y + size.y * 0.5f;
	float bottom = pos.y - size.y * 0.5f;

	vertices.emplace_back(left, top, startUV.x, startUV.y);
	vertices.emplace_back(right, top, endUV.x, startUV.y);
	vertices.emplace_back(left, bottom, startUV.x, endUV.y);
	vertices.emplace_back(right, bottom, endUV.x, endUV.y);

	Init();
}

Quad::Quad(Vector2 size, Vector2 pos)
{
	float left = pos.x - size.x * 0.5f;
	float right = pos.x + size.x * 0.5f;
	float top = pos.y + size.y * 0.5f;
	float bottom = pos.y - size.y * 0.5f;

	vertices.emplace_back(left, top, 0, 0);
	vertices.emplace_back(right, top, 1, 0);
	vertices.emplace_back(left, bottom, 0, 1);
	vertices.emplace_back(right, bottom, 1, 1);
	
	Init();
}

Quad::~Quad()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete worldBuffer;
	delete colorBuffer;
	delete valueBuffer;
	delete sizeBuffer;
}

void Quad::Render()
{
	texture->PSSet();

	worldBuffer->Set(world);
	worldBuffer->SetVS(0);

	colorBuffer->SetPS(0);
	valueBuffer->SetPS(1);
	sizeBuffer->SetPS(2);

	vertexBuffer->Set();
	indexBuffer->Set();

	vertexShader->Set();
	pixelShader->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void Quad::SetPixelShader(wstring file)
{
	pixelShader = Shader::AddPS(file);
}

void Quad::Resize(Vector2 size, Vector2 pos)
{
	float left = pos.x - size.x * 0.5f;
	float right = pos.x + size.x * 0.5f;
	float top = pos.y + size.y * 0.5f;
	float bottom = pos.y - size.y * 0.5f;

	vertices.emplace_back(left, top, startUV.x, startUV.y);
	vertices.emplace_back(right, top, endUV.x, startUV.y);
	vertices.emplace_back(left, bottom, startUV.x, endUV.y);
	vertices.emplace_back(right, bottom, endUV.x, endUV.y);

	vertexBuffer->Update(vertices.data(), vertices.size());
}

void Quad::Init()
{
	vertexShader = Shader::AddVS(L"Shaders/VertexUV.hlsl");
	pixelShader = Shader::AddPS(L"Shaders/PixelUV.hlsl");

	vertexBuffer = new VertexBuffer(vertices.data(),
		sizeof(Vertex), vertices.size());

	indices = { 0, 1, 2, 2, 1, 3 };
	indexBuffer = new IndexBuffer(indices.data(), indices.size());

	worldBuffer = new MatrixBuffer();
	colorBuffer = new ColorBuffer();
	valueBuffer = new IntValueBuffer();
	sizeBuffer = new FloatValueBuffer();

	sizeBuffer->values[0] = size.x;
	sizeBuffer->values[1] = size.y;

	valueBuffer->values[0] = 4.0f;
}
