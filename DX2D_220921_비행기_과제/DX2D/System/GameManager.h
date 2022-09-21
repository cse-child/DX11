#pragma once

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Update();
	void Render();

private:
	void Create();
	void Delete();

	void CreateProjection();

private:
	Scene* scene;

	MatrixBuffer* view;
	MatrixBuffer* projection;
};