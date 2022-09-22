#pragma once

class Quad : public Transform
{
public:
	Quad(Vector2 size, Vector2 pos = Vector2());
	~Quad();

	void Render();

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	MatrixBuffer* worldBuffer;

	vector<Vertex> vertices;
	vector<UINT> indices;
};