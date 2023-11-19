#ifndef __CDXInputHandler_H
#define __CDXInputHandler_H


#include "InputHandler.h"
#include "..\..\DirectX\Header\DInput.h"



class CGame;





class CDXInputHandler : public CInputHandler
	{
	public:

		CDXInputHandler();

		virtual BOOL Init(CGame * pGame, BOOL UseKeyboard, BOOL UseMouse, BOOL UseJoystick, BOOL StrictSuccess);
		virtual void DeInit();

		virtual void Poll();

		void SetJoystickGUID(GUID JoyGUID);


	protected:

		LPDIRECTINPUT			m_pDInput;

		LPDIRECTINPUTDEVICE		m_pKeyboard;
		LPDIRECTINPUTDEVICE		m_pMouse;
		LPDIRECTINPUTDEVICE2	m_pJoystick;

		GUID 					m_GUIDJoystick;
	};



#endif