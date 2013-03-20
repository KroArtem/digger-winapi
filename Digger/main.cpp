#include <iostream>
#include <string.h> 
#include "App.h"
#include "GfxWin.h"
#include <windows.h>
#include "object.h"
#include "digger.h"
#include "ground.h"
#include "gold.h"
#include "bmp.h"
#include "resource.h"
#include <time.h>
#include "bot.h"
using namespace std;

class MyWindow: public GfxWindow
{
public:

	MyWindow(int x, int y, int w, int h, const char* title): GfxWindow(x,y,w,h,title),digge(0,0,read_bmp("digger_inv.bmp"),true)
	{
		time1 = 0.0;
		time2 = 0.0;
		ScoreAmount = 0;
		for (int i = 0; i < 20; ++i)
		{
			gld[i] = NULL;			//init gold
			timeGld[i] = 0.0;
		}

		for (int i=0; i<4; ++i)
		{
			bot[i] = NULL;			//init bots
		}
		CreateField();
		isPlaying = false;
		background = read_bmp("bwmenu1.bmp");
	}


	~MyWindow() 
	{
		for (int i = 0; i < 20; ++i) 
		{
			delete gld[i];
		}
		DeleteField();
		if (background) delete []background;
	}


	virtual void OnCommand(int param1, int param2)
	{
		if(param1 == ID_MENU_EXIT)
		{
			SendMessage(this->GetHandle(), WM_DESTROY, 0, 0);
		}
		if(param1 == ID_MENU_NEWDIG)
		{
			DeleteField();
			CreateField();
			SetDelta(0.15f);
			isPlaying = true;
		}

	}

	virtual void OnMouseUp(int Button, int x, int y) 
	{
			if (x>=30 && x<=220 && y>= 53 && y<= 103)           //	new game
			{
				DeleteField();
				CreateField();
				SetDelta(0.15f);
				
				isPlaying = true;
			}
			if (x>=30 && x<220 && y>= 139 && y< 189)            //     this is my dumb about messagebox
			{
				MessageBox(NULL, "This is a first version of my own digger.\n\nDigger 0.4\nKrosheninnikov Artem\n2012","About Digger", MB_OK);
			}

			if (x>=30 && x<220 && y>=221 && y<271)				//		exit
			{
				SendMessage(this->GetHandle(), WM_DESTROY, 0, 0);
			}

	}

	void DeleteField ()
	{
		memset(buff, 220, 800*600*3);
		for (int i=0; i<20; ++i)
		{
			delete gld[i];
			gld[i] = NULL;
		}
		for (int i=0; i<4; ++i)
		{
			delete bot[i];
			bot[i] = NULL;
		}
	}

	void CreateField ()
	{
		
		memset(buff, 220, 800*600*3);
		gr.InitGround(buff);
		digge.Insert_Digger(0,0,buff);

	}

	void Insert_Gold() 
	{
		int x;
		int y;

		while (true) 
		{
			x = rand()%32;
			y = rand()%24;		
			Point ptr = digge.GetCoord();
			if (ptr.x == x && ptr.y == y)	// checks to see whether it generates on the same place as digger or another gold
			{
				continue;
			}
			for (int i = 0; i < 20; ++i) 
			{
				if (gld[i]) 
				{
					ptr = gld[i] -> GetCoord();
					if (ptr.x == x && ptr.y == y) 
					{
						break;
					}		
				}
			}
			if (ptr.x == x && ptr.y == y) 
			{
				continue;
			}
			break;
		}
		int i = 0;
		for (; i < 20; ++i)
		{
			if (!gld[i]) break;
		}
		if (i == 20) return;
		gld[i] = new Gold(x,y,read_bmp("gem.bmp"),true);
		gld[i] -> Insert_Object(x,y,buff);
		time1 = GetTime();

	}

	void Insert_Bot()
	{
		int x;
		int y;

		while (true) 
		{
			x = rand()%32;
			y = rand()%24;		
			Point ptr = digge.GetCoord();
			if (ptr.x == x && ptr.y == y)	// checks to see whether it generates on the same place as digger or another bot
			{
				continue;
			}
			for (int i = 0; i < 4; ++i) 
			{
				if (bot[i]) 
				{
					ptr = bot[i] -> GetCoord();
					if (ptr.x == x && ptr.y == y) 
					{
						break;
					}		
				}
			}
			if (ptr.x == x && ptr.y == y) 
			{
				continue;
			}
			break;
		}
		int i = 0;
		for (; i < 4; ++i)
		{
			if (!bot[i]) break;
		}
		if (i == 4) return;
		bot[i] = new Bot(x,y,read_bmp("opponent.bmp"),true);
		bot[i] ->Insert_Object(x,y,buff);
		time2 = GetTime();
	}

	void FitsFood() 
	{
		Point ptr = digge.GetCoord();
		for (int i=0; i<20; ++i)
		{
			if (!gld[i]) 
			{
				continue;
			}
			Point ptr2 = gld[i]-> GetCoord();
			if ((ptr.x == ptr2.x) && (ptr.y == ptr2.y))
			{
				delete gld[i];
				gld[i] = NULL;
				timeGld[i] = 0.0;
				ScoreAmount = ScoreAmount + 10;
			}
		}

	}

	void FitsBot()
	{
		Point ptr = digge.GetCoord();
		for (int i=0; i<4; ++i)
		{
			if (!bot[i]) 
			{
				continue;
			}
			Point ptr2 = bot[i]->GetCoord();
			if ((ptr.x == ptr2.x) && (ptr.y == ptr2.y))
			{
				delete bot[i];
				bot[i] = NULL;
				isPlaying = false;
				MessageBox(GetHandle(),"You were killed by a stupid bot","Awesome messagebox",MB_OK);
				ScoreAmount = ScoreAmount + 10;
			}
		}
	}

