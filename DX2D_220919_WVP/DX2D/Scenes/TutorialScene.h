#pragma once

class TutorialScene : public Scene
{
public:
	TutorialScene();
	~TutorialScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Rect* rect;

	MatrixBuffer* world;
	MatrixBuffer* view;
	MatrixBuffer* projection;

	XMFLOAT4X4 worldMatrix;
};