#pragma once

// Shader�� ������ ��ü���� ��Ƴ��� ��ȭ������ ����
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
	UINT width, height; // ��ȭ�� ũ��

	ID3D11Texture2D* rtvTexture;
	ID3D11RenderTargetView* rtv; // ����� ���鶧 ����߾���
	ID3D11ShaderResourceView* srv; // Texture���·� GPU�� �ѱ涧 ���
};