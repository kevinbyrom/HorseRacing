#include <windows.h>
#include "..\Header\WndStage.h"




void CWndStage::Opening()
	{
	m_pMouseCapture = NULL;
	m_pKeyFocus		= NULL;
	m_LastCursorX	= 0;
	m_LastCursorY	= 0;
	m_LButtonDown	= 0;
	m_RButtonDown	= 0;

	m_GUI			= 0;

	memset(m_KeyState, 0, sizeof(char) * 256);

	ShowCursor(TRUE);
	MouseHandlesCursor(TRUE);
	}




void CWndStage::DoInput(CInput * pInput)
	{
	int CurX, CurY;
	CWnd * pWnd = NULL;



	// Call the base function first //

	CStage::DoInput(pInput);


	if (!m_GUI)
		return;


	pWnd = m_WndList.GetWndFromPos(GetCursorX(), GetCursorY());


	// Get the cursor location relative to the window it is over //

	if (m_pMouseCapture)
		{
		CurX = GetCursorX() - m_pMouseCapture->GetScreenX();
		CurY = GetCursorY() - m_pMouseCapture->GetScreenY();
		}
	else if (pWnd)
		{
		CurX = GetCursorX() - pWnd->GetScreenX();
		CurY = GetCursorY() - pWnd->GetScreenY();
		}



	// If a window has mouse capture, then call its OnMouseMove function //

	if (m_LastCursorX != GetCursorX() || m_LastCursorY != GetCursorY())
		{
		m_LastCursorX = GetCursorX();
		m_LastCursorY = GetCursorY();


		if (m_pMouseCapture)
			m_pMouseCapture->OnMouseMove(CurX, CurY);
		else if (pWnd)
			pWnd->OnMouseMove(CurX, CurY);
		}



	// If LButton is pressed, call the appropriate OnLButtonDown function //

	if (pInput->Mouse.Button[0] && !m_LButtonDown)
		{
		m_LButtonDown = TRUE;


		if (m_pMouseCapture)
			m_pMouseCapture->OnLMouseDown(CurX, CurY);
		else if (pWnd)
			pWnd->OnLMouseDown(CurX, CurY);
		}



	// If LButton is released, call the appropriate OnLButtonUp function //

	if (!pInput->Mouse.Button[0] && m_LButtonDown)
		{
		m_LButtonDown = FALSE;


		if (m_pMouseCapture)
			m_pMouseCapture->OnLMouseUp(CurX, CurY);
		else if (pWnd)
			pWnd->OnLMouseUp(CurX, CurY);
		}



	// If RButton is pressed, call the appropriate OnRButtonDown function //

	if (pInput->Mouse.Button[1] && !m_RButtonDown)
		{
		m_RButtonDown = TRUE;


		if (m_pMouseCapture)
			m_pMouseCapture->OnRMouseDown(CurX, CurY);
		else if (pWnd)
			pWnd->OnRMouseDown(CurX, CurY);
		}



	// If RButton is released, call the appropriate OnRButtonUp function //

	if (!pInput->Mouse.Button[1] && m_RButtonDown)
		{
		m_RButtonDown = FALSE;


		if (m_pMouseCapture)
			m_pMouseCapture->OnRMouseUp(CurX, CurY);
		else if (pWnd)
			pWnd->OnRMouseUp(CurX, CurY);
		}


	// Check for key presses //

	for (int i = 0; i < 256; i++)
		{
		if (pInput->KeyPressed(i))
			{
			m_KeyState[i] = 1;

			if (m_pKeyFocus)
				m_pKeyFocus->OnKeyDown(i);
			else
				OnKeyDown(i);
			}
		else if (!pInput->KeyPressed(i) && m_KeyState[i])
			{
			m_KeyState[i] = 0;

			if (m_pKeyFocus)
				{
				m_pKeyFocus->OnKeyUp(i);
				m_pKeyFocus->OnKeyPressed(i);
				}
			else
				{
				OnKeyUp(i);
				OnKeyPressed(i);
				}
			}
		}
	}




//////////////////////
// WndList Routines //
//////////////////////


void CWndStage::AddToWndList(CWnd * pWnd)			
	{ 
	m_WndList.Add(pWnd); 
	}



void CWndStage::RemoveFromWndList(CWnd * pWnd)		
	{ 
	m_WndList.Remove(pWnd); 
	}