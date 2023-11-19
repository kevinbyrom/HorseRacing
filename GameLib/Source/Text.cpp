#include <windows.h>
#include "..\Header\Text.h"
#include "..\Header\Bitmap.h"



CText DefText;



//////////////////////////////
//							//
// Constructor / Destructor //
//							//
//////////////////////////////



CText::CText()
	{
	CBitmap FontBmp;

	m_Width			= 0;
	m_Height		= 0;
	m_LettersLoaded	= FALSE;

	Load("..\\Font.bmp", 7, 12);
	}




CText::~CText()
	{
	}




////////////////////////
//	                  //
// Acquiring routines //
//	                  //
////////////////////////



void CText::Grab(CBitmap * pSrc, U32 Width, U32 Height)
	{
	U32 ypos, xpos;


	// Unload the letters if already loaded //

	if (m_LettersLoaded)
		UnloadAll();


	// Set the properties //

	m_Width		= Width;
	m_Height	= Height;


	// Read each row //

	for (ypos = 0; ypos < 6; ypos++)
		for (xpos = 0; xpos < 16; xpos++)
			{
			m_LetterSpr[xpos + (ypos * 16)].Grab(pSrc, (xpos * Width) + (xpos + 1), (ypos * Height) + (ypos + 1), Width, Height, 0);
			}


	// Set the loaded flag //

	m_LettersLoaded = TRUE;
	}




BOOL CText::Load(char * strFile, U32 Width, U32 Height)
	{
	U32 ypos, xpos;
	CBitmap Bitmap;



	// Attempt to load the bitmap //

	if (!Bitmap.LoadBMP(strFile))
		return FALSE;


	// Unload the letters if already loaded //

	if (m_LettersLoaded)
		UnloadAll();


	// Set the properties //

	m_Width		= Width;
	m_Height	= Height;


	// Read each row //

	for (ypos = 0; ypos < 6; ypos++)
		for (xpos = 0; xpos < 18; xpos++)
			{
			m_LetterSpr[xpos + (ypos * 18)].Grab(&Bitmap, (xpos * Width) + (xpos + 1), (ypos * Height) + (ypos + 1), Width, Height, 0);
			}


	// Set the loaded flag //

	m_LettersLoaded = TRUE;


	return TRUE;
	}





void CText::UnloadAll()
	{

	////////////////////////////////////
	//								  //
	// Used to unload all the sprites //
	//								  //
	////////////////////////////////////


	for (int i = 0; i < 108; i++)
		m_LetterSpr[i].Unload();


	m_LettersLoaded = FALSE;
	}






//////////////////////
//					//
// Drawing routines //
//					//
//////////////////////




void CText::DrawText(CBitmap * pDest, char * strText, int x, int y)
	{
	int xpos = x;
	int ypos = y;
	int i;


	for (i = 0; i < strlen(strText); i++)
		{
		if (strText[i] != 32)
			m_LetterSpr[strText[i] - 33].Draw(pDest, xpos, ypos);

		xpos += m_Width;
		}
	}






void CText::DrawText8(CBitmap * pDest, char * strText, int x, int y)
	{
	int xpos = x;
	int ypos = y;
	int i;


	for (i = 0; i < strlen(strText); i++)
		{
		if (strText[i] != 32)
			m_LetterSpr[strText[i] - 33].Draw8(pDest, xpos, ypos, m_Width, m_Height, 0, 0);
			
		xpos += m_Width;
		}
	}






void CText::DrawText16(CBitmap * pDest, char * strText, int x, int y)
	{
	int xpos = x;
	int ypos = y;
	int i;


	for (i = 0; i < strlen(strText); i++)
		{
		if (strText[i] != 32)
			m_LetterSpr[strText[i] - 33].Draw16(pDest, xpos, ypos, m_Width, m_Height, 0, 0);

		xpos += m_Width;
		}
	}






void CText::DrawTextRect(CBitmap * pDest, char * strText, RECT Rect)
	{
	if (pDest->GetBPP() == 8)
		DrawTextRect8(pDest, strText, Rect);

	else if (pDest->GetBPP() == 16)
		DrawTextRect16(pDest, strText, Rect);
	}





