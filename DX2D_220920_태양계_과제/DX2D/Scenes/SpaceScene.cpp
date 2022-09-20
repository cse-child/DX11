#include "Framework.h"
#include "SpaceScene.h"

SpaceScene::SpaceScene()
{
	sun = new Circle({ 0, 0 }, 130, {1,0,1}, { 1,0,0 });
	earth = new Circle({ 0, 0 }, 40, { 0,1,0 }, { 0,0,1 });
	moon = new Circle({ 0, 0 }, 20, { 1,1,1 }, { 0,0,0 });

	sWorld = new Transform({ CENTER_X, CENTER_Y });
	eWorld = new Transform();
	mWorld = new Transform();

	eWorld->Pos().x = 260;
	mWorld->Pos().x = 80;

	worldBuffer = new MatrixBuffer();
}

SpaceScene::~SpaceScene()
{
	delete sun;
	delete earth;
	delete moon;
	delete sWorld;
	delete eWorld;
	delete mWorld;
	delete worldBuffer;
}

void SpaceScene::Update()
{
	sWorld->Angle() += 0.5f * DELTA;
	eWorld->Angle() += DELTA;
	mWorld->Angle() += DELTA;

	sWorld->Set();
	eWorld->Set();
	mWorld->Set();

	eWorld->GetWorld() *= sWorld->GetWorld();
	mWorld->GetWorld() *= eWorld->GetWorld();
}

void SpaceScene::Render()
{
	worldBuffer->Set(sWorld->GetWorld());
	worldBuffer->SetVS(0);
	sun->Render();

	worldBuffer->Set(eWorld->GetWorld());
	worldBuffer->SetVS(0);
	earth->Render();

	worldBuffer->Set(mWorld->GetWorld());
	worldBuffer->SetVS(0);
	moon->Render();
}

void SpaceScene::PostRender()
{
}
