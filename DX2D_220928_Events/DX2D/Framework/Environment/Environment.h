#pragma once

class Environment : public Singleton<Environment>
{
public:
	Environment();
	~Environment();

private:
	void CreateProjection();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateRasterizerState();

private:
	MatrixBuffer* view;
	MatrixBuffer* projection;

	// Texture ����Ҷ� ���
	ID3D11SamplerState* samplerState;
	
	// Alpha ���
	ID3D11BlendState* alphaBlendState;

	// Rasterizer ����:
	// ViewPort ��ȯ, ���� �����Ͽ� ����, !������ ��� ���!
	ID3D11RasterizerState* rasterizerState;
};