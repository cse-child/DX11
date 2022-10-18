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
	
	// �ϳ��� ������Ʈ ��ġ�� �ű� �� ������Ʈ�� ���� ��� ������
	// ��ġ�� �Űܾ��ϴ°��� ������ �ʹ� �����ϱ� ������
	// world��� 4x4�迭�� ���� ������Ʈ�� �������� �ϳ��� ��ü�� ���´�.
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
	worldMatrix._41 = mousePos.x; // _41:world ��Ŀ����� x�ڸ�
	worldMatrix._42 = mousePos.y; // _42:world ��Ŀ����� y�ڸ�

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
