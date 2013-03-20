#pragma once

#include "bmp.h"
#include "object.h"

class Ground: public Object //this should have practically the same properties as object 
{
public:
	Ground():Object(0,0,read_bmp("ground.bmp"), true){}

	Ground(int x, int y, unsigned char *z, bool isEatable):Object(x,y,z, isEatable)
	{}

	void InitGround(unsigned char* field)
	{
		for(int i=0; i< 800/Object_size; ++i)
			{
				for (int j=0; j < 600/Object_size; ++j)
				{
					Insert_Object(i,j,field);
				}
			}	
	} 

};
