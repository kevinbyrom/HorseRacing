#include <windows.h>
#include "MainStage.h"
#include "Game.h"



void CMainStage::Opening()
	{
	CWndStage::Opening();

	DisableGUI();
	ShowCursor(FALSE);
	MouseHandlesCursor(FALSE);


	Timer.Enabled(FALSE);


	// Set the state //

	m_State = STATE_RACING;


	// Create the maps //

	BgMap.Create(1, 2, 16, 16, 0);
	BgMap.SetRowVal(1, 0);

	Map.Create((Track.Distance / 16) + 1, 8, 16, 16, 3);
	Map.SetColVal(Track.Distance / 16, 5);
	Map.SetRowVal(0, 4);
	Map.SetRowVal(6, 1);
	Map.SetRowVal(7, 2);


	MainView.Create(this, NULL, 0, 0, 320, 240);

	BgLayer.Create(&MainView, 0, 88, 320, 32, TRUE, FALSE, 8);
	BgLayer.SetMap(&BgMap);
	BgLayer.SetSpriteArray(TerrainSpr);

	TrackLayer.Create(&MainView, 0, 112, 320, 128, TRUE, FALSE, 8);
	TrackLayer.SetMap(&Map);
	TrackLayer.SetSpriteArray(TerrainSpr);

	ScoreLayer.Create(&MainView, 0, 12, 320, 100);
	SpriteLayer.Create(&MainView, 0, 112, 320, 128);
	
	
	// Set the horse positions //

	SetHorseStartPositions();
	

	// Begin the race //

	Race.Begin();
	}






void CMainStage::Closing(CStage * pStage)
	{
	BgMap.Destroy();
	Map.Destroy();
	}






void CMainStage::DoLogic()
	{
	Camera.X = 180;
	Camera.Y = 64;

	for (int h = 0; h < MAX_HORSES; h++)
		{
		Horse[h].Move();

		if (Horse[h].x > Camera.X)
			Camera.X = Horse[h].x;
		}

	if (Camera.X > Track.Distance)
		Camera.X = Track.Distance;

	BgLayer.SetEyePos(Camera.X / 2, 4);
	TrackLayer.SetEyePos(Camera.X, Camera.Y);
	SpriteLayer.SetEyePos(Camera.X, Camera.Y);
	ScoreLayer.SetEyePos(Camera.X, 0);

	if (Race.IsFinished())
		{
		if (m_State != STATE_FINISHED)
			{
			m_State = STATE_FINISHED;
			Timer.Enabled(TRUE);
			Timer.CountDownSecs(5);
			}
		else if (Timer.IsDone())
			{
			Timer.Enabled(FALSE);
			Race.Finished();
			}
		}
	
	}






void CMainStage::DoGraphics(CBitmap * pBuffer)
	{
	pBuffer->Fill(175);

	CWndStage::DoGraphics(pBuffer);
	}







void CMainStage::SetHorseStartPositions()
	{
	for (int h = 0; h < MAX_HORSES; h++)
		{
		Horse[h].x = 0;
		Horse[h].y = 12 + (h * 16);
		Horse[h].RunState = STANDING;
		}
	}