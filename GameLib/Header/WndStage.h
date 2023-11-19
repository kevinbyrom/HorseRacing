#ifndef __WNDSTAGE_H
#define __WNDSTAGE_H


#include "Stage.h"
#include "Wnd.h"


class CWndStage : public CStage
	{
	public:

		virtual void Opening();

		virtual void DoInput(CInput * Input);
		virtual void DoGraphics(CBitmap * pBuffer)	{ m_WndList.DoGraphics(pBuffer); CStage::DoGraphics(pBuffer); }

		void SetCapture(CWnd * pCapture)			{ m_pMouseCapture = pCapture; }
		void SetFocus(CWnd * pFocus)				{ m_pKeyFocus = pFocus; }


		//////////////////////
		// WndList Routines //
		//////////////////////

		void AddToWndList(CWnd * pWnd);			
		void RemoveFromWndList(CWnd * pWnd);		


	protected:

		CWndList m_WndList;

		CWnd * m_pMouseCapture;
		CWnd * m_pKeyFocus;

		int m_GUI;

		int m_LastCursorX, m_LastCursorY;
		int m_LButtonDown, m_RButtonDown;

		unsigned char m_KeyState[256];

		void EnableGUI()	{ m_GUI = 1; }
		void DisableGUI()	{ m_GUI = 0; }


	public:

		virtual void OnMouseMove(int x, int y)			{}
		virtual void OnLMouseDown(int x, int y)			{}
		virtual void OnLMouseUp(int x, int y)			{}
		virtual void OnRMouseDown(int x, int y)			{}
		virtual void OnRMouseUp(int x, int y)			{}
		virtual void OnKeyDown(unsigned char key)		{}
		virtual void OnKeyUp(unsigned char key)			{}
		virtual void OnKeyPressed(unsigned char key)	{}
	};

#endif