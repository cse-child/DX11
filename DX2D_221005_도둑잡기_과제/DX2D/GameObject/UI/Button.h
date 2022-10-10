#pragma once

class Button : public Quad
{
protected:
	enum State
	{
		NONE, DOWN, OVER
	};

public:
	Button(wstring textureFile, bool isCard = false);
	~Button();

	void Update();
	void Render();

	void ButtonColorUpdate();

	void SetEvent(Event event) { this->event = event; }
	void SetObjEvent(ObjEvent event) { objEvent = event; }

	void SetObject(void* object) { this->object = object; }

	Collider* GetCollider() { return collider; }

protected:
	State state = NONE;

	Float4 noneColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	Float4 downColor = { 0.5f, 0.5f, 0.5f, 0.5f };
	Float4 overColor = { 0.9f, 0.9f, 0.9f, 0.9f };

private:
	Collider* collider;

	Event event = nullptr;
	ObjEvent objEvent = nullptr;

	bool isDownCheck = false;

	void* object;
};
