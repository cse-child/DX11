#pragma once

class Triangle : public Transform
{
public:
	Triangle(Float2 pos, float size);
	~Triangle();

	void Update();
	void Render();

	void SetColor(Float3 color);

private:
	void Move();
	void Fire();

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	MatrixBuffer* worldBuffer;

	vector<VertexColor> vertices;
	vector<UINT> indices;

	float speed;
};