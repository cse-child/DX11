#pragma once

class Tile : public Button
{
public:
	enum Type
	{
		BG, OBJ // 나중에는 관통되는거, 블락되는거 등등 구분해서 만들기
	};

	struct Data
	{
		wstring textureFile;
		Vector2 pos;
		float angle = -0;
		Type type = BG;
	};

public:
	Tile(Data data);
	~Tile();

	void SetTexture(wstring file);
	void SetAngle(float angle);

	Data GetData() { return data; }

private:
	Data data;
};