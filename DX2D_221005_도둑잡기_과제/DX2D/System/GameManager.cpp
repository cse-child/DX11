#include "Framework.h"

#include "Scenes/TextureScene.h"
#include "Scenes/ShootingScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/AnimationScene.h"
#include "Scenes/ShaderScene.h"
#include "Scenes/PuzzleScene.h"
#include "Scenes/RenderTargetScene.h"
#include "Scenes/CatchingThiefScene.h"

GameManager::GameManager()
{
	Create();

	//scene = new TextureScene();
	//scene = new ShootingScene();
	//scene = new CollisionScene();
	//scene = new AnimationScene();
	//scene = new ShaderScene();
	//scene = new PuzzleScene();
	//scene = new RenderTargetScene();
	scene = new CatchingThiefScene();
}

GameManager::~GameManager()
{
	delete scene;
	
	Delete();
}

void GameManager::Update()
{
	Keyboard::Get()->Update();
	Timer::Get()->Update();
	EffectManager::Get()->Update();

	scene->Update();

	CAM->Update();
}

void GameManager::Render()
{
	scene->PreRender();

	Device::Get()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Device::Get()->SetRenderTarget();

	scene->Render();

	EffectManager::Get()->Render();

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	ImGui::Text(fps.c_str());
	CAM->GUIRender();

	scene->PostRender();

	// 따로 개념들을 외우고 할 필요는 없고 그냥 이런식으로 쓰는구나 하고 지나가기
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::Get()->Present();
}

void GameManager::Create()
{
	Keyboard::Get();
	Timer::Get();
	Device::Get();
	Environment::Get();
	EffectManager::Get();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Delete()
{
	Keyboard::Delete();
	Timer::Delete();
	Device::Delete();
	Environment::Delete();
	Texture::Delete();
	Shader::Delete();
	EffectManager::Delete();
}
