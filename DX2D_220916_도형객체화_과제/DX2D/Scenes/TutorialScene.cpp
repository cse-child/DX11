#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	vertexShader = new VertexShader(L"Shaders/Tutorial.hlsl");
	pixelShader = new PixelShader(L"Shaders/Tutorial.hlsl");

	vertices.emplace_back(0.5f, 0.5f, 1, 0, 0);
	vertices.emplace_back(-0.5f, -0.5f, 0, 1, 0);
	vertices.emplace_back(-0.5f, 0.5f, 0, 0, 1);

	vertexBuffer = new VertexBuffer(vertices.data(), 
		sizeof(VertexColor), vertices.size());
}

TutorialScene::~TutorialScene()
{
	delete vertexShader;
	delete pixelShader;
	delete vertexBuffer;
}

void TutorialScene::Update()
{
}

void TutorialScene::Render()
{
	vertexBuffer->Set();

	vertexShader->Set();
	pixelShader->Set();

	DC->Draw(vertices.size(), 0);
}

void TutorialScene::PostRender()
{
}
