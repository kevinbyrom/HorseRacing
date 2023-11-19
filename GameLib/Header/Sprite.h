#ifndef __CSprite_H
#define __CSprite_H


#include "DataTypes.h"
#include "Bitmap.h"
#include "FXPalette.h"


class CSprite
	{
	public:
		
		CSprite();
		~CSprite();


		// Acquiring routines //

		void Grab(CBitmap * pSrc, int x, int y, int width, int height, U32 transclr);
		void Unload(void);


		// Blitting routines //

		void Blit(CBitmap * pDest, int x, int y);
		void Blit8(CBitmap * pDest, int x, int y, int width, int height, int sx, int sy);
		void Blit16(CBitmap * pDest, int x, int y, int width, int height, int sx, int sy);


		// Drawing routines //

		void Draw(CBitmap * pDest, int x, int y);
		void Draw8(CBitmap * pDest, int x, int y, int width, int height, int sx, int sy);
		void Draw16(CBitmap * pDest, int x, int y, int width, int height, int sx, int sy);

		void DrawTrans(CBitmap * pDest, CFXPalette * pFXPal, int x, int y);
		void DrawTrans8(CBitmap * pDest, CFXPalette * pFXPal, int x, int y, int width, int height, int sx, int sy);

		void DrawLit(CBitmap * pDest, CFXPalette * pFXPal, int x, int y);
		void DrawLit8(CBitmap * pDest, CFXPalette * pFXPal, int x, int y, int width, int height, int sx, int sy);


	protected:

		U8	m_BPP;
		U32 m_Width,
			m_Height;

		U8	* m_pBits8;
		U16 * m_pBits16;
		
		U8  m_TransClr8;
		U16 m_TransClr16;
	};



#endif