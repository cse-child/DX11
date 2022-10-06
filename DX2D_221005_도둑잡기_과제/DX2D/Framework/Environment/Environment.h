#pragma once

class Environment : public Singleton<Environment>
{
public:
	Environment();
	~Environment();

	Camera* GetMainCamera() { return mainCamera; }

	void SetAlphaBlend();
	void SetAdditiveBlend();

private:
	void CreateProjection();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateRasterizerState();

private:
	Camera* mainCamera; // view ��ſ� ī�޶�
	MatrixBuffer* projection;

	// Texture ����Ҷ� ���
	ID3D11SamplerState* samplerState;
	
	// Alpha ���
	ID3D11BlendState* alphaBlendState;
	
	ID3D11BlendState* additiveBlendState;

	// Rasterizer ����:
	// ViewPort ��ȯ, ���� �����Ͽ� ����, !������ ��� ���!
	ID3D11RasterizerState* rasterizerState;
};