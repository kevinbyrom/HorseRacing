#include <windows.h>
#include "..\Header\Wnd.h"
#include "..\Header\WndStage.h"




/////////////////////////
//					   //
// CWnd Implementation //
//					   //
/////////////////////////



void CWnd::Create(CWndStage * pWndStage, CWnd * pParentWnd, int x, int y, int width, int height, int BPP, BOOL Transparent)
	{

	//////////////////////////
	//						//
	// Used to create a wnd //
	//						//
	//////////////////////////


	m_pWndStage		= pWndStage;
	m_pParentWnd	= pParentWnd;
	m_X				= x;
	m_Y				= y;
	m_Width			= width;
	m_Height		= height;
	m_Visible		= TRUE;
	m_Transparent	= Transparent;
	m_BackColor		= 0;


	// Add to a wnd list //

	if (m_pParentWnd)
		{
		m_pParentWnd->AddToWndList(this);
		m_ScreenX = m_pParentWnd->GetScreenX() + m_X;
		m_ScreenY = m_pParentWnd->GetScreenY() + m_Y;
		}
	else 
		{
		m_pWndStage->AddToWndList(this);
		m_ScreenX = m_X;
		m_ScreenY = m_Y;
		}


	// Create the buffer bitmap //
	
	m_Bmp.Create(m_Width, m_Height, BPP);


	// Call the virtual OnCreate function //

	OnCreate();
	}




void CWnd::Destroy()
	{

	/////////////////////////////
	//						   //
	// Used to destroy the wnd //
	//						   //
	/////////////////////////////


	// Call the virtual OnDestroy Function //

	OnDestroy();


	// Remove the wnd from any wnd list it belongs to //

	if (m_pParentWnd)
		m_pParentWnd->RemoveFromWndList(this);
	else if (m_pWndStage)
		m_pWndStage->RemoveFromWndList(this);


	// Set the variables to NULL or Zero //

	m_pWndStage		= NULL;
	m_pParentWnd	= NULL;
	m_X				= 0;
	m_Y				= 0;
	m_Width			= 0;
	m_Height		= 0;
	m_Visible		= FALSE;

	
	// Destroy the buffer bitmap //

	m_Bmp.Destroy();
	}





void CWnd::DoGraphics(CBitmap * pBuffer)
	{

	/////////////////////////////////////////////
	//										   //
	// Used to handle the graphics for the wnd //
	//										   //
	/////////////////////////////////////////////


	if (m_Visible)
		{
		// Fill the work buffer with the specified back color //

		if (!m_Transparent)
			m_Bmp.Fill(m_BackColor);


		// If transparent, copy the screen buffer to the work buffer //

		if (m_Transparent)
			m_Bmp.Blit(pBuffer, 0, 0, m_Width, m_Height, m_ScreenX, m_ScreenY);


		// Call the virtual paint function //

		OnPaint();


		// Blit the work buffer onto the screen buffer //

		pBuffer->Blit(&m_Bmp, m_X, m_Y, m_Width, m_Height, 0, 0);


		// Call the wnd list DoGraphics for any child wnds //

		m_WndList.DoGraphics(&m_Bmp);
		}
	}




///////////////////////////////
//						     //
// CWndList Implementation //
//						     //
///////////////////////////////



CWndList::CWndList()
	{
	m_pFirst = NULL;
	m_pLast	 = NULL;
	}



CWndList::~CWndList()
	{
	RemoveAll();
	}




void CWndList::Add(CWnd * pWnd)
	{

	///////////////////////////////////////
	//									 //
	// Used to add a wnd to the wnd list //
	//									 //
	///////////////////////////////////////


	if (!m_pFirst)
		{
		m_pFirst = new WND_ITEM;

		m_pFirst->pPrev = NULL;
		m_pFirst->pNext = NULL;

		m_pLast = m_pFirst;
		}
	else
		{
		m_pLast->pNext = new WND_ITEM;

		m_pLast->pNext->pPrev = m_pLast;
		m_pLast->pNext->pNext = NULL;

		m_pLast = m_pLast->pNext;
		}


	m_pLast->pWnd = pWnd;
	}




void CWndList::Remove(CWnd * pWnd)
	{

	////////////////////////////////////////////
	//									      //
	// Used to remove a wnd from the wnd list //
	//									      //
	////////////////////////////////////////////


	WND_ITEM * pCurr,
			 * pNext;


	pCurr = m_pFirst;


	while(pCurr)
		{
		pNext = pCurr;

		if (pWnd == pCurr->pWnd)
			{
			if (pCurr->pPrev)
				pCurr->pPrev->pNext = pCurr->pNext;

			if (pCurr->pNext)
				pCurr->pNext->pPrev = pCurr->pPrev;

			if (pCurr == m_pFirst)
				{
				if (pCurr->pNext)
					m_pFirst = pCurr->pNext;
				else
					m_pFirst = NULL;
				}

			if (pCurr == m_pLast)
				{
				if (pCurr->pPrev)
					m_pLast = pCurr->pPrev;
				else
					m_pLast = NULL;
				}

			delete pCurr;
			}


		pCurr = pNext;
		}
	}




void CWndList::RemoveAll()
	{

	///////////////////////////////////////////////
	//											 //
	// Used to remove all wnds from the wnd list //
	//											 //
	///////////////////////////////////////////////


	WND_ITEM * pCurr,
			 * pNext;


	pCurr = m_pFirst;


	while (pCurr)
		{
		pNext = pCurr->pNext;

		delete pCurr;

		pCurr = pNext;
		}

	m_pFirst	= NULL;
	m_pLast		= NULL;
	}






