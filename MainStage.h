#ifndef __MAINSTAGE_H
#define __MAINSTAGE_H


#include "Gamelib\Header\WndStage.h"
#include "Gamelib\Header\Object.h"
#include "Gamelib\Header\View.h"
#include "Gamelib\Header\MapLayer.h"
#include "Gamelib\Header\Timer.h"
#include "SpriteLayer.h"
#include "ScoreLayer.h"


#define STATE_RACING	0
#define STATE_FINISHED	1


class CMainStage : public CWndStage
	{
	public:

		virtual void Opening();				
		virtual void Closing(CStage * pStage);
		virtual void DoLogic();
		virtual void DoGraphics(CBitmap * pBuffer);


	protected:

		CTimer			Timer;

		CObject			Camera;
		CView			MainView;
		CMapLayer		BgLayer;
		CMapLayer		TrackLayer;
		CSpriteLayer	SpriteLayer;
		CScoreLayer		ScoreLayer;

		void SetHorseStartPositions();
	};


#endif