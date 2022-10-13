#pragma once

class Effect : public Quad
{
private:
	const float FRAME_PER_SECOND = 10.0f;

	class FrameBuffer : public ConstBuffer
	{
	private:
		struct Data
		{
			Vector2 maxFrame;
			Vector2 curFrame;
		};

	public:
		FrameBuffer() : ConstBuffer(&data, sizeof(Data))
		{
		}
	
		void SetMaxFrame(Vector2 frame) { data.maxFrame = frame; }
		Vector2& GetCurFrame() { return data.curFrame; }

	private:
		Data data;
	};


public:
	Effect(wstring textureFile, Vector2 maxFrame, float speed, bool isAdditive);
	~Effect();

	void Update();
	void Render();

	void Play(Vector2 position);
	void End();

private:
	FrameBuffer* frameBuffer;

	float delayTime = 1 / FRAME_PER_SECOND;
	float frameTime = 0.0f;
	float speed = 0.0f;

	UINT curFrameNum = 0;
	UINT maxFrameNum = 0;

	UINT maxFrameX = 0;

	bool isAdditive;
};