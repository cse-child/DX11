#pragma once

// Shader를 적용할 객체들을 모아놓은 도화지같은 개념
class RenderTarget 
{
public:
	RenderTarget(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	~RenderTarget();

	void Set(Float4 clearColor = Float4(1,1,1,1));

	ID3D11ShaderResourceView* GetSRV() { return srv; }

private:
	void CreateRTVTexture();
	void CreateRTV();
	void CreateSRV();

private:
	UINT width, height; // 도화지 크기

	ID3D11Texture2D* rtvTexture;
	ID3D11RenderTargetView* rtv; // 백버퍼 만들때 사용했었음
	ID3D11ShaderResourceView* srv; // Texture형태로 GPU에 넘길때 사용
};