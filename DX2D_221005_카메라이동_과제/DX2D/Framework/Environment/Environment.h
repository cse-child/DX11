#pragma once

class Environment : public Singleton<Environment>
{
public:
	Environment();
	~Environment();

	Camera* GetMainCamera() { return mainCamera; }

private:
	void CreateProjection();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateRasterizerState();

private:
	Camera* mainCamera; // view 대신에 카메라
	MatrixBuffer* projection;

	// Texture 출력할때 사용
	ID3D11SamplerState* samplerState;
	
	// Alpha 출력
	ID3D11BlendState* alphaBlendState;

	// Rasterizer 역할:
	// ViewPort 변환, 색상 보간하여 적용, !폴리곤 양면 출력!
	ID3D11RasterizerState* rasterizerState;
};