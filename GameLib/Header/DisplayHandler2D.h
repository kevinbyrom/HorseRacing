#ifndef __CDisplayHandler2D_H
#define __CDisplayHandler2D_H



#include "Bitmap.h"
#include "DataTypes.h"


class CGame;





class CDisplayHandler2D
	{
	public:

		virtual BOOL Init(CGame * pGame, int Width, int Height, int BPP, BOOL FullScreen);
		virtual void DeInit()									{}

		CBitmap * GetBufferBitmap();

		void SetPalette(PALETTEENTRY * pPal);
		PALETTEENTRY * GetPalette();

		int GetScreenWidth();
		int GetScreenHeight();

		int GetBPP()			{ return m_BPP; }


		// Overrideables //

		virtual void UpdateScreen()								{}
		virtual void OnPaletteChanged()							{}


	protected:

		HWND			m_hWnd;							// Attached window 

		int				m_Width,						// Display width, height, and bits 
						m_Height,						// per pixel
						m_BPP;

		BOOL			m_FullScreen;					// Fullscreen or windowed

		CBitmap 		m_BufferBmp;					// Bitmap to draw to

		PALETTEENTRY	m_Pal[256];						// Palette if display is 8 bit or less
	};





#endif