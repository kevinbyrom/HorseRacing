#ifndef __SHOWHORSESSTAGE_H
#define __SHOWHORSESSTAGE_H


#include "Gamelib\Header\WndStage.h"


class CShowHorsesStage : public CWndStage
	{
	public:

		virtual void Opening();				
		virtual void Closing(CStage * pStage);
		virtual void DoGraphics(CBitmap * pBuffer);

		virtual void OnKeyPressed(unsigned char key);


	private:

		CBitmap m_HInfoBmp;

		void DrawHorseInfo(CBitmap * pBuffer, int HNum, int x, int y);
		void DrawStat(CBitmap * pBuffer, char * strText, int x, int y, int NumBars);
	};


#endif