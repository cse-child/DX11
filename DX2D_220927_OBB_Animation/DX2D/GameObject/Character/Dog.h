#pragma once

class Dog : public Transform
{
private:
	enum ActionType
	{
		IDLE, WALK, RUN, DEAD, FALL, HURT, JUMP
	};

public:
	Dog();
	~Dog();

	void Update();
	void Render();
	void RenderUI();

private:
	void LoadClip(ActionType state, string path, string file,
		bool isLoop, float speed = 1.0f);

	void SetAction(ActionType action);

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	MatrixBuffer* worldBuffer;
	
	map<int, Clip*> clips;

	ActionType curAction;
};