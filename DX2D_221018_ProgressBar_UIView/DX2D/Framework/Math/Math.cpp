#include "Framework.h"
#include "Math.h"

int GameMath::Random(const int& min, const int& max)
{
    return rand() % (max - min) + min;
}

float GameMath::Random(const float& min, const float& max)
{
    float normal = rand() / (float)RAND_MAX;

    return min + (max - min) * normal;
}

float GameMath::Clamp(const float& min, const float& max, float value)
{
    if (value < min)
        value = min;
    if (value > max)
        value = max;
    
    return value;
}

Vector2 GameMath::Lerp(const Vector2& start, const Vector2& end, float t)
{
    t = Clamp(0.0f, 1.0f, t);

    return LERP(start, end, t);
}
