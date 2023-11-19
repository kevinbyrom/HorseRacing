#ifndef __TITLESTAGE_H
#define __TITLESTAGE_H


#include "Stage.h"


class CTitleStage : public CStage
	{
	public:

		virtual void Opening();					
		virtual void Closing(CStage * pStage);	
		virtual void DoInput(CInput & Input);	
		virtual void DoLogic();					
		virtual void DoGraphics(CBitmap & Buffer);

	protected:

		CBitmap TitleBmp;
	};


#endif