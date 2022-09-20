#pragma once

class SpaceScene : public Scene
{
public:
	SpaceScene();
	~SpaceScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Circle* sun;
	Circle* earth;
	Circle* moon;

	MatrixBuffer* worldBuffer;

	Transform* sWorld;
	Transform* eWorld;
	Transform* mWorld;
};