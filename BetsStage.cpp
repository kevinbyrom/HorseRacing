#include <windows.h>
#include <stdio.h>
#include "BetsStage.h"
#include "Game.h"



void CBetsStage::Opening()
	{
	CBitmap TerrainBmp;
	PALETTEENTRY * Pal;

	TerrainBmp.LoadBMP("Tile.bmp");
	Pal = TerrainBmp.GetPalette();
//	Game.SetPalette(Pal);


	CWndStage::Opening();

	EnableGUI();
	ShowCursor(FALSE);
	MouseHandlesCursor(FALSE);

	CurrPlayer	= 0;
	CursorPos	= CURSOR_PLAYER;
	}




void CBetsStage::Closing(CStage * pStage)
	{
	}




void CBetsStage::DoLogic()
	{
	switch(Player[CurrPlayer].Bet.Type)
		{
		case BET_SHOW:
			Player[CurrPlayer].Bet.Payoff = 1;
			break;

		case BET_PLACE:
			Player[CurrPlayer].Bet.Payoff = 2;
			break;

		case BET_WIN:
			Player[CurrPlayer].Bet.Payoff = 3;
			break;

		case BET_EXACTA:
			Player[CurrPlayer].Bet.Payoff = 4;
			break;

		case BET_TRIFECTA:
			Player[CurrPlayer].Bet.Payoff = 5;
			break;
		}
	}




void CBetsStage::DoGraphics(CBitmap * pBuffer)
	{
	char strText[256];


	pBuffer->Fill(16);


	// Draw the current player //

	if (CursorPos == CURSOR_PLAYER)
		pBuffer->DrawFillRect8(0, 0, 75, 9, 1);

	sprintf(strText, "PLAYER %d", CurrPlayer + 1);
	Text.DrawText(pBuffer, strText, 0, 0);	
	
	sprintf(strText, "TOTAL MONEY = $%d", Player[CurrPlayer].Money);
	Text.DrawText(pBuffer, strText, 0, 12);

	sprintf(strText, "WINS : %d     LOSSES : %d", Player[CurrPlayer].Wins, Player[CurrPlayer].Losses);
	Text.DrawText(pBuffer, strText, 0, 24);

	sprintf(strText, "PAYOFF : %d", Player[CurrPlayer].Bet.Payoff + 1);
	Text.DrawText(pBuffer, strText, 0, 36);


	// Draw the race type //

	switch(Player[CurrPlayer].Bet.Type)
		{
		case BET_WIN:
			sprintf(strText, ": WIN");
			break;

		case BET_SHOW:
			sprintf(strText, ": SHOW");
			break;

		case BET_PLACE:
			sprintf(strText, ": PLACE");
			break;

		case BET_EXACTA:
			sprintf(strText, ": EXACTA");
			break;

		case BET_TRIFECTA:
			sprintf(strText, ": TRIFECTA");
			break;
		}

	if (CursorPos == CURSOR_TYPE)
		pBuffer->DrawFillRect8(0, 48, 75, 57, 1);

	Text.DrawText(pBuffer, "BET TYPE", 0, 48);
	Text.DrawText(pBuffer, strText, 90, 48);


	// Draw the amount of money placed //

	if (CursorPos == CURSOR_MONEY)
		pBuffer->DrawFillRect8(0, 60, 75, 69, 1);

	sprintf(strText, ": $%d", Player[CurrPlayer].Bet.Total);
	Text.DrawText(pBuffer, "BET AMOUNT", 0, 60);
	Text.DrawText(pBuffer, strText, 90, 60);
	

	// Draw the first place //

	if (CursorPos == CURSOR_FIRST)
		pBuffer->DrawFillRect8(0, 84, 75, 93, 1);
	
	if (Player[CurrPlayer].Bet.Type != BET_PLACE &&
		Player[CurrPlayer].Bet.Type != BET_SHOW)		Text.DrawText(pBuffer, "WIN", 0, 84);
	else if (Player[CurrPlayer].Bet.Type == BET_PLACE)	Text.DrawText(pBuffer, "PLACE", 0, 84);
	else if (Player[CurrPlayer].Bet.Type == BET_SHOW)	Text.DrawText(pBuffer, "SHOW", 0, 84);
	
	sprintf(strText, ": %d", Player[CurrPlayer].Bet.Show[0] + 1);
	Text.DrawText(pBuffer, strText, 90, 84);


	// Draw the second place //

	if (Player[CurrPlayer].Bet.Type == BET_EXACTA ||
		Player[CurrPlayer].Bet.Type == BET_TRIFECTA)
		{
		if (CursorPos == CURSOR_SECOND)
			pBuffer->DrawFillRect8(0, 96, 75, 105, 1);

		sprintf(strText, ": %d", Player[CurrPlayer].Bet.Show[1] + 1);
		Text.DrawText(pBuffer, "PLACE", 0, 96);
		Text.DrawText(pBuffer, strText, 90, 96);
		}


	// Draw the third place //

	if (Player[CurrPlayer].Bet.Type == BET_TRIFECTA)
		{
		if (CursorPos == CURSOR_THIRD)
			pBuffer->DrawFillRect8(0, 108, 75, 117, 1);

		sprintf(strText, ": %d", Player[CurrPlayer].Bet.Show[2] + 1);
		Text.DrawText(pBuffer, "SHOW", 0, 108);
		Text.DrawText(pBuffer, strText, 90, 108);
		}


	// Draw Race //

	if (CursorPos == CURSOR_RACE)
		pBuffer->DrawFillRect8(270, 227, 319, 236, 1);

	Text.DrawText(pBuffer, "<RACE>", 270, 227);



	CWndStage::DoGraphics(pBuffer);
	}




