#pragma once

#include "bmp.h"
#include "Win.h"
#include <time.h>
//using namespace std;

enum Direction{UP,LEFT,DOWN,RIGHT};

enum BotDirection{BUP,BLEFT,BDOWN,BRIGHT};

int const Object_size = 25;		// default object size as all objects are 10x10 pixels 


struct Point
{
	int x;
	int y;
	Point (int X,int Y): x(X),y(Y){}
};


class Object
{
public:
	bool isEatable;			  // basic structure for object. They all have coordinates, pictures (imgbuf) and probably something else
	int Pos_x, Pos_y;		  // all objects have their coordinates
	unsigned char *imgBuf;

	Object(int x, int y, unsigned char *z, bool isEatable): Pos_x(x), Pos_y(y), imgBuf(z), isEatable(isEatable)
	{
	}																		  //default constructor
		
	~Object()																  //destructor
	{
		Pos_x = Pos_y = -1;													  // I'm sure we don't have negative coordinates
		if (imgBuf)
		{
			delete []imgBuf;
		}
		imgBuf = NULL; 
	}


	void Insert_Object(int x, int y, unsigned char *field) //insert object in 1 turn, 10x10 pixels
		{
			Pos_x = x;
			Pos_y = y;
			if (!Fits(x,y,field)) {return;}
			for (int i = y * Object_size; (i <y * Object_size + Object_size); ++i)
			{
				for (int j = x * Object_size; (j < x * Object_size + Object_size); ++j)
				{ 
					int index1 = ((i - y*Object_size) * Object_size + (j-x * Object_size)) * 3;
					int index2 = (((599-i) * 800) + j) * 3;  // inversing y coordinate 
					field[index2 + 0] = imgBuf [index1 + 0];
					field[index2 + 1] = imgBuf [index1 + 1];
					field[index2 + 2] = imgBuf [index1 + 2];
				}
			}
		}

	void Clear_Object(int x, int y, unsigned char *field) //delete object from the screen
		{
			for (int i = y * Object_size; i <y * Object_size + Object_size; ++i)
			{
				for (int j = x * Object_size; j < x * Object_size + Object_size; ++j)
				{ 
					field[((599-i) * 800 + j) * 3 + 0] = 255;
					field[((599-i) * 800 + j) * 3 + 1] = 255;
					field[((599-i) * 800 + j) * 3 + 2] = 255;
				}
			}
		}

	bool Fits(int x, int y ,unsigned char *field) // do we fit the screen?
	{
		if((x>=0) && (x<800/Object_size) && (y>=0) && (y<600/Object_size))
		{
			return true;
		}
			return false;	
	}


	Point GetCoord()
	{
		return Point(Pos_x,Pos_y);
	}


};