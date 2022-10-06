#include "Framework.h"

RectCollider::RectCollider(Vector2 size)
    :size(size)
{
    type = Type::RECT;

    CreateLine();
}

//bool RectCollider::IsPointCollision(Vector2 point)
//{
//    // 역행렬 - 회전된 Rect 충돌을 체크하기 위함
//    Matrix invWorld = XMMatrixInverse(nullptr, world);
//
//    point *= invWorld;
//
//    Vector2 half = size * 0.5f;
//
//    if (abs(point.x) < half.x && abs(point.y) < half.y)
//        return true;
//
//    return false;
//}

/* 내적을 이용한 점 충돌 */
bool RectCollider::IsPointCollision(Vector2 point)
{
    ObbDesc obb = GetObb();

    Vector2 D = obb.position - point;

    float d = abs(Vector2::Dot(D, obb.axis[0]));

    if (d > obb.halfSize.x)
        return false;
    
    d = abs(Vector2::Dot(D, obb.axis[1]));

    if (d > obb.halfSize.y)
        return false;

    return true;
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

RectCollider::ObbDesc RectCollider::GetObb()
{
    obbDesc.position = GlobalPosition();
    obbDesc.halfSize = Size() * 0.5f;

    obbDesc.axis[0] = Right();
    obbDesc.axis[1] = Up();

    return obbDesc;
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
    ObbDesc obbA = GetObb();
    ObbDesc obbB = rect->GetObb();

    if (IsSeparate(obbA.axis[0], obbA, obbB)) return false;
    if (IsSeparate(obbA.axis[1], obbA, obbB)) return false;
    if (IsSeparate(obbB.axis[0], obbA, obbB)) return false;
    if (IsSeparate(obbB.axis[1], obbA, obbB)) return false;

    return true;
}

bool RectCollider::IsSeparate(Vector2 separateAxis, ObbDesc box1, ObbDesc box2)
{
    // Rect의 중점간의 벡터와 분리축과의 내적
    float d = abs(Vector2::Dot(separateAxis, box1.position - box2.position));

    // 벡터와 스칼라의 곱셈
    Vector2 right = box1.axis[0] * box1.halfSize.x;
    Vector2 up = box1.axis[1] * box1.halfSize.y;

    float r1 = abs(Vector2::Dot(separateAxis, right)) + abs(Vector2::Dot(separateAxis, up));

    right = box2.axis[0] * box2.halfSize.x;
    up = box2.axis[1] * box2.halfSize.y;

    float r2 = abs(Vector2::Dot(separateAxis, right)) + abs(Vector2::Dot(separateAxis, up));

    return d > (r1 + r2); // 분리되어있다.
}
