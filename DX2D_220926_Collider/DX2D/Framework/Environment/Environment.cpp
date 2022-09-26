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
	// sampler의 descript(정보) 구조체
	D3D11_SAMPLER_DESC samplerDesc = {};
	// POINT, LINEAR 두가지로 나뉨.
	// POINT : 점 보정을 안해서 그대로 출력하는 방식(2D)
	// LINEAR : 실사 느낌을 위해 계단효과를 보정을 해서 출력(3D)
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	
	// UV가 최대 개수를 넘었을 때 출력되는 방식
	// WRAP(일반출력?), MIRROR(반사출력), CLAMP(제일 끝 색상으로 채우기)
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER; // 어떤식으로 비교할지? 안씀(never)
	
	// LOD (Level Of Detail) : 카메라와의 거리에 따라서
	// 퀄리티를 다르게 표현하는 방법 -> 최적화 방법 중 하나
	// <3D에서 쓰는 방법>
	// High Polygon Model / Low Polygon Model 두개를 준비해서 선택해서 출력
	// 코딩으로 Mesh를 조절해서 출력
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	DEVICE->CreateSamplerState(&samplerDesc, &samplerState);

	DC->PSSetSamplers(0, 1, &samplerState);
	
}

void Environment::CreateBlendState()
{
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.RenderTarget[0].BlendEnable = true;

	// Src(Source) : 원본 리소스, 출력 대상
	// SRC_ALPHA : 원본 데이터의 알파값을 곱함
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	// Dest(Destination) : 출력할 뒷 배경
	// INV_SRC_ALPHA (Inverse SRC~): 알파값의 역순(1-알파값)을 곱함

	// D3D11_BLEND_ONE : 1을 곱해서 광원효과를 냄
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	// 그리고 두개를 더함
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	// 이런 알파값 연산들을 조정해서 다양한 효과를 나타내기도 함.

	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&blendDesc, &alphaBlendState);

	float blendFactor[4] = {};
	// OM(Output Mergy): 알파값 들어갔을때 최종적으로 Render연산해주는 역할
	DC->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
}