void CText::DrawTextRect8(CBitmap * pDest, char * strText, RECT Rect)
	{
	char * strWork;
	char * pWord[2000];
	int TextLen;
	int NumWords = 0;
	int i;
	int xpos, ypos;
	int Done = 0;
	int WordPos;
	int WordWidth;


	// Get the length of the string //

	TextLen = strlen(strText);

	if (!TextLen)
		return;


	// Allocate a work buffer //

	strWork = (char *)malloc(strlen(strText) + 1);
	strcpy(strWork, strText);


	// Search through the work buffer, and for every space that is not followed //
	// by another space, convert that character to NULL and flag the next char  //
	// as the start of a new word, before doing this, set the first character   //
	// as the start of the first word											//

	pWord[0]	= &strWork[0];
	NumWords	= 1;

	for (i = 0; i < TextLen; i++)
		if (strWork[i] == 32 && (strWork[i + 1] != 32 && strWork[i + 1] != '\0'))
			{
			strWork[i]		= '\0';
			pWord[NumWords] = &strWork[i + 1];

			NumWords++;
			}


	// Set the first x/y positions //

	xpos = Rect.left;
	ypos = Rect.top;


	// Loop until done flag is set //

	WordPos = 0;

	while(!Done)
		{

		// Get the width of the next word //

		WordWidth = strlen(pWord[WordPos]) * m_Width;


		// Check to see if the word fits ... //
		// If so...							 //

		if (WordWidth + xpos < Rect.right && ypos + m_Height < Rect.bottom)
			{

			// Draw the text //

			DrawText8(pDest, pWord[WordPos], xpos, ypos);


			// Increment the xpos by the width of the word and a letter (space) //

			xpos += WordWidth + m_Width;


			// Set the next word position //

			WordPos++;
			}


		// else ... //

		else
			{
			
			// Set the xpos to the origin left //

			xpos = Rect.left;


			// Increment the ypos by the height of the letters //

			ypos += m_Height;
			}



		// If we have drawn all words, set the done flag //

		if (WordPos >= NumWords)
			Done = 1;


		// If we are beyond the y limits, set the done flag //

		if (ypos + m_Height >= Rect.right)
			Done = 1;
		}


	// Free up the work buffer //

	free(strWork);
	}





void CText::DrawTextRect16(CBitmap * pDest, char * strText, RECT Rect)
	{
	char * strWork;
	char * pWord[2000];
	int TextLen;
	int NumWords = 0;
	int i;
	int xpos, ypos;
	int Done = 0;
	int WordPos;
	int WordWidth;


	// Get the length of the string //

	TextLen = strlen(strText);

	if (!TextLen)
		return;


	// Allocate a work buffer //

	strWork = (char *)malloc(strlen(strText) + 1);
	strcpy(strWork, strText);


	// Search through the work buffer, and for every space that is not followed //
	// by another space, convert that character to NULL and flag the next char  //
	// as the start of a new word, before doing this, set the first character   //
	// as the start of the first word											//

	pWord[0]	= &strWork[0];
	NumWords	= 1;

	for (i = 0; i < TextLen; i++)
		if (strWork[i] == 32 && (strWork[i + 1] != 32 && strWork[i + 1] != '\0'))
			{
			strWork[i]		= '\0';
			pWord[NumWords] = &strWork[i + 1];

			NumWords++;
			}


	// Set the first x/y positions //

	xpos = Rect.left;
	ypos = Rect.top;


	// Loop until done flag is set //

	WordPos = 0;

	while(!Done)
		{

		// Get the width of the next word //

		WordWidth = strlen(pWord[WordPos]) * m_Width;


		// Check to see if the word fits ... //
		// If so...							 //

		if (WordWidth + xpos < Rect.right && ypos + m_Height < Rect.bottom)
			{

			// Draw the text //

			DrawText16(pDest, pWord[WordPos], xpos, ypos);


			// Increment the xpos by the width of the word and a letter (space) //

			xpos += WordWidth + m_Width;


			// Set the next word position //

			WordPos++;
			}


		// else ... //

		else
			{
			
			// Set the xpos to the origin left //

			xpos = Rect.left;


			// Increment the ypos by the height of the letters //

			ypos += m_Height;
			}



		// If we have drawn all words, set the done flag //

		if (WordPos >= NumWords)
			Done = 1;


		// If we are beyond the y limits, set the done flag //

		if (ypos + m_Height >= Rect.right)
			Done = 1;
		}


	// Free up the work buffer //

	free(strWork);
	}




void CText::DrawTextTrans(CBitmap * pDest, CFXPalette * pFXPal, char * strText, int x, int y)
	{
	int xpos = x;
	int ypos = y;
	int i;


	for (i = 0; i < strlen(strText); i++)
		{
		if (strText[i] != 32)
			m_LetterSpr[strText[i] - 33].DrawTrans(pDest, pFXPal, xpos, ypos);

		xpos += m_Width;
		}
	}





void CText::DrawTextLit(CBitmap * pDest, CFXPalette * pFXPal, char * strText, int x, int y)
	{
	int xpos = x;
	int ypos = y;
	int i;


	for (i = 0; i < strlen(strText); i++)
		{
		if (strText[i] != 32)
			m_LetterSpr[strText[i] - 33].DrawLit(pDest, pFXPal, xpos, ypos);

		xpos += m_Width;
		}
	}


