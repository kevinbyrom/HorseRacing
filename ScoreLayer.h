#ifndef __SCORELAYER_H
#define __SCORELAYER_H


#include "Gamelib\Header\Layer.h"



class CScoreLayer : public CLayer
	{
	public:

		virtual void Create(CView * pParentView, int x, int y, int width, int height, int BPP = 8);


	public:

		virtual void DoGraphics(CBitmap * pBuffer);
	};



#endif