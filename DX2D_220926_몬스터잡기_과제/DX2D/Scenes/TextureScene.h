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

	// Texture �ҷ����� ����
	// View�� GPU�� ���õ� �ڷ���
	ID3D11ShaderResourceView* srv;

	ID3D11SamplerState* samplerState;
};