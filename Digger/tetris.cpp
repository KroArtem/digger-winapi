#include <iostream>
#include <string.h> 

#include "App.h"
#include "GfxWin.h"
#include <windows.h>

const int Field_w=10, Field_h=20, w1=4, h1=4;

int fx, fy;

int Field[Field_w][Field_h], Figure[w1][h1];

void Clear(){
  memset(Field, 0, Field_w*Field_h*4);
}

void print(int x, int y, bool f=false) {

  for(int j=0; j<Field_h; ++j) {

    for(int i=0; i<Field_w; ++i) {
 
	if (f && i-x >= 0 && j-y >= 0 && i-x < w1 && j-y < h1) {
	    if (Figure[i][j]!=0) {
                std::cout << Figure[i][j] << " ";
            } else {
                std::cout << Field[i][j] << " ";
            }
	} else {
	  std::cout << Field[i][j] << " ";
	}
    }
    std::cout << std::endl;
  }
}

void Generate(int t, int color){
  memset(Figure, 0, w1*h1*4);
  switch(t){
  case 0:
  Figure[0][0] = color;
  Figure[0][1] = color;
  Figure[1][0] = color;
  Figure[1][1] = color;
  break;
  case 1:
  Figure[0][0] = color;
  Figure[0][1] = color;
  Figure[0][2] = color;
  Figure[0][3] = color;
  break;
  }
}

void Place(int x, int y){
  if (x<0 || y<0) {return;}
  for(int i=0; i<w1; ++i){
     for(int j=0; j<h1; ++j)
	if (Figure[i][j]!=0) {Field[x+i][y+j] = Figure[i][j];}
  }
}


bool Fits(int x, int y){
  if (x<0 || y<0) {return false;}
  for(int i=0; i<w1; ++i){
     for(int j=0; j<h1; ++j)
        if (Figure[i][j]!=0) {
	  if(x+i >= Field_w || y+j >= Field_h) {return false;}
	  if(Field[x+i][j+y]!=0) {return false;}
	}
  }
  return true;
}

void TestField(){
  Generate(0,1);
  Place(0,0);
  Place(5,5);
  print(0, 0);
  Generate(1,2);
  if (Fits(1,1)) {std::cout << "OK" << std::endl;}
  Place(2,2);
  print(0, 0);
}

int Colors[] = {0xFFFFFF, 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0x00FFFF};

int cw = 20, ch = 20;
bool GameOver = false;
class Test_Window: public GfxWindow{
	unsigned char* Buffer;
public:
	Test_Window(int x, int y, int w, int h, const char* title): GfxWindow(x,y,w,h,title)
	{
		Clear();
		Generate(0,2);
		fx = 5; fy = 0;
		Buffer = new unsigned char [w*h*3];
	}	
	void Box(int x1, int y1, int x2, int y2, int color)
	{
		int w = GetWidth();
		int h = GetHeight();
		for(int i=x1; i<=x2; ++i)
		{
			for(int j=y1; j<=y2; ++j)
			{
				int ofs = ((h - 1 - j) * w + i) * 3; //смещение до точки в массиве Buffer 
				Buffer[ofs + 0] = color & 0xFF; 
				Buffer[ofs + 1] = (color>>8) & 0xFF;
				Buffer[ofs + 2] = (color>>16) & 0xFF;
			}
		}	
	}
	virtual void OnKeyUp(int key)
	{
		std::cout<<"OnKeyUp "<<key<<std::endl;
		if(key == VK_LEFT)
		{
			if(Fits(fx - 1,fy))
			{
				fx--;
			}
		}
		if(key == VK_RIGHT)
		{
			if(Fits(fx + 1,fy))
			{
				fx++;
			}
		}
	}
	virtual void OnTimer() 
	{
		GfxWindow::OnTimer();
		DrawField();
		DrawFigure();
		if(GameOver) return;
		if(Fits(fx, fy + 1)){
			fy++;
		}else
		{
			Place(fx, fy);
			Generate(rand()%2, rand()%5 + 1);
			fy = 0; fx = 5;
			if(!Fits(fx, fy))
			{
				GameOver = true;
				return;
			}
		}	
	
		SetBuffer(Buffer);
		this->Repaint();
	}
	void DrawField()
	{
		for(int i=0; i<Field_w; ++i)
		{
			for(int j=0; j<Field_h; ++j)
			{
				Box(i * cw, j * ch, (i + 1)*cw, (j + 1)*ch, Colors[Field[i][j]]);	
				
			}
		}				
	}
	void DrawFigure()
	{
		for(int i=0; i<w1; ++i)
		{
			for(int j=0; j<h1; ++j)
			{
				if (Figure[i][j]!=0)
				{
				int i1 = i + fx;
				int j1 = j + fy;
				Box(i1 * cw, j1 * ch, (i1 + 1)*cw, (j1 + 1)*ch, Colors[Figure[i][j]]);	
				}
			}
		}				
	}

};

int main(){


 	//  TestField();
	App a;
	GfxWindow* w = new Test_Window(100, 100, 300, 600, "Tetris");
	/// 1 секунда
	w->SetDelta(0.1f);
	w->Show(true);
	return a.Run();

}






