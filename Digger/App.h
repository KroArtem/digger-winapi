#pragma once

#include <windows.h>

#include <map>
#include <vector>

class Window;

class App
{
public:
	App() { Init(); }

	// регистрация класса и прочие вспомогательные вещи
	int Init();

	// запуск цикла обработки сообщений
	int Run();

	// запрос на выход
	void Exit();

	// главное окно
	void SetMainWindow(Window* W) { MainWnd = W; }

	/// имя оконного класса по умолчанию
	static const char* szWinName;

private:
	static LRESULT CALLBACK MyFunc(HWND, UINT, WPARAM, LPARAM);

	// главное окно (кому посылать WM_DESTROY)
	Window* MainWnd;
};
