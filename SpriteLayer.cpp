#include <windows.h>
#include "SpriteLayer.h"
#include "Game.h"



void CSpriteLayer::Create(CView * pParentView, int x, int y, int width, int height, int BPP)
	{
	// Call the default create //

	CLayer::Create(pParentView, x, y, width, height, BPP);


	// Set default property values //

	m_EyeX = 0;
	m_EyeY = 0;
	}






void CSpriteLayer::DoGraphics(CBitmap * pBuffer)
	{

	/////////////////////////
	//					   //
	// Paint event handler //
	//					   //
	/////////////////////////


	int LeftEyeX,
		TopEyeY,
		HorseX,
		HorseY;

	CHorse DrawHorse[MAX_HORSES];
	

	// Find the start & end tiles //

	LeftEyeX	= (m_EyeX - (m_Width * .5));
	TopEyeY		= (m_EyeY - (m_Height * .5));


	// Arrange the horses //

	for (int h = 0; h < MAX_HORSES; h++)
		{
		// Calculate the view X/Y position of the horses //

		HorseX = int(Horse[h].x - LeftEyeX);
		HorseY = int(Horse[h].y - TopEyeY);


		// Return if drawing horses out of the limits //

		if (HorseX < 0 || HorseX >= m_Width + Horse[h].width ||
			HorseY < 0 || HorseY >= m_Height + Horse[h].height)
			continue;


		// Draw the horse //

		Horse[h].Draw(pBuffer, m_X + HorseX, m_Y + HorseY);
		}
	}