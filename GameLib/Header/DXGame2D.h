#ifndef __CDXGame_H
#define __CDXGame_H


#include "Game2D.h"
#include "DXDisplayHandler2D.h"
#include "DXInputHandler.h"




class CDXGame : public CGame
	{
	public:

		CDXGame()		{ m_pDisplay = new CDXDisplayHandler2D; m_pInput = new CDXInputHandler; }
		~CDXGame()		{ if (m_pDisplay) delete m_pDisplay;  if (m_pInput) delete m_pInput; }
	};





#endif