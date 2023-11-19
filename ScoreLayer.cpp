#include <windows.h>
#include "ScoreLayer.h"
#include "Game.h"



void CScoreLayer::Create(CView * pParentView, int x, int y, int width, int height, int BPP)
	{
	// Call the default create //

	CLayer::Create(pParentView, x, y, width, height, BPP);


	// Set default property values //

	m_EyeX = 0;
	m_EyeY = 0;
	}






void CScoreLayer::DoGraphics(CBitmap * pBuffer)
	{

	/////////////////////////
	//					   //
	// Paint event handler //
	//					   //
	/////////////////////////


	int LeftEyeX,
		TopEyeY,
		ScoreX,
		ScoreY;


	// Find the start & end tiles //

	LeftEyeX	= (m_EyeX - (m_Width * .5));
	TopEyeY		= (m_EyeY - (m_Height * .5));


	// Draw the scoreboard //

	ScoreX = int(Track.Distance - 100 - LeftEyeX);
	ScoreY = 0;

	if (ScoreX < 0 || ScoreX >= m_Width + 200 ||
		ScoreY < 0 || ScoreY >= m_Height)
		return;

	Scoreboard.Draw(pBuffer, m_X + ScoreX, m_Y);
	}