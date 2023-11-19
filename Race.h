#ifndef __RACE_H
#define __RACE_H


#include "Horse.h"


class CRace
	{
	public:

		void New();
		void Begin();

		BOOL IsFinished()	{ return m_Finished; }		
		void HorseFinished(int HNum);

		void Finished();
		void CalculateWins();

		int Placed[MAX_HORSES];


	protected:

		BOOL m_Finished;
		int m_NumPlaced;
	};



#endif