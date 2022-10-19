#include "Framework.h"

Clip::Clip(vector<Frame*> frames, bool isLoop, float speed)
	:frames(frames), isLoop(isLoop), speed(speed)
{
	delayTime = 1.0f / FRAME_PER_SECOND;
}

Clip::~Clip()
{
	for (Frame* frame : frames)
		delete frame;
	frames.clear();
}

void Clip::Update()
{
	if (!isPlay) return;

	frameTime += DELTA * speed;
	playTime += DELTA * speed;

	if (frameTime < delayTime) return;

	frameTime -= delayTime;

	curFrameNum++;

	if (isLoop)
	{
		curFrameNum %= frames.size(); // 배열크기를 못넘도록 나머지 연산
	}
	else
	{
		if (curFrameNum >= frames.size())
		{
			curFrameNum--;
			Stop(); // 루프 안돌면 마지막 프레임으로 고정
		}
	}

	// map은 events[curFrameNum]하면 이벤트가 있든없든 무조건 노드가 생성됨
	// 따라서 count로 비교해서 이벤트가 있을때만 실행
	if (events.count(curFrameNum) > 0)
	{
		events[curFrameNum]();
	}
}

void Clip::Render()
{
	frames[curFrameNum]->Render();
}

void Clip::Play()
{
	isPlay = true;
	frameTime = 0.0f;
	playTime = 0.0f;
	curFrameNum = 0.0f;
}

void Clip::Stop()
{
	isPlay = false;
}

void Clip::SetEvent(Event event, int frameNum)
{
	if (frameNum == -1)
		frameNum = frames.size() - 1;

	if(frameNum >= frames.size()) // index 초과시
		frameNum = frames.size() - 1;

	events[frameNum] = event;
}

