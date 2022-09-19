#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	rect = new Rect({ 0, 0 }, { 100, 100 });

	world = new MatrixBuffer();
	view = new MatrixBuffer();
	projection = new MatrixBuffer();

	Matrix orthographic = XMMatrixOrthographicOffCenterLH(
		0.0f, WIN_WIDTH, 0.0f, WIN_HEIGHT, -1.0f, 1.0f);

	projection->Set(orthographic);

	worldMatrix._11 = 1;
	worldMatrix._22 = 1;
	worldMatrix._33 = 1;
	worldMatrix._44 = 1;
}

TutorialScene::~TutorialScene()
{
	delete rect;

	delete world;
	delete view;
	delete projection;
}

void TutorialScene::Update()
{
}

void TutorialScene::Render()
{
	world->SetVS(0);
	view->SetVS(1);
	projection->SetVS(2);

	rect->Render();
}

void TutorialScene::PostRender()
{
}
