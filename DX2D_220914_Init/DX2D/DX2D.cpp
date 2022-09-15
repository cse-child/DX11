#include "framework.h"
#include "DX2D.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
HWND hWnd;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ID3D11Device* device;                    // CPU
ID3D11DeviceContext* deviceContext;      // GPU

IDXGISwapChain* swapChain;               // BackBuffer 관리
ID3D11RenderTargetView* renderTargetView;// VRAM BackBuffer 메모리를 관리

void InitDevice();
void Render();
void ReleaseDevice();

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DX2D, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DX2D));

    MSG msg = {};

    InitDevice();

    // 게임 종료 메시지가 오면 탈출
    while (msg.message != WM_QUIT)
    {
        // 메시지가 들어왔을때만 처리함
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            Render();
        }
    }
    ReleaseDevice();

    return (int) msg.wParam;
}

void InitDevice()
{
    UINT width = WIN_WIDTH;
    UINT height = WIN_HEIGHT;

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1; // BackBuffer 개수
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // RGB 8비트씩, Unsigned Normal(0~255가 아닌 0~1)
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60; // 사람은 모니터가 1초에 60번이상 깜빡여도 모른다
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    // RefreshRate : 디스플레이 모드 갱신율(주사율 : Numerator / Denominator) -> 프레임과 다른 개념
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Render Target(BackBuffer)의 출력용으로 쓰겠다.
    swapChainDesc.OutputWindow = hWnd; // 만든 윈도우창에 연결
    swapChainDesc.SampleDesc.Count = 1; // 표본을 1개만 두겠다.
    swapChainDesc.SampleDesc.Quality = 0; // 퀄리티가 1이라는 것은 기능이 있지만 사용하지 않는다는 것
    swapChainDesc.Windowed = true; // 창모드 유무

    D3D11CreateDeviceAndSwapChain(
        nullptr, // 게임 중간에 화면 창 조절하는 Adapter
        D3D_DRIVER_TYPE_HARDWARE, // 가상 소프트웨어를 사용할 때
        0,
        D3D11_CREATE_DEVICE_DEBUG, // 디버그 용도로 사용
        nullptr, // 어느 사양까지 사용가능한지 알려주지만 사용X
        0,
        D3D11_SDK_VERSION, // direct X 11버전 사용
        &swapChainDesc,
        &swapChain,
        &device,
        nullptr,
        &deviceContext
    );

    ID3D11Texture2D* backBuffer;

    // uuidof로 backBuffer의 자료형을 void포인터에게 알려줌
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
    backBuffer->Release();

    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
}

void Render()
{
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    // 출력 관련된 일은 모두 deviceContext가 담당
    deviceContext->ClearRenderTargetView(renderTargetView, clearColor);

    // Render

    swapChain->Present(0, 0);
}

void ReleaseDevice()
{
    device->Release();
    deviceContext->Release();

    swapChain->Release();
    renderTargetView->Release();
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DX2D));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DX2D);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   RECT rc = { 0, 0, WIN_WIDTH, WIN_HEIGHT };

   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 
       rc.right - rc.left, rc.bottom - rc.top, 
       nullptr, nullptr, hInstance, nullptr);

   SetMenu(hWnd, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
