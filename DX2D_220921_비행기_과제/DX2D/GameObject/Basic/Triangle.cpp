#include "Framework.h"

Triangle::Triangle(Float2 pos, float size)
{
	vertexShader = new VertexShader(L"Shaders/VertexColor.hlsl");
	pixelShader = new PixelShader(L"Shaders/PixelColor.hlsl");

	vertices.emplace_back(0, size*1.5, 1, 0, 0);
	vertices.emplace_back(size, 0, 1, 1, 0);
	vertices.emplace_back(-size, 0, 1, 0, 1);

	indices = { 0,1,2 };

	vertexBuffer = new VertexBuffer(vertices.data(),
		sizeof(VertexColor), vertices.size());

	indexBuffer = new IndexBuffer(indices.data(), indices.size());

	worldBuffer = new MatrixBuffer();

	speed = 500.0f;
}

Triangle::~Triangle()
{
	delete vertexShader;
	delete pixelShader;
	delete vertexBuffer;
	delete indexBuffer;
	delete worldBuffer;
}

void Triangle::Update()
{
	Move();
	Fire();
	UpdateWorld();
}

void Triangle::Render()
{
	worldBuffer->Set(world);
	worldBuffer->SetVS(0);

	vertexBuffer->Set();
	indexBuffer->Set();

	vertexShader->Set();
	pixelShader->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void Triangle::SetColor(Float3 color)
{
	for (VertexColor& vertex : vertices)
	{
		vertex.color = Float4(color.x, color.y, color.z, 1.0f);
	}

	vertexBuffer->Update(vertices.data(), vertices.size());
}

void Triangle::Move()
{
	if (KEY_PRESS('W'))
		Position().y += speed * DELTA;
	if (KEY_PRESS('S'))
		Position().y -= speed * DELTA;
	if (KEY_PRESS('A'))
		Position().x -= speed * DELTA;
	if (KEY_PRESS('D'))
		Position().x += speed * DELTA;

	Rotation().z = atan2(mousePos.y - Position().y, mousePos.x - Position().x) - XMConvertToRadians(90);
}

void Triangle::Fire()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 direction = Vector2(mousePos) - Position();

		BulletManager::Get()->Fire(Position(), direction);
	}
}
