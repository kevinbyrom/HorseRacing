#ifndef __GAME_H
#define __GAME_H


#define WINDOW_CLASS_NAME		"GAMELIBCLASS"


class GAME
	{
	public:

		/////////////////////////////
		// Init / DeInit functions //
		/////////////////////////////

		BOOL Init(HINSTANCE hInstance, WNDPROC WProc, LPCTSTR lpstrWndName, int Width = 320, int Height = 240, int BPP = 8, BOOL FullScreen = TRUE, int FPS = 30);
		void ShutDown();

		void End()								{ m_Exiting = TRUE; }
		BOOL Exiting()							{ return m_Exiting; }


		///////////////////////////////////
		// Overridable Virtual Functions //
		///////////////////////////////////
		
		virtual void Loop();
		virtual void Opening(){}
		virtual void Closing(){}


		////////////////////////////////////////
		// State and Transition set functions //
		////////////////////////////////////////

		void SetStage(CStage * pStage);
		void SetTransition(CTransition * pTransition);


		///////////////////////////////
		// Property attain functions //
		///////////////////////////////

		HINSTANCE	GetInstance()				{ return Instance; }
		HWND		GetWindow()					{ return Wnd; }

		int GetScreenWidth()					{ return DDraw.GetScreenWidth(); }
		int GetScreenHeight()					{ return DDraw.GetScreenHeight(); }
		int GetBPP()							{ return DDraw.GetBPP(); }


		//////////////////////
		// Palette Routines //
		//////////////////////

		//void SetPalette(PALETTEENTRY * pPal)	{ m_pDisplay->SetPalette(pPal); }
		//PALETTEENTRY * GetPalette()				{ return m_pDisplay->GetPalette(); }
		

		////////////////////
		// Debug Routines //
		////////////////////

		int GetFPSCount()						{ return LastFPSCount; }


	protected:

		///////////////////////
		// Window Properties //
		///////////////////////

		HINSTANCE	Instance;
		HWND		Wnd;
		char		WndName[256];
		WNDPROC		WndProc;


		STAGE		* CurrStage;
		TRANSITION	* Transition;


		/////////////////
		// Game States //
		/////////////////

		BOOL	Exiting;
		BOOL	InTransition;
		

		////////////////////////////////
		// Frames Per Second Counters //
		////////////////////////////////

		int		FPS;
		DWORD	LastTickCount;


		////////////////////////
		// Debug FPS Counters //
		////////////////////////

		int FPSCount;
		int LastFPSCount;
		DWORD LastTCount;


		virtual BOOL CreateMainWindow(int Width, int Height, BOOL FullScreen);
	};




#endif