	void MoveBot()

	{
		for (int i = 0; i < 4; ++i) 
		{
			if (!bot[i]) continue;
			if (bot[i] -> FitsMove(buff)) 
				if (timeBot[i]==0.0) 
				{
					timeBot[i] = GetTime();
				}
			if (GetTime() - timeBot[i] > 1.0)
			{
				if ( bot[i] -> FitsMove(buff)) 
				{ 
					bot[i] -> Move(buff);
					 
					Point ptr1 = bot[i] -> GetCoord();
					Point ptr2 = digge.GetCoord();

					if ((ptr1.x == ptr2.x) && (ptr1.y == ptr2.y)) 
					{ 
						isPlaying = false; 
						MessageBox(GetHandle(),"Game over.", "Awesome messagebox",MB_OK);
					}

				} 
				else
				{
					timeBot[i] = 0.0;
				}
			}
		}
	}


	void MoveGold()
	{
		for (int i = 0; i < 20; ++i) 
		{
			if (!gld[i]) continue;
			if (gld[i] -> FitsMove(buff)) 
				if (timeGld[i]==0.0) 
				{
					timeGld[i] = GetTime();
				}
			if (GetTime() - timeGld[i] > 1.0)
			{
				if ( gld[i] -> FitsMove(buff)) 
				{ 
					gld[i] -> MoveDown(buff);
					 
					Point ptr1 = gld[i] -> GetCoord();
					Point ptr2 = digge.GetCoord();

					if ((ptr1.x == ptr2.x) && (ptr1.y == ptr2.y)) 
					{ 
						isPlaying = false; 
						MessageBox(GetHandle(),"Game over.", "Awesome messagebox",MB_OK);
					}

				} 
				else
				{
					timeGld[i] = 0.0;
				}
			}
		}
	}


	virtual void OnPaint()
	{
		if (!isPlaying) 
		{
			SetBuffer(background);
			GfxWindow::OnPaint();
		}
		else 
		{
			GfxWindow::OnPaint();
		}
	}

	virtual void OnTimer()
	{
		Window::OnTimer();
		if (isPlaying) 
		{
			if ((GetTime() - time1) > 10) 
			{
				Insert_Gold();
			}
			if ((GetTime() - time2) > 13)
			{
				Insert_Bot();
			}
			digge.Move(buff);
			MoveGold();
			FitsFood(); // do we eat?
			MoveBot();
			FitsBot();
			SetBuffer(buff);
		}
		else 
		{
			KillTimer(GetHandle(),111);
		}
		
		this->Repaint();
	}

	virtual void OnKeyUp(int key)
	{
		if(key == VK_LEFT)
		{	
			digge.moving = false;
			digge.DiggerDirection = LEFT;
			digge.isLeft = true;								//dumb check to change pictures when we change direction
			digge.isDown = digge.isUp = digge.isRight = false;
		}
		if(key == VK_RIGHT)
		{
			digge.moving = false;
			digge.DiggerDirection = RIGHT;
			digge.isRight = true;
			digge.isDown = digge.isUp = digge.isLeft = false;

		}
		if(key == VK_UP)
		{
			digge.moving = false;
			digge.DiggerDirection = UP;
			digge.isUp = true;
			digge.isDown = digge.isLeft = digge.isRight = false;
		}
		if(key == VK_DOWN)
		{
			digge.moving = false;
			digge.DiggerDirection = DOWN;
			digge.isDown = true;
			digge.isLeft = digge.isUp = digge.isRight = false;
		}

		if (key == VK_F1) 
		{
			if (!isPlaying)
			{
				SetDelta(0.15f);
				isPlaying = !isPlaying;
				OnTimer();
			}
			else
			{
				KillTimer(GetHandle(),111);
				isPlaying = !isPlaying;
				MessageBox(NULL,"Pause.\nPress F1 again to continue.","Pause",MB_OK);
			}
		}

		if (key == VK_ESCAPE) 
		{
			DeleteField();
			memset(buff, 255,800*600*3);
			isPlaying = false;
			
		}

	}

	virtual void OnKeyDown(int key)
	{
		if(key == VK_LEFT)
		{
			digge.DiggerDirection = LEFT;
			digge.moving = true;
			if(!digge.isLeft)
			{
			digge.imgBuf = read_bmp("digger.bmp");
			}
		}
		if(key == VK_RIGHT)
		{
			digge.DiggerDirection = RIGHT;
			digge.moving = true;
			if(!digge.isRight)
			{
			digge.imgBuf = read_bmp("digger_inv.bmp");
			}
			//digge.Turn_Right(digge.imgBuf);
		}
		if(key == VK_UP)
		{
			digge.DiggerDirection = UP;
			digge.moving = true;
			if(!digge.isUp)
			{
			digge.imgBuf = read_bmp("digger_up.bmp");
			}
		}
		if(key == VK_DOWN)
		{
			digge.DiggerDirection = DOWN;
			digge.moving = true;
			if(!digge.isDown)
			{
			digge.imgBuf = read_bmp("digger_down.bmp");
			}
		}
	}

private:

	unsigned char buff[800*600*3+1]; // we'll paint in this buffer
	Ground gr;
	Digger digge;
	Gold *gld[20];
	Bot *bot[4];
	bool isPlaying;					//whether game is active or not
	unsigned char *background;
	bool aliveGame;
	float time1;
	float time2;
	int ScoreAmount;
	float timeGld[20];
	float timeBot[4];
};



int main()
{
	App a;
	GfxWindow* w = new MyWindow(50, 50, 800, 600, "Awesome_Digger");

	w->SetSize(815,658);
	
	w->Show(true);

	return a.Run();
}