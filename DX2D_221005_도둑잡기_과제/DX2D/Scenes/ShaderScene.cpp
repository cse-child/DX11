#include "Framework.h"
#include "ShaderScene.h"

ShaderScene::ShaderScene()
{
    quad = new Quad(L"Textures/test.jpg");
    quad->Position() = { CENTER_X, CENTER_Y };
    quad->UpdateWorld();

    //quad->SetPixelShader(L"Shaders/PixelGrayscale.hlsl");
    //quad->SetPixelShader(L"Shaders/PixelFilter.hlsl");
    //quad->SetPixelShader(L"Shaders/PixelOutline.hlsl");
    //quad->SetPixelShader(L"Shaders/PixelMulti.hlsl");
    quad->SetPixelShader(L"Shaders/PixelLight.hlsl");

    dog = new Dog();
    dog->SetPixelShader(L"Shaders/PixelCustom.hlsl");
    dog->Position() = { CENTER_X, CENTER_Y };

    //secondMap = Texture::Add(L"Textures/Shooting/pexplosion.png");
    secondMap = Texture::Add(L"Textures/rainbow.png");
    valueBuffer = new IntValueBuffer();
    sizeBuffer = new FloatValueBuffer();

    sizeBuffer->values[0] = quad->Size().x;
    sizeBuffer->values[1] = quad->Size().y;
}

ShaderScene::~ShaderScene()
{
    delete quad;
    delete valueBuffer;
    delete sizeBuffer;
    delete dog;
}

void ShaderScene::Update()
{
    dog->Update();
}

void ShaderScene::Render()
{
    valueBuffer->SetPS(1);
    sizeBuffer->SetPS(2);

    secondMap->PSSet(1);

    quad->Render();
    dog->Render();
}

void ShaderScene::PostRender()
{
    ImGui::SliderInt("Index", &valueBuffer->values[0], 0, 2);
    ImGui::SliderInt("Scale", &valueBuffer->values[1], 0, 300);
    ImGui::SliderInt("RadialScale1", &valueBuffer->values[2], 0, 100);
    ImGui::SliderInt("RadialScale2", &valueBuffer->values[3], 0, 100);
    ImGui::DragFloat2("LightPos", &sizeBuffer->values[2]);

    ImGui::ColorEdit4("Color", (float*)&quad->GetColorBuffer()->Get(), ImGuiColorEditFlags_PickerHueWheel);
}
