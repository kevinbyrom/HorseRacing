#ifndef __DXDisplayHandler2D_H
#define __DXDisplayHandler2D_H




#include "DisplayHandler2D.h"
#include "DXBitmap.h"
#include "..\..\DirectX\Header\DDraw.h"




class CDXDisplayHandler2D : public CDisplayHandler2D
	{
	public:

		CDXDisplayHandler2D();

		virtual BOOL Init(CGame * pGame, int Width, int Height, int BPP, BOOL FullScreen);
		virtual void DeInit();

		virtual void UpdateScreen();
		virtual void OnPaletteChanged();


	protected:


		LPDIRECTDRAW4			m_pDDraw;
		LPDIRECTDRAWSURFACE4	m_pPrimary,
								m_pBack;

		LPDIRECTDRAWPALETTE		m_pPalette;

		LPDIRECTDRAWCLIPPER		m_pClipper;

		CDXBitmap				m_BackSurfBmp;						// Bitmap to attach to back surface
	};


#endif