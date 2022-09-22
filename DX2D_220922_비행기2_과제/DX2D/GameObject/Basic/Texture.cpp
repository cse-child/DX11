#include "Framework.h"
#include "Texture.h"

Texture::Texture(wstring file)
{
	ScratchImage image;

	LoadFromWICFile(file.c_str(),
		WIC_FLAGS_NONE, nullptr, image);

	CreateShaderResourceView(DEVICE, image.GetImages(),
		image.GetImageCount(), image.GetMetadata(), &srv);
}

Texture::~Texture()
{
	srv->Release();
}

void Texture::Render()
{
	DC->PSSetShaderResources(0, 1, &srv);
}
