#include "Framework.h"
#include "SRTScene.h"

SRTScene::SRTScene()
// Scale은 사용안해도 1로 초기화
	: scale(1, 1), pivot(-50, 0)
{
	rect = new Rect({ 0, 0 }, { 100, 100 });

	worldBuffer = new MatrixBuffer();

	//world._11 = 1;
	//world._22 = 1;
	//world._33 = 1;
	//world._44 = 1;
	//
	//// 4x4 행렬 중 "41,42,43=(x,y,z)"은 Position에 관여한다.
	//world._41 = CENTER_X;
	//world._42 = CENTER_Y;
}

SRTScene::~SRTScene()
{
	delete rect;
	delete worldBuffer;
}

void SRTScene::Update()
{
	position = mousePos;

	if (KEY_PRESS('W'))
		scale.y += DELTA;
	if (KEY_PRESS('S'))
		scale.y -= DELTA;
	if (KEY_PRESS('A'))
		scale.x -= DELTA;
	if (KEY_PRESS('D'))
		scale.x += DELTA;

	if (KEY_PRESS(VK_UP))
		angle += DELTA;
	if (KEY_PRESS(VK_DOWN))
		angle -= DELTA;

	//world._11 = cos(angle);
	//world._12 = sin(angle);
	//world._21 = -sin(angle);
	//world._22 = cos(angle);

	// 4x4 행렬 중 "11,22,33=(x,y,z)"는 Scale에 관여한다.
	//world._11 = scale.x;
	//world._22 = scale.y;

	// x축 회전 행렬: 22,23,32,33
	// y축 회전 행렬: 11,13,31,33
	// z축 회전 행렬: 11(cos),12(sin),21(-sin),22(cos)

	Matrix S = XMMatrixScaling(scale.x, scale.y, 1.0f);
	Matrix R = XMMatrixRotationZ(angle);
	Matrix T = XMMatrixTranslation(position.x, position.y, 0.0f);
	//Matrix P = XMMatrixTranslation(pivot.x, pivot.y, 0.0f);
	//Matrix IP = XMMatrixInverse(nullptr, P);

	// 순서 중요
	//world = IP * S * R * T * P;
	world = S * R * T;

	angle2 += DELTA;
	world2 = XMMatrixRotationZ(angle2);

	world2 *= world;
}

void SRTScene::Render()
{
	//Matrix temp = XMLoadFloat4x4(&world);
	//worldBuffer->Set(temp);

	worldBuffer->Set(world);

	worldBuffer->SetVS(0);
	rect->Render();

	worldBuffer->Set(world2);
	worldBuffer->SetVS(0);
	rect->Render();
}

void SRTScene::PostRender()
{
}
