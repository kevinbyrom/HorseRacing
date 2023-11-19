#include <windows.h>
#include <stdio.h>
#include "Scoreboard.h"
#include "Game.h"



void CScoreboard::Draw(CBitmap * pBuffer, int x, int y)
	{
	char strText[256];
	int h;

	pBuffer->DrawFillRect(x, y, x + 199, y + 99, 7);
	pBuffer->DrawRect(x, y, x + 199, y + 99, 15);

	pBuffer->DrawFillRect(x + 2, y + 2, x + 197, y + 97, 16);
	pBuffer->DrawRect(x + 2, y + 2, x + 197, y + 97, 15);


	for (h = 0; h < MAX_HORSES; h++)
		{
		if (Race.Placed[h] != -1)
			sprintf(strText, "%d : %d", h + 1, Race.Placed[h] + 1);
		else
			sprintf(strText, "%d :", h + 1);

		Text.DrawText(pBuffer, strText, x + 14, y + 14 + (12 * h));
		}
	}