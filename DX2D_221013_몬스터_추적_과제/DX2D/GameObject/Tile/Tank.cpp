#include "Framework.h"

Tank::Tank()
{
	wstring file = L"Textures/tank.png";
	Texture* texture = Texture::Add(file);

	Vector2 cutSize = texture->GetSize() / Vector2(8, 4);

	vector<Frame*> frames;
	frames.push_back(new Frame(file, cutSize.x * 0, cutSize.y * 2, cutSize.x, cutSize.y));
	frames.push_back(new Frame(file, cutSize.x * 1, cutSize.y * 2, cutSize.x, cutSize.y));
	frames.push_back(new Frame(file, cutSize.x * 2, cutSize.y * 2, cutSize.x, cutSize.y));
	frames.push_back(new Frame(file, cutSize.x * 3, cutSize.y * 2, cutSize.x, cutSize.y));
	frames.push_back(new Frame(file, cutSize.x * 4, cutSize.y * 2, cutSize.x, cutSize.y));
	frames.push_back(new Frame(file, cutSize.x * 5, cutSize.y * 2, cutSize.x, cutSize.y));
	frames.push_back(new Frame(file, cutSize.x * 6, cutSize.y * 2, cutSize.x, cutSize.y));
	frames.push_back(new Frame(file, cutSize.x * 7, cutSize.y * 2, cutSize.x, cutSize.y));
	clips[0] = new Clip(frames);

	curClip = clips[0];
	curClip->Stop();

	collider = new RectCollider(cutSize);
	collider->SetParent(this);
}

Tank::~Tank()
{
	delete collider;
}

void Tank::Update()
{
	if (!isActive) return;

	Control();
	MovePath();

	AnimObject::Update();
	collider->UpdateWorld();
}

void Tank::Render()
{
	if (!isActive) return;
	AnimObject::Render();
	collider->Render();
}

void Tank::Control()
{
	if (KEY_PRESS('W'))
	{
		localPosition += Right() * moveSpeed * DELTA;
	}
	if (KEY_PRESS('S'))
	{
		localPosition -= Right() * moveSpeed * DELTA;
	}
	if (KEY_PRESS('A'))
	{
		localRotation.z += rotSpeed * DELTA;
	}
	if (KEY_PRESS('D'))
	{
		localRotation.z -= rotSpeed * DELTA;
	}
}

void Tank::MovePath()
{
	if (path.empty())
	{
		curClip->Stop();
		return;
	}

	// 攀农->格利瘤 规氢狼 氦磐 积己
	Vector2 direction = path.back() - localPosition;
	localRotation.z = direction.Angle();

	localPosition += Right() * moveSpeed * DELTA;

	if (direction.Length() < 5.0f)
		path.pop_back();
}
