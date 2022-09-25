#include "Framework.h"
#include "SolarSystemScene.h"

SolarSystemScene::SolarSystemScene()
{
	sun = new Rect({ 0, 0 }, { 100, 100 });
	sun->SetColor(Float3(1, 0.5f, 0));
	sun->Position() = { CENTER_X, CENTER_Y };
	sun->SetTag("Sun");

	earth = new Rect({ 0, 0 }, { 50,50 });
	earth->SetColor(Float3(0, 0.5f, 1));
	earth->Position().x = 250;
	earth->SetParent(sun);
	earth->SetTag("Earth");

	moon = new Rect({ 0, 0 }, { 30, 30 });
	moon->SetColor(Float3(1, 1, 0.7f));
	moon->Position().x = 100;
	moon->SetParent(earth);
	moon->SetTag("Moon");
}

SolarSystemScene::~SolarSystemScene()
{
	delete sun;
	delete earth;
	delete moon;
}

void SolarSystemScene::Update()
{
	sun->Rotation().z += DELTA;
	sun->UpdateWorld();

	earth->Rotation().z += DELTA * 2;
	earth->UpdateWorld();

	moon->Rotation().z -= DELTA;
	moon->UpdateWorld();
}

void SolarSystemScene::Render()
{
	sun->Render();
	earth->Render();
	moon->Render();
}

void SolarSystemScene::PostRender()
{
	sun->RenderUI();
	earth->RenderUI();
	moon->RenderUI();
}
