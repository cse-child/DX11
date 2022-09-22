﻿#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define CENTER_X (WIN_WIDTH * 0.5f)
#define CENTER_Y (WIN_HEIGHT * 0.5f)

#define KEY_DOWN(k) Keyboard::Get()->Down(k)
#define KEY_UP(k) Keyboard::Get()->Up(k)
#define KEY_PRESS(k) Keyboard::Get()->Press(k)

#define DELTA Timer::Get()->GetTimeElapsed()

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

// ImGui
#include "Libraries/ImGui/imgui.h"
#include "Libraries/ImGui/imgui_impl_dx11.h"
#include "Libraries/ImGui/imgui_impl_win32.h"

#pragma comment(lib, "Libraries/Lib/ImGui.lib")

// DirectXTex
#include "Libraries/DirectXTex/DirectXTex.h"

#pragma comment(lib, "Libraries/Lib/DirectXTex.lib")


using namespace std;
using namespace DirectX;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMMATRIX Matrix;

// Framework Header
#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Keyboard.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/BinaryReader.h"
#include "Framework/Utilities/BinaryWriter.h"

#include "Framework/Device/Device.h"

#include "Framework/Buffer/VertexLayouts.h"
#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/GlobalBuffer.h"

#include "Framework/Shader/VertexShaer.h"
#include "Framework/Shader/PixelShader.h"

#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"

#include "Framework/Environment/Environment.h"

// Object Header
#include "GameObject/Basic/Quad.h"
#include "GameObject/Basic/Texture.h"

#include "GameObject/Shooting/Background.h"
#include "GameObject/Shooting/Bullet.h"
#include "GameObject/Shooting/BulletManager.h"
#include "GameObject/Shooting/Plane.h"

// Scene
#include "Scenes/Scene.h"
#include "System/GameManager.h"

extern HWND hWnd;
extern Float2 mousePos;