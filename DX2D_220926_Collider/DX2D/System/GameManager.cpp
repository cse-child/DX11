#include "Framework.h"

#include "Scenes/TextureScene.h"
#include "Scenes/ShootingScene.h"
#include "Scenes/CollisionScene.h"

GameManager::GameManager()
{
	Create();

	//scene = new TextureScene();
	//scene = new ShootingScene();
	scene = new CollisionScene();
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

	scene->Update();
}

void GameManager::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	scene->Render();

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	ImGui::Text(fps.c_str());

	scene->PostRender();

	// 따로 개념들을 외우고 할 필요는 없고 그냥 이런식으로 쓰는구나 하고 지나가기
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void GameManager::Create()
{
	Keyboard::Get();
	Timer::Get();
	Device::Get();
	Environment::Get();

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
}
