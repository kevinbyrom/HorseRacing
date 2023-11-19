#ifndef __CWnd_H
#define __CWnd_H


#include "Input.h"
#include "Bitmap.h"



class CWndStage;
class CWnd;



//////////////////////////
//						//
// Wnd List Declaration //
//						//
//////////////////////////



struct WND_ITEM
	{
	CWnd * pWnd;
	
	WND_ITEM * pPrev,
			 * pNext;
	};




class CWndList
	{
	public:

		CWndList();
		~CWndList();

		void Add(CWnd * pWnd);
		void Remove(CWnd * pWnd);
		void RemoveAll();

		void DoGraphics(CBitmap * pBuffer);
		void DoInput(CInput * pInput);

		void MovePrev(CWnd * pWnd);
		void MoveNext(CWnd * pWnd);
		void MoveToFirst(CWnd * pWnd);
		void MoveToLast(CWnd * pWnd);

		CWnd * GetWndFromPos(int x, int y);


	protected:

		WND_ITEM * m_pFirst,
				 * m_pLast;
	};



//////////////////////
//					//
// CWnd Declaration //
//					//
//////////////////////



class CWnd
	{
	public:
 
		virtual void Create(CWndStage * m_pWndStage, CWnd * pParentWnd, int x, int y, int width, int height, int BPP = 8, BOOL Transparent = FALSE);
		virtual void Destroy();

		void SetVisible(BOOL Val)			{ m_Visible = Val; }

		virtual void DoInput(CInput * pInput){}
		virtual void DoGraphics(CBitmap * pBuffer);

		int GetScreenX()					{ return m_ScreenX; }
		int GetScreenY()					{ return m_ScreenY; }

		int GetX()							{ return m_X; }
		int GetY()							{ return m_Y; }

		int GetWidth()						{ return m_Width; }
		int GetHeight()						{ return m_Height; }

		void SetTransparent(BOOL Val)		{ m_Transparent	= Val; }
		void SetBackColor(int Val)			{ m_BackColor	= Val; }

		void AddToWndList(CWnd * pWnd)		{ m_WndList.Add(pWnd); }
		void RemoveFromWndList(CWnd * pWnd)	{ m_WndList.Remove(pWnd); }

		friend class CWnd;
		friend class CWndList;


	protected:

		CWndStage * m_pWndStage;
		CWnd  * m_pParentWnd;

		int m_ScreenX,
			m_ScreenY,
			m_X,
			m_Y,
			m_Width,
			m_Height;

		int m_BackColor;

		BOOL m_Visible,
			 m_Transparent;

		CBitmap m_Bmp;

		CWndList m_WndList;


	public:

		virtual void OnCreate()							{}
		virtual void OnDestroy()						{}
		virtual void OnPaint()							{}
		virtual void OnFocus()							{}
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