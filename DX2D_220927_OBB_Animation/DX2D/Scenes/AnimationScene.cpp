#include "Framework.h"
#include "AnimationScene.h"

AnimationScene::AnimationScene()
{
	dog = new Dog();
	dog->Position() = { CENTER_X, CENTER_Y };
}

AnimationScene::~AnimationScene()
{
	delete dog;
}

void AnimationScene::Update()
{
	dog->Update();
}

void AnimationScene::Render()
{
	dog->Render();
}

void AnimationScene::PostRender()
{
	dog->RenderUI();
}
