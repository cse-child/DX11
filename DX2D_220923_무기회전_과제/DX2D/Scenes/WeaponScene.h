#pragma once

class WeaponScene : public Scene
{
public:
	WeaponScene();
	~WeaponScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Player* player;
	Gun* gun;
};