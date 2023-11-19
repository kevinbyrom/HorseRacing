#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "..\Header\Sprite.h"
#include "..\Header\Memory.h"


#define ROUND(x)	x - int(x) >= .5 ? int(x) + 1 : int(x)


//////////////////////////////
//							//
// Constructor / Destructor //
//							//
//////////////////////////////



CSprite::CSprite()
	{
	m_Width			= 0;
	m_Height		= 0;
	m_BPP			= 0;
	m_TransClr8		= 0;
	m_TransClr16	= 0;

	m_pBits8		= NULL;
	m_pBits16		= NULL;
	}




CSprite::~CSprite()
	{
	Unload();
	}




////////////////////////
//	                  //
// Acquiring routines //
//	                  //
////////////////////////



void CSprite::Grab(CBitmap * pSrc, int x, int y, int width, int height, U32 transclr)
	{

	//////////////////////////////////////////////////////
	//													//
	// Used to grab a sprite image from a loaded bitmap //
	//													//
	//////////////////////////////////////////////////////


	U8  * pSrcBits8;
	U16 * pSrcBits16;
	U32 SrcPitch;

	
	pSrcBits8	= pSrc->GetBits8();
	pSrcBits16	= (U16 *)pSrcBits8;
	SrcPitch	= pSrc->GetPitch();

	m_BPP		= pSrc->GetBPP();
	m_Width		= width;
	m_Height	= height;


	m_pBits8	= (U8 *)malloc((m_Width * m_Height) * (m_BPP / 8));
	m_pBits16	= (U16 *)m_pBits8;


	if (m_BPP == 8)
		m_TransClr8		= (U8)transclr;
	else if (m_BPP == 16)
		m_TransClr16	= (U16)transclr;



	// Read each row //

	for (U32 ypos = 0; ypos < m_Height; ypos++)
		{
		switch (m_BPP)
			{
			case 8:
				memcpy(&m_pBits8[ypos * m_Width], &pSrcBits8[x + ((y + ypos) * SrcPitch)], m_Width);
				break;

			case 16:
				memcpy16(&m_pBits16[ypos * m_Width], &pSrcBits16[x + ((y + ypos) * SrcPitch)], m_Width);
				break;
			}
		}
	}




void CSprite::Unload()
	{

	///////////////////////////////
	//							 //
	// Used to unload the sprite //
	//							 //
	///////////////////////////////


	if (m_pBits8 != NULL)
		free(m_pBits8);

	m_pBits8	= NULL;
	m_pBits16	= NULL;
	}





///////////////////////
//					 //
// Blitting routines //
//					 //
///////////////////////




void CSprite::Blit(CBitmap * pDest, int x, int y)
	{

	///////////////////////////////////////////
	//										 //
	// Used to blit the sprite onto a bitmap //
	//										 //
	///////////////////////////////////////////


	int sx,
		sy;

	int	width, 
		height;
	
	
	// Set default variables //

	sx		= 0;
	sy		= 0;
	width	= m_Width;
	height	= m_Height;


	// Perform clipping if necessary //

	if (x < 0)
		{
		x = 0;
		sx = -x;
		width -= sx;
		}


	if (y < 0)
		{
		y = 0;
		sy = -y;
		height -= sy;
		}


	if (x + width >= pDest->GetWidth())
		width = pDest->GetWidth() - x;


	if (y + height >= pDest->GetHeight())
		height = pDest->GetHeight() - y;


	// Return if the sprite is out of the bitmap range //

	if (width <= 0 || height <= 0)
		return;
		

	// Call the proper Blit function based on the BPP //

	switch(m_BPP)
		{
		case 8:
			Blit8(pDest, x, y, width, height, sx, sy);
			return;


		case 16:
			Blit16(pDest, x, y, width, height, sx, sy);
			return;
		}
	}




void CSprite::Blit8(CBitmap * pDest, int x, int y, int width, int height, int sx, int sy)
	{

	////////////////////////////////////////////////
	//											  //
	// Used to blit an 8 bit sprite onto a bitmap //
	//											  //
	////////////////////////////////////////////////


	U8 * pCopyBits8;

	U8 * pDestBits8,
	   * pCopyDestBits8;

	U32 DestPitch;
	U32 ypos;


	// If the sprite has not been initialized then return //

	if (m_pBits8 == NULL)
		return;


	// Get the destination pointer and bits //

	DestPitch		= pDest->GetPitch();
	pDestBits8		= pDest->GetBits8();


	// Blit the sprite to the destination bitmap //

	pCopyBits8		= &m_pBits8[sx + (sy * m_Width)];
	pCopyDestBits8  = &pDestBits8[x + (y * DestPitch)];


	for (ypos = 0; ypos < height; ypos++)
		{
		memcpy(pCopyDestBits8, pCopyBits8, width);

		pCopyBits8		+= m_Width;
		pCopyDestBits8	+= DestPitch;
		}
	}





