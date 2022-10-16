#pragma once

class Button : public Quad
{
protected:
	enum State
	{
		NONE, DOWN, OVER
	};

public:
	Button(wstring textureFile);
	Button(Vector2 size, Vector2 pos = Vector2());
	~Button();

	void Update();
	void Render();

	void SetEvent(Event event) { this->event = event; }
	void SetObjectEvent(ObjectEvent event) { objectEvent = event; }

	void SetObject(void* object) { this->object = object; }

	Collider* GetCollider() { return collider; }

private:
	Collider* collider;

	State state = NONE;

	Float4 noneColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	Float4 downColor = { 0.5f, 0.5f, 0.5f, 0.5f };
	Float4 overColor = { 0.9f, 0.9f, 0.9f, 0.9f };

	bool isDownCheck = false;

	Event event = nullptr;
	ObjectEvent objectEvent = nullptr;

	void* object;
};
