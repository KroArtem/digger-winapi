#pragma once

#include "bmp.h"
#include "object.h"
#include "digger.h"


class Bot: public Digger
{
public:
	Direction BotDirection;

	Bot():Digger(-1,-1,NULL, true),moving(false),isLeft(false),isRight(false),isUp(false),isDown(false)
	{
	}

	Bot(int x, int y, unsigned char *z, bool isEatable): Digger(x,y,z,isEatable)
	{
	}

	bool moving;
	bool isLeft, isRight,isUp,isDown;


	bool FitsMove(unsigned char *field)							
	{
		int dy = Pos_y + 1;
		if (dy >= 600/Object_size) 
		{ 
			moving = false;
			return false ;
		}
		int index = ((600 - dy*Object_size - 1)*800 +Pos_x*Object_size)*3;
		if (field[index + 0] !=255 || field[index + 1] !=255 || field[index + 2] !=255) //genius check
		{
			return false;
		}
		return true;
	}

	void Move(unsigned char *field)
	{	
		if (!moving) return;
		
		Clear_Object(Pos_x, Pos_y, field);

		int x = rand()%4;;
		
		
		switch (x) 
		{
		case 0:
			if (Fits(Pos_x,Pos_y-1,field))
			{
				--(Pos_y);
				break;
				
			}
			else 
			{ 
				Insert_Object (Pos_x, Pos_y, field); 
				return;
			}
		case 1:
			if (Fits(Pos_x,Pos_y+1,field))
			{
				++(Pos_y); 
				break;
			}
			else 
			{ 
				Insert_Object (Pos_x, Pos_y, field); 
				return;
			}
		case 2:
			if (Fits(Pos_x -1, Pos_y, field))
			{

				--(Pos_x);
				break;
			}
			else 
			{ 
				Insert_Object (Pos_x, Pos_y, field); 
				return;
			}
		case 3:
			if (Fits(Pos_x+1,Pos_y,field))
			{
				++(Pos_x);
				break;
			}
			else 
			{ 
				Insert_Object (Pos_x, Pos_y, field); 
				return;
			}
		}
		
		Insert_Object (Pos_x, Pos_y, field); 
		// FIXME: also need to check if something in front of us is eatable before moving 
	}

};