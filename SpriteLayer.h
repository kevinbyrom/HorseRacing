#ifndef __SPRITELAYER_H
#define __SPRITELAYER_H


#include "Gamelib\Header\Layer.h"



class CSpriteLayer : public CLayer
	{
	public:

		virtual void Create(CView * pParentView, int x, int y, int width, int height, int BPP = 8);


	public:

		virtual void DoGraphics(CBitmap * pBuffer);
	};



#endif