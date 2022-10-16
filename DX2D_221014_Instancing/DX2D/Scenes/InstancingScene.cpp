#include "Framework.h"
#include "InstancingScene.h"

InstancingScene::InstancingScene()
{
	//quads.resize(SIZE);

	//for (Quad*& quad : quads)
	//{
	//	quad = new Quad(L"Textures/Tile/Characters/yellow_character.png");
	//	quad->Position().x = Random(0, WIN_WIDTH);
	//	quad->Position().y = Random(0, WIN_HEIGHT);

	//	quad->Scale().x = Random(1.0f, 3.0f);
	//	quad->Scale().y = Random(1.0f, 3.0f);

	//	quad->UpdateWorld();

	//}

	//wstring file = L"Textures/Tile/Characters/yellow_character.png";
	wstring file = L"Textures/items.png";
	quad = new Quad(file, Vector2(), Vector2(0.1f, 0.1f)); // 가로세로 10개중 1번째
	quad->SetVertexShader(L"Shaders/VertexInstancing.hlsl");
	quad->SetPixelShader(L"Shaders/PixelInstancing.hlsl");

	instances.resize(SIZE);

	for (InstanceData& instance : instances)
	{
		Transform transform;

		transform.Position().x = Random(0, WIN_WIDTH);
		transform.Position().y = Random(0, WIN_HEIGHT);
		
		transform.Scale().x = Random(1.0f, 3.0f);
		transform.Scale().y = Random(1.0f, 3.0f);

		transform.Rotation().z = Random(0.0f, XM_2PI);

		transform.UpdateWorld();

		instance.maxFrame = { 10, 10 };
		instance.curFrame.x = Random(0, 8);
		instance.curFrame.y = Random(0, 4);

		instance.transform = XMMatrixTranspose(transform.GetWorld());
	}

	instanceBuffer = new VertexBuffer(instances.data(),
		sizeof(InstanceData), instances.size());

}

InstancingScene::~InstancingScene()
{
	//for (Quad* quad : quads)
	//	delete quad;
	//quads.clear();

	delete quad;
	delete instanceBuffer;
}

void InstancingScene::Update()
{

}

void InstancingScene::Render()
{
	//for (Quad* quad : quads)
	//	quad->Render();

	instanceBuffer->Set(1);

	quad->SetRender();

	// 0,1,2 - 2,1,3
	DC->DrawIndexedInstanced(6, instances.size(), 0, 0, 0); 
}

void InstancingScene::PostRender()
{
}
