#include "App.h"

#include "Win.h"

#include <windowsx.h>
#include "resource.h"
const char* App::szWinName = "OurApplicationWindow";

// запрос на выход
void App::Exit()
{
	if(!MainWnd) { return; }

	SendMessage(MainWnd->GetHandle(), WM_DESTROY, 0, 0);
}

int App::Init()
{
	MainWnd = NULL;

	WNDCLASS wcl;

	wcl.hInstance = NULL;
	wcl.lpszClassName = szWinName;
	wcl.lpfnWndProc = App::MyFunc;
	wcl.style = 0;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;

	wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);

	if(!RegisterClass(&wcl)) return 0;

	// всё хорошо
	return 1;
}

int App::Run()
{
	MSG msg;

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK App::MyFunc(HWND this_hwnd,UINT message, WPARAM wParam, LPARAM lParam)
{
	Window* W = ( Window* )GetWindowLongPtr( this_hwnd, GWLP_USERDATA );

	switch(message) 
	{
	case WM_DESTROY:
		if(W) { W->OnDestroy(); }

		PostQuitMessage(0);
		break;

	case WM_COMMAND:
		if(W) { W->OnCommand(wParam, lParam); }
		break;
	case WM_KEYUP:
		if(W) {W->OnKeyUp(wParam);}
		break;
	case WM_KEYDOWN:
		if(W) {W->OnKeyDown(wParam);}
		break;

	case WM_CREATE:
		if(W) { W->OnCreate(); }
		break;

	case WM_TIMER:
		if(W) { W->OnTimer(); }
		break;

	case WM_LBUTTONDOWN:
		SetCapture(this_hwnd);
		if(W) { W->OnMouseDown(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); }
		break;

	case WM_MOUSEMOVE:
		if(W) { W->OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); }
		break;

	case WM_LBUTTONUP:
		if(W) { W->OnMouseUp(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); }
		ReleaseCapture();
		break;

	case WM_RBUTTONDOWN:
		SetCapture(this_hwnd);
		if(W) { W->OnMouseDown(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); }
		break;

	case WM_RBUTTONUP:
		if(W) { W->OnMouseUp(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); }
		ReleaseCapture();
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC ThisDC = BeginPaint(this_hwnd, &ps);

			if(W) { W->OnPaint(); }

			EndPaint(this_hwnd, &ps);
		}

		break;

	case WM_MOUSEWHEEL:
	{
		if ( static_cast<int>( wParam ) > 0 )
		{
			if(W) { W->OnWheelUp(); }
		}
		else
		{
			if(W) { W->OnWheelDown(); }
		}

		break;
	}

/*
	case WM_XBUTTONDOWN:
	{
		SetCapture( this_hwnd );
		XDown = true;
		break;
	}

	case WM_XBUTTONUP:
	{
		ReleaseCapture();
		XDown = false;
		break;
	}
*/
	}

	return DefWindowProc(this_hwnd, message, wParam, lParam);
}
