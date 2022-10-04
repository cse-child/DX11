#include "Framework.h"

Transform::Transform()
	:tag("Untagged"), localScale(1,1), isActive(true)
{
	world = XMMatrixIdentity(); // 초기값은 단위행렬로
}

void Transform::UpdateWorld()
{
	S = XMMatrixScaling(localScale.x, localScale.y, 1.0f);
	R = XMMatrixRotationRollPitchYaw(localRotation.x, 
		localRotation.y, localRotation.z);
	T = XMMatrixTranslation(localPosition.x, localPosition.y, 0.0f);
	
	world = S * R * T; // 행렬은 교환법칙이 성립안되기 때문에 순서가 바뀌면 다른 값이 나온다.

	if (parent != nullptr)
		world *= parent->GetWorld();

	XMStoreFloat4x4(&matWorld, world);
	right = Vector2(matWorld._11, matWorld._12);
	up = Vector2(matWorld._21, matWorld._22);

	XMVECTOR outS, outR, outT;
	XMMatrixDecompose(&outS, &outR, &outT, world);

	XMStoreFloat2(&globalPosition, outT);
	XMStoreFloat2(&globalScale, outS);
}

void Transform::RenderUI()
{
	ImGui::Text(tag.c_str());

	string temp = tag + "_Pos";
	ImGui::DragFloat2(temp.c_str(), (float*)&localPosition, 1.0f);
	
	temp = tag + "_Rot";
	Float3 rot;
	rot.x = XMConvertToDegrees(localRotation.x);
	rot.y = XMConvertToDegrees(localRotation.y);
	rot.z = XMConvertToDegrees(localRotation.z);

	ImGui::DragFloat3(temp.c_str(), (float*)&rot, 1.0f, -180, 180);

	localRotation.x = XMConvertToRadians(rot.x);
	localRotation.y = XMConvertToRadians(rot.y);
	localRotation.z = XMConvertToRadians(rot.z);

	temp = tag + "_Scale";
	ImGui::DragFloat2(temp.c_str(), (float*)&localScale, 0.1f);
}

bool Transform::Active()
{
	if (parent != nullptr && !parent->Active())
		return false;
		
	return isActive;
}
