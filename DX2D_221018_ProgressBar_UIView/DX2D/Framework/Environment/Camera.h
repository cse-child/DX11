#pragma once

class Camera : public Transform
{
public:
	Camera();
	~Camera();

	void Update();
	void GUIRender();

	void SetView();

	Vector2 ScreenToWorld(Vector2 pos);
	Vector2 WorldToScreen(Vector2 pos);

	void SetTarget(Transform* target) { this->target = target; }

	void SetLeftBottom(Vector2 leftBottom) { this->leftBottom = leftBottom; }
	void SetRightTop(Vector2 rightTop) { this->rightTop = rightTop; }

private:
	void FreeMode();
	void FollowMode();

	void FixPosition(Vector2& position);

private:
	MatrixBuffer* viewBuffer;
	Matrix view;

	float speed = 100.0f;

	Transform* target = nullptr;

	Vector2 targetOffset = Vector2( CENTER_X, CENTER_Y );
	Vector2 leftBottom;
	Vector2 rightTop = { WIN_WIDTH, WIN_HEIGHT };
};