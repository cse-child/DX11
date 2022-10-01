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
		curFrameNum %= frames.size(); // �迭ũ�⸦ ���ѵ��� ������ ����
	}
	else
	{
		if (curFrameNum >= frames.size())
		{
			curFrameNum--;
			Stop(); // ���� �ȵ��� ������ ���������� ����
		}
	}

	// map�� events[curFrameNum]�ϸ� �̺�Ʈ�� �ֵ���� ������ ��尡 ������
	// ���� count�� ���ؼ� �̺�Ʈ�� �������� ����
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

	if(frameNum >= frames.size()) // index �ʰ���
		frameNum = frames.size() - 1;

	events[frameNum] = event;
}

