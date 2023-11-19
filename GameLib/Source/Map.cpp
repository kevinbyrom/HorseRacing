#include <windows.h>
#include "..\Header\Map.h"
#include "..\Header\Memory.h"



CMap::CMap()
	{
	Tile = NULL;

	NumX = 0;
	NumY = 0;
	ResX = 0;
	ResY = 0;
	}



CMap::~CMap()
	{
	Destroy();
	}




BOOL CMap::Create(int NX, int NY, int RX, int RY, int DefTileVal)
	{

	//////////////////////////
	//						//
	// Used to create a map //
	//						//
	//////////////////////////


	if (NX == 0 || NY == 0 || Tile != NULL)
		return FALSE;


	Tile = new char[NY * NX];


	NumX = NX;
	NumY = NY;
	ResX = RX;
	ResY = RY;
	
	NumTiles = NumX * NumY;


	memset(Tile, DefTileVal, NumTiles);


	return TRUE;
	}




void CMap::Destroy()
	{

	///////////////////////////
	//						 //
	// Used to destroy a map //
	//						 //
	///////////////////////////


	if (Tile != NULL)
		delete[] Tile;

	Tile = NULL;

	NumX = 0;
	NumY = 0;
	ResX = 0;
	ResY = 0;	
	}




BOOL CMap::Resize(int NewX, int NewY, int DefTileVal, BOOL KeepInfo)
	{

	///////////////////////////////////////
	//									 //
	// Used to resize a map's dimensions //
	//									 //
	///////////////////////////////////////

	
	char * BackupTile;
	
	int BackupX,
		BackupY,
		BackupRX,
		BackupRY;

	int SmallX,
		SmallY,
		YPos;


	// Return false if resizing to an invalid size //

	if (NewX == 0 || NewY == 0 || Tile == NULL)
		return FALSE;



	// Backup the information //

	BackupTile	= new char[NumY * NumX];
	BackupX		= NumX;
	BackupY		= NumY;
	BackupRX	= ResX;
	BackupRY	= ResY;



	// Destroy the map & Create a new one //

	Destroy();

	if (!Create(NewX, NewY, BackupRX, BackupRY, DefTileVal))
		return FALSE;


	if (!KeepInfo)
		{
		delete[] BackupTile;
		return TRUE;
		}



	// Figure out the smallest X & Y dimensions //

	SmallX = NewX < BackupX ? NewX : BackupX;
	SmallY = NewY < BackupY ? NewY : BackupY;



	// Copy the old tile info to the new map //

	for (YPos = 0; YPos < SmallY; YPos++)
		memcpy(&Tile[YPos * SmallX], &BackupTile[YPos * SmallX], SmallX);



	// Delete the backup //

	delete[] BackupTile;


	return TRUE;
	}




int CMap::GetTileX(int PointX)
	{

	//////////////////////////////////////////////
	//											//
	// Used to get a tile position from a point //
	//											//
	//////////////////////////////////////////////


	if (Tile == NULL || PointX < 0 || PointX >= NumX * ResX)
		return -1;

	
	return (PointX / ResX);
	}




int CMap::GetTileY(int PointY)
	{

	//////////////////////////////////////////////
	//											//
	// Used to get a tile position from a point //
	//											//
	//////////////////////////////////////////////


	if (Tile == NULL || PointY < 0 || PointY >= NumY * ResY)
		return -1;

	
	return (PointY / ResY);
	}




void CMap::SetRowVal(int Row, char Val)
	{

	/////////////////////////////////////////////////
	//											   //
	// Used to set the value of all tiles in a row //
	//											   //
	/////////////////////////////////////////////////


	if (Tile == NULL || Row < 0 || Row >= NumY)
		return;


	memset(&Tile[Row * NumX], Val, NumX);
	}




void CMap::SetColVal(int Col, char Val)
	{
	int y;


	if (Tile == NULL || Col < 0 || Col >= NumX)
		return;

	
	for (y = 0; y < NumY; y++)
		Tile[Col + (y * NumX)] = Val;
	}



//////////////////////////
//						//
// Save / Load Routines //
//						//
//////////////////////////




BOOL CMap::Save(LPCTSTR strFile)
	{

	//////////////////////////
	//						//
	// Used to save the map //
	//						//
	//////////////////////////


	HANDLE hFile;
	
	
	// Attempt to open the map file, if failure, return false //

	if ((hFile = CreateFile(strFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
		return FALSE;



	// Continue the saving at another function //

	return Save(hFile);
	}





BOOL CMap::Load(LPCTSTR strFile)
	{

	//////////////////////////
	//						//
	// Used to load the map //
	//						//
	//////////////////////////


	HANDLE hFile;
	
	
	// Attempt to open the map file, if failure, return false //

	if ((hFile = CreateFile(strFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
		return FALSE;



	// Continue the loading at another function //

	return Load(hFile);
	}





BOOL CMap::Save(HANDLE hFile)
	{

	//////////////////////////
	//						//
	// Used to save the map //
	//						//
	//////////////////////////


	DWORD NumWritten;


	// Return false if the map is invalid //

	if (NumTiles == 0 || Tile == NULL)
		{
		CloseHandle(hFile);
		return FALSE;
		}



	// Write the number of tiles & resolution first //

	WriteFile(hFile, &NumX, sizeof(NumX), &NumWritten, NULL);
	WriteFile(hFile, &NumY, sizeof(NumY), &NumWritten, NULL);
	WriteFile(hFile, &ResX, sizeof(ResX), &NumWritten, NULL);
	WriteFile(hFile, &ResY, sizeof(ResY), &NumWritten, NULL);



	// Now write the tile info //

	WriteFile(hFile, Tile, NumTiles, &NumWritten, NULL);



	// Close the handle //
		
	CloseHandle(hFile);


	return TRUE;
	}





BOOL CMap::Load(HANDLE hFile)
	{

	//////////////////////////
	//						//
	// Used to load the map //
	//						//
	//////////////////////////


	DWORD NumRead;
	int NX, NY, RX, RY;



	// If a map is already loaded, destroy it //

	if (Tile != NULL)
		Destroy();



	// Read the number of tiles & resolution first //

	ReadFile(hFile, &NX, sizeof(NX), &NumRead, NULL);
	ReadFile(hFile, &NY, sizeof(NY), &NumRead, NULL);
	ReadFile(hFile, &RX, sizeof(RX), &NumRead, NULL);
	ReadFile(hFile, &RY, sizeof(RY), &NumRead, NULL);



	// Create the map //

	if (!Create(NX, NY, RX, RY))
		return FALSE;



	// Now read the tile info //

	ReadFile(hFile, Tile, NumTiles, &NumRead, NULL);



	// Close the handle //
		
	CloseHandle(hFile);


	return TRUE;
	}