void CSprite::Blit16(CBitmap * pDest, int x, int y, int width, int height, int sx, int sy)
	{

	////////////////////////////////////////////////
	//											  //
	// Used to blit a 16 bit sprite onto a bitmap //
	//											  //
	////////////////////////////////////////////////


	U16 * pCopyBits16;

	U16 * pDestBits16,
	    * pCopyDestBits16;

	U32 DestPitch;
	U32 ypos;


	// If the sprite has not been initialized then return //
	
	if (m_pBits16 == NULL)
		return;


	// Get the destination pointer and bits //

	DestPitch		= pDest->GetPitch();
	pDestBits16		= pDest->GetBits16();


	// Blit the sprite to the destination bitmap //

	pCopyBits16		= &m_pBits16[sx + (sy * m_Width)];
	pCopyDestBits16  = &pDestBits16[x + (y * DestPitch)];


	for (ypos = 0; ypos < height; ypos++)
		{
		memcpy16(pCopyDestBits16, pCopyBits16, width);

		pCopyBits16		+= m_Width;
		pCopyDestBits16	+= DestPitch;
		}
	}




//////////////////////
//					//
// Drawing routines //
//					//
//////////////////////




void CSprite::Draw(CBitmap * pDest, int x, int y)
	{

	///////////////////////////////////////////////////////////
	//														 //
	// Used to draw a sprite with transparency onto a bitmap //
	//														 //
	///////////////////////////////////////////////////////////


	int sx,
		sy;

	int	width, 
		height;
	
	
	// Set default variables //

	sx		= 0;
	sy		= 0;
	width	= m_Width;
	height	= m_Height;


	// Perform clipping if necessary //

	if (x < 0)
		{
		sx = -x;
		x = 0;	
		width -= sx;
		}


	if (y < 0)
		{
		sy = -y;
		y = 0;
		height -= sy;
		}


	if (width <= 0 || height <= 0)
		return;


	if ((x + width) >= pDest->GetWidth())
		width = pDest->GetWidth() - x;


	if ((y + height) >= pDest->GetHeight())
		height = pDest->GetHeight() - y;


	// Return if the sprite is out of the bitmap range //

	if (width <= 0 || height <= 0)
		return;
		

	// Call the proper Draw function based on the BPP //

	switch(m_BPP)
		{
		case 8:
			Draw8(pDest, x, y, width, height, sx, sy);
			return;


		case 16:
			Draw16(pDest, x, y, width, height, sx, sy);
			return;
		}
	}






void CSprite::Draw8(CBitmap * pDest, int x, int y, int width, int height, int sx, int sy)
	{

	//////////////////////////////////////////////////////////////////
	//														        //
	// Used to draw an 8 bit sprite with transparency onto a bitmap //
	//														        //
	//////////////////////////////////////////////////////////////////


	U8 * pCopyBits8;

	U8 * pDestBits8,
	   * pCopyDestBits8;

	U32 DestPitch;
	U32 ypos, xpos;


	// If the sprite has not been initialized then return //

	if (m_pBits8 == NULL)
		return;


	// Get the destination pitch and bits //

	DestPitch		= pDest->GetPitch();
	pDestBits8		= pDest->GetBits8();


	// Now, go through each pixel, checking if the pixel to place is //
	// transparent or not, if not, then place the pixel				 //

	for (ypos = 0; ypos < height; ypos++)
		{
		pCopyBits8		= &m_pBits8[sx + ((sy + ypos) * m_Width)];
		pCopyDestBits8  = &pDestBits8[x + ((y + ypos) * DestPitch)];

		for (xpos = 0; xpos < width; xpos++)
			{
			if (*pCopyBits8 != m_TransClr8)
 				*pCopyDestBits8 = *pCopyBits8;

			pCopyBits8++;
			pCopyDestBits8++;
			}
		}
	}




void CSprite::Draw16(CBitmap * pDest, int x, int y, int width, int height, int sx, int sy)
	{

	//////////////////////////////////////////////////////////////////
	//														        //
	// Used to draw a 16 bit sprite with transparency onto a bitmap //
	//														        //
	//////////////////////////////////////////////////////////////////


	U16 * pCopyBits16;

	U16 * pDestBits16,
	    * pCopyDestBits16;

	U32 DestPitch;
	U32 ypos, xpos;


	// If the sprite has not been initialized then return //

	if (m_pBits16 == NULL)
		return;


	// Get the destination pitch and bits //

	DestPitch		= pDest->GetPitch();
	pDestBits16		= pDest->GetBits16();


	// Now, go through each pixel, checking if the pixel to place is //
	// transparent or not, if not, then place the pixel				 //

	for (ypos = 0; ypos < height; ypos++)
		{
		pCopyBits16		= &m_pBits16[sx + ((sy + ypos) * m_Width)];
		pCopyDestBits16 = &pDestBits16[x + ((y + ypos) * DestPitch)];

		for (xpos = 0; xpos < width; xpos++)
			{
			if (*pCopyBits16 != m_TransClr16)
				*pCopyDestBits16 = *pCopyBits16;

			pCopyBits16++;
			pCopyDestBits16++;
			}
		}
	}




