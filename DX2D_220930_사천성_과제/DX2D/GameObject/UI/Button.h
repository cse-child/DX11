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
	~Button();

	void Update();
	void Redner();

	void SetEvent(Event event) { this->event = event; }
	void SetObjEvent(ObjEvent event) { objEvent = event; }

	void ExcuteObjEvent(void* obj) { objEvent(obj); }

	Collider* GetCollider() { return collider; }

private:
	Collider* collider;

	State state = NONE;

	Float4 noneColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	Float4 downColor = { 0.5f, 0.5f, 0.5f, 0.5f };
	//Float4 overColor = { 0.9f, 0.9f, 0.9f, 0.9f };
	Float4 overColor = { 1.0f, 0.0f, 0.0f, 1.0f };
	Float4 selectColor = { 0.0f, 1.0f, 0.0f, 1.0f };

	Event event = nullptr;
	ObjEvent objEvent = nullptr;

	bool isDownCheck = false;

protected:
	bool isSelected = false;
};
