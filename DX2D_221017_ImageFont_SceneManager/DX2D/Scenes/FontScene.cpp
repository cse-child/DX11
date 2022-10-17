#include "Framework.h"
#include "FontScene.h"

FontScene::FontScene()
{
	imageFont = new ImageFont(L"Textures/number.png");
	imageFont->Position() = { CENTER_X, CENTER_Y };
	imageFont->SetAligned(ImageFont::LEFT);
	/// ���� �ڵ� ��ġ��?!!!!!!!!!!!!!!
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
