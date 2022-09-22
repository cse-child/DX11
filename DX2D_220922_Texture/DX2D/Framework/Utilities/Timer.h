#pragma once

class Timer : public Singleton<Timer>
{
public:
    Timer();
    ~Timer();

    void Update();

    void SetLockFPS(float lockFPS) { this->lockFPS = lockFPS; }

    float GetTimeElapsed() { return timeElapsed; }
    int GetFPS() { return frameRate; }

private:
    float timeScale = 0.0f;
    float timeElapsed = 0.0f;

    __int64 curTime = 0;
    __int64 lastTime = 0;
    __int64 periodFrequency = 0;

    int frameRate = 0;
    int frameCount = 0;

    float oneSecCount = 0.0f;

    float lockFPS = 0.0f;
};