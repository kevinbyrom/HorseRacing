#include <windows.h>
#include <math.h>
#include "..\Header\FXPalette.h"


#define DOMINANT_RED	0
#define DOMINANT_GREEN	1
#define DOMINANT_BLUE	2


void CFXPalette::CreateTransPal(PALETTEENTRY * pPal, int TPercent)
	{

	////////////////////////////////////////////
	//										  //
	// Used to create the translucent palette //
	//										  //
	////////////////////////////////////////////

	int i, ii, iii;
	int TRed, TGreen, TBlue;
	int Diff, LastDiff;
	int Dominant, ThisDom, HighColor;


	for (i = 0; i < 256; i++)
		for (ii = 0; ii < 256; ii++)
			{
			// Calculate the desired RGB value after blending //

			TRed	= int(float(pPal[i].peRed) * (float(100 - TPercent) / 100)) + int(float(pPal[ii].peRed) * (float(TPercent) / 100));
			TGreen	= int(float(pPal[i].peGreen) * (float(100 - TPercent) / 100)) + int(float(pPal[ii].peGreen) * (float(TPercent) / 100));
			TBlue	= int(float(pPal[i].peBlue) * (float(100 - TPercent) / 100)) + int(float(pPal[ii].peBlue) * (float(TPercent) / 100));
			

			// Calculate which color is dominant //

			Dominant	= DOMINANT_RED;	
			HighColor	= TRed;

			if (TGreen > HighColor)
				{
				Dominant	= DOMINANT_GREEN;
				HighColor	= TGreen;
				}

			if (TBlue > HighColor)
				Dominant	= DOMINANT_BLUE;


			// Now, find the RGB Val that most matches //

			LastDiff			= abs(TRed - pPal[0].peRed) + abs(TGreen - pPal[0].peGreen) + abs(TBlue - pPal[0].peBlue);
			Entry[i].Blend[ii]	= 0;


			for (iii = 1; iii < 256; iii++)
				{

				// Calculate which color is dominant for the dest color //		

				ThisDom		= DOMINANT_RED;	
				HighColor	= pPal[iii].peRed;

				if (pPal[iii].peGreen > HighColor)
					{
					ThisDom		= DOMINANT_GREEN;
					HighColor	= pPal[iii].peGreen;
					}

				if (pPal[iii].peBlue > HighColor)
					ThisDom		= DOMINANT_BLUE;


				// Calculate the difference //

				Diff = abs(TRed - pPal[iii].peRed) + abs(TGreen - pPal[iii].peGreen) + abs(TBlue - pPal[iii].peBlue);

				if (Diff < LastDiff && Dominant == ThisDom)
					{
					LastDiff = Diff;
					Entry[i].Blend[ii] = iii;
					}
				}
			}
	}





void CFXPalette::CreateLitPal(PALETTEENTRY * pPal, int HighRed, int HighGreen, int HighBlue)
	{

	/////////////////////////////////////////
	//									   //
	// Used to create the lighting palette //
	//									   //
	/////////////////////////////////////////

	int i, ii, iii;
	int LRed, LGreen, LBlue;
	int Diff, LastDiff;
	int Dominant, ThisDom, HighColor;
	float Percent;


	for (i = 0; i < 256; i++)
		for (ii = 0; ii < 256; ii++)
			{
			// Calculate the desired RGB value after blending //

			if (ii < 128)
				{
				LRed	= (float(ii) / 127) * pPal[i].peRed;
				LGreen	= (float(ii) / 127) * pPal[i].peGreen;
				LBlue	= (float(ii) / 127) * pPal[i].peBlue;
				}
			else
				{
				Percent = float(ii - 128) / 127;

				LRed	= int(float(pPal[i].peRed) * float(1 - Percent)) + int(float(HighRed) * Percent);
				LGreen	= int(float(pPal[i].peGreen) * float(1 - Percent)) + int(float(HighGreen) * Percent);
				LBlue	= int(float(pPal[i].peBlue) * float(1 - Percent)) + int(float(HighBlue) * Percent);
				}
			

			// Calculate which color is dominant //

			Dominant	= DOMINANT_RED;	
			HighColor	= LRed;

			if (LGreen > HighColor)
				{
				Dominant	= DOMINANT_GREEN;
				HighColor	= LGreen;
				}

			if (LBlue > HighColor)
				Dominant	= DOMINANT_BLUE;


			// Now, find the RGB Val that most matches //

			LastDiff			= abs(LRed - pPal[0].peRed) + abs(LGreen - pPal[0].peGreen) + abs(LBlue - pPal[0].peBlue);
			Entry[i].Blend[ii]	= 0;


			for (iii = 1; iii < 256; iii++)
				{

				// Calculate which color is dominant for the dest color //		

				ThisDom		= DOMINANT_RED;	
				HighColor	= pPal[iii].peRed;

				if (pPal[iii].peGreen > HighColor)
					{
					ThisDom		= DOMINANT_GREEN;
					HighColor	= pPal[iii].peGreen;
					}

				if (pPal[iii].peBlue > HighColor)
					ThisDom		= DOMINANT_BLUE;


				Diff = abs(LRed - pPal[iii].peRed) + abs(LGreen - pPal[iii].peGreen) + abs(LBlue - pPal[iii].peBlue);

				if (Diff < LastDiff && Dominant == ThisDom)
					{
					LastDiff = Diff;
					Entry[i].Blend[ii] = iii;
					}
				}
			}
	}




BOOL CFXPalette::Save(char * strFile)
	{

	/////////////////////////////////////////
	//									   //
	// Used to save the FX palette to file //
	//									   //
	/////////////////////////////////////////


	HANDLE hFile;

	
	// Attempt to create the palette file, if failure, return false //

	if ((hFile = CreateFile(strFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0)) == INVALID_HANDLE_VALUE)
		return FALSE;


	// Continue the saving at another file //

	return Save(hFile);
	}




BOOL CFXPalette::Save(HANDLE hFile)
	{

	/////////////////////////////////////////
	//									   //
	// Used to save the FX palette to file //
	//									   //
	/////////////////////////////////////////

	DWORD NumWritten;


	for (int i = 0 ; i < 256; i++)
		{
		WriteFile(hFile, Entry[i].Blend, 256, &NumWritten, NULL);

		if (NumWritten != 256)
			{
			CloseHandle(hFile);
			return FALSE;
			}
		}


	CloseHandle(hFile);

	return TRUE;
	}




BOOL CFXPalette::Load(char * strFile)
	{

	///////////////////////////////////////////
	//									     //
	// Used to load the FX palette from file //
	//									     //
	///////////////////////////////////////////


	HANDLE hFile;

	
	// Attempt to open the palette file, if failure, return false //

	if ((hFile = CreateFile(strFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0)) == INVALID_HANDLE_VALUE)
		return FALSE;


	// Continue the loading at another file //

	return Load(hFile);
	}




BOOL CFXPalette::Load(HANDLE hFile)
	{

	///////////////////////////////////////////
	//									     //
	// Used to load the FX palette from file //
	//									     //
	///////////////////////////////////////////


	DWORD NumRead;


	for (int i = 0 ; i < 256; i++)
		{
		ReadFile(hFile, Entry[i].Blend, 256, &NumRead, NULL);

		if (NumRead != 256)
			{
			CloseHandle(hFile);
			return FALSE;
			}
		}


	CloseHandle(hFile);

	return TRUE;
	}