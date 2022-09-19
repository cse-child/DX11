#pragma once

class DrowShapeScene : public Scene
{
public:
	DrowShapeScene();
	~DrowShapeScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Shape* shape;
	Shape* shape2;
	Shape* shape3;
};