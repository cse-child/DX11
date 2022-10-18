﻿#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_WIDTH 1200
//#define WIN_WIDTH 1800
#define WIN_HEIGHT 900

#define CENTER_X (WIN_WIDTH * 0.5f)
#define CENTER_Y (WIN_HEIGHT * 0.5f)

#define KEY_DOWN(k) Keyboard::Get()->Down(k)
#define KEY_UP(k) Keyboard::Get()->Up(k)
#define KEY_PRESS(k) Keyboard::Get()->Press(k)

#define DELTA Timer::Get()->GetTimeElapsed()

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

#define CAM Environment::Get()->GetMainCamera()

#define SCENE SceneManager::Get()

#define LERP(s, e, t) (s + (e - s) * t)
#define SLERP(s, e, t) (s + (e - s) * t * t)

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <algorithm>

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

// ImGui
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include <dirent/dirent.h>
#include <ImGuiFileDialog.h>
#include <ImGuiFileDialogConfig.h>

#pragma comment(lib, "Libraries/Lib/ImGui.lib")

// DirectXTex
#include "Libraries/DirectXTex/DirectXTex.h"

#pragma comment(lib, "Libraries/Lib/DirectXTex.lib")

// DirectWrite
#include <d2d1_2.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")


using namespace std;
using namespace DirectX;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMMATRIX Matrix;
typedef function<void()> Event;
typedef function<void(void*)> ObjectEvent;

// Framework Header
#include "Framework/Utilities/Utility.h"

using namespace Utility;

#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Keyboard.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/BinaryReader.h"
#include "Framework/Utilities/BinaryWriter.h"
#include "Framework/Utilities/tinyxml2.h"
#include "Framework/Utilities/Font.h"

#include "Framework/Device/Device.h"

#include "Framework/Buffer/VertexLayouts.h"
#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/GlobalBuffer.h"

#include "Framework/Shader/Shader.h"
#include "Framework/Shader/VertexShaer.h"
#include "Framework/Shader/PixelShader.h"

#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"
#include "Framework/Math/Math.h"

using namespace GameMath;

#include "Framework/Render/Texture.h"
#include "Framework/Render/Frame.h"
#include "Framework/Render/Clip.h"
#include "Framework/Render/RenderTarget.h"

#include "Framework/Collision/Collider.h"
#include "Framework/Collision/CircleCollider.h"
#include "Framework/Collision/RectCollider.h"
#include "Framework/Collision/LineCollider.h"

#include "Framework/Environment/Camera.h"
#include "Framework/Environment/Environment.h"

// Object Header
#include "GameObject/Basic/Quad.h"
#include "GameObject/Basic/AnimObject.h"
#include "GameObject/Basic/Effect.h"

#include "GameObject/UI/Button.h"
#include "GameObject/UI/ImageFont.h"
#include "GameObject/UI/ProgressBar.h"

#include "GameObject/Algorithm/DNode.h"
#include "GameObject/Algorithm/Dijkstra.h"
#include "GameObject/Algorithm/Node.h"
#include "GameObject/Algorithm/Heap.h"
#include "GameObject/Algorithm/AStar.h"

#include "GameObject/Shooting/Plane.h"
#include "GameObject/Shooting/Bullet.h"
#include "GameObject/Shooting/BulletManager.h"

#include "GameObject/Character/Dog.h"

#include "GameObject/Puzzle/Card.h"
#include "GameObject/Puzzle/CardManager.h"

#include "GameObject/Tile/Tile.h"
#include "GameObject/Tile/TileMap.h"
#include "GameObject/Tile/GameTileMap.h"
#include "GameObject/Tile/Tank.h"

#include "GameObject/Manager/EffectManager.h"

// Scene
#include "Scenes/Scene.h"
#include "System/GameManager.h"
#include "System/SceneManager.h"

extern HWND hWnd;
extern Vector2 mousePos;
extern short mouseWheel;