#ifndef __GAME_H
#define __GAME_H


#include "Gamelib\Header\DXGame2D.h"
#include "BetsStage.h"
#include "ShowHorsesStage.h"
#include "ShowTrackStage.h"
#include "ShowWinsStage.h"
#include "MainStage.h"
#include "Race.h"
#include "Player.h"
#include "Horse.h"
#include "Scoreboard.h"
#include "Gamelib\Header\Map.h"
#include "Track.h"
#include "Gamelib\Header\Text.h"


#define MAX_PLAYERS		4


extern CBetsStage			BetsStage;
extern CShowHorsesStage		ShowHorsesStage;
extern CShowTrackStage		ShowTrackStage;
extern CShowWinsStage		ShowWinsStage;
extern CMainStage			MainStage;
extern CRace				Race;
extern CPlayer				Player[MAX_PLAYERS];
extern CHorse				Horse[MAX_HORSES];
extern CScoreboard			Scoreboard;
extern CMap					BgMap, Map;
extern CTrack				Track;
extern CText				Text;
extern CSprite				TerrainSpr[10];
extern CSprite				HorseSpr[12];


class CHorseRacingGame : public CDXGame
	{
	public:

		virtual void Opening();
		virtual void Closing();

		void StartNewRace();


	protected:

		void LoadTerrainSprites();
		void LoadHorseSprites();
	};


extern CHorseRacingGame Game;


#endif