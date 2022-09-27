#include "Framework.h"
#include "AnimationScene.h"

AnimationScene::AnimationScene()
{
	dog = new Dog();
	dog->Position() = { CENTER_X, CENTER_Y };

	bg = new Quad(L"Textures/BG.png");
	bg->Position() = { CENTER_X, CENTER_Y };
	bg->Size() = { WIN_WIDTH, WIN_HEIGHT };
	bg->UpdateWorld();
}

AnimationScene::~AnimationScene()
{
	delete dog;
	delete bg;
}

void AnimationScene::Update()
{
	dog->Update();
}

void AnimationScene::Render()
{
	bg->Render();
	dog->Render();
}

void AnimationScene::PostRender()
{
	dog->RenderUI();
}
