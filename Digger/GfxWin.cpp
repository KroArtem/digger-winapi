#include "GfxWin.h"

#include "App.h"

GfxWindow::GfxWindow(int x, int y, int w, int h, const char* title)
{
	InitWithParams(App::szWinName, x, y, w, h, title);
	OnSize(w, h);
}

void GfxWindow::OnCreate()
{
}

void GfxWindow::OnDestroy()
{
	Bmp.DestroyDCs();
}

void GfxWindow::OnSize(int NewW, int NewH)
{
	Bmp.DestroyDCs();

	HDC h = this->GetDC();

	Bmp.CreateDCs(h, NewW, NewH);

	ReleaseDC(this->GetHandle(), h);
}

void GfxWindow::OnPaint()
{
	HDC h = this->GetDC();

	Bmp.Blit(h, 0, 0);

	ReleaseDC(this->GetHandle(), h);
}
