#pragma once

class Transform
{
public:
	Transform();

	void UpdateWorld();
	void RenderUI();

	Matrix& GetWorld() { return world; }
	
	void SetParent(Transform* transform) 
	{
		parent = &transform->GetWorld(); 
	}

	Vector2 Right() { return right.Normalize(); }
	Vector2 Up() { return up.Normalize(); }

	void SetTag(string tag) { this->tag = tag; }

	bool& Active() { return isActive; }
	Vector2& Position() { return localPosition; }
	Float3& Rotation() { return localRotation; }
	Vector2& Scale() { return localScale; }

	Vector2 GlobalPosition() { return globalPosition; }
	Vector2 GlobalScale() { return globalScale; }

protected:
	string tag;

	bool isActive;

	Vector2 localPosition;
	Float3 localRotation;
	Vector2 localScale;

	Matrix world;
	
private:
	Matrix* parent = nullptr;

	Matrix S, R, T;

	Vector2 right, up;

	XMFLOAT4X4 matWorld;

	Vector2 globalPosition;
	Vector2 globalScale;
};