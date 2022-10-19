#pragma once

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();

	void Update();
	void PreRender();
	void Render();
	void PostRender();

	void Create(string key, Scene* scene);

	void Add(string key);
	void Remove(string key);

	static int CompareSceneDepth(Scene* scene1, Scene* scene2)
	{
		return scene1->GetDepth() < scene2->GetDepth();
	}

private:
	map<string, Scene*> scenes;

	vector<Scene*> curScenes;
};