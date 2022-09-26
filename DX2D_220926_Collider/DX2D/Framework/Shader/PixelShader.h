#pragma once

class PixelShader : public Shader
{
public:
	PixelShader(wstring file);
	~PixelShader();

	virtual void Set() override;

private:
	ID3D11PixelShader* pixelShader;
};