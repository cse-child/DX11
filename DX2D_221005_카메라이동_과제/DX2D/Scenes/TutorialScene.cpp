#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	rects.push_back(new Rect({0, 0}, {100, 100}));
	rects.push_back(new Rect({300, 300}, {300, 300}));

	world = new MatrixBuffer();
	world2 = new MatrixBuffer();
	view = new MatrixBuffer();
	projection = new MatrixBuffer();

	Matrix orthographic = XMMatrixOrthographicOffCenterLH(
		0.0f, WIN_WIDTH, 0.0f, WIN_HEIGHT, -1.0f, 1.0f);

	projection->Set(orthographic);

	// (x,y,z,1) 
	worldMatrix._11 = 1;
	worldMatrix._22 = 1;
	worldMatrix._33 = 1;
	worldMatrix._44 = 1;

	viewMatrix._11 = 1;
	viewMatrix._22 = 1;
	viewMatrix._33 = 1;
	viewMatrix._44 = 1;
	
	// 하나의 오브젝트 위치를 옮길 때 오브젝트에 속한 모든 정점의
	// 위치를 옮겨야하는것은 연산이 너무 복잡하기 때문에
	// world라는 4x4배열을 만들어서 오브젝트의 정점들을 하나의 객체로 묶는다.
}

TutorialScene::~TutorialScene()
{
	for(Rect* rect : rects)
		delete rect;

	delete world;
	delete view;
	delete projection;
}

void TutorialScene::Update()
{
	worldMatrix._41 = mousePos.x; // _41:world 행렬에서의 x자리
	worldMatrix._42 = mousePos.y; // _42:world 행렬에서의 y자리

	if (KEY_PRESS('W'))
		viewMatrix._42 += 100 * DELTA;
	if (KEY_PRESS('S'))
		viewMatrix._42 -= 100 * DELTA;
	if (KEY_PRESS('A'))
		viewMatrix._41 -= 100 * DELTA;
	if (KEY_PRESS('D'))
		viewMatrix._41 += 100 * DELTA;

	Matrix temp = XMLoadFloat4x4(&worldMatrix);
	world->Set(temp);

	temp = XMLoadFloat4x4(&viewMatrix);
	view->Set(temp);
}

void TutorialScene::Render()
{
	world->SetVS(0);
	view->SetVS(1);
	projection->SetVS(2);

	rects[0]->Render();

	world2->SetVS(0);
	rects[1]->Render();
}

void TutorialScene::PostRender()
{
}
