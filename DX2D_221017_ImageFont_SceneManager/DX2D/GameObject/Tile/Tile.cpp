#include "Framework.h"

Tile::Tile(Data data)
	:Button(data.textureFile), data(data)
{
	localPosition = data.pos;
	localRotation.z = data.angle;
}

Tile::~Tile()
{
}

void Tile::SetTexture(wstring file)
{
	Quad::SetTexture(Texture::Add(file));
	data.textureFile = file;
}

void Tile::SetAngle(float angle)
{
	data.angle = angle;
	localRotation.z = angle;
}
