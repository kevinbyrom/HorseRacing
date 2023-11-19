#ifndef __CFXPalette_H
#define __CFXPalette_H


struct TColor
	{
	char Blend[256];
	};



class CFXPalette
	{
	public:

		void CreateTransPal(PALETTEENTRY * pPal, int TPercent);
		void CreateLitPal(PALETTEENTRY * pPal, int HighRed, int HighGreen, int HighBlue);

		BOOL Save(char * strFile);
		BOOL Save(HANDLE hFile);

		BOOL Load(char * strFile);
		BOOL Load(HANDLE hFile);

		TColor Entry[256];
	};


#endif