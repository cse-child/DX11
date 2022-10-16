#pragma once

class ShootingScene : public Scene
{
public:
	ShootingScene();
	~ShootingScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Plane* plane;

	Quad* bg;
	Quad* cursor;
};