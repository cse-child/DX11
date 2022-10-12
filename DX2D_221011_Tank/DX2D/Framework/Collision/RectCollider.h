#pragma once

class RectCollider : public Collider
{
public:
	struct ObbDesc
	{
		Vector2 position;
		Vector2 axis[2]; // รเ: Up, Right
		Vector2 halfSize;
	};

public:
	RectCollider(Vector2 size);

	virtual bool IsPointCollision(Vector2 point) override;
	virtual bool IsRectCollision(RectCollider* rect, Vector2* overlap) override;
	virtual bool IsCircleCollision(CircleCollider* circle) override;
	
	virtual bool PushCollider(Collider* collider) override;

	ObbDesc GetObb();

	Vector2 Size() { return size * GlobalScale(); }

	float R() { return (GlobalPosition() + Right() * Size().x * 0.5f).x; }
	float L() { return (GlobalPosition() - Right() * Size().x * 0.5f).x; }
	float T() { return (GlobalPosition() + Up() * Size().y * 0.5f).y; }
	float B() { return (GlobalPosition() - Up() * Size().y * 0.5f).y; }

private:
	void CreateLine();

	bool IsAABB(RectCollider* rect, Vector2* overlap);
	bool IsOBB(RectCollider* rect);

	bool IsSeparate(Vector2 separateAxis, ObbDesc box1, ObbDesc box2);

	Direction GetDirection(Collider* collider);

private:
	Vector2 size;

	ObbDesc obbDesc;
};