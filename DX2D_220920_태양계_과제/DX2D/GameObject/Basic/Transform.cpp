#include "Framework.h"
#include "Transform.h"

Transform::Transform(Float2 position, Float2 scale, float angle)
	:position(position), scale(scale), angle(angle)
{
}

Transform::~Transform()
{
}

void Transform::Set()
{
	Matrix S = XMMatrixScaling(scale.x, scale.y, 1.0f);
	Matrix R = XMMatrixRotationZ(angle);
	Matrix T = XMMatrixTranslation(position.x, position.y, 0.0f);

	world = XMMatrixRotationZ(angle);

	world = S * R * T;
}
