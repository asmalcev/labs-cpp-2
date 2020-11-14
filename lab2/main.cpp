#include <Windows.h>
#include <wingdi.h>
#include <sstream>
#include <gdiplus.h>

int color = 0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMSG, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (uMSG)
	{
	case WM_CREATE:
	{
		std::stringstream ss;
		DWORD version = GetVersion();

		ss << "Made by Malcev Alexander I595 WinApi Version: ";
		ss << version;
		CreateWindow(
				TEXT("STATIC"),
				TEXT(ss.str().c_str()),
				WS_VISIBLE | WS_CHILD,
				90, 32, 230, 32, hwnd, nullptr, nullptr, nullptr);
	}
	break;

	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		Gdiplus::Graphics gf(hdc);
		Gdiplus::SolidBrush brush(Gdiplus::Color(255, color, color, color));

		gf.FillRectangle(&brush, 168, 200, 64, 64);
		EndPaint(hwnd, &ps);
	}
	break;

	case WM_LBUTTONDOWN:
		color += 30;
		InvalidateRect(hwnd, nullptr, true);
		break;

	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		return 0;

	default:
		break;
	}
	return DefWindowProc(hwnd, uMSG, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE currentInstance, HINSTANCE, LPSTR cmdLine, int nCmdShow)
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	MSG msg{};
	HWND hwnd{};
	WNDCLASSEX wc{sizeof(WNDCLASSEX)};

	wc.hInstance = currentInstance;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = "LAB2";
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wc))
	{
		return EXIT_FAILURE;
	}

	hwnd = CreateWindow(wc.lpszClassName, "LAB2",
											WS_OVERLAPPEDWINDOW,
											CW_USEDEFAULT, CW_USEDEFAULT,
											400, 400,
											nullptr, nullptr, wc.hInstance, nullptr);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
	Gdiplus::GdiplusShutdown(gdiplusToken);
	return (int)msg.wParam;
}