void CBetsStage::OnKeyPressed(unsigned char key)
	{
	switch(key)
		{
		case KEY_RETURN:
			if (CursorPos == CURSOR_RACE)
				Game.SetStage(&MainStage);
			break;


		case KEY_H:
			Game.SetStage(&ShowHorsesStage);
			break;

		
		case KEY_T:
			Game.SetStage(&ShowTrackStage);
			break;


		case KEY_UP:
			CursorPos--;
			if (CursorPos < CURSOR_PLAYER)
				CursorPos = CURSOR_RACE;

			if (CursorPos == CURSOR_THIRD && Player[CurrPlayer].Bet.Type != BET_TRIFECTA)
				CursorPos = CURSOR_SECOND;
			if (CursorPos == CURSOR_SECOND && Player[CurrPlayer].Bet.Type != BET_EXACTA)
				CursorPos = CURSOR_FIRST;
			break;


		case KEY_DOWN:
			CursorPos++;
			if (CursorPos > CURSOR_RACE)
				CursorPos = CURSOR_PLAYER;

			if (CursorPos == CURSOR_SECOND && Player[CurrPlayer].Bet.Type != BET_EXACTA &&
				Player[CurrPlayer].Bet.Type != BET_TRIFECTA)
				CursorPos = CURSOR_RACE;
			break;


		case KEY_LEFT:
			switch(CursorPos)
				{
				case CURSOR_PLAYER:
					if (CurrPlayer > 0)
						CurrPlayer--;
					break;

				case CURSOR_TYPE:
					Player[CurrPlayer].DecreaseBetType();
					break;

				case CURSOR_MONEY:
					Player[CurrPlayer].DecreaseBet();
					break;

				case CURSOR_FIRST:
					Player[CurrPlayer].Bet.Show[0]--;

					if (Player[CurrPlayer].Bet.Show[0] < 0)
						Player[CurrPlayer].Bet.Show[0] = MAX_HORSES - 1;
					break;

				case CURSOR_SECOND:
					Player[CurrPlayer].Bet.Show[1]--;

					if (Player[CurrPlayer].Bet.Show[1] < 0)
						Player[CurrPlayer].Bet.Show[1] = MAX_HORSES - 1;
					break;

				case CURSOR_THIRD:
					Player[CurrPlayer].Bet.Show[2]--;

					if (Player[CurrPlayer].Bet.Show[2] < 0)
						Player[CurrPlayer].Bet.Show[2] = MAX_HORSES - 1;
					break;
				}
			break;


		case KEY_RIGHT:
			switch(CursorPos)
				{
				case CURSOR_PLAYER:
					if (CurrPlayer < MAX_PLAYERS - 1)
						CurrPlayer++;
					break;

				case CURSOR_TYPE:
					Player[CurrPlayer].IncreaseBetType();
					break;

				case CURSOR_MONEY:
					Player[CurrPlayer].IncreaseBet();
					break;

				case CURSOR_FIRST:
					Player[CurrPlayer].Bet.Show[0]++;

					if (Player[CurrPlayer].Bet.Show[0] >= MAX_HORSES)
						Player[CurrPlayer].Bet.Show[0] = 0;
					break;

				case CURSOR_SECOND:
					Player[CurrPlayer].Bet.Show[1]++;

					if (Player[CurrPlayer].Bet.Show[1] >= MAX_HORSES)
						Player[CurrPlayer].Bet.Show[1] = 0;
					break;


				case CURSOR_THIRD:
					Player[CurrPlayer].Bet.Show[2]++;

					if (Player[CurrPlayer].Bet.Show[2] >= MAX_HORSES)
						Player[CurrPlayer].Bet.Show[2] = 0;
					break;
				}
			break;
		}
	}