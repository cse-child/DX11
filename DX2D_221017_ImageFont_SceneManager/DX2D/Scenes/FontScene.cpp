#include "Framework.h"
#include "FontScene.h"

FontScene::FontScene()
{
	imageFont = new ImageFont(L"Textures/number.png");
	imageFont->Position() = { CENTER_X, CENTER_Y };
	imageFont->SetAligned(ImageFont::LEFT);
	/// 왼쪽 코드 고치기?!!!!!!!!!!!!!!
}

FontScene::~FontScene()
{
	delete imageFont;
}

void FontScene::Update()
{
	static float time = 0;
	time += DELTA * 1000;

	imageFont->SetValue((UINT)time);
	imageFont->Update();
}

void FontScene::Render()
{
	imageFont->Render();
}

void FontScene::PostRender()
{
}
