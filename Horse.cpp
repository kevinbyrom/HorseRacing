#include <windows.h>
#include <stdio.h>
#include "Horse.h"
#include "Game.h"



void CHorse::Draw(CBitmap * pBuffer, int dx, int dy)
	{
	char strText[50];

	HorseSpr[(Color * 2) + AnimPos].Draw(pBuffer, dx - width, dy - height);
	//Buffer.DrawFillRect(dx - width, dy - height, dx, dy, 0);
	//sprintf(strText, "%.2f  %d", Stamina.Val, RunState);
	//Text.DrawText(Buffer, strText,dx - width, dy - height);
	}




void CHorse::RaceStarted()
	{
	Finished		= FALSE;
	RunState		= RUNNING;
	Stamina.Val		= Stamina.Max;

	AnimPos = 0;
	AnimTimer.Enabled(TRUE);

	//RunTimer.Create();
	}




void CHorse::Move()
	{
	int rval;


	if (RunTimer.IsDone())
		{
		rval = rand() % 100;

		if (rval < 25)
			{
			Stamina.Val += 30;
			if (Stamina.Val > Stamina.Max)
				Stamina.Val = Stamina.Max;

			Accel.Max = Speed.Max * .5;

			RunState = PACING;
			RunTimer.CountDown(3000 + (5000 * ((100 - Stamina.Max) / 100)));
			//OutputDebugString("PACING\r\n");
			}
		else if (rval < 90 || Stamina.Val < 50)
			{
			Stamina.Val -= 10;

			Accel.Max = Speed.Max;

			RunState = RUNNING;
			RunTimer.CountDown(3000);
			//OutputDebugString("RUNNING\r\n");
			} 
		else if (rval < 99)
			{
			Stamina.Val -= 50;
			if (Stamina.Val < 0)
				Stamina.Val = 0;

			Accel.Max = 10;
			
			RunState = BOOSTING;
			RunTimer.CountDown(3000 + (3000 * (Stamina.Max / 100)));
			//OutputDebugString("BOOSTING\r\n");
			}
		else
			{
			Stamina.Val -= 50;
			Accel.Max = 11 ;
			RunState = SUPER_BOOSTING;
			OutputDebugString("SUPER BOOSTING\r\n");
			RunTimer.CountDown(6000);
			}
		}


	switch(RunState)
		{
		case STANDING:
			Stamina.Val  = Stamina.Max;
			Speed.Val	 = 0;
			Accel.Val	 = 0;
			break;


		case RUNNING:
			//Speed.Val	 = Speed.Max;
			break;


		case PACING:
			//Speed.Val	 = Speed.Max * .5;
			break;


		case BOOSTING:
			//Speed.Val	 = 10;
			break;

		case SUPER_BOOSTING:
			//Speed.Val	 = 12;
			break;
		}


	if (Speed.Val < Accel.Max)
		{
		Speed.Val += .1;
		if (Speed.Val > Accel.Max)
			Speed.Val = Accel.Max;
		}
	else if (Speed.Val > Accel.Max)
		{
		Speed.Val -= .1;
		if (Speed.Val < Accel.Max)
			Speed.Val = Accel.Max;
		}


	// Calculate penalties //

	
	// Calculate the next state //

	if (Stamina.Val <= 0 && RunState != SUPER_BOOSTING)
		{
		Stamina.Val += 30;
		if (Stamina.Val > Stamina.Max)
			Stamina.Val = Stamina.Max;

		Accel.Max = Speed.Max * .5;

		RunState = PACING;
		RunTimer.CountDown(5000 + (5000 * ((100 - Stamina.Max) / 100)));
		}
	//else if (Stamina.Val > (1000 - Stamina.Max) && RunState == PACING)
	//	{
	//	Stamina.Val = Stamina.Max;
	//	RunState = RUNNING;
	//	OutputDebugString("RUNNING\r\n");
	//	}


	// Do the movement //

	x += ((Speed.Val * 3 ) / 10) + 1;


	// Check if the horse finished //

	if (x >= Track.Distance && !Finished)
		{
		Race.HorseFinished(Number);
		Finished = TRUE;
		}


	// Increase the animation //

	if (AnimTimer.IsDone())
		{
		AnimPos++;

		if (AnimPos >= 2)
			AnimPos = 0;

		if (RunState == PACING)
			AnimTimer.CountDown(150);
		else if (RunState == RUNNING)
			AnimTimer.CountDown(80);
		else
			AnimTimer.CountDown(50);
		}	
	}




void CHorse::Randomize()
	{
	Speed.Max		= (rand() % 5) + 5;
	Accel.Max		= (rand() % 5) + 5;
	Stamina.Max		= (rand() % 50) + 50;
	}
