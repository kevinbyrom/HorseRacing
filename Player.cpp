#include <windows.h>
#include "Player.h"
#include "Game.h"



void CPlayer::BetWon()
	{
	LastWin	= Bet.Total * Bet.Payoff;

	Money	+= LastWin;

	Wins++;
	}




void CPlayer::BetLost()
	{
	LastWin	= 0;
	
	Money	-= Bet.Total;

	Losses++;

	if (Money <= 0)
		Broke = 1;
	}




void CPlayer::ClearBets()
	{
	Bet.Type = BET_WIN;
	memset(Bet.Show, 0, sizeof(int) * MAX_HORSES);
	}