#pragma once

#include "bmp.h"
#include "object.h"

class Gold: public Object // Stone would fall if there are no ground under it
						   // Also it is not eatable
						   // In case it falls on the digger it kills him
{
private:
	bool moving;
public:
	Gold():Object(-1,-1,NULL, true){moving = false;}
	Gold(int x, int y, unsigned char *z, bool isEatable):Object(x,y,z, isEatable),moving(false)
	{
	}

	bool FitsMove(unsigned char *field)							// FIXME: doesn't work :'(
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

	void MoveDown(unsigned char *field)
	{
		Clear_Object(Pos_x, Pos_y, field);
		++Pos_y;
		Insert_Object (Pos_x, Pos_y, field);
	}


	void InitGold(int x, int y, unsigned char *field, unsigned char *field2)
	{
		if (Fits(x,y,field2))
		{
		Insert_Object(x,y,field);

		}
	}


};
