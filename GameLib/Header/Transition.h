#ifndef __CTransition_H
#define __CTransition_H


#include "Bitmap.h"


class CTransition
	{
	public:

		CTransition()								{ m_IsDone = TRUE; }

		virtual void Start()						{ m_IsDone = FALSE; }
		virtual void DoGraphics(CBitmap * pBitmap)	{}
		
		BOOL IsDone()	{ return m_IsDone; }


	protected:

		BOOL m_IsDone;
	};


#endif