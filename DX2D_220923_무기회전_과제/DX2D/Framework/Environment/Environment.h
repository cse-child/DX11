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

	// Texture 출력할때 사용
	ID3D11SamplerState* samplerState;
	
	// Alpha 출력
	ID3D11BlendState* alphaBlendState;
};