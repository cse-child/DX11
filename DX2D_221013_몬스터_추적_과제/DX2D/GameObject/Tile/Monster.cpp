#include "Framework.h"

Monster::Monster()
{
	wstring file = L"Textures/BearTank.png";
	Texture* texture = Texture::Add(file);

	Vector2 cutSize = texture->GetSize() / Vector2(5, 1);

	vector<Frame*> frames;
	frames.push_back(new Frame(file, cutSize.x * 0, cutSize.y, cutSize.x, cutSize.y));
	clips[WAKE_UP] = new Clip(frames);

	frames.clear();
	frames.push_back(new Frame(file, cutSize.x * 1, cutSize.y, cutSize.x, cutSize.y));
	frames.push_back(new Frame(file, cutSize.x * 2, cutSize.y, cutSize.x, cutSize.y));
	frames.push_back(new Frame(file, cutSize.x * 3, cutSize.y, cutSize.x, cutSize.y));
	frames.push_back(new Frame(file, cutSize.x * 4, cutSize.y, cutSize.x, cutSize.y));
	clips[SLEEP] = new Clip(frames, true, 0.4f);

	curClip = clips[1];
	curClip->Play();

	collider = new RectCollider(cutSize);
	collider->SetParent(this);
}

Monster::~Monster()
{
	delete collider;
}

void Monster::Update()
{
	MovePath();

	AnimObject::Update();
	collider->UpdateWorld();
}

void Monster::Render()
{
	AnimObject::Render();
	collider->Render();

	ImGui::Text("Rotation.z : %d",(int)localRotation.z);
}

void Monster::MovePath()
{
	if (path.empty())
	{
		curClip = clips[SLEEP];
		return;
	}

	if (curClip != clips[WAKE_UP]) 
		curClip = clips[WAKE_UP];

	Vector2 direction = path.back() - localPosition;
	localRotation.z = direction.Angle();

	localPosition += Right() * moveSpeed * DELTA;

	if (direction.Length() < 5.0f)
		path.pop_back();
}
