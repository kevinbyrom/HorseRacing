#include <windows.h>
#include <stdio.h>
#include "ShowHorsesStage.h"
#include "Game.h"



void CShowHorsesStage::Opening()
	{
	CWndStage::Opening();

	EnableGUI();
	ShowCursor(FALSE);
	MouseHandlesCursor(FALSE);

	m_HInfoBmp.Create(150, 70, 8);
	}




void CShowHorsesStage::Closing(CStage * pStage)
	{
	//m_HInfoBmp.Destroy();
	}




void CShowHorsesStage::DoGraphics(CBitmap * pBuffer)
	{
	int i;


	pBuffer->Fill(0);


	for (i = 0; i < 3; i++)
		{
		DrawHorseInfo(pBuffer, i, 5, i * 80 + 5);
		DrawHorseInfo(pBuffer, i + 3, 165, i * 80 + 5);
		}


	CWndStage::DoGraphics(pBuffer);
	}




void CShowHorsesStage::OnKeyPressed(unsigned char key)
	{
	Game.SetStage(&BetsStage);
	}





void CShowHorsesStage::DrawHorseInfo(CBitmap * pBuffer, int HNum, int x, int y)
	{
	m_HInfoBmp.Fill8(1);


	sprintf(m_strText, "HORSE #%d", HNum + 1);
	Text.DrawText8(&m_HInfoBmp, m_strText, 10, 7);


	// Draw the speed //

	DrawStat(&m_HInfoBmp, "SPEED   :", 10, 22, Horse[HNum].Speed.Max);  


	// Draw the accel //

	DrawStat(&m_HInfoBmp, "ACCEL   :", 10, 37, Horse[HNum].Accel.Max);


	// Draw the stamina //

	DrawStat(&m_HInfoBmp, "STAMINA :", 10, 52, int(Horse[HNum].Stamina.Max / 10));



	m_HInfoBmp.DrawRect8(0, 0, 149, 69, 8);
	pBuffer->Blit8(&m_HInfoBmp, x, y, 150, 70, 0, 0);
	}



void CShowHorsesStage::DrawStat(CBitmap * pBuffer, char * strText, int x, int y, int NumBars)
	{
	int i;
	int BarX,
		BarY;


	Text.DrawText8(pBuffer, strText, x, y);
	
	pBuffer->DrawFillRect8(x + 70, y, x + 131, y + 8, 16);

	for (i = 0; i < NumBars; i++)
		{
		BarX = (x + 70) + (i * 5) + (i + 1);
		BarY = y + 1;

		pBuffer->DrawFillRect8(BarX, BarY, BarX + 4, BarY + 6, 35);
		pBuffer->DrawRect8(BarX, BarY, BarX + 4, BarY + 6, 33);
		}
	}