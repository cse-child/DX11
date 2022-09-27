#pragma once

class Dog : public Transform
{
private:
	const float JUMP_POWER = 500.0f;
	const float GRAVITY = 700.0f;

	enum ActionType
	{
		IDLE, WALK, RUN, DEAD, FALL, HURT, JUMP, SLIDE
	};

public:
	Dog();
	~Dog();

	void Update();
	void Render();
	void RenderUI();

private:
	void Move();
	void Jump();
	void Attack();

	void EndAction();

	void CreateClip();

	void LoadClip(ActionType state, string path, string file,
		bool isLoop, float speed = 1.0f);

	void SetAction(ActionType action);

	void SetAnimation();

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	MatrixBuffer* worldBuffer;
	
	map<int, Clip*> clips;

	ActionType curAction;

	Vector2 velocity;

	Vector2 spriteSize;

	float speed = 300.0f;

	bool isSlide = false;
	bool isJump = false;
	bool isRun = false;
};