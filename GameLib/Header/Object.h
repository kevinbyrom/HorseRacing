#ifndef __Object_H
#define __Object_H



#include "Bitmap.h"



class CObject
	{
	public:

		virtual void DoGraphics(CBitmap * pBuffer) {}

		int X,
			Y,
			Width,
			Height;
	};





#endif