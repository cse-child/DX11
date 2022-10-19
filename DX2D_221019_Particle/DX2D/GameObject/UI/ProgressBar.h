#pragma once

class ProgressBar : public Quad
{
public:
	ProgressBar(wstring frontImageFile, wstring backImageFile, float maxAmount);
	~ProgressBar();

	void Render();

	void SetAmount(float value);

private:
	FloatValueBuffer* valueBuffer;
	Texture* backImage;

	float maxAmount;

};