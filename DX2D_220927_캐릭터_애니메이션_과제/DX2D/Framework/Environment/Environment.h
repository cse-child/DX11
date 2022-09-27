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

private:
	MatrixBuffer* view;
	MatrixBuffer* projection;

	// Texture ����Ҷ� ���
	ID3D11SamplerState* samplerState;
	
	// Alpha ���
	ID3D11BlendState* alphaBlendState;
};