#include "Win.h"

#include "App.h"

Window::Window()
{
	hWnd = (HWND)INVALID_HANDLE_VALUE;

	LocalTime = 0;
}

Window::Window(int x, int y, int w, int h, const char* title)
{
	InitWithParams(App::szWinName, x, y, w, h, title);
}

Window::~Window()
{
}

void Window::InitWithParams(const char* WndClass, int x, int y, int w, int h, const char* title)
{
	Init(WndClass);

	SetPos(x, y);
	SetSize(w, h);
	SetTitle(title);
}

void Window::Init(const char* WndClass) //WS_OVERLAPPEDWINDOW
{
	hWnd = CreateWindowA(WndClass, "", WS_OVERLAPPEDWINDOW /* WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU */, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, HWND_DESKTOP, NULL, NULL, NULL);
	SetWindowLongPtrA( hWnd, GWLP_USERDATA, (LONG_PTR)this );
}

void Window::SetTitle(const char* title) { SetWindowText(hWnd, title); }

void Window::SetPos(int x, int y) { SetWindowPos(hWnd, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE); }

void Window::SetSize(int w, int h) { SetWindowPos(hWnd, NULL, 0, 0, w, h, SWP_NOZORDER | SWP_NOMOVE); Width = w; Height = h; }

void Window::Show(bool Visible) { ShowWindow(hWnd, Visible ? SW_SHOW : SW_HIDE); }

void Window::SetDelta(float dt)
{
	DeltaTime = dt;

	SetTimer(hWnd, 111, (int)(1000.0f * dt), NULL);
}

void Window::Repaint()
{
	InvalidateRect(hWnd, NULL, 0);
}
