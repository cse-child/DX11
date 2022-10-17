#include "Framework.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	for (pair<string, Scene*> scene : scenes)
		delete scene.second;
}

void SceneManager::Update()
{
	for (Scene* scene : curScenes)
		scene->Update();
}

void SceneManager::PreRender()
{
	for (Scene* scene : curScenes)
		scene->PreRender();
}

void SceneManager::Render()
{
	for (Scene* scene : curScenes)
		scene->Render();
}

void SceneManager::PostRender()
{
	for (Scene* scene : curScenes)
		scene->PostRender();
}

void SceneManager::Create(string key, Scene* scene)
{
	if (scenes.count(key) > 0) return;

	scenes[key] = scene;
}

void SceneManager::Add(string key)
{
	if (scenes.count(key) == 0) return;

	for (Scene* scene : curScenes)
	{
		if (scenes[key] == scene)
			return;
	}

	curScenes.push_back(scenes[key]);
	curScenes.back()->Start();

	sort(curScenes.begin(), curScenes.end(), CompareSceneDepth);
}

void SceneManager::Remove(string key)
{
	if (scenes.count(key) == 0) return;

	for (UINT i = 0; i < curScenes.size(); i++)
	{
		if (curScenes[i] == scenes[key])
		{
			scenes[key]->End();
			curScenes.erase(curScenes.begin() + i);
			return;
		}
	}
}
