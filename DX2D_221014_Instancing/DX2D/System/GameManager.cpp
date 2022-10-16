#include "Framework.h"

#include "Scenes/TextureScene.h"
#include "Scenes/ShootingScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/AnimationScene.h"
#include "Scenes/ShaderScene.h"
#include "Scenes/PuzzleScene.h"
#include "Scenes/RenderTargetScene.h"
#include "Scenes/TileScene.h"
#include "Scenes/TankScene.h"
#include "Scenes/DijkstraScene.h"
#include "Scenes/InstancingScene.h"

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
	//scene = new TileScene();
	//scene = new TankScene();
	//scene = new DijkstraScene();
	scene = new InstancingScene();
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

	Font::Get()->GetDC()->BeginDraw(); // Clear

	Device::Get()->SetRenderTarget();

	scene->Render();

	EffectManager::Get()->Render();

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	Font::Get()->RenderText(fps, Vector2(100, WIN_HEIGHT - 20));
	//ImGui::Text(fps.c_str());

	CAM->GUIRender();

	scene->PostRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Font::Get()->GetDC()->EndDraw();

	Device::Get()->Present();
}

void GameManager::Create()
{
	Keyboard::Get();
	Timer::Get();
	Device::Get();
	Environment::Get();
	EffectManager::Get();
	Font::Get();

	Font::Get()->AddColor("White", Float3(1, 1, 1));
	Font::Get()->AddStyle("Default", L"¸¼Àº°íµñ");

	Font::Get()->SetColor("White");
	Font::Get()->SetStyle("Default");

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
	Font::Delete();
}
