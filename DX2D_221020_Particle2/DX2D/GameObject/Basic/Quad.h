#pragma once

class Quad : public Transform
{
public:
	Quad(wstring file, Vector2 startUV = Vector2(0, 0),
		Vector2 endUV = Vector2(1, 1), Vector2 pos = Vector2());
	Quad(Vector2 size, Vector2 pos = Vector2());
	~Quad();

	void Render();

	void SetRender();

	void SetTexture(Texture* texture) { this->texture = texture; }

	void SetVertexShader(wstring file);
	void SetPixelShader(wstring file);
	void SetPixelShader(PixelShader* shader) { pixelShader = shader; }

	//Vector2 Size() { return texture->GetSize(); }
	Vector2 Size() { return size; }
	wstring GetFile() { return texture->GetFile(); }
	
	Texture* GetTexture() { return texture; }
	ColorBuffer* GetColorBuffer() { return colorBuffer; }

	void Resize(Vector2 size, Vector2 pos = Vector2());

private:
	void Init();

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	MatrixBuffer* worldBuffer;
	ColorBuffer* colorBuffer;

	vector<Vertex> vertices;
	vector<UINT> indices;

	Vector2 startUV = Vector2();
	Vector2 endUV = Vector2(1, 1);

protected:
	Texture* texture;

	Vector2 size;
};