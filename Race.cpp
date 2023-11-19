#include <windows.h>
#include "Race.h"
#include "Game.h"



void CRace::New()
	{
	int h;


	m_NumPlaced = 0;

	for (h = 0; h < MAX_HORSES; h++)
		{
		Placed[h] = -1;
		Horse[h].Randomize();
		Horse[h].Number = h;
		Horse[h].Color = h;
		}


	Track.Randomize();
	}




void CRace::Begin()
	{
	int h;

	m_Finished = FALSE;

	for (h = 0; h < MAX_HORSES; h++)
		Horse[h].RaceStarted();
	}




void CRace::HorseFinished(int HNum)
	{
	if (m_NumPlaced >= MAX_HORSES)
		return;

	Placed[m_NumPlaced] = HNum;
	m_NumPlaced++;


	if (m_NumPlaced >= MAX_HORSES)
		m_Finished = TRUE;
	}




void CRace::Finished()
	{
	CalculateWins();
	Game.SetStage(&ShowWinsStage);
	}



void CRace::CalculateWins()
	{
	int p;


	for (p = 0; p < MAX_PLAYERS; p++)
		{
		switch(Player[p].Bet.Type)
			{
			case BET_WIN:
				if (Player[p].Bet.Show[0] == Placed[0])
					Player[p].BetWon();
				else
					Player[p].BetLost();
				break;


			case BET_PLACE:
				if (Player[p].Bet.Show[0] == Placed[0] ||
					Player[p].Bet.Show[0] == Placed[1])
					Player[p].BetWon();
				else
					Player[p].BetLost();
				break;


			case BET_SHOW:
				if (Player[p].Bet.Show[0] == Placed[0] ||
					Player[p].Bet.Show[0] == Placed[1] ||
					Player[p].Bet.Show[0] == Placed[2])
					Player[p].BetWon();
				else
					Player[p].BetLost();
				break;


			case BET_EXACTA:
				if (Player[p].Bet.Show[0] == Placed[0] &&
					Player[p].Bet.Show[1] == Placed[1])
					Player[p].BetWon();
				else
					Player[p].BetLost();
				break;


			case BET_TRIFECTA:
				if (Player[p].Bet.Show[0] == Placed[0] &&
					Player[p].Bet.Show[1] == Placed[1] &&
					Player[p].Bet.Show[2] == Placed[2])
					Player[p].BetWon();
				else
					Player[p].BetLost();
				break;
			}
		}
	}