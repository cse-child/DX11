#pragma once

class Dog : public AnimObject
{
private:
	enum ActionType
	{
		IDLE, WALK, RUN, DEAD, FALL, HURT, JUMP, SLIDE
	};

public:
	Dog();
	~Dog();

	void Update();
	void Render();
	void RenderUI();

	void Damage();

private:
	void LoadAnimations();
	void Control();
	void Move();
	void SetMotioin();
	void Attack();
	void EndAttack();
	void EndDamage();

	void FlickerEffect();

	void OnAttackCollider();
	void OffAttackCollider();

	void LoadClip(ActionType state, string path, string file,
		bool isLoop, float speed = 1.0f);

	void SetAction(ActionType action);

private:
	Collider* bodyCollider;
	Collider* attackCollider;

	ActionType curAction;

	Vector2 velocity;

	float moveSpeed = 100.0f;
	float alphaSpeed = 100.0f;
	float alphaValue = 1.0f;

	bool isAttack = false;
	bool isAlphaState = false;
};