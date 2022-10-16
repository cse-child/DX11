#pragma once

class TextureScene : public Scene
{
public:
	TextureScene();
	~TextureScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Quad* quad;

	// Texture 불러오는 변수
	// View는 GPU와 관련된 자료형
	ID3D11ShaderResourceView* srv;

	ID3D11SamplerState* samplerState;
};