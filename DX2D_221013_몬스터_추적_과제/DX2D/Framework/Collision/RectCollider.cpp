#include "Framework.h"

RectCollider::RectCollider(Vector2 size)
    :size(size)
{
    type = Type::RECT;

    CreateLine();
}

/* ������ �̿��� �� �浹 - �и��� �浹 �� */
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
    ObbDesc obb = GetObb();

    Vector2 D = obb.position - circle->GlobalPosition();

    float distanceX = abs(Vector2::Dot(D, obb.axis[0]));
    float distanceY = abs(Vector2::Dot(D, obb.axis[1]));

    if (distanceX > obb.halfSize.x + circle->Radius()) return false;
    if (distanceY > obb.halfSize.y + circle->Radius()) return false;

    // ���� ������ �簢�� �ȿ� ������ �浹O
    if (distanceX < obb.halfSize.x) return true;
    if (distanceY < obb.halfSize.y) return true;

    // ������ �簢������ ���� ����� ���� ��ǥ
    float x = distanceX - obb.halfSize.x;
    float y = distanceY - obb.halfSize.y;
    
    float edgeToCircle = sqrt(x * x + y * y);
    
    return edgeToCircle < circle->Radius();
}

bool RectCollider::PushCollider(Collider* collider)
{
    if (IsCollision(collider) == false)
        return false;
    //  up->down , down->up
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

Vector2 RectCollider::LeftTop()
{
    Vector2 leftTop = {-size.x, size.y };

    return leftTop * world;
}

Vector2 RectCollider::LeftBottom()
{
    Vector2 leftBottom = size * -0.5f;
    
    return leftBottom * world;
}

Vector2 RectCollider::RightTop()
{
    Vector2 rightTop = size * 0.5f;

    return rightTop * world;
}

Vector2 RectCollider::RightBottom()
{
    Vector2 rightBottom = { size.x, -size.y };

    return rightBottom * world;
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
    float minRight = min(RightTop().x, rect->RightTop().x);
    float maxLeft = max(LeftBottom().x, rect->LeftBottom().x);
    float minTop = min(RightTop().y, rect->RightTop().y);
    float maxBottom = max(LeftBottom().y, rect->LeftBottom().y);

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
    Vector2 leftTop = LeftTop() - GlobalPosition();
    Vector2 rightTop = RightTop() - GlobalPosition();

    // �� ��ġ���� �ݶ��̴� ������ ���͸� �����
    Vector2 direction = collider->GlobalPosition() - GlobalPosition();

    // Rect�� �߾ӿ��� �� ���������� ���� ���� ���� �ȿ� direction ���Ͱ� �������� Ȯ��
    float crossLeft = Vector2::Cross(leftTop, direction);
    float crossRight = Vector2::Cross(rightTop, direction);

    // ������ �� ���͸� ���ؼ� ������ ������ Up �Ǵ� Down �浹
    if (crossLeft * crossRight < 0)
    {
        float dot = Vector2::Dot(Up(), direction.Normalize());
        float angle = acos(dot);

        if (abs(angle) < XM_PIDIV2)
            return Direction::UP;
        else
            return Direction::DOWN;
    }
    else // Left �Ǵ� Right �浹
    {
        float dot = Vector2::Dot(Right(), direction.Normalize());
        float angle = acos(dot);

        if (abs(angle) < XM_PIDIV2)
            return Direction::RIGHT;
        else
            return Direction::LEFT;
    }
}