void CWndList::DoGraphics(CBitmap * pBuffer)
	{

	///////////////////////////////////////////////////////////////
	//															 //
	// Used to perform the graphics for all wnds in the wnd list //
	//															 //
	///////////////////////////////////////////////////////////////


	WND_ITEM * pCurr;


	pCurr = m_pFirst;


	while (pCurr)
		{
		pCurr->pWnd->DoGraphics(pBuffer);	

		pCurr = pCurr->pNext;
		}
	}





void CWndList::MovePrev(CWnd * pWnd)
	{

	/////////////////////////////////////////////
	//										   //
	// Used to move a wnd back in the wnd list //
	//										   //
	/////////////////////////////////////////////


	WND_ITEM * pCurr, 
			 * pNext;
	
	CWnd * pPrevWnd;


	pCurr = m_pFirst;


	// Scroll through the list until we find a matching wnd //

	while(pCurr)
		{
		pNext = pCurr->pNext;

		if (pCurr->pWnd == pWnd)
			{
			if (pCurr->pPrev)
				{
				pPrevWnd = pCurr->pPrev->pWnd;

				pCurr->pPrev->pWnd	= pCurr->pWnd;
				pCurr->pWnd			= pPrevWnd;
				}

			return;
			}

		pCurr = pNext;
		}
	}





void CWndList::MoveNext(CWnd * pWnd)
	{

	////////////////////////////////////////////////
	//										      //
	// Used to move a wnd forward in the wnd list //
	//										      //
	////////////////////////////////////////////////


	WND_ITEM * pCurr, 
			 * pNext;
	
	CWnd * pNextWnd;


	pCurr = m_pFirst;


	// Scroll through the list until we find a matching wnd //

	while(pCurr)
		{
		pNext = pCurr->pNext;

		if (pCurr->pWnd == pWnd)
			{
			if (pCurr->pNext)
				{
				pNextWnd = pCurr->pNext->pWnd;

				pCurr->pNext->pWnd	= pCurr->pWnd;
				pCurr->pWnd			= pNextWnd;
				}

			return;
			}

		pCurr = pNext;
		}
	}





void CWndList::MoveToFirst(CWnd * pWnd)
	{

	/////////////////////////////////////////////////////
	//										           //
	// Used to move a wnd to the front of the wnd list //
	//										           //
	/////////////////////////////////////////////////////


	WND_ITEM * pCurr, 
			 * pNext;
	

	pCurr = m_pFirst;


	// Scroll through the list until we find a matching wnd //

	while(pCurr)
		{
		pNext = pCurr->pNext;

		if (pCurr->pWnd == pWnd)
			{
			// Do nothing if moving a wnd to first if already in first spot //

			if (pCurr == m_pFirst)
				return;

			if (pCurr == m_pLast)
				{
				m_pLast = pCurr->pPrev;
				pCurr->pPrev->pNext = NULL;
				}

			m_pFirst->pPrev = pCurr;

			pCurr->pNext = m_pFirst;
			pCurr->pPrev = NULL;

			m_pFirst = pCurr; 

			return;
			}

		pCurr = pNext;
		}
	}





void CWndList::MoveToLast(CWnd * pWnd)
	{

	////////////////////////////////////////////////////
	//										          //
	// Used to move a wnd to the back of the wnd list //
	//										          //
	////////////////////////////////////////////////////


	WND_ITEM * pCurr, 
			 * pNext;
	

	pCurr = m_pFirst;


	// Scroll through the list until we find a matching wnd //

	while(pCurr)
		{
		pNext = pCurr->pNext;

		if (pCurr->pWnd == pWnd)
			{
			// Do nothing if moving a wnd to last if already in last spot //

			if (pCurr == m_pLast)
				return;

			if (pCurr == m_pFirst)
				{
				m_pFirst = pCurr->pNext;
				pCurr->pNext->pPrev = NULL;
				}

			m_pLast->pNext = pCurr;

			pCurr->pPrev = m_pLast;
			pCurr->pNext = NULL;

			m_pLast = pCurr; 

			return;
			}

		pCurr = pNext;
		}
	}




CWnd * CWndList::GetWndFromPos(int x, int y)
	{
	CWnd * pWnd			= NULL;
	CWnd * pIsWndAtPos	= NULL;
	CWnd * pWndAtPos	= NULL;

	WND_ITEM * pCurr, 
			 * pNext;
	

	pCurr = m_pFirst;


	// Scroll through the list until we find a matching wnd //

	while(pCurr)
		{
		pNext = pCurr->pNext;

		pWnd = pCurr->pWnd;

		if (x >= pWnd->GetScreenX() && x < pWnd->GetScreenX() + pWnd->GetWidth() &&
			y >= pWnd->GetScreenY() && y < pWnd->GetScreenY() + pWnd->GetHeight())
			{
			pWndAtPos = pWnd;

			pIsWndAtPos = NULL;
			pIsWndAtPos = pWnd->m_WndList.GetWndFromPos(x, y);

			if (pIsWndAtPos)
				pWndAtPos = pIsWndAtPos;
			}

		pCurr = pNext;
		}


	return pWndAtPos;
	}