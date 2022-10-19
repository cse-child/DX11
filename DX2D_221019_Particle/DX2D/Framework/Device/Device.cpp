#include "Framework.h"

Device::Device()
{
    UINT width = WIN_WIDTH;
    UINT height = WIN_HEIGHT;

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1; 
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
    swapChainDesc.OutputWindow = hWnd; 
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0; 
    swapChainDesc.Windowed = true;

    D3D11CreateDeviceAndSwapChain(
        nullptr, // ���� �߰��� ȭ�� â �����ϴ� Adapter
        D3D_DRIVER_TYPE_HARDWARE, // ���� ����Ʈ��� ����� ��
        0,
        D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT, // ����� �뵵�� ���, dwrite ��Ʈ ���
        nullptr, // ��� ������ ��밡������ �˷������� ���X
        0,
        D3D11_SDK_VERSION, // direct X 11���� ���
        &swapChainDesc,
        &swapChain,
        &device,
        nullptr,
        &deviceContext
    );

    ID3D11Texture2D* backBuffer;

    // uuidof�� backBuffer�� �ڷ����� void�����Ϳ��� �˷���
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
    backBuffer->Release();

    D3D11_VIEWPORT viewPort;
    viewPort.Width = width;
    viewPort.Height = height;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;

    deviceContext->RSSetViewports(1, &viewPort);
}

Device::~Device()
{
    device->Release();
    deviceContext->Release();

    swapChain->Release();
    renderTargetView->Release();
}

void Device::Clear()
{
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    deviceContext->ClearRenderTargetView(renderTargetView, clearColor);

}

void Device::Present()
{
    swapChain->Present(0, 0);
}

void Device::SetRenderTarget()
{
    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
}
