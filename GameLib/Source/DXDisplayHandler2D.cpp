#include <windows.h>
#include "..\Header\DXDisplayHandler2D.h"
#include "..\Header\DXBitmap.h"




CDXDisplayHandler2D::CDXDisplayHandler2D()		
	{ 

	/////////////////
	//			   //
	// Constructor //
	//			   //
	/////////////////


	m_pDDraw	= NULL; 
	m_pPrimary	= NULL; 
	m_pBack		= NULL; 
	m_pClipper	= NULL;
	}






BOOL CDXDisplayHandler2D::Init(CGame * pGame, int Width, int Height, int BPP, BOOL FullScreen)
	{

	/////////////////////////////////////////
	//									   //
	// Used to init the DirectDraw Display //
	//									   //
	/////////////////////////////////////////


	LPDIRECTDRAW lptempdd;
	DDSURFACEDESC2 ddsd;
	PALETTEENTRY GrayPal[256];



	if (!CDisplayHandler2D::Init(pGame, Width, Height, BPP, FullScreen))
		return FALSE;



	// Create the direct draw object //

	if (FAILED(DirectDrawCreate(NULL, &lptempdd, NULL)))
		return FALSE;



	// Get the latest interface //

	if (FAILED(lptempdd->QueryInterface(IID_IDirectDraw4, (LPVOID *)&m_pDDraw)))
		{
		lptempdd->Release();
		return FALSE;
		}



	// Set the cooperation level //

	lptempdd->Release();

	if (m_FullScreen)
		{
		if (FAILED(m_pDDraw->SetCooperativeLevel(m_hWnd, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE)))
			return FALSE;
		}
	else
		{
		if (FAILED(m_pDDraw->SetCooperativeLevel(m_hWnd, DDSCL_NORMAL)))
			return FALSE;
		}



	// Set the display mode //

	if (m_FullScreen)
		if (FAILED(m_pDDraw->SetDisplayMode(m_Width, m_Height, m_BPP, 0, 0)))
			return FALSE;



	// Create the main palette//

	if (m_BPP < 16)
		{
		for (int pal = 0; pal < 256; pal++)
			{
			GrayPal[pal].peRed		= pal;
			GrayPal[pal].peGreen	= pal;
			GrayPal[pal].peBlue		= pal;
			GrayPal[pal].peFlags	= PC_NOCOLLAPSE;
			}


		if (FAILED(m_pDDraw->CreatePalette(DDPCAPS_8BIT | DDPCAPS_ALLOW256 | DDPCAPS_INITIALIZE, GrayPal, &m_pPalette, NULL)))
			return FALSE;
		}



	// Now create the primary surface //

	memset(&ddsd, 0, sizeof(ddsd));

	if (m_FullScreen)
		{
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags			= DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		ddsd.dwBackBufferCount	= 1;
		ddsd.ddsCaps.dwCaps		= DDSCAPS_PRIMARYSURFACE | DDSCAPS_COMPLEX | DDSCAPS_FLIP;
		}
	else
		{
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags			= DDSD_CAPS;
		ddsd.ddsCaps.dwCaps		= DDSCAPS_PRIMARYSURFACE;
		}


	if (FAILED(m_pDDraw->CreateSurface(&ddsd, &m_pPrimary, NULL)))
		return FALSE;



	// Set the palette to the primary surface //

	if (m_BPP < 16)
		if (FAILED(m_pPrimary->SetPalette(m_pPalette)))
			return FALSE;



	// Create the back surface //

	if (m_FullScreen)
		{
		ddsd.ddsCaps.dwCaps	= DDSCAPS_BACKBUFFER;

		if (FAILED(m_pPrimary->GetAttachedSurface(&ddsd.ddsCaps, &m_pBack)))
			return FALSE;
		}
	else
		{
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags			= DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		ddsd.ddsCaps.dwCaps		= DDSCAPS_OFFSCREENPLAIN;
		ddsd.dwHeight			= Height;
		ddsd.dwWidth			= Width;

		if (FAILED(m_pDDraw->CreateSurface(&ddsd, &m_pBack, NULL)))
			return FALSE;
		}



	// Create the screen //

	m_BufferBmp.Create(Width, Height, BPP);



	// Attach the back surface to the buffer bitmap //

	m_BackSurfBmp.AttachToDDSurface(m_pBack);



	// Create a clipper //

	if (!m_FullScreen)
		{
		if (FAILED(m_pDDraw->CreateClipper(0, &m_pClipper, NULL)))
			return FALSE;

		if (FAILED(m_pClipper->SetHWnd(0, m_hWnd)))
			return FALSE;

		if (FAILED(m_pPrimary->SetClipper(m_pClipper)))
			return FALSE;
		}

	return TRUE;
	}





void CDXDisplayHandler2D::DeInit()
	{

	//////////////////////////////////////////////////
	//												//
	// Used to de-initialize the DirectDraw Display //
	//												//
	//////////////////////////////////////////////////



	if (m_pDDraw && m_FullScreen)
		m_pDDraw->RestoreDisplayMode();
		
	if (m_pPrimary)
		m_pPrimary->Release();

	if (m_pDDraw)
		m_pDDraw->Release();
	}






void CDXDisplayHandler2D::UpdateScreen()
	{

	///////////////////////////////
	//							 //
	// Used to update the screen //
	//							 //
	///////////////////////////////

	RECT rectBlt, rectWnd;
	POINT Window;


	// Lock the back bitmap //

	m_BackSurfBmp.LockDDSurface();
	m_BackSurfBmp.Blit(&m_BufferBmp, 0, 0, m_Width, m_Height, 0, 0);
	m_BackSurfBmp.UnlockDDSurface();

	if (m_FullScreen)
		m_pPrimary->Flip(NULL, DDFLIP_WAIT);
	else
		{
		Window.x = 0;
		Window.y = 0;

		ClientToScreen(m_hWnd, &Window);

		SetRect(&rectWnd, Window.x, Window.y, Window.x + m_Width, Window.y + m_Height);
		SetRect(&rectBlt, 0, 0, m_Width, m_Height);
		m_pPrimary->Blt(&rectWnd, m_pBack, &rectBlt, DDBLT_WAIT, NULL);
		}
	}




void CDXDisplayHandler2D::OnPaletteChanged()
	{

	////////////////////////////////////
	//								  //
	// Used to handle palette changes //
	//								  //
	////////////////////////////////////


	for (int i = 0; i < 10; i++)
		{
		m_Pal[i].peFlags		= PC_EXPLICIT;
		m_Pal[i + 246].peFlags	= PC_EXPLICIT;
		}

	m_pPalette->SetEntries(0, 0, 256, m_Pal);     
	}