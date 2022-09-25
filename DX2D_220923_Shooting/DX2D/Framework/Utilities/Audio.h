#pragma once

using namespace FMOD;

class Audio : public Singleton<Audio>
{
private:
	const int MAX_CHANNEL = 20;
	struct SoundInfo
	{
		Sound* sound = nullptr;
		Channel* channel = nullptr;

		~SoundInfo()
		{
			sound->release();
		}
	};

public:
	Audio();
	~Audio();

	// 게임 하다가 사운드가 뚝 끊기면 sound를 Update하지 않은것
	void Update();

	void Add(string key, string file, bool bgm = false, bool loop = false);

	void Play(string key, float volume = 1.0f);
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);

	bool IsPlaySound(string key);

private:
	System* soundSystem;

	unordered_map<string, SoundInfo*> sounds;

};