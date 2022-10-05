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

	void SetCamBgSize(Vector2 size) { camBgSize = size; }

private:
	void FreeMode();
	void FollowMode();

private:
	MatrixBuffer* viewBuffer;
	Matrix view;

	float speed = 100.0f;

	Transform* target = nullptr;

	Vector2 targetOffset = Vector2( CENTER_X, CENTER_Y );
	Vector2 camBgSize;
};