#include <windows.h>
#include "..\Header\DXBitmap.h"




//////////////////////
//					//
// Surface routines //
//					//
//////////////////////




void CDXBitmap::AttachToDDSurface(LPDIRECTDRAWSURFACE4 lpSurface)
	{

	///////////////////////////////////////////////////////
	//													 //
	// Used to attach a DirectDraw surface to the bitmap //
	//													 //
	///////////////////////////////////////////////////////


	m_lpSurface = lpSurface;
	}





BOOL CDXBitmap::LockDDSurface()
	{

	/////////////////////////////////////////////
	//										   //
	// Used to lock the surface for drawing to //
	//										   //
	/////////////////////////////////////////////
	

	DDSURFACEDESC2 ddsd;


	// If there is no surface attached, return false //

	if (m_lpSurface == NULL)
		return FALSE;


	// Lock the surface //

	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);

	m_lpSurface->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL); 


	// Get the surface properties //
	
	m_Pitch		= ddsd.lPitch;
	m_Width		= ddsd.dwWidth;
	m_Height	= ddsd.dwHeight;
	m_BPP		= (U8)ddsd.ddpfPixelFormat.dwRGBBitCount;


	// Get pointer to surface //

	m_pBits8	= (U8 *)ddsd.lpSurface;
	m_pBits16	= (U16 *)ddsd.lpSurface;


	return TRUE;
	}





BOOL CDXBitmap::UnlockDDSurface()
	{

	/////////////////////////////////////////////////
	//											   //
	// Used to unlock a surface which was drawn to //
	//											   //
	/////////////////////////////////////////////////


	// If there is no surface attached, return false //

	if (m_lpSurface == NULL)
		return FALSE;


	// Unlock the surface //

	m_lpSurface->Unlock(NULL);


	// Get rid of the surface properties //

	m_Pitch		= 0;
	m_Width		= 0;
	m_Height	= 0;
	m_BPP		= 0;

	m_pBits8	= NULL;
	m_pBits16	= NULL;


	return TRUE;
	}