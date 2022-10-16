#pragma once

class Clip
{
public:
	enum Type
	{
		END, LOOP
	};

private:
	const float FRAME_PER_SECOND = 10.0f;

public:
	Clip(vector<Frame*> frames, bool isLoop = true, float speed = 1.0f);
	~Clip();

	void Update();
	void Render();

	void Play();
	void Stop();

	void SetEvent(Event event, int frameNum = -1);

	Frame* GetCurFrame() { return frames[curFrameNum]; }

private:
	vector<Frame*> frames;

	map<UINT, Event> events;

	UINT curFrameNum = 0;

	float frameTime = 0.0f;
	float playTime = 0.0f;
	float speed = 0.0f;
	float delayTime = 0.0f;

	bool isLoop = false;
	bool isPlay = false;
};