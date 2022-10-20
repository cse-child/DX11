#include "Framework.h"

Particle::Particle(string file)
{
	LoadData(file);

	instanceBuffer = new VertexBuffer(instances.data(),
		sizeof(InstanceData), data.count);
}

Particle::~Particle()
{
	delete quad;
	delete instanceBuffer;
}

void Particle::Update()
{
	if (!isPlay) return;

	lifeTime += DELTA;

	color.x = LERP(data.startColor.x, data.endColor.x, lifeTime / data.duration);
	color.y = LERP(data.startColor.y, data.endColor.y, lifeTime / data.duration);
	color.z = LERP(data.startColor.z, data.endColor.z, lifeTime / data.duration);
	color.w = LERP(data.startColor.w, data.endColor.w, lifeTime / data.duration);

	for (UINT i = 0; i < data.count; i++)
	{
		if (particleInfos[i].startTime > lifeTime)
		{
			transforms[i].Scale() = { 0,0 };
			transforms[i].UpdateWorld();
			instances[i].transform = XMMatrixTranspose(transforms[i].GetWorld());
			continue;
		}

		particleInfos[i].velocity += particleInfos[i].accelation * DELTA;
		transforms[i].Position() += particleInfos[i].velocity * particleInfos[i].speed * DELTA;
		transforms[i].Rotation().z += particleInfos[i].angularVelocity * DELTA;
		transforms[i].Scale() = particleInfos[i].scale;
		transforms[i].UpdateWorld();

		instances[i].transform = XMMatrixTranspose(transforms[i].GetWorld());
	}

	quad->GetColorBuffer()->Set(color);
	instanceBuffer->Update(instances.data(), instances.size());

	if (lifeTime > data.duration)
		Stop();

	quad->UpdateWorld();
}

void Particle::Render()
{
	if (!isPlay) return;

	instanceBuffer->Set(1);

	quad->SetRender();

	DC->DrawIndexedInstanced(6, instances.size(), 0, 0, 0);
}

void Particle::Play(Vector2 pos)
{
	quad->Position() = pos;
	UpdateParticleInfo();

	isPlay = true;
}

void Particle::Stop()
{
	isPlay = false;
}

void Particle::LoadData(string file)
{
	BinaryReader* reader = new BinaryReader(file);

	wstring textureFile = reader->WString();
	quad = new Quad(textureFile);
	quad->SetVertexShader(L"Shaders/VertexParticle.hlsl");

	ParticleData* particleData = new ParticleData();
	reader->Byte((void**)&particleData, sizeof(ParticleData));

	data = *particleData;

	instances.resize(data.count);
	particleInfos.resize(data.count);
	transforms.resize(data.count);

	delete reader;
}

void Particle::UpdateParticleInfo()
{
	color = data.startColor;
	lifeTime = 0.0f;

	for (Transform& transform : transforms)
	{
		transform.Position() = { 0,0 };
		transform.Rotation() = { 0,0,0 };
		transform.Scale() = { 1,1 };
	}

	for (ParticleInfo& info : particleInfos)
	{
		info.velocity.x = Random(data.minVelocity.x, data.maxVelocity.x);
		info.velocity.y = Random(data.minVelocity.y, data.maxVelocity.y);
		info.accelation.x = Random(data.minAccelation.x, data.maxAccelation.x);
		info.accelation.y = Random(data.minAccelation.y, data.maxAccelation.y);
		info.angularVelocity = Random(data.minAngularVelocity, data.maxAngularVelocity);
		info.speed = Random(data.minSpeed, data.maxSpeed);
		info.startTime = Random(data.minStartTime, data.maxStartTime);
		info.scale.x = Random(data.minScale.x, data.maxScale.x);
		info.scale.y = Random(data.minScale.y, data.maxScale.y);

		info.velocity = info.velocity.Normalize();
	}
}
