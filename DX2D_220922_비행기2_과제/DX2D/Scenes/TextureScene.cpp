#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	plane = new Plane();
	bg = new Background();
}

TextureScene::~TextureScene()
{
	delete plane;
	delete bg;
}

void TextureScene::Update()
{
	plane->Update();
	bg->Update();
}

void TextureScene::Render()
{
	bg->Render();
	plane->Render();
}

void TextureScene::PostRender()
{
	plane->PostRender();
}
