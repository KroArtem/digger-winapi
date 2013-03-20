#pragma once

#include "bmp.h"
#include "object.h"

class Digger: public Object //here we suppose digger can have additional functions like move
{

public:
	Direction DiggerDirection;

	Digger():Object(-1,-1,NULL, true),moving(false),isLeft(false),isRight(false),isUp(false),isDown(false)
	{
	}

	Digger(int x, int y, unsigned char *z, bool isEatable): Object(x,y,z,isEatable)
	{
	}
	
	float Digger_Speed; //I'll use it later to speed up my digger with bonuses. Or not. Nobody knows.
	bool moving;
	bool isLeft, isRight,isUp,isDown;

	void Insert_Digger(int x, int y, unsigned char *field)
	{
		Pos_x = x;
		Pos_y = y;
		if (Fits(x,y,field))
		{
		Insert_Object(x,y,field);
		}
		
	}

	void Move(unsigned char *field)
	{	
		if (!moving) return;
		
		Clear_Object(Pos_x, Pos_y, field);

		switch (DiggerDirection) 
		{
		case UP:
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
		case DOWN:
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
		case LEFT:
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
		case RIGHT:
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


	void Turn_Right (unsigned char *field) 
	{
		unsigned char *tmp = new unsigned char [25 * 25 * 3];
		int increment = -1;

		for (int j = 0; j < 25 ; ++j)
		{
			for (int i = 0; i < 25; ++i)
			{

				++increment;
				int index1 = increment * 3,
					index2 = (((25 - 1 - i)) * 25 + j) * 3;

				tmp [index1 + 0] = imgBuf[index2 + 0]; 
				tmp [index1 + 1] = imgBuf[index2 + 1];
				tmp [index1 + 2] = imgBuf[index2 + 2];

			}
		}

		delete []imgBuf;
		imgBuf = tmp;
	}

};



