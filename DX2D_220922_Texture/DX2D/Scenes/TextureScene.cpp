#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	quad = new Quad({ 200, 200 });
	quad->Position() = { CENTER_X, CENTER_Y };

	ScratchImage image;
	// WICFile: png, jpg ó�� ���� ���� ����
	LoadFromWICFile(L"Textures/Shooting/player.png",
		WIC_FLAGS_NONE, nullptr, image);

	// SRV �Ҵ��ϱ�
	CreateShaderResourceView(DEVICE, image.GetImages(),
		image.GetImageCount(), image.GetMetadata(), &srv);
}

TextureScene::~TextureScene()
{
	delete quad;
	
	srv->Release();
}

void TextureScene::Update()
{
	quad->UpdateWorld();
}

void TextureScene::Render()
{
	DC->PSSetShaderResources(0, 1, &srv);
	quad->Render();
}

void TextureScene::PostRender()
{
	quad->RenderUI();
}
