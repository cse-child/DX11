#pragma once

namespace GameMath
{
	enum class Direction
	{
		UP, DOWN, LEFT, RIGHT, NONE
	};

	int Random(const int& min, const int& max);

	float Clamp(const float& min, const float& max, float value);

	Vector2 Lerp(const Vector2& start, const Vector2& end, float t);
}