#include <windows.h>
#include "..\Header\Timer.h"



TIMER_ITEM * CTimer::m_pFirst	= NULL;
TIMER_ITEM * CTimer::m_pLast	= NULL;
DWORD CTimer::m_LastTickCount	= GetTickCount();



///////////////////////////
//						 //
// CTimer Implementation //
//						 //
///////////////////////////



CTimer::CTimer()
	{
	m_Done		= TRUE;
	m_Enabled	= FALSE;
	m_Count		= 0;
	m_Type		= TIMER_COUNT_DOWN;
	m_Created	= FALSE;

	Create();
	}




CTimer::~CTimer()
	{
	Remove(this);
	}




void CTimer::Add(CTimer * pTimer)
	{
	if (!m_pFirst)
		{
		m_pFirst = new TIMER_ITEM;

		m_pFirst->pPrev = NULL;
		m_pFirst->pNext = NULL;

		m_pLast = m_pFirst;
		}
	else
		{
		m_pLast->pNext = new TIMER_ITEM;

		m_pLast->pNext->pPrev = m_pLast;
		m_pLast->pNext->pNext = NULL;

		m_pLast = m_pLast->pNext;
		}


	m_pLast->pTimer = pTimer;
	}




void CTimer::Remove(CTimer * pTimer)
	{
	TIMER_ITEM * pCurr,
			   * pNext;


	pCurr = m_pFirst;


	while(pCurr)
		{
		pNext = pCurr->pNext;

		if (pTimer == pCurr->pTimer)
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

			free(pCurr);
			}


		pCurr = pNext;
		}
	}




void CTimer::RemoveAll()
	{
	TIMER_ITEM * pCurr,
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





void CTimer::DoLogic()
	{
	TIMER_ITEM * pCurr,
			   * pNext;

	DWORD TickCount;
	int TickDelta;


	// Return if no timers are loaded //

	if (!m_pFirst)
		return;


	// Get the tick count delta //

	TickCount		= GetTickCount();
	TickDelta		= TickCount - m_LastTickCount;

	m_LastTickCount	= TickCount;



	// Scroll through the timer list and do logic for each timer //

	pCurr = m_pFirst;

	while(pCurr)
		{
		pNext = pCurr->pNext;

		DoLogic(pCurr->pTimer, TickDelta);

		pCurr = pNext;
		}
	}




void CTimer::DoLogic(CTimer * pTimer, int MSecDelta)
	{
	if (!pTimer->m_Enabled || pTimer->m_Done)
		return;


	switch(pTimer->m_Type)
		{
		case TIMER_COUNT_UP:
			pTimer->m_Count += MSecDelta;
			break;


		case TIMER_COUNT_DOWN:
			pTimer->m_Count -= MSecDelta;

			if (pTimer->m_Count <= 0)
				{
				pTimer->m_Count		= 0;
				pTimer->m_Enabled	= FALSE;
				pTimer->m_Done		= TRUE;
				}
			break;
		}
	}




void CTimer::StopAll()
	{
	TIMER_ITEM * pCurr,
			   * pNext;


	pCurr = m_pFirst;


	while (pCurr)
		{
		pNext = pCurr->pNext;

		pCurr->pTimer->Stop();

		pCurr = pNext;
		}
	}




void CTimer::PauseAll()
	{
	TIMER_ITEM * pCurr,
			   * pNext;


	pCurr = m_pFirst;


	while (pCurr)
		{
		pNext = pCurr->pNext;

		if (!pCurr->pTimer->IsDone())
			pCurr->pTimer->Pause();

		pCurr = pNext;
		}
	}




void CTimer::ResumeAll()
	{
	TIMER_ITEM * pCurr,
			   * pNext;


	pCurr = m_pFirst;


	while (pCurr)
		{
		pNext = pCurr->pNext;

		if (!pCurr->pTimer->IsDone())
			pCurr->pTimer->Resume();

		pCurr = pNext;
		}
	}




void CTimer::Create()
	{
	if (!m_Created)
		{
		Add(this);
		m_Created = TRUE;
		}
	}



void CTimer::Remove()
	{
	Remove(this);
	}



void CTimer::CountDown(int MSecs)
	{
	m_Count		= MSecs;
	m_Enabled	= TRUE;
	m_Done		= FALSE;
	m_Type		= TIMER_COUNT_DOWN;
	}



void CTimer::CountUp(int MSecs)
	{
	m_Count		= MSecs;
	m_Enabled	= TRUE;
	m_Done		= FALSE;
	m_Type		= TIMER_COUNT_UP;
	}







