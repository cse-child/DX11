#include "Framework.h"

RectCollider::RectCollider(Vector2 size)
    :size(size)
{
    type = Type::RECT;

    CreateLine();
}

/* ������ �̿��� �� �浹 */
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

bool RectCollider::PushCollider(Collider* collider)
{
    if (IsCollision(collider) == false)
        return false;

    Direction dir = GetDirection(collider);

    Transform* object = collider->GetParent();

    switch (dir)
    {
    case GameMath::Direction::UP:
        object->Position() += Up() * PUSH_SPEED * DELTA;
        break;
    case GameMath::Direction::DOWN:
        object->Position() -= Up() * PUSH_SPEED * DELTA;
        break;
    case GameMath::Direction::LEFT:
        object->Position() -= Right() * PUSH_SPEED * DELTA;
        break;
    case GameMath::Direction::RIGHT:
        object->Position() += Right() * PUSH_SPEED * DELTA;
        break;
    }
    return true;
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
    // Rect�� �������� ���Ϳ� �и������ ����
    float d = abs(Vector2::Dot(separateAxis, box1.position - box2.position));

    // ���Ϳ� ��Į���� ����
    Vector2 right = box1.axis[0] * box1.halfSize.x;
    Vector2 up = box1.axis[1] * box1.halfSize.y;

    float r1 = abs(Vector2::Dot(separateAxis, right)) + abs(Vector2::Dot(separateAxis, up));

    right = box2.axis[0] * box2.halfSize.x;
    up = box2.axis[1] * box2.halfSize.y;

    float r2 = abs(Vector2::Dot(separateAxis, right)) + abs(Vector2::Dot(separateAxis, up));

    return d > (r1 + r2); // �и��Ǿ��ִ�.
}

Direction RectCollider::GetDirection(Collider* collider)
{
    if(collider->GlobalPosition() == GlobalPosition())
        return Direction::NONE;

    // GlobalPosition�� ������ �߾ӿ� ��ġ�Ѵٴ� �����Ͽ� ������
    Vector2 leftTop = Vector2(L(), T()) - GlobalPosition();
    Vector2 rightTop = Vector2(R(), T()) - GlobalPosition();

    // �� ��ġ���� �ݶ��̴� ������ ���͸� �����
    Vector2 direction = collider->GlobalPosition() - GlobalPosition();

    // Rect�� �߾ӿ��� �� ���������� ���� ���� ���� �ȿ� direction ���Ͱ� �������� Ȯ��
    float crossLeft = Vector2::Cross(leftTop, direction);
    float crossRight = Vector2::Cross(rightTop, direction);

    // ������ �� ���͸� ���ؼ� ������ ������ Up �Ǵ� Down �浹
    if (crossLeft * crossRight < 0)
    {
        if (collider->GlobalPosition().y < GlobalPosition().y)
            return Direction::DOWN;
        else
            return Direction::UP;
    }
    else // Left �Ǵ� Right �浹
    {
        if (collider->GlobalPosition().x < GlobalPosition().x)
            return Direction::LEFT;
        else
            return Direction::RIGHT;
    }
}
