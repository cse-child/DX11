#include "Framework.h"

Font::Font()
{
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory), (IUnknown**)&writeFactory);

	D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory);

	IDXGIDevice* dxgiDevice;
	DEVICE->QueryInterface(&dxgiDevice);

	factory->CreateDevice(dxgiDevice, &device);

	device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS,
		&context);

	IDXGISurface* dxgiSurface;
	Device::Get()->GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (void**)&dxgiSurface);

	D2D1_BITMAP_PROPERTIES1 bp;
	bp.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
	bp.dpiX = 96;
	bp.dpiY = 96;
	bp.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	bp.colorContext = nullptr;

	context->CreateBitmapFromDxgiSurface(dxgiSurface, &bp, &targetBitmap);

	context->SetTarget(targetBitmap);
}

Font::~Font()
{
	for (pair<string, ID2D1SolidColorBrush*> brush : brushes)
		brush.second->Release();
	brushes.clear();

	for (pair<string, IDWriteTextFormat*> format : formats)
		format.second->Release();
	formats.clear();

	factory->Release();
	writeFactory->Release();
	targetBitmap->Release();
	context->Release();
	device->Release();
}

void Font::AddColor(string key, Float3 color)
{
	if (brushes.count(key) > 0) return;

	ID2D1SolidColorBrush* brush = nullptr;

	D2D1::ColorF colorF(color.x, color.y, color.z);
	context->CreateSolidColorBrush(colorF, &brush);

	brushes[key] = brush;
}

void Font::AddStyle(string key, wstring font, float size, DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STYLE style, DWRITE_FONT_STRETCH stretch)
{
	if (formats.count(key) > 0) return;

	IDWriteTextFormat* format = nullptr;

	writeFactory->CreateTextFormat(font.c_str(), nullptr,
		weight, style, stretch, size,
		L"ko", &format);

	formats[key] = format;
}

void Font::SetColor(string key)
{
	if (brushes.count(key) == 0) return;

	curBrush = brushes[key];
}

void Font::SetStyle(string key)
{
	if (formats.count(key) == 0) return;

	curFormat = formats[key];
}

void Font::RenderText(wstring text, Float2 pos, Float2 size)
{
	if (size.x == 0 && size.y == 0)
	{
		size.x = text.size() * curFormat->GetFontSize();
		size.y = curFormat->GetFontSize();
	}

	Float2 halfSize = { size.x * 0.5f, size.y * 0.5f };

	// 좌표계가 반대
	pos.y = WIN_HEIGHT - pos.y;

	D2D1_RECT_F rectF;
	rectF.left = pos.x - halfSize.x;
	rectF.right = pos.x + halfSize.x;
	rectF.top = pos.y - halfSize.y;
	rectF.bottom = pos.y + halfSize.y;

	context->DrawTextW(text.c_str(), text.size(),
		curFormat, &rectF, curBrush);
}

void Font::RenderText(string text, Float2 pos, Float2 size)
{
	if (size.x == 0 && size.y == 0)
	{
		size.x = text.size() * curFormat->GetFontSize();
		size.y = curFormat->GetFontSize();
	}

	Float2 halfSize = { size.x * 0.5f, size.y * 0.5f };

	// 좌표계가 반대
	pos.y = WIN_HEIGHT - pos.y;

	D2D1_RECT_F rectF;
	rectF.left = pos.x - halfSize.x;
	rectF.right = pos.x + halfSize.x;
	rectF.top = pos.y - halfSize.y;
	rectF.bottom = pos.y + halfSize.y;

	wstring temp = ToWString(text);

	context->DrawTextW(temp.c_str(), text.size(),
		curFormat, &rectF, curBrush);
}
