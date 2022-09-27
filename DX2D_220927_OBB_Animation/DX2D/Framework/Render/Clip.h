#pragma once

class Clip
{
public:
	enum Type
	{
		END, LOOP
	};

private:
	const float UPDATE_TIME = 0.1f;

public:
	Clip(vector<Frame*> frames, bool isLoop = true, float speed = 1.0f);
	~Clip();

	void Update();
	void Render();

	void Play();
	void Stop();

private:
	vector<Frame*> frames;

	UINT curFrameNum = 0;

	float frameTime = 0.0f;
	float playTime = 0.0f;
	float speed = 0.0f;

	bool isLoop = false;
	bool isPlay = false;
};