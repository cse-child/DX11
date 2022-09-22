#include "Framework.h"

Background::Background()
	:Texture(L"Textures/Shooting/sky_bg.png")
{
	bgs[0] = new Quad({ WIN_WIDTH, WIN_HEIGHT });
	bgs[0]->Position() = { CENTER_X, CENTER_Y };

	bgs[1] = new Quad({ WIN_WIDTH, WIN_HEIGHT });
	bgs[1]->Position() = { CENTER_X + WIN_WIDTH, CENTER_Y };
}

Background::~Background()
{
	for (Quad* bg : bgs)
		delete bg;
}

void Background::Update()
{
	for (Quad* bg : bgs)
	{
		bg->Position().x -= speed * DELTA;

		if (bg->Right() <= 0)
			bg->Position().x += WIN_WIDTH * 2.0f;
	}

	for (Quad* bg : bgs)
		bg->UpdateWorld();
}

void Background::Render()
{
	Texture::Render();
	for (Quad* bg : bgs)
		bg->Render();
}
