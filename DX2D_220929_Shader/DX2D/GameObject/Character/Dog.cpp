#include "Framework.h"

Dog::Dog()
{
	LoadAnimations();

	curClip = clips[IDLE];
	curClip->Play();

	//bodyCollider = new RectCollider(curClip->GetCurFrame()->Size());
	bodyCollider = new RectCollider({300,480});
	bodyCollider->Position().x = -20;
	bodyCollider->SetParent(this);

	attackCollider = new RectCollider({ 500,200 });
	attackCollider->Position().x = 100;
	attackCollider->Position().y = -100;
	attackCollider->SetParent(this);
	attackCollider->SetActive(false);

	localScale *= 0.3f;
}

Dog::~Dog()
{
	delete bodyCollider;
	delete attackCollider;
}

void Dog::Update()
{
	Control();
	Move();
	SetMotioin();
	Attack();
	FlickerEffect();

	AnimObject::Update();
	bodyCollider->UpdateWorld();
	attackCollider->UpdateWorld();
}

void Dog::Render()
{
	AnimObject::Render();
	bodyCollider->Render();
	attackCollider->Render();
}

void Dog::RenderUI()
{
}

void Dog::LoadAnimations()
{
	string path = "Textures/Dog/";
	LoadClip(IDLE, path, "Dog_Idle.xml", true);
	LoadClip(WALK, path, "Dog_Walk.xml", true);
	LoadClip(RUN, path, "Dog_Run.xml", true);
	LoadClip(DEAD, path, "Dog_Dead.xml", false);
	LoadClip(FALL, path, "Dog_Fall.xml", false);
	LoadClip(HURT, path, "Dog_Hurt.xml", false);
	LoadClip(JUMP, path, "Dog_Jump.xml", false);
	LoadClip(SLIDE, path, "Dog_Slide.xml", false);

	clips[SLIDE]->SetEvent(bind(&Dog::EndAttack, this));
	clips[SLIDE]->SetEvent(bind(&Dog::OnAttackCollider, this), 3);
	clips[SLIDE]->SetEvent(bind(&Dog::OffAttackCollider, this), 7);
	
	clips[HURT]->SetEvent(bind(&Dog::EndDamage, this));
}

void Dog::Control()
{
	bool isMove = false;

	if (KEY_PRESS('D'))
	{
		velocity.x = 1.0f;
		isMove = true;

		// Rotation으로 양면 출력하는 방법
		//localRotation.y = 0.0f;

		// Scale로 양면 출력하는 방법(Scale을 안건들였을때 가능)
		localScale.x = 0.3f;
	}
	if (KEY_PRESS('A'))
	{
		velocity.x = -1.0f;
		isMove = true;

		//localRotation.y = XM_PI; // y축 뒤집기

		localScale.x = -0.3f;
	}

	if (KEY_PRESS(VK_LSHIFT))
	{
		velocity.x *= 2.0f;
	}

	if (!isMove)
		velocity.x = 0.0f;
}

void Dog::Move()
{
	localPosition += velocity * moveSpeed * DELTA;
}

void Dog::SetMotioin()
{
	if (isAttack) return;
	if (curAction == HURT) return;

	if (abs(velocity.x) >= 2.0f)
		SetAction(RUN);
	else if (abs(velocity.x) >= 1.0f)
		SetAction(WALK);
	else
		SetAction(IDLE);
}

void Dog::Attack()
{
	if (isAttack) return;

	if (KEY_DOWN(VK_LBUTTON))
	{
		isAttack = true;
		SetAction(SLIDE);
	}
}

void Dog::EndAttack()
{
	isAttack = false;
}

void Dog::Damage()
{
	SetAction(HURT);
	SetColor(1, 0.5f, 0.5f);
	isAlphaState = true;
}

void Dog::EndDamage()
{
	SetAction(IDLE);
	SetColor(1, 1, 1);
	isAlphaState = false;
}

void Dog::FlickerEffect()
{
	if (!isAlphaState) return;

	alphaValue += alphaSpeed * DELTA;

	if (alphaValue > 1.0f)
	{
		alphaValue = 1.0f;
		alphaSpeed *= -1.0f;
	}

	if (alphaValue < 0.0f)
	{
		alphaValue = 0.0f;
		alphaSpeed *= -1.0f;
	}

	SetColor(1, 0.7f, 0.7f, alphaValue);
}

void Dog::OnAttackCollider()
{
	attackCollider->SetActive(true);
}

void Dog::OffAttackCollider()
{
	attackCollider->SetActive(false);
}

// file: xml파일
void Dog::LoadClip(ActionType state, string path, string file, bool isLoop, float speed)
{
	tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument();
	document->LoadFile((path + file).c_str());

	tinyxml2::XMLElement* atlas = document->FirstChildElement();
	string fileName = path + atlas->Attribute("imagePath");

	vector<Frame*> frames;
	tinyxml2::XMLElement* sprite = atlas->FirstChildElement();

	while (sprite != nullptr)
	{
		float x, y, w, h;

		x = sprite->FloatAttribute("x");
		y = sprite->FloatAttribute("y");
		w = sprite->FloatAttribute("w");
		h = sprite->FloatAttribute("h");

		frames.push_back(new Frame(ToWString(fileName), x, y, w, h));

		sprite = sprite->NextSiblingElement();
	}

	clips[state] = new Clip(frames, isLoop, speed);

	delete document;
}

void Dog::SetAction(ActionType action)
{
	if (curAction != action)
	{
		curAction = action;
		curClip = clips[curAction];
		curClip->Play();
	}
}
