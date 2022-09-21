#pragma once

class Vector2 : public Float2
{
public:
	Vector2() : Float2(0, 0) {}
	Vector2(float x, float y) : Float2(x, y) {}
	Vector2(Float2 value) : Float2(value) {}
};