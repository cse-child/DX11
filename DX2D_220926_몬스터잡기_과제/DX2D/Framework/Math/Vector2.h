#pragma once

class Vector2 : public Float2
{
public:
	Vector2() : Float2(0, 0) {}
	Vector2(float x, float y) : Float2(x, y) {}
	Vector2(Float2 value) : Float2(value) {}

	Vector2 operator+ (const Vector2& value) const
	{
		return Vector2(x + value.x, y + value.y);
	}
	Vector2 operator- (const Vector2& value) const
	{
		return Vector2(x - value.x, y - value.y);
	}
	Vector2 operator* (const Vector2& value) const
	{
		return Vector2(x * value.x, y * value.y);
	}
	Vector2 operator/ (const Vector2& value) const
	{
		return Vector2(x / value.x, y / value.y);
	}

	Vector2 operator+ (const float& value) const
	{
		return Vector2(x + value, y + value);
	}
	Vector2 operator- (const float& value) const
	{
		return Vector2(x - value, y - value);
	}
	Vector2 operator* (const float& value) const
	{
		return Vector2(x * value, y * value);
	}
	Vector2 operator/ (const float& value) const
	{
		return Vector2(x / value, y / value);
	}

	void operator+= (const Vector2& value)
	{
		x += value.x;
		y += value.y;
	}
	void operator-= (const Vector2& value)
	{
		x -= value.x;
		y -= value.y;
	}
	void operator*= (const Vector2& value)
	{
		x *= value.x;
		y *= value.y;
	}
	void operator/= (const Vector2& value)
	{
		x /= value.x;
		y /= value.y;
	}

	void operator+= (const float& value)
	{
		x += value;
		y += value;
	}
	void operator-= (const float& value)
	{
		x -= value;
		y -= value;
	}
	void operator*= (const float& value)
	{
		x *= value;
		y *= value;
	}
	void operator/= (const float& value)
	{
		x /= value;
		y /= value;
	}

	Vector2 operator* (const Matrix& value) const
	{
		XMVECTOR temp = XMLoadFloat2(this);

		// TransformCoord : w값을 1로 넣고 계산
		// TransformNormal : w값을 0으로 넣고 계산 (벡터를 특정 좌표계로 옮긴다는 개념)
		temp = XMVector2TransformCoord(temp, value);

		Vector2 tempPos;
		XMStoreFloat2(&tempPos, temp);

		return tempPos;
	}

	void operator*= (const Matrix& value)
	{
		XMVECTOR temp = XMLoadFloat2(this);

		temp = XMVector2TransformCoord(temp, value);

		XMStoreFloat2(this, temp);
	}

	float Angle()
	{
		return atan2(y, x);
	}

	float Length() 
	{
		return sqrt(x * x + y * y);
	}

	Vector2 Normalize()
	{
		float length = Length();
		return Vector2(x / length, y / length);
	}

	static float Distance(const Vector2& v1, const Vector2& v2)
	{
		return (v1 - v2).Length();
	}
};