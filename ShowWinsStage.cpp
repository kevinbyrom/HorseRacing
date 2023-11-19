#include <windows.h>
#include <stdio.h>
#include "ShowWinsStage.h"
#include "Game.h"



void CShowWinsStage::Opening()
	{
	CWndStage::Opening();

	EnableGUI();
	ShowCursor(FALSE);
	MouseHandlesCursor(FALSE);
	}




void CShowWinsStage::Closing(CStage * pStage)
	{
	}




void CShowWinsStage::DoGraphics(CBitmap * pBuffer)
	{
	char strText[256];
	int p;
	int y = 0;


	pBuffer->Fill(16);

	for (p = 0; p < MAX_PLAYERS; p++)
		{
		if (Player[p].LastWin)
			{
			sprintf(strText, "PLAYER %d WON $%d", p + 1, Player[p].LastWin);
			Text.DrawText(pBuffer, strText, 0, y);
			y += 12;
			}
		}


	CWndStage::DoGraphics(pBuffer);
	}




void CShowWinsStage::OnKeyPressed(unsigned char key)
	{
	Game.StartNewRace();
	}