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

	static float Distance(const Vector2& v1, Vector2& v2)
	{
		return (v1 - v2).Length();
	}
};