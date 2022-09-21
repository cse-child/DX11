#pragma once

class PlaneScene : public Scene
{
public:
	PlaneScene();
	~PlaneScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Triangle* plane;

	
};