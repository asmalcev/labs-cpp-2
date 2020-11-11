#include <windows.h>
#include <gdiplus.h>

#include <cstdlib>
#include <iostream>

#define WINDOW_CLASS L"AppClass"

BYTE red = 255, green = 0, blue = 255;
bool flag = false;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	HDC hdc;
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		return 0;

	case WM_LBUTTONDOWN:
		if (flag)
		{
			red = 0;
			green = 255;
			blue = 0;
		}
		else
		{
			red = 255;
			green = 0;
			blue = 255;
		}
		flag = !flag;
		break;

	case WM_PAINT:
		draw(red, green, blue);
		break;

	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
}

void draw(BYTE r, BYTE g, BYTE b)
{
	hdc = BeginPaint(hWnd, &ps);
	WCHAR szTest[10];
	DWORD Version = GetVersion();
	swprintf_s(szTest, 10, L"%d", Version);


	wsprintfW(szBuff, L"WinApi version: %d.%d\0", dwMajorVersion, dwMinorVersion);

	HDC hdc;
	PAINTSTRUCT ps;
	LOGFONT lf;
	HFONT hFont;
	DWORD Version = GetVersion();
	WCHAR szTest[10];
	swprintf_s(szTest, 10, L"%d", Version);

	hdc = BeginPaint(hWnd, &ps);

	lf.lfHeight = 20;
	lf.lfItalic = 1;
	lf.lfStrikeOut = 0;
	lf.lfUnderline = 0;
	lf.lfWidth = 10;
	lf.lfWeight = 40;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfPitchAndFamily = DEFAULT_PITCH;
	lf.lfEscapement = 0;
	hFont = CreateFontIndirect(&lf);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(0, 0, 0));

	TextOut(hdc, 80, 60, L"Malcev A.S. I595", 11);
	TextOut(hdc, 80, 80, L"Version WinAPI:", 15);
	TextOut(hdc, 250, 80, szTest, 10);
	recten(hdc);

	ValidateRect(hWnd, NULL);
	EndPaint(hWnd, &ps);
}

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	MSG msg{};
	HWND hwnd{};
	WNDCLASS wc{sizeof(WNDCLASS)};

	const char *CLASS_NAME = "";
	wc.hInstance = hInstance;
	wc.lpszClassName = WINDOW_CLASS;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProc;
	if (!RegisterClass(&wc))
		return EXIT_FAILURE;

	hwnd = CreateWindow(wc.lpszClassName, "WinAPI 32",
											WS_OVERLAPPEDWINDOW,
											100, 100,
											800, 600,
											nullptr, nullptr, wc.hInstance, nullptr);
	if (hwnd == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}