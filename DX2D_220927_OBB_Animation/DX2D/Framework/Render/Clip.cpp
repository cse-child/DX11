#include "Framework.h"

Clip::Clip(vector<Frame*> frames, bool isLoop, float speed)
	:frames(frames), isLoop(isLoop), speed(speed)
{
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

	if (frameTime < UPDATE_TIME) return;

	frameTime -= UPDATE_TIME;

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
