#pragma once

class Tile : public Button
{
public:
	enum Type
	{
		BG, OBJ // ���߿��� ����Ǵ°�, ����Ǵ°� ��� �����ؼ� �����
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