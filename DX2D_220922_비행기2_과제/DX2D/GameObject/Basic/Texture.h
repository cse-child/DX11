#pragma once

class Texture
{
public:
	Texture(wstring file);
	~Texture();

	void Render();

private:
	ID3D11ShaderResourceView* srv;

	ID3D11SamplerState* samplerState;
};