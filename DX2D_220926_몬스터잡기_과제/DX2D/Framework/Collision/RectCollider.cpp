#include "Framework.h"

RectCollider::RectCollider(Vector2 size)
    :size(size)
{
    type = Type::RECT;

    CreateLine();
}

bool RectCollider::IsPointCollision(Vector2 point)
{
    // 역행렬 - 회전된 Rect 충돌을 체크하기 위함
    Matrix invWorld = XMMatrixInverse(nullptr, world);

    point *= invWorld;

    Vector2 half = size * 0.5f;

    if (abs(point.x) < half.x && abs(point.y) < half.y)
        return true;

    return false;
}

bool RectCollider::IsRectCollision(RectCollider* rect, Vector2* overlap)
{
    if (overlap != nullptr)
        return IsAABB(rect, overlap);
    else
        return IsOBB(rect);
}

bool RectCollider::IsCircleCollision(CircleCollider* circle)
{
    return false;
}

void RectCollider::CreateLine()
{
    Vector2 half = size * 0.5f;

    vertices.emplace_back(-half.x, half.y); // LT
    vertices.emplace_back(half.x, half.y); // RT
    vertices.emplace_back(half.x, - half.y); // RB
    vertices.emplace_back(-half.x, - half.y); // LB
    vertices.emplace_back(-half.x , half.y); // LT

    vertexBuffer = new VertexBuffer(vertices.data(),
        sizeof(VertexPos), vertices.size());
}

bool RectCollider::IsAABB(RectCollider* rect, Vector2* overlap)
{
    float minRight = min(R(), rect->R());
    float maxLeft = max(L(), rect->L());
    float minTop = min(T(), rect->T());
    float maxBottom = max(B(), rect->B());

    Vector2 temp = Vector2(minRight - maxLeft, minTop - maxBottom);

    if (overlap != nullptr)
        *overlap = temp;

    if (temp.x > 0 && temp.y > 0)
        return true;

    return false;
}

bool RectCollider::IsOBB(RectCollider* rect)
{
    return false;
}
