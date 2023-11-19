#ifndef __CMap_H
#define __CMap_H



class CMap
	{
	public:

		CMap();
		~CMap();

		BOOL Create(int NX, int NY, int RX = 1, int RY = 1, int DefTileVal = 0);
		void Destroy();

		BOOL Resize(int NewX, int NewY, int DefTileVal = 0, BOOL KeepInfo = TRUE);

		int GetTileX(int PointX);
		int GetTileY(int PointY);

		void SetRowVal(int Row, char Val);
		void SetColVal(int Col, char Val);

		BOOL Save(LPCTSTR strFile);
		BOOL Load(LPCTSTR strFile);

		BOOL Save(HANDLE hFile);
		BOOL Load(HANDLE hFile);

		char * Tile;
		
		int NumX,
			NumY,
			NumTiles;

		int ResX, 
			ResY;
	};



#endif