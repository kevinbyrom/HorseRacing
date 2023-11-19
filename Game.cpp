#include <windows.h>
#include "Game.h"


CHorseRacingGame	Game;
CBetsStage			BetsStage;
CShowTrackStage		ShowTrackStage;
CShowHorsesStage	ShowHorsesStage;
CShowWinsStage		ShowWinsStage;
CMainStage			MainStage;
CRace				Race;
CPlayer				Player[MAX_PLAYERS];
CHorse				Horse[MAX_HORSES];
CScoreboard			Scoreboard;
CMap				BgMap, Map;
CTrack				Track;
CText				Text;
CSprite				TerrainSpr[10];
CSprite				HorseSpr[12];



void CHorseRacingGame::Opening()
	{
	// Load the sprites //

	LoadTerrainSprites();
	LoadHorseSprites();


	// Load the fonts //	

	Text.Load("FONT.BMP", 7, 12);
	

	// Start a new race //

	StartNewRace();
	}




void CHorseRacingGame::Closing()
	{
	}





void CHorseRacingGame::StartNewRace()
	{
	int p;


	Race.New();

	for (p = 0; p < MAX_PLAYERS; p++)
		Player[p].ClearBets();


	SetStage(&BetsStage);
	}




void CHorseRacingGame::LoadTerrainSprites()
	{
	CBitmap TerrainBmp;
//	PALETTEENTRY * Pal;

	TerrainBmp.LoadBMP("GrassT.bmp");
//	Pal = TerrainBmp.GetPalette();
//	SetPalette(Pal);

	for (int i = 0; i < 10; i++)
		TerrainSpr[i].Grab(&TerrainBmp, (i * 16) + (i + 1), 1, 16, 16, 255);
	}




void CHorseRacingGame::LoadHorseSprites()
	{
	CBitmap HorseBmp;
	PALETTEENTRY * Pal;




	//HorseBmp.LoadBMP("HAnim.bmp");

	//for (int i = 0; i < 4; i++)
	//	HorseSpr[i].Grab(&HorseBmp, (i * 58) + (i + 1), 1, 58, 40, 255);

	HorseBmp.LoadBMP("GrYoshi.bmp");
	Pal = HorseBmp.GetPalette();
	SetPalette(Pal);

	HorseSpr[0].Grab(&HorseBmp, 1, 34, 36, 26, 255);
	HorseSpr[1].Grab(&HorseBmp, 38, 34, 36, 26, 255);


	HorseBmp.Destroy();
	HorseBmp.LoadBMP("BlYoshi.bmp");
	HorseSpr[2].Grab(&HorseBmp, 1, 34, 36, 26, 255);
	HorseSpr[3].Grab(&HorseBmp, 38, 34, 36, 26, 255);


	HorseBmp.Destroy();
	HorseBmp.LoadBMP("YeYoshi.bmp");
	HorseSpr[4].Grab(&HorseBmp, 1, 34, 36, 26, 255);
	HorseSpr[5].Grab(&HorseBmp, 38, 34, 36, 26, 255);


	HorseBmp.Destroy();
	HorseBmp.LoadBMP("OrYoshi.bmp");
	HorseSpr[6].Grab(&HorseBmp, 1, 34, 36, 26, 255);
	HorseSpr[7].Grab(&HorseBmp, 38, 34, 36, 26, 255);


	HorseBmp.Destroy();
	HorseBmp.LoadBMP("ViYoshi.bmp");
	HorseSpr[8].Grab(&HorseBmp, 1, 34, 36, 26, 255);
	HorseSpr[9].Grab(&HorseBmp, 38, 34, 36, 26, 255);


	HorseBmp.Destroy();
	HorseBmp.LoadBMP("RdYoshi.bmp");
	HorseSpr[10].Grab(&HorseBmp, 1, 34, 36, 26, 255);
	HorseSpr[11].Grab(&HorseBmp, 38, 34, 36, 26, 255);
	}


