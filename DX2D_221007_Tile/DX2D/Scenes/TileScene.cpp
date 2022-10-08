#include "Framework.h"
#include "TileScene.h"

TileScene::TileScene()
{
	CreateSample();
	selectSample = new Quad(sampleTileSize);

	tileMap = new TileMap(13, 13);
	tileMap->Position() = { 80, 80 };

	char path[128];
	GetCurrentDirectoryA(sizeof(path), path);
	projectPath = path;
}

TileScene::~TileScene()
{
	for (Button* button : sampleBtns)
		delete button;
	sampleBtns.clear();

	delete tileMap;
	delete selectSample;
}

void TileScene::Update()
{
	// ImGui::GetIO().WantCaptureMouse : ImGui위에 마우스가 올라가있는지 체크
	if (KEY_PRESS(VK_LBUTTON) && !ImGui::GetIO().WantCaptureMouse)
	{
		if (selectSampleFile.length() > 0)
			tileMap->ClickTile(selectSample, Tile::BG);
	}

	if (KEY_DOWN(VK_F1))
		tileMap->Save("TextData/TestTileMap.map");

	if (KEY_DOWN(VK_F2))
		tileMap->Load("TextData/TestTileMap.map");

	for (Button* button : sampleBtns)
		button->Update();

	tileMap->Update();

	if (selectSampleFile.length() > 0)
	{
		if (mouseWheel > 0)
		{
			selectSample->Rotation().z += XM_PIDIV2; // +90도
			if (selectSample->Rotation().z > XM_2PI) // 360도 넘으면 원점
				selectSample->Rotation().z -= XM_2PI;
			mouseWheel = 0;
		}
		else if (mouseWheel < 0)
		{
			selectSample->Rotation().z -= XM_PIDIV2; // -90도
			if (selectSample->Rotation().z < 0)
				selectSample->Rotation().z += XM_2PI;
			mouseWheel = 0;
		}

		selectSample->Position() = mousePos;
		selectSample->UpdateWorld();
	}
}

void TileScene::Render()
{
	for (Button* button : sampleBtns)
		button->Render();

	tileMap->Render();

	if(selectSampleFile.length() > 0)
		selectSample->Render();
}

void TileScene::PostRender()
{
	Save();
	Load();
}

void TileScene::ClickSampleBtn(void* sampleBtn)
{
	Button* button = (Button*)sampleBtn;

	selectSampleFile = button->GetFile();
	selectSample->SetTexture(Texture::Add(selectSampleFile));
	selectSample->Rotation().z = 0.0f;
}

void TileScene::CreateSample()
{
	HANDLE handle;

	WIN32_FIND_DATA findData;
	handle = FindFirstFile(L"Textures/Tile/*.png", &findData);

	bool result = true;
	wstring fileName;

	UINT width = 7;

	Vector2 size = sampleTileSize;

	Vector2 startPos(WIN_WIDTH - size.x, WIN_HEIGHT - size.y);

	while (result)
	{
		fileName = L"Textures/Tile/";
		fileName += findData.cFileName;
		result = FindNextFile(handle, &findData);

		UINT index = sampleBtns.size();

		Vector2 pos(index % width, index / width);

		Button* button = new Button(size);
		button->SetTexture(Texture::Add(fileName));
		button->Position() = startPos - (pos * size);
		button->SetObject(button);
		button->SetObjectEvent(bind(&TileScene::ClickSampleBtn, this, placeholders::_1));

		sampleBtns.push_back(button);
	}

}

void TileScene::Save()
{
	if (ImGui::Button("Save"))
		ImGuiFileDialog::Instance()->OpenDialog("Save", "SaveFile", ".map", ".");

	if (ImGuiFileDialog::Instance()->Display("Save"))
	{
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			string file = ImGuiFileDialog::Instance()->GetFilePathName();
			file = file.substr(projectPath.size() + 1, file.length());

			tileMap->Save(file);
		}

		ImGuiFileDialog::Instance()->Close();
	}
}

void TileScene::Load()
{
	if (ImGui::Button("Load"))
		ImGuiFileDialog::Instance()->OpenDialog("Load", "LoadFile", ".map", ".");

	if (ImGuiFileDialog::Instance()->Display("Load"))
	{
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			string file = ImGuiFileDialog::Instance()->GetFilePathName();
			file = file.substr(projectPath.size() + 1, file.length());

			tileMap->Load(file);
		}

		ImGuiFileDialog::Instance()->Close();
	}
}
