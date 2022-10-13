#include "Framework.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
	for (pair<string, Effects> effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			delete effect;
		effects.second.clear();
	}
	totalEffect.clear();
}

void EffectManager::Update()
{
	for (pair<string, Effects> effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			effect->Update();
	}
}

void EffectManager::Render()
{
	for (pair<string, Effects> effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			effect->Render();
	}
}

void EffectManager::Add(string key, UINT poolingCount, wstring textureFile, Vector2 maxFrame, float speed, bool isAdditive)
{
	if (totalEffect.count(key) > 0) return;

	Effects effects(poolingCount);

	for (Effect*& effect : effects)
		effect = new Effect(textureFile, maxFrame, speed, isAdditive);

	totalEffect[key] = effects;
}

void EffectManager::Play(string key, Vector2 position)
{
	if (totalEffect.count(key) == 0) return;

	for (Effect* effect : totalEffect[key])
	{
		if (!effect->Active())
		{
			effect->Play(position);
			break;
		}
	}
}