void CSprite::DrawTrans(CBitmap * pDest, CFXPalette * pFXPal, int x, int y)
	{

	/////////////////////////////////////////////////////
	//												   //
	// Used to draw a translucent sprite onto a bitmap //
	//												   //
	/////////////////////////////////////////////////////


	int sx,
		sy;

	int	width, 
		height;
	
	
	// Set default variables //

	sx		= 0;
	sy		= 0;
	width	= m_Width;
	height	= m_Height;


	// Perform clipping if necessary //

	if (x < 0)
		{
		sx = -x;
		x = 0;
		width -= sx;
		}


	if (y < 0)
		{
		sy = -y;
		y = 0;
		height -= sy;
		}


	if (x + width >= pDest->GetWidth())
		width = pDest->GetWidth() - x;


	if (y + height >= pDest->GetHeight())
		height = pDest->GetHeight() - y;


	// Return if the sprite is out of the bitmap range //

	if (width <= 0 || height <= 0)
		return;
		

	// Call the proper DrawTrans function based on the BPP //

	switch(m_BPP)
		{
		case 8:
			DrawTrans8(pDest, pFXPal, x, y, width, height, sx, sy);
			return;


		case 16:
			return;
		}
	}





void CSprite::DrawTrans8(CBitmap * pDest, CFXPalette * pFXPal, int x, int y, int width, int height, int sx, int sy)
	{

	////////////////////////////////////////////////////////////
	//														  //
	// Used to draw an 8 bit translucent sprite onto a bitmap //
	//														  //
	////////////////////////////////////////////////////////////


	U8 * pCopyBits8;

	U8 * pDestBits8,
	   * pCopyDestBits8;

	U8 TColor;

	U32 DestPitch;
	U32 ypos, xpos;


	// If the sprite has not been initialized then return //

	if (m_pBits8 == NULL)
		return;


	// Get the destination pitch and bits //

	DestPitch		= pDest->GetPitch();
	pDestBits8		= pDest->GetBits8();


	// Now, go through each pixel, checking if the pixel to place is //
	// transparent or not, if not, then place the pixel				 //

	for (ypos = 0; ypos < height; ypos++)
		{
		pCopyBits8		= &m_pBits8[sx + ((sy + ypos) * m_Width)];
		pCopyDestBits8  = &pDestBits8[x + ((y + ypos) * DestPitch)];
		
		for (xpos = 0; xpos < width; xpos++)
			{
			if (*pCopyBits8 != m_TransClr8)
				{
				TColor = pFXPal->Entry[*pCopyBits8].Blend[*pCopyDestBits8];
				*pCopyDestBits8 = TColor;
				}

			pCopyBits8++;
			pCopyDestBits8++;
			}
		}
	}





void CSprite::DrawLit(CBitmap * pDest, CFXPalette * pFXPal, int x, int y)
	{

	/////////////////////////////////////////////////
	//											   //
	// Used to draw a lighted sprite onto a bitmap //
	//											   //
	/////////////////////////////////////////////////


	int sx,
		sy;

	int	width, 
		height;
	
	
	// Set default variables //

	sx		= 0;
	sy		= 0;
	width	= m_Width;
	height	= m_Height;


	// Perform clipping if necessary //

	if (x < 0)
		{
		sx = -x;
		x  = 0;
		width -= sx;
		}


	if (y < 0)
		{
		sy = -y;
		y = 0;
		height -= sy;
		}


	if (x + width >= pDest->GetWidth())
		width = pDest->GetWidth() - x;


	if (y + height >= pDest->GetHeight())
		height = pDest->GetHeight() - y;


	// Return if the sprite is out of the bitmap range //

	if (width <= 0 || height <= 0)
		return;
		

	// Call the proper DrawLit function based on the BPP //

	switch(m_BPP)
		{
		case 8:
			DrawLit8(pDest, pFXPal, x, y, width, height, sx, sy);
			return;


		case 16:
			return;
		}
	}






void CSprite::DrawLit8(CBitmap * pDest, CFXPalette * pFXPal, int x, int y, int width, int height, int sx, int sy)
	{

	////////////////////////////////////////////////////////
	//											          //
	// Used to draw an 8 bit lighted sprite onto a bitmap //
	//											          //
	////////////////////////////////////////////////////////


	U8 * pCopyBits8;

	U8 * pDestBits8,
	   * pCopyDestBits8;

	U8 TColor;

	U32 DestPitch;
	U32 ypos, xpos;


	// If the sprite has not been initialized then return //

	if (m_pBits8 == NULL)
		return;


	// Get the destination pitch and bits //

	DestPitch		= pDest->GetPitch();
	pDestBits8		= pDest->GetBits8();


	// Now, go through each pixel, checking if the pixel to place is //
	// transparent or not, if not, then place the pixel				 //

	for (ypos = 0; ypos < height; ypos++)
		{
		pCopyBits8		= &m_pBits8[sx + ((sy + ypos) * m_Width)];
		pCopyDestBits8  = &pDestBits8[x + ((y + ypos) * DestPitch)];
		
		for (xpos = 0; xpos < width; xpos++)
			{
			TColor = pFXPal->Entry[*pCopyDestBits8].Blend[*pCopyBits8];
			*pCopyDestBits8 = TColor;

			pCopyBits8++;
			pCopyDestBits8++;
			}
		}
	}







