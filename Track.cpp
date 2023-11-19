#include <windows.h>
#include "Track.h"




void CTrack::Randomize()
	{
	switch (rand() % 3)
		{
		case 0:
			RandomizeShort();
			break;

		case 1:
			RandomizeMedium();
			break;

		case 2:
			RandomizeLong();
			break;
		}
	}



void CTrack::RandomizeShort()
	{
	Type		= TRACK_TYPE_SHORT;
	Distance	= (220 + (rand() % 10)) * 8; 
	Terrain		= rand() % 3;
	}



void CTrack::RandomizeMedium()
	{
	Type		= TRACK_TYPE_MEDIUM;
	Distance	= (300 + (rand() % 20)) * 8;
	Terrain		= rand() % 3;
	}



void CTrack::RandomizeLong()
	{
	Type		= TRACK_TYPE_LONG;
	Distance	= (400 + (rand() % 20)) * 8;
	Terrain		= rand() % 3;
	}