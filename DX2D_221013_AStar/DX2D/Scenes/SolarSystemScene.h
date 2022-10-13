#pragma once

class SolarSystemScene : public Scene
{
public:
	SolarSystemScene();
	~SolarSystemScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Rect* sun;
	Rect* earth;
	Rect* moon;
};