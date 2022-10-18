#pragma once

class Device : public Singleton<Device>
{
public:
	Device();
	~Device();

	void Clear();
	void Present();

	void SetRenderTarget();

	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDeviceContext() { return deviceContext; }

	IDXGISwapChain* GetSwapChain() { return swapChain; }

private:
	ID3D11Device* device;                    // CPU
	ID3D11DeviceContext* deviceContext;      // GPU
	
	IDXGISwapChain* swapChain;               // BackBuffer 包府
	ID3D11RenderTargetView* renderTargetView;// VRAM BackBuffer 皋葛府甫 包府
	
};