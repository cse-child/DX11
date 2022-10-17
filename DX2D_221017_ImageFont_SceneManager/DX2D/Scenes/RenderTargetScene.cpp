#include "Framework.h"
#include "RenderTargetScene.h"

RenderTargetScene::RenderTargetScene()
{
	bg = new Quad(L"Textures/test.jpg");
	bg->Resize(Vector2(WIN_WIDTH, WIN_HEIGHT));
	bg->Position() = { CENTER_X, CENTER_Y };
	bg->UpdateWorld();

	dog = new Dog();
	dog->Position() = { CENTER_X, CENTER_Y };

	// 용도
	// 1. 전체화면을 도화지처럼 사용
	// 2. 화면분할에 사용
	renderTarget = new RenderTarget();

	Texture* texture = Texture::Add(L"rt", renderTarget->GetSRV());

	Quad* renderTexture;
	renderTexture = new Quad(Vector2(CENTER_X, CENTER_Y));
	renderTexture->Position() = { CENTER_X / 2, CENTER_Y / 2 };
	renderTexture->UpdateWorld();
	renderTexture->SetTexture(texture);
	renderTextures.push_back(renderTexture);

	renderTexture = new Quad(Vector2(CENTER_X, CENTER_Y));
	renderTexture->Position() = { CENTER_X / 2 * 3, CENTER_Y / 2 };
	renderTexture->UpdateWorld();
	renderTexture->SetTexture(texture);
	renderTexture->SetPixelShader(Shader::AddPS(L"Shaders/PixelGrayScale.hlsl"));
	renderTextures.push_back(renderTexture);
	
	indexBuffer = new IntValueBuffer();
	indexBuffer->values[0] = 1;
}

RenderTargetScene::~RenderTargetScene()
{
	delete bg;
	delete dog;
	
	delete renderTarget;
	
	for (Quad* renderTexture : renderTextures)
		delete renderTexture;

	delete indexBuffer;
}

void RenderTargetScene::Update()
{
	dog->Update();
}

void RenderTargetScene::PreRender()
{
	renderTarget->Set();

	bg->Render();
	dog->Render();
}

void RenderTargetScene::Render()
{
	indexBuffer->SetPS(1);

	for(Quad* renderTexture : renderTextures)
		renderTexture->Render();
}

void RenderTargetScene::PostRender()
{
}
