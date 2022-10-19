#include "Framework.h"
#include "ParticleScene.h"

ParticleScene::ParticleScene()
{
	wstring file = L"Textures/Particle/enemy_particle0001.png";
	quad = new Quad(file);
	quad->SetVertexShader(L"Shaders/VertexInstancing.hlsl");
	quad->SetPixelShader(L"Shaders/PixelInstancing.hlsl");

	UpdateParticleInfo();

	Start();

	instanceBuffer = new VertexBuffer(instances.data(),
		sizeof(InstanceData), MAX_PARTICLE);
}

ParticleScene::~ParticleScene()
{
	delete quad;
	delete instanceBuffer;
}

void ParticleScene::Update()
{
	Play();
}

void ParticleScene::Render()
{
	instanceBuffer->Set(1);

	quad->SetRender();

	DC->DrawIndexedInstanced(6, instances.size(), 0, 0, 0);
}

void ParticleScene::PostRender()
{
	ImGui::Text("Particle Editor");
	ImGui::SliderInt("ParticleCount", (int*)&particleCount, 1, MAX_PARTICLE);
	ImGui::DragFloat("Duration", &data.duration);
	ImGui::ColorEdit4("StartColor", (float*)&data.startColor);
	ImGui::ColorEdit4("EndColor", (float*)&data.endColor);
	ImGui::SliderFloat2("MinVelocity", (float*)&data.minVelocity, -1, 1);
	ImGui::SliderFloat2("MaxVelocity", (float*)&data.maxVelocity, -1, 1);
	ImGui::SliderFloat2("MinAccelation", (float*)&data.minAccelation, -5, 5);
	ImGui::SliderFloat2("MaxAccelation", (float*)&data.maxAccelation, -5, 5);
	ImGui::SliderFloat("MinAngularVelocity", (float*)&data.minAngularVelocity, -10, data.maxAngularVelocity);
	ImGui::SliderFloat("MaxAngularVelocity", (float*)&data.maxAngularVelocity, data.minAngularVelocity, 10);
	ImGui::SliderFloat("MinSpeed", &data.minSpeed, 1, data.maxSpeed);
	ImGui::SliderFloat("MaxSpeed", &data.maxSpeed, data.minSpeed, 200);
	ImGui::SliderFloat("MinStartTime", &data.minStartTime, 0.0f, data.maxStartTime);
	ImGui::SliderFloat("MaxStartTime", &data.maxStartTime, data.minStartTime, data.duration);
	ImGui::SliderFloat2("MinScale", (float*)&data.minScale, 0.0f, 5.0f);
	ImGui::SliderFloat2("MaxScale", (float*)&data.maxScale, 0.0f, 5.0f);
}

void ParticleScene::Play()
{
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
		Start();
}

void ParticleScene::UpdateParticleInfo()
{
	instances.resize(data.count);
	particleInfos.resize(data.count);
	transforms.resize(data.count);

	color = data.startColor;

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

void ParticleScene::Start()
{
	lifeTime = 0.0f;
	data.count = particleCount;

	for (Transform& transform : transforms)
	{
		transform.Position() = startPos;
		transform.Rotation() = { 0,0,0 };
		transform.Scale() = { 1,1 };
	}
	UpdateParticleInfo();
}
