#include "Framework.h"
#include "ShaderScene.h"

ShaderScene::ShaderScene()
{
	quad = new Quad(L"Textures/Shooting/player.png");
	quad->Position() = { CENTER_X, CENTER_Y };
	quad->UpdateWorld();

	//quad->SetPixelShader(L"Shaders/PixelGrayScale.hlsl");
	//quad->SetPixelShader(L"Shaders/PixelFilter.hlsl");
	quad->SetPixelShader(L"Shaders/PixelOutline.hlsl");

	dog = new Dog();
	dog->SetPixelShader(L"Shaders/PixelOutline.hlsl");
	dog->Position() = { CENTER_X, CENTER_Y };
	dog->UpdateWorld();

	valueBuffer = new IntValueBuffer();
	sizeBuffer = new FloatValueBuffer();

	sizeBuffer->values[0] = quad->Size().x;
	sizeBuffer->values[1] = quad->Size().y;
}

ShaderScene::~ShaderScene()
{
	delete quad;
	delete dog;
	delete valueBuffer;
	delete sizeBuffer;
}

void ShaderScene::Update()
{
	dog->Update();
}

void ShaderScene::Render()
{
	valueBuffer->SetPS(1);
	sizeBuffer->SetPS(2);
	
	dog->Render();
	//quad->Render();
}

void ShaderScene::PostRender()
{
	ImGui::SliderInt("Index", & valueBuffer->values[0], 0, 10);
	ImGui::SliderInt("Scale", &valueBuffer->values[1], 0, 100);
	ImGui::SliderInt("RadialScale1", &valueBuffer->values[2], 0, 100);
	ImGui::SliderInt("RadialScale2", &valueBuffer->values[3], 0, 100);
	ImGui::ColorEdit4("Color", (float*)&quad->GetColorBuffer()->Get(), ImGuiColorEditFlags_PickerHueWheel);
}
