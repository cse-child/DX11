#pragma once

class Collider : public Transform
{
protected:
	enum class Type
	{
		RECT, CIRCLE
	};

public:
	Collider();
	~Collider();

	void Render();

	bool IsCollision(Collider* collider);

	virtual bool IsPointCollision(Vector2 point) = 0;
	virtual bool IsRectCollision(class RectCollider* rect, Vector2* overlap = nullptr) = 0;
	virtual bool IsCircleCollision(class CircleCollider* circle) = 0;

	void SetColor(float r, float g, float b) { colorBuffer->Set(r, g, b); }

protected:
	Type type;

	VertexBuffer* vertexBuffer;

	vector<VertexPos> vertices;

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	MatrixBuffer* worldBuffer;
	ColorBuffer* colorBuffer;
};