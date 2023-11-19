#ifndef __PLAYER_H
#define __PLAYER_H


#include "Horse.h"


#define BET_WIN			0
#define BET_PLACE		1
#define BET_SHOW		2
#define BET_EXACTA		3
#define BET_TRIFECTA	4



class CBet
	{
	public:
		
		CBet()	{ Type	= BET_WIN; 
				  Total	= 0; } 

		int Type;
		int Show[MAX_HORSES];
		int Payoff;
		int Total;
	};



class CPlayer
	{
	public:

		CPlayer()		{ Broke = 0; Money = 2000; }

		int Broke;
		int Money;
		int Wins;
		int Losses;
		int LastWin;

		CBet Bet;

		void DecreaseBetType()		{ Bet.Type--; if (Bet.Type < BET_WIN) Bet.Type = BET_TRIFECTA; }
		void IncreaseBetType()		{ Bet.Type++; if (Bet.Type > BET_TRIFECTA) Bet.Type = BET_WIN; }

		void DecreaseBet()		{ Bet.Total -= 50; if (Bet.Total < 0) Bet.Total = 0; }
		void IncreaseBet()		{ if (Bet.Total + 50 <= Money) Bet.Total += 50; }

		void BetWon();
		void BetLost();

		void ClearBets();
	};


#endif