#include "Framework.h"
#include "DrawShapeScene.h"

DrowShapeScene::DrowShapeScene()
{
	shape = new Shape(0.6f, 10, 0.3f, 0.3f);
	shape2 = new Shape(0.5f, 360, -0.5f, -0.3f);
	shape3 = new Shape(0.3f, 3, -0.3f, 0.6f);
}

DrowShapeScene::~DrowShapeScene()
{
	delete shape;
	delete shape2;
	delete shape3;
}

void DrowShapeScene::Update()
{
}

void DrowShapeScene::Render()
{
	shape->Render();
	shape2->Render();
	shape3->Render();
}

void DrowShapeScene::PostRender()
{
}
