#include "Framework.h"

#include "Scenes/TutorialScene.h"
#include "Scenes/SRTScene.h"
#include "Scenes/SolarSystemScene.h"

GameManager::GameManager()
{
	Create();
	CreateProjection();

	//scene = new TutorialScene();
	//scene = new SRTScene();
	scene = new SolarSystemScene();
}

GameManager::~GameManager()
{
	delete scene;
	delete view;
	delete projection;

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
}

void GameManager::CreateProjection()
{
	view = new MatrixBuffer();
	projection = new MatrixBuffer();

	Matrix orthographic = XMMatrixOrthographicOffCenterLH(
		0.0f, WIN_WIDTH, 0.0f, WIN_HEIGHT, -1.0f, 1.0f);

	projection->Set(orthographic);

	view->SetVS(1);
	projection->SetVS(2);
}
