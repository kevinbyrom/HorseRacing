#ifndef __HORSE_H
#define __HORSE_H


#include "Gamelib\Header\Bitmap.h"
#include "Gamelib\Header\Timer.h"


#define MAX_HORSES		6


struct ODDS
	{
	int From, To;
	};



struct ATTRIBUTE
	{
	float Val;
	float Max;
	float Bonus;
	};


#define STANDING		0
#define PACING			1
#define RUNNING			2
#define BOOSTING		3
#define SUPER_BOOSTING	4


class CHorse
	{
	public:

		CHorse()	{ x = 24; y = 24; width = 38; height = 26; color = 0; RunState = STANDING; }

		char strName[50];

		float x, y;
		int width, height;
		int color;

		ATTRIBUTE Speed,
				  Accel,
				  Stamina;

		int Number;
		int BestTerrain;
		int Luck;
		int RunState;
		int Finished;
		int AnimPos;

		char HairColor,
			 Color;

		ODDS Odds;

		CTimer RunTimer,
			   AnimTimer;


	public:

		void Draw(CBitmap * pBuffer, int dx, int dy);
		void RaceStarted();
		void Move();

		void Randomize();
	};



#endif