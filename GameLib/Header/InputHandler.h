#ifndef __CInputHandler_H
#define __CInputHandler_H


#include "Input.h"


class CGame;


class CInputHandler
	{
	public:

		virtual BOOL Init(CGame * pGame, BOOL UseKeyboard, BOOL UseMouse, BOOL UseJoystick, BOOL StrictSuccess)	{ m_pGame = pGame; m_UseKeyboard = UseKeyboard; m_UseMouse = UseMouse; m_UseJoystick = UseJoystick; return TRUE; }
		virtual void DeInit() {}

		virtual void Poll()	{}

		CInput * GetInput()			{ return &m_Input; }


	protected:

		CGame * m_pGame;

		CInput	m_Input;

		int		m_UseKeyboard,
				m_UseJoystick,
				m_UseMouse;
	};




#endif