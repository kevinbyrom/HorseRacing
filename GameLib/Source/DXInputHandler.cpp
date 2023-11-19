#include <windows.h>
#include "..\Header\DXInputHandler.h"
#include "..\Header\Game2D.h"




CDXInputHandler::CDXInputHandler()
	{
	m_pDInput	= NULL;
	m_pKeyboard = NULL;
	m_pJoystick	= NULL;
	m_pMouse	= NULL;
	}




BOOL CDXInputHandler::Init(CGame * pGame, BOOL UseKeyboard, BOOL UseMouse, BOOL UseJoystick, BOOL StrictSuccess)
	{
	LPDIRECTINPUTDEVICE  pJoystick;



	// Call the parent class's Init function //

	if (!CInputHandler::Init(pGame, UseKeyboard, UseMouse, UseJoystick, StrictSuccess))
		return FALSE;



	// Create the main DirectInput object //

	if (FAILED(DirectInputCreate(pGame->GetInstance(), DIRECTINPUT_VERSION, &m_pDInput, NULL)))
		return FALSE;



	// Create a keyboard device //

	if (UseKeyboard)
		{
		if (FAILED(m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL)))
			{
			if (StrictSuccess)
				return FALSE;


			m_UseKeyboard = FALSE;
			}
		else
			{

			// Set the keyboard cooperation level //

			if (FAILED(m_pKeyboard->SetCooperativeLevel(pGame->GetWindow(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
				return FALSE;


			// Set the keyboard data format //

			if (FAILED(m_pKeyboard->SetDataFormat(&c_dfDIKeyboard)))
				return FALSE;


			// Acquire the keyboard //

			if (FAILED(m_pKeyboard->Acquire()))
				return FALSE;


			m_UseKeyboard = TRUE;
			}
		}




	// Create the mouse device //

	if (UseMouse)
		{
		if (FAILED(m_pDInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL)))
			{
			if (StrictSuccess)
				return FALSE;


			m_UseMouse = FALSE;
			}
		else
			{
			// Set the mouse cooperation level //

			if (FAILED(m_pMouse->SetCooperativeLevel(pGame->GetWindow(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
				return FALSE;


			// Set the mouse data format //

			if (FAILED(m_pMouse->SetDataFormat(&c_dfDIMouse)))
				return FALSE;


			// Acquire the mouse //

			if (FAILED(m_pMouse->Acquire()))
				return FALSE;


			m_Input.Mouse.X = 0;
			m_Input.Mouse.Y = 0;

			m_UseMouse = TRUE;
			}
		}




	// Create the joystick device //

	if (UseJoystick)
		{
		if (FAILED(m_pDInput->CreateDevice(m_GUIDJoystick, &pJoystick, NULL)))
			{
			if (StrictSuccess)
				return FALSE;


			m_UseJoystick = FALSE;
			}
		else
			{

			// Query the newest interface //

			if (FAILED(pJoystick->QueryInterface(IID_IDirectInputDevice2, (void **)&m_pJoystick)))
				{
				pJoystick->Release();

				if (StrictSuccess)
					return FALSE;
				}


			// Set the joystick cooperation level //

			if (FAILED(m_pJoystick->SetCooperativeLevel(pGame->GetWindow(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
				return FALSE;


			// Set the joystick data format //

			if (FAILED(m_pJoystick->SetDataFormat(&c_dfDIJoystick)))
				return FALSE;


			// Acquire the joystick //

			if (FAILED(m_pJoystick->Acquire()))
				return FALSE;


			m_UseJoystick = TRUE;
			}
		}



	return TRUE;
	}






void CDXInputHandler::DeInit()
	{

	////////////////////////////////////////////////////
	//												  //
	// Used to Deinitialize the DirectX Input handler //
	//												  //
	////////////////////////////////////////////////////


	if (m_pKeyboard != NULL)
		{
		m_pKeyboard->Unacquire();
		m_pKeyboard->Release();
		m_pKeyboard = NULL;
		}


	if (m_pMouse != NULL)
		{
		m_pMouse->Unacquire();
		m_pMouse->Release();
		m_pMouse = NULL;
		}


	if (m_pJoystick != NULL)
		{
		m_pJoystick->Unacquire();
		m_pJoystick->Release();
		m_pJoystick = NULL;
		}


	if (m_pDInput != NULL)
		{
		m_pDInput->Release();
		m_pDInput = NULL;
		}
	}






void CDXInputHandler::Poll()
	{
	

	// Get the keyboard state //

	if (m_UseKeyboard && m_pKeyboard->GetDeviceState(sizeof(char) * 256, (LPVOID)m_Input.KB.Key) == DIERR_INPUTLOST)
		{
		}



	// Get the mouse state //

	if (m_UseMouse)
		{
		if (m_pMouse->GetDeviceState(sizeof(m_Input.Mouse), (LPVOID)&m_Input.Mouse) == DIERR_INPUTLOST)
			{
			}
		}



	// Get the joystick state //

	if (m_UseJoystick)
		{
		m_pJoystick->Poll();


		if (m_pJoystick->GetDeviceState(sizeof(m_Input.Joy), (LPVOID)&m_Input.Joy) == DIERR_INPUTLOST)
			{
			}
		}
	}





void CDXInputHandler::SetJoystickGUID(GUID JoyGUID)			
	{ 

	//////////////////////////////////////////////
	//											//
	// Used to set the COM GUID of the joystick //
	//											//
	//////////////////////////////////////////////


	m_GUIDJoystick = JoyGUID; 
	}