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
	void Render();

	void SetEvent(Event event) { this->event = event; }

	Collider* GetCollider() { return collider; }

protected:
	State state = NONE;

	Float4 noneColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	Float4 downColor = { 0.5f, 0.5f, 0.5f, 0.5f };
	Float4 overColor = { 0.9f, 0.9f, 0.9f, 0.9f };

private:
	Collider* collider;

	Event event = nullptr;

	bool isDownCheck = false;
};
