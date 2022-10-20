#include "Framework.h"

ImageFont::ImageFont(wstring imageFile, float interval)
    : interval(interval)
{
    quads.resize(MAX_LENGTH);

    for (UINT i = 0; i < MAX_LENGTH; i++)
    {
        quads[i] = new Quad(imageFile, Vector2(), Vector2(0.1f, 1.0f));
        quads[i]->Position().x = i * -quads[i]->Size().x - interval * i;
        quads[i]->SetActive(false);
        quads[i]->SetParent(this);
        quads[i]->SetPixelShader(L"Shaders/PixelImageFont.hlsl");
    }

    fontSize = quads[0]->Size();

    valueBuffer = new IntValueBuffer();
}

ImageFont::~ImageFont()
{
    for (Quad* quad : quads)
        delete quad;

    delete valueBuffer;
}

void ImageFont::Update()
{
    if (!isActive) false;

    strValue = to_string(value);

    float start = 0.0f;
    float intervalSize = interval * (strValue.size() - 1);

    if (strValue.size() > 1)
    {
        switch (alignedType)
        {
        case ImageFont::LEFT:
            start = fontSize.x * strValue.size() + intervalSize;
            break;
        case ImageFont::CENTER:
            start = (fontSize.x * strValue.size() + intervalSize) / 2;
            break;
        case ImageFont::RIGHT:
            start = 0.0f;
            break;
        default:
            break;
        }
    }

    for (UINT i = 0; i < strValue.size(); i++)
    {
        quads[i]->SetActive(strValue.size() > i);
        quads[i]->Position().x = i * -quads[i]->Size().x - interval * i + start;
        quads[i]->UpdateWorld();
    }

    UpdateWorld();
}

void ImageFont::Render()
{
    if (!isActive) return;

    for (UINT i = 0; i < strValue.size(); i++)
    {
        int num = strValue[i] - '0';
        int index = strValue.size() - i - 1;

        valueBuffer->values[0] = num;
        valueBuffer->SetPS(1);

        quads[index]->Render();
    }
}
