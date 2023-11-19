#ifndef __CStage_H
#define __CStage_H


#include "Bitmap.h"
#include "Input.h"
#include "Cursor.h"


class CTransition;



class CStage
	{
	public:

		///////////////////
		// Overrideables //
		///////////////////

		virtual void Opening()						{ ShowCursor(FALSE); MouseHandlesCursor(FALSE); }
		virtual void Closing(CStage * pStage)		{}
		virtual void DoInput(CInput * pInput)		{ if (m_MouseHandlesCursor) m_Cursor.Move(pInput); }
		virtual void DoLogic()						{}
		virtual void DoGraphics(CBitmap * pBuffer)	{ if (m_ShowCursor)	m_Cursor.Draw(pBuffer); }


		/////////////////////
		// Cursor Routines //
		/////////////////////

		void ShowCursor(BOOL Show)				{ m_ShowCursor = Show; }
		void SetCursorSprite(CSprite * pSprite)	{ m_Cursor.SetSprite(pSprite); }
		void MouseHandlesCursor(BOOL Val)		{ m_MouseHandlesCursor = Val; }
		void SetCursorLimits(int x1, int y1, int x2, int y2, int z1 = 0, int z2 = 0)	{ m_Cursor.SetPosLimits(x1, y1, x2, y2, z1, z2); }
		void SetCursorSpeed(int Speed)			{ m_Cursor.SetSpeed(Speed); }
		int GetCursorX()						{ return m_Cursor.GetXPos(); }
		int GetCursorY()						{ return m_Cursor.GetYPos(); }
		int GetCursorZ()						{ return m_Cursor.GetZPos(); }
		void SetCursorX(int Val)				{ m_Cursor.SetXPos(Val); }	
		void SetCursorY(int Val)				{ m_Cursor.SetYPos(Val); }	
		void SetCursorZ(int Val)				{ m_Cursor.SetZPos(Val); }	



	protected:

		int m_State;


		///////////////////
		// Cursor Object //
		///////////////////

		CCursor		m_Cursor;


		///////////////////
		// Cursor States //
		///////////////////

		BOOL	m_ShowCursor;
		BOOL	m_MouseHandlesCursor;


		///////////////////////
		// Misc. Text Buffer //
		///////////////////////

		char	m_strText[256];
	};


#endif