#pragma once

class Quad : public Transform
{
public:
	Quad(Vector2 size, Vector2 pos = Vector2());
	~Quad();

	void Render();

	float Left() { return Position().x - size.x * 0.5f; }
	float Right() { return Position().x + size.x * 0.5f; }
	float Top() { return Position().y + size.y * 0.5f; }
	float Bottom() { return Position().y - size.y * 0.5f; }
	
	Vector2 Half() { return Vector2(size.x * 0.5f, size.y * 0.5f); }

	Vector2& Size() { return size; }

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	MatrixBuffer* worldBuffer;

	vector<Vertex> vertices;
	vector<UINT> indices;

	Vector2 size;
};