#ifndef __BETSSTAGE_H
#define __BETSSTAGE_H


#include "Gamelib\Header\WndStage.h"



#define CURSOR_PLAYER	0
#define CURSOR_TYPE		1
#define CURSOR_MONEY	2
#define CURSOR_FIRST	3
#define CURSOR_SECOND	4
#define CURSOR_THIRD	5
#define CURSOR_RACE		6


class CBetsStage : public CWndStage
	{
	public:

		virtual void Opening();				
		virtual void Closing(CStage * pStage);
		virtual void DoLogic();
		virtual void DoGraphics(CBitmap * pBuffer);

		virtual void OnKeyPressed(unsigned char key);


	protected:

		int CurrPlayer;
		int CursorPos;
	};


#endif