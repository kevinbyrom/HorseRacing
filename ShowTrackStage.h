#ifndef __SHOWTRACKSTAGE_H
#define __SHOWTRACKSTAGE_H


#include "Gamelib\Header\WndStage.h"


class CShowTrackStage : public CWndStage
	{
	public:

		virtual void Opening();				
		virtual void Closing(CStage * pStage);
		virtual void DoGraphics(CBitmap * pBuffer);

		virtual void OnKeyPressed(unsigned char key);
	};


#endif