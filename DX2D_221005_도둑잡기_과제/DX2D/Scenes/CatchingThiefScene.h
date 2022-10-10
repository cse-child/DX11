#pragma once

class CatchingThiefScene : public Scene
{
public:
	CatchingThiefScene();
	~CatchingThiefScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Quad* bg;
	Quad* cursor;

	Button* nextTurnBtn;
	Button* sortBtn;
	Button* swapBtn;

	Texture* noneCursor;
	Texture* clickCursor;

};