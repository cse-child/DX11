#include "Framework.h"

ProgressBar::ProgressBar(wstring frontImageFile, wstring backImageFile, float maxAmount)
	:Quad(frontImageFile), maxAmount(maxAmount)
{
	SetPixelShader(L"Shaders/PixelProgressBar.hlsl");

	backImage = Texture::Add(backImageFile);

	valueBuffer = new FloatValueBuffer();
	valueBuffer->values[0] = 1.0f;
}

ProgressBar::~ProgressBar()
{
	delete valueBuffer;
}

void ProgressBar::Render()
{
	valueBuffer->SetPS(1);
	backImage->PSSet(1);

	Quad::Render();
}

void ProgressBar::SetAmount(float value)
{
	valueBuffer->values[0] = value / maxAmount;
}
