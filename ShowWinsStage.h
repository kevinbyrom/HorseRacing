#ifndef __SHOWWINSSTAGE_H
#define __SHOWWINSSTAGE_H


#include "Gamelib\Header\WndStage.h"


class CShowWinsStage : public CWndStage
	{
	public:

		virtual void Opening();				
		virtual void Closing(CStage * pStage);
		virtual void DoGraphics(CBitmap * pBuffer);

		virtual void OnKeyPressed(unsigned char key);
	};


#endif