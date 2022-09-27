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

	Vector2 Size() { return frames[curFrameNum]->Size();}

	void SetEndEvent(function<void()> Event) { this->Event = Event; }

private:
	vector<Frame*> frames;

	function<void()> Event;

	UINT curFrameNum = 0;

	float frameTime = 0.0f;
	float playTime = 0.0f;
	float speed = 0.0f;

	bool isLoop = false;
	bool isPlay = false;
};