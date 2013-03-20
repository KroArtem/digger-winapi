#pragma once

#include <windows.h>

// просто окно
class Window
{
public:
	Window();

	Window(int x, int y, int w, int h, const char* title);

	~Window();

	void InitWithParams(const char* WndClass, int x, int y, int w, int h, const char* title);

	void Init(const char* WndClass);

	void Repaint();

	void SetTitle(const char* title);

	void SetPos(int x, int y);

	void SetSize(int w, int h);

	void Show(bool Visible);

	int GetWidth() const { return Width; }
	int GetHeight() const { return Height; }

	// события

	// квант времени
	void SetDelta(float dt);

	virtual void OnCreate() {}

	virtual void OnDestroy() {}

	virtual void OnPaint() {}

	virtual void OnCommand(int param1, int param2) {}

	virtual void OnSize(int NewW, int NewH) {}

	virtual void OnMouseDown(int Button, int x, int y) {}

	virtual void OnMouseUp(int Button, int x, int y) {}

	virtual void OnMouseMove(int x, int y) {}

	virtual void OnKeyDown(int key) {}

	virtual void OnKeyUp(int key) {}

	virtual void OnTimer() { LocalTime += DeltaTime; }

	virtual void OnWheelUp() {}
	virtual void OnWheelDown() {}

	HDC GetDC() { return ::GetDC(hWnd); }

	HWND GetHandle() { return hWnd; }

	float GetTime() const { return LocalTime; }

private:
	int Width, Height;

	float DeltaTime;

	float LocalTime;

	HWND hWnd;
};
