#include "Framework.h"

Environment::Environment()
{
	CreateProjection();
	CreateSamplerState();
	CreateBlendState();
}

Environment::~Environment()
{
	delete view;
	delete projection;
	
	samplerState->Release();
	alphaBlendState->Release();
}

void Environment::CreateProjection()
{
	view = new MatrixBuffer();
	projection = new MatrixBuffer();

	Matrix orthographic = XMMatrixOrthographicOffCenterLH(
		0.0f, WIN_WIDTH, 0.0f, WIN_HEIGHT, -1.0f, 1.0f);

	projection->Set(orthographic);

	view->SetVS(1);
	projection->SetVS(2);
}

void Environment::CreateSamplerState()
{
	// sampler�� descript(����) ����ü
	D3D11_SAMPLER_DESC samplerDesc = {};
	// POINT, LINEAR �ΰ����� ����.
	// POINT : �� ������ ���ؼ� �״�� ����ϴ� ���(2D)
	// LINEAR : �ǻ� ������ ���� ���ȿ���� ������ �ؼ� ���(3D)
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	
	// UV�� �ִ� ������ �Ѿ��� �� ��µǴ� ���
	// WRAP(�Ϲ����?), MIRROR(�ݻ����), CLAMP(���� �� �������� ä���)
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER; // ������� ������? �Ⱦ�(never)
	
	// LOD (Level Of Detail) : ī�޶���� �Ÿ��� ����
	// ����Ƽ�� �ٸ��� ǥ���ϴ� ��� -> ����ȭ ��� �� �ϳ�
	// <3D���� ���� ���>
	// High Polygon Model / Low Polygon Model �ΰ��� �غ��ؼ� �����ؼ� ���
	// �ڵ����� Mesh�� �����ؼ� ���
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	DEVICE->CreateSamplerState(&samplerDesc, &samplerState);

	DC->PSSetSamplers(0, 1, &samplerState);
	
}

void Environment::CreateBlendState()
{
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.RenderTarget[0].BlendEnable = true;

	// Src(Source) : ���� ���ҽ�, ��� ���
	// SRC_ALPHA : ���� �������� ���İ��� ����
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	// Dest(Destination) : ����� �� ���
	// INV_SRC_ALPHA (Inverse SRC~): ���İ��� ����(1-���İ�)�� ����

	// D3D11_BLEND_ONE : 1�� ���ؼ� ����ȿ���� ��
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	// �׸��� �ΰ��� ����
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	// �̷� ���İ� ������� �����ؼ� �پ��� ȿ���� ��Ÿ���⵵ ��.

	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&blendDesc, &alphaBlendState);

	float blendFactor[4] = {};
	// OM(Output Mergy): ���İ� ������ ���������� Render�������ִ� ����
	DC->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
}
