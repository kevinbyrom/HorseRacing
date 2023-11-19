#ifndef __CText_H
#define __CText_H


#include "DataTypes.h"
#include "Sprite.h"


class CBitmap;


class CText
	{
	public:
		
		CText();
		~CText();


		// Acquiring routines //

		void Grab(CBitmap * pSrc, U32 Width, U32 Height);
		BOOL Load(char * strFile, U32 Width, U32 Height);
		void UnloadAll();


		// Drawing routines //

		void DrawText(CBitmap * pDest, char * strText, int x, int y);
		void DrawText8(CBitmap * pDest, char * strText, int x, int y);
		void DrawText16(CBitmap * pDest, char * strText, int x, int y);

		void DrawTextRect(CBitmap * pDest, char * strText, RECT Rect);
		void DrawTextRect8(CBitmap * pDest, char * strText, RECT Rect);
		void DrawTextRect16(CBitmap * pDest, char * strText, RECT Rect);
		
		void DrawTextTrans(CBitmap * pDest, CFXPalette * pFXPal, char * strText, int x, int y);
		void DrawTextLit(CBitmap * pDest, CFXPalette * pFXPal, char * strText, int x, int y);
		

	protected:

		CSprite m_LetterSpr[108];

		U32 m_Width,
			m_Height;

		BOOL m_LettersLoaded;
	};



extern CText DefText;

#endif