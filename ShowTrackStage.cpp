#include <windows.h>
#include <stdio.h>
#include "ShowTrackStage.h"
#include "Game.h"



void CShowTrackStage::Opening()
	{
	CWndStage::Opening();

	Track.Randomize();

	EnableGUI();
	ShowCursor(FALSE);
	MouseHandlesCursor(FALSE);
	}




void CShowTrackStage::Closing(CStage * pStage)
	{
	}




void CShowTrackStage::DoGraphics(CBitmap * pBuffer)
	{
	char strText[256];
	int i;


	pBuffer->Fill(0);

	
	Text.DrawText(pBuffer, "TRACK INFO", 0, 0);
	Text.DrawText(pBuffer, "DISTANCE", 0, 24);
	Text.DrawText(pBuffer, "TERRAIN", 0, 48);


	switch(Track.Type)
		{
		case TRACK_TYPE_SHORT:
			Text.DrawText(pBuffer, ": SHORT", 100, 24);
			break;


		case TRACK_TYPE_MEDIUM:
			Text.DrawText(pBuffer, ": MEDIUM", 100, 24);
			break;


		case TRACK_TYPE_LONG:
			Text.DrawText(pBuffer, ": LONG", 100, 24);
			break;
		}


	CWndStage::DoGraphics(pBuffer);
	}




void CShowTrackStage::OnKeyPressed(unsigned char key)
	{
	Game.SetStage(&BetsStage);
	}