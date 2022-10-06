#pragma once

class Texture
{
private:
	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);
	~Texture();
	
public:
	void PSSet(UINT slot = 0);

	Vector2 GetSize()
	{
		return Vector2(image.GetMetadata().width,
			image.GetMetadata().height);
	}

public:
	static Texture* Add(wstring file);
	static Texture* Add(wstring key, ID3D11ShaderResourceView* srv);

	static void Delete();

private:
	ScratchImage image;
	ID3D11ShaderResourceView* srv;

	static unordered_map<wstring, Texture*> textures;
};
