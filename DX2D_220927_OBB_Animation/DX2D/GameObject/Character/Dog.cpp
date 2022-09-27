#include "Framework.h"

Dog::Dog()
{
	vertexShader = Shader::AddVS(L"Shaders/VertexUV.hlsl");
	pixelShader = Shader::AddPS(L"Shaders/PixelUV.hlsl");

	worldBuffer = new MatrixBuffer();

	string path = "Textures/Dog/";
	LoadClip(IDLE, path, "Dog_Idle.xml", true);
	LoadClip(WALK, path, "Dog_Walk.xml", true);
	LoadClip(RUN, path, "Dog_Run.xml", true);
	LoadClip(DEAD, path, "Dog_Dead.xml", false);
	LoadClip(FALL, path, "Dog_Fall.xml", false);
	LoadClip(HURT, path, "Dog_Hurt.xml", false);
	LoadClip(JUMP, path, "Dog_Jump.xml", false);
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
	if (KEY_DOWN('1'))
	{
		SetAction(IDLE);
	}
	if (KEY_DOWN('2'))
	{
		SetAction(WALK);
	}
	if (KEY_DOWN('3'))
	{
		SetAction(RUN);
	}
	if (KEY_DOWN('4'))
	{
		SetAction(DEAD);
	}
	if (KEY_DOWN('5'))
	{
		SetAction(FALL);
	}
	if (KEY_DOWN('6'))
	{
		SetAction(HURT);
	}
	if (KEY_DOWN('7'))
	{
		SetAction(JUMP);
	}

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
