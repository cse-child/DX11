#include "Framework.h"
#include "Math.h"

int GameMath::Random(const int& min, const int& max)
{
    return rand() % (max - min) + min;
}
