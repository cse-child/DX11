#include "Framework.h"

Dog::Dog()
{
	vertexShader = Shader::AddVS(L"Shaders/VertexUV.hlsl");
	pixelShader = Shader::AddPS(L"Shaders/PixelUV.hlsl");

	worldBuffer = new MatrixBuffer();

	CreateClip();

	localScale *= 0.4f;
}

Dog::~Dog()
{
	for (pair<int, Clip*> clip : clips)
		delete clip.second;
	clips.clear();

	delete worldBuffer;
}

void Dog::Update()
{
	Move();
	Jump();
	Attack();
	SetAnimation();
	
	clips[curAction]->Update();
	UpdateWorld();
}

void Dog::Render()
{
	worldBuffer->Set(world);
	worldBuffer->SetVS(0);

	vertexShader->Set();
	pixelShader->Set();

	clips[curAction]->Render();
}

void Dog::RenderUI()
{
}

void Dog::Move()
{
	if ((KEY_DOWN(VK_LEFT) || KEY_DOWN(VK_RIGHT)) && !isSlide && !isJump)
	{
		SetAction(WALK);
		isRun = true;
	}

	if (KEY_PRESS(VK_LEFT))
	{
		if (KEY_PRESS(VK_CONTROL))
		{
			localPosition.x -= speed * DELTA * 2;
			SetAction(RUN);
		}
		else
		{
			localPosition.x -= speed * DELTA;
		}
	}
	if (KEY_PRESS(VK_RIGHT))
	{
		if (KEY_PRESS(VK_CONTROL))
		{
			localPosition.x += speed * DELTA * 2;
			SetAction(RUN);
		}
		else
		{
			localPosition.x += speed * DELTA;
		}
	}

	if (KEY_UP(VK_LEFT) || KEY_UP(VK_RIGHT))
	{
		SetAction(IDLE);
		isRun = false;
	}

	if (localPosition.x > WIN_WIDTH)
		localPosition.x = 0;
}

void Dog::Jump()
{
	if (KEY_DOWN(VK_UP))
	{
		velocity.y = JUMP_POWER;
		isJump = true;
	}

	velocity.y -= GRAVITY * DELTA;
	localPosition.y += velocity.y * DELTA;
	
	if (localPosition.y - spriteSize.y*0.5f < 0)
	{
		localPosition.y = spriteSize.y * 0.5f;
		velocity.y = 0.0f;
	}
}

void Dog::Attack()
{
	if (KEY_DOWN(VK_SPACE))
	{
		SetAction(SLIDE);
		isSlide = true;
	}
}

void Dog::EndAction()
{
	if (!isRun)
		SetAction(IDLE);
	else
		SetAction(WALK);

	isSlide = false;
	isJump = false;
}

void Dog::SetAnimation()
{
	if (curAction == WALK) return;
	if (curAction == RUN) return;
	if (curAction == SLIDE) return;

	if (velocity.y > 1.0f)
	{
		SetAction(JUMP);
		return;
	}
	else if (velocity.y < -1.0f)
	{
		SetAction(FALL);
		return;
	}

	SetAction(IDLE);
}

void Dog::CreateClip()
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

	clips[SLIDE]->SetEndEvent(bind(&Dog::EndAction, this));
	clips[JUMP]->SetEndEvent(bind(&Dog::EndAction, this));
	clips[FALL]->SetEndEvent(bind(&Dog::EndAction, this));

	clips[curAction]->Play();
}

// file: xmlÆÄÀÏ
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

		spriteSize = { w, h };

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
		clips[curAction]->Play();
	}
}


