#include <windows.h>
#include "..\Header\MapLayer.h"
#include "..\Header\Formulas.h"




void CMapLayer::Create(CView * pParentView, int x, int y, int width, int height, BOOL WrapX, BOOL WrapY, int BPP)
	{
	// Call the default create //

	CLayer::Create(pParentView, x, y, width, height, BPP);


	// Set default property values //

	m_WrapX = WrapX;
	m_WrapY = WrapY;

	m_EyeX = 0;
	m_EyeY = 0;

	m_pMap		= NULL;
	m_pSprite	= NULL;
	}






void CMapLayer::SetEyePos(float x, float y)		
	{ 
	float XLimit, 
		  YLimit;

	
	CLayer::SetEyePos(x, y);


	if (m_WrapX)
		{
		XLimit = m_pMap->NumX * m_pMap->ResX;
		
		if (m_EyeX < 0 || m_EyeX >= XLimit)
			m_EyeX = FLOAT_OVERLAP(m_EyeX, XLimit);
		}


	if (m_WrapY)
		{
		YLimit = m_pMap->NumY * m_pMap->ResY;
		
		if (m_EyeY < 0 || m_EyeY >= YLimit)
			m_EyeY = FLOAT_OVERLAP(m_EyeY, YLimit);
		}
	}





void CMapLayer::MoveEyePos(float xdelta, float ydelta)	
	{ 
	float XLimit, 
		  YLimit;


	CLayer::MoveEyePos(xdelta, ydelta); 


	if (m_WrapX)
		{
		XLimit = m_pMap->NumX * m_pMap->ResX;
		
		if (m_EyeX < 0 || m_EyeX >= XLimit)
			m_EyeX = FLOAT_OVERLAP(m_EyeX, XLimit);
		}


	if (m_WrapY)
		{
		YLimit = m_pMap->NumY * m_pMap->ResY;
		
		if (m_EyeY < 0 || m_EyeY >= YLimit)
			m_EyeY = FLOAT_OVERLAP(m_EyeY, YLimit);
		}
	}





void CMapLayer::DoGraphics(CBitmap * pBuffer)
	{

	/////////////////////////
	//					   //
	// Paint event handler //
	//					   //
	/////////////////////////


	int NumTilesX,
		NumTilesY,
		StartTileX,
		StartTileY,
		EndTileX,
		EndTileY,
		LeftEyeX,
		TopEyeY,
		RightEyeX,
		BottomEyeY,
		OffsetX,
		OffsetY,
		ResX,
		ResY,
		MapNumX,
		MapNumY,
		x,
		y,
		TileValX,
		TileValY,
		TilePos,
		SprXPos,
		SprYPos,
		SprSX,
		SprSY,
		SprWidth,
		SprHeight;

	char * pTile;



	// Return if there is no map or sprite //

	if (m_pMap == NULL || m_pSprite == NULL)
		return;



	// Get the resolutions //

	ResX = m_pMap->ResX;
	ResY = m_pMap->ResY;


	MapNumX = m_pMap->NumX;
	MapNumY = m_pMap->NumY;

	pTile = m_pMap->Tile;



	// Find the start & end tiles //

	LeftEyeX	= (m_EyeX - (m_Width * .5));
	TopEyeY		= (m_EyeY - (m_Height * .5));
	RightEyeX	= (m_EyeX + (m_Width * .5));
	BottomEyeY	= (m_EyeY + (m_Height * .5));

	StartTileX = (LeftEyeX / ResX) - 1;
	StartTileY = (TopEyeY / ResY) - 1;
	EndTileX   = RightEyeX / ResX;
	EndTileY   = BottomEyeY / ResY;



	// Return if drawing tiles out of the limits //


	if ((StartTileX < 0 && EndTileX < 0) ||
		(StartTileX >= MapNumX && EndTileX >= MapNumX) ||
		(StartTileY < 0 && EndTileY < 0) ||
		(StartTileY >= MapNumY && EndTileY >= MapNumY))
		return;



	// Calculate how many tiles to draw //
	
	NumTilesX = EndTileX - StartTileX + 1;
	NumTilesY = EndTileY - StartTileY + 1;



	// Find the offset of the tile //

	OffsetX = LeftEyeX - (StartTileX * ResX);
	OffsetY = TopEyeY - (StartTileY * ResY);



	// Draw the tiles //

	if (NumTilesX > 0 && NumTilesY > 0)
		{
		for (y = 0; y < NumTilesY; y++)
			{
			for (x = 0; x < NumTilesX; x++)
				{
				TileValX = StartTileX + x;
				TileValY = StartTileY + y;


				// Wrap the map if wrap variables are set //

				if (m_WrapX)
					{
					if (TileValX < 0 || TileValX >= MapNumX)
						TileValX = OVERLAP(TileValX, MapNumX);
					}


				if (m_WrapY)
					{
					if (TileValY < 0 || TileValY >= MapNumY)
						TileValY = OVERLAP(TileValY, MapNumY);
					}


				

				if (TileValX < 0 || TileValX >= MapNumX ||
					TileValY < 0 || TileValY >= MapNumY)
					continue;


				TilePos = TileValX + (TileValY * MapNumX);
				
				
				if (pTile[TilePos] == 0)
					continue;

				SprXPos		= m_X + ((x * ResX) - OffsetX);
				SprYPos		= m_Y + ((y * ResY) - OffsetY);

				m_pSprite[pTile[TilePos]].Draw(pBuffer, SprXPos, SprYPos);
				}
			}
		}
	}