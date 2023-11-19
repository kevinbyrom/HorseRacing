#include <windows.h>
#include "..\Header\DisplayHandler2D.h"
#include "..\Header\Game2D.h"





BOOL CDisplayHandler2D::Init(CGame * pGame, int Width, int Height, int BPP, BOOL FullScreen)	
	{ 

	//////////////////////////////////////
	//									//
	// Used to init the display handler //
	//									//
	//////////////////////////////////////


	m_hWnd			= pGame->GetWindow(); 
	m_Width			= Width; 
	m_Height		= Height; 
	m_BPP			= BPP; 
	m_FullScreen	= FullScreen; 
	

	return TRUE; 
	}	






CBitmap * CDisplayHandler2D::GetBufferBitmap()	
	{ 

	///////////////////////////////////
	//								 //
	// Used to get the buffer bitmap //
	//								 //
	///////////////////////////////////


	return &m_BufferBmp; 
	}






void CDisplayHandler2D::SetPalette(PALETTEENTRY * pPal)				
	{ 

	/////////////////////////////////////
	//								   //
	// Used to set the palette entries //
	//								   //
	/////////////////////////////////////


	memcpy(m_Pal, pPal, sizeof(PALETTEENTRY) * 256); 

	OnPaletteChanged();
	}






PALETTEENTRY * CDisplayHandler2D::GetPalette()						
	{
	
	/////////////////////////////////////
	//								   //
	// Used to get the palette entries //
	//								   //
	/////////////////////////////////////


	return m_Pal; 
	}






int CDisplayHandler2D::GetScreenWidth()
	{

	//////////////////////////////////
	//								//
	// Used to get the screen width //
	//								//
	//////////////////////////////////


	return m_Width;
	}





int CDisplayHandler2D::GetScreenHeight()
	{

	///////////////////////////////////
	//								 //
	// Used to get the screen height //
	//								 //
	///////////////////////////////////


	return m_Height;
	}