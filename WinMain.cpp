#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "WinMain.h"
#include "Game.h"
#include "Gamelib\Header\Timer.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
	{
	MSG msg;
	CTimer Timer;


	srand(time(NULL));

	if (!Game.Init(hInstance, WndProc, "Horse Racing", 320, 240, 8, TRUE, 30))
		return 0;

	Game.Opening();

	while(!Game.Exiting())
		{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{ 
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
			}
		else
			{
			Game.Loop();
			}
		}



	Game.Closing();
	Game.ShutDown();


	return (msg.wParam);
	}





LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
	switch(msg)
		{
		case WM_CREATE:
			ShowCursor(FALSE);
			return 1;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}


	return DefWindowProc(hWnd, msg, wParam, lParam);
	}
