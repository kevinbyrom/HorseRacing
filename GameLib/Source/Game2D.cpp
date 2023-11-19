#include <windows.h>
#include <stdio.h>
#include "..\Header\Game2D.h"
#include "..\Header\Timer.h"




BOOL CGame::Init(HINSTANCE hInstance, WNDPROC WndProc, LPCTSTR lpstrWndName, int Width, int Height, int BPP, BOOL FullScreen, int FPS)
	{

	/////////////////////////////////
	//							   //
	// Used to initialize the game //
	//							   //
	/////////////////////////////////



	// Set the hInstance variable and wnd name //

	m_hInstance	= hInstance;
	m_WndProc	= WndProc;

	sprintf(m_strWndName, "%s", lpstrWndName);



	// Create the main window //

	if (!CreateMainWindow(Width, Height, FullScreen))
		return FALSE;




	// Initialize the graphics //

	if (!m_pDisplay->Init(this, Width, Height, BPP, FullScreen))
		return FALSE;



	// Init the input //

	if (!m_pInput->Init(this, TRUE, TRUE, FALSE, TRUE))
		return FALSE;


	// Set the flags //

	m_pCurrStage			= NULL;
	m_Exiting				= FALSE;
	m_InTransition			= FALSE;
	m_FPS					= FPS;


	// Get the initial tick count //

	m_LastTickCount	= GetTickCount();

#ifdef _DEBUG
	m_LastTCount = GetTickCount();
	m_FPSCount	 = 0;
#endif


	return TRUE;
	}





void CGame::ShutDown()
	{

	//////////////////////////////////////////////
	//											//
	// Used to handle de-initiation of the game //
	//											//
	//////////////////////////////////////////////


	// Shut down the Display handler //

	m_pDisplay->DeInit();


	// Shut down the Input handler //

	m_pInput->DeInit();
	}





BOOL CGame::CreateMainWindow(int Width, int Height, BOOL FullScreen)
	{

	/////////////////////////////////////////////////
	//											   //
	// Used to create the main window for the game //
	//											   //
	/////////////////////////////////////////////////



	WNDCLASSEX wndclass;

	memset(&wndclass, 0, sizeof(WNDCLASSEX));

	wndclass.cbSize			= sizeof(WNDCLASSEX);
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.lpfnWndProc	= m_WndProc;
	wndclass.hInstance		= m_hInstance;
	wndclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground	= NULL;
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= WINDOW_CLASS_NAME;

	if (!RegisterClassEx(&wndclass))
		return FALSE;


	// Create the main window //

	if (FullScreen)
		{
		m_hWnd = CreateWindowEx(WS_EX_TOPMOST, WINDOW_CLASS_NAME, m_strWndName, WS_POPUP | WS_VISIBLE, 
								 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
								 NULL, NULL, m_hInstance, NULL);
		}
	else
		{
		m_hWnd = CreateWindowEx(0, WINDOW_CLASS_NAME, m_strWndName, WS_POPUP | WS_VISIBLE, 
								 (GetSystemMetrics(SM_CXSCREEN) / 2) - (Width / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (Height / 2), Width, Height,
								 NULL, NULL, m_hInstance, NULL);
		}

	
	return (m_hWnd != NULL);
	}




void CGame::SetStage(CStage * pStage)
	{

	////////////////////////////////
	//							  //
	// Used to set the next stage //
	//							  //
	////////////////////////////////



	// Call the closing for the current stage //

	if (m_pCurrStage)
		m_pCurrStage->Closing(pStage);


	// Set the new stage variable //

	m_pCurrStage = pStage;
	

	// Transfer the game pointer to the stage //

	if (m_pCurrStage)
		{
		m_pCurrStage->Opening();
		}
	}





void CGame::Loop()
	{

	////////////////////////
	//					  //
	// The main game loop //
	//					  //
	////////////////////////

	DWORD TickCount = GetTickCount();


	// Check for exiting flag //

	if (m_Exiting)
		{
		if (m_pCurrStage)
			m_pCurrStage->Closing(NULL);

		return;
		}



	// Process all the timers //

	CTimer::DoLogic();



	// Compare the tick count for maintaining FPS //

	if (TickCount < m_LastTickCount + int(1000 / m_FPS))
		return;

	m_LastTickCount = TickCount;



	// Display the Actual FPS in debug mode 

#ifdef _DEBUG

	m_FPSCount++;

	if (TickCount > m_LastTCount + 1000)
		{
		char strText[256];

		sprintf(strText, "%d\r\n", m_FPSCount);
		OutputDebugString(strText);

		m_LastFPSCount	= m_FPSCount;
		m_FPSCount		= 0;
		m_LastTCount	= TickCount;
		}
#endif


	// Call the stage logic functions //

	if (m_pCurrStage)
		{
		// Poll the input //

		m_pInput->Poll();

		
		if (m_InTransition)
			{
			m_pTransition->DoGraphics(m_pDisplay->GetBufferBitmap());
			}
		else
			{
			m_pCurrStage->DoInput(m_pInput->GetInput());
			m_pCurrStage->DoLogic();
			m_pCurrStage->DoGraphics(m_pDisplay->GetBufferBitmap());
			}
		}



	// Check if transition is done //

	if (m_InTransition)
		if (m_pTransition->IsDone())
			{
			m_InTransition	= FALSE;
			m_pTransition	= NULL;
			}
		


	// Update the screen //

	m_pDisplay->UpdateScreen();
	}






void CGame::SetTransition(CTransition * pTransition)
	{

	////////////////////////////////
	//							  //
	// Used to set the transition //
	//							  //
	////////////////////////////////
		

	if (pTransition)
		{
		m_InTransition = TRUE;
		pTransition->Start();
		}


	m_pTransition = pTransition;
	}

