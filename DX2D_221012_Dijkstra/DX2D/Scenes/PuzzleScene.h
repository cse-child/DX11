#pragma once

class PuzzleScene : public Scene
{
public:
	PuzzleScene();
	~PuzzleScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

};