#ifndef __TRACK_H
#define __TRACK_H


#define TRACK_TYPE_SHORT	0
#define TRACK_TYPE_MEDIUM	1
#define TRACK_TYPE_LONG		2


class CTrack
	{
	public:

		int Type;
		int Terrain;
		int Distance;


		void Randomize();
		void RandomizeShort();
		void RandomizeMedium();
		void RandomizeLong();
	};


#endif