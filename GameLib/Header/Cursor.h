#ifndef __CCursor_H
#define __CCursor_H




class CBitmap;
class CInput;
class CSprite;



class CCursor
	{
	public:

		CCursor()							{ m_pSprite = NULL; m_X = 0; m_Y = 0; m_MinX = 0; m_MinY = 0; m_MaxX = 0; m_MaxY = 0; m_Color = 0; m_Speed = 1; }

		void Draw(CBitmap * pBuffer);
		void Move(CInput * pInput);

		void SetSprite(CSprite * pSprite);

		int GetXPos()						{ return m_X; }
		int GetYPos()						{ return m_Y; }
		int GetZPos()						{ return m_Z; }

		void SetXPos(int Val);
		void SetYPos(int Val);
		void SetZPos(int Val);
		void SetPos(int x, int y, int z = 0);
		void SetPosLimits(int x1, int y1, int x2, int y2, int z1 = 0, int z2 = 0);
		
		
		void SetSpeed(int Speed)			{ m_Speed = Speed; }


	protected:

		CSprite * m_pSprite;

		int m_X,
			m_Y,
			m_Z;

		int m_MinX,
			m_MinY,
			m_MinZ,
			m_MaxX,
			m_MaxY,
			m_MaxZ;

		int m_Color;

		int m_Speed;
	};




#endif