#ifndef __CTimer_H
#define __CTimer_H



#define TIMER_COUNT_DOWN	0
#define TIMER_COUNT_UP		1



////////////////////////
//					  //
// CTimer Declaration //
//					  //
////////////////////////


class CTimer;




struct TIMER_ITEM
	{
	CTimer * pTimer;

	TIMER_ITEM * pPrev,
			   * pNext;
	};




class CTimer
	{
	public:

		CTimer();
		~CTimer();

		static void Add(CTimer * pTimer);
		static void Remove(CTimer * pTimer);
		static void RemoveAll();

		static void DoLogic();
		static void DoLogic(CTimer * pTimer, int MSecDelta);

		static void StopAll();
		static void PauseAll();
		static void ResumeAll();

		void Create();
		void Remove();

		void CountDown(int MSecs);
		void CountUp(int MSecs = 0);
		int GetCount()					{ return m_Count; }

		void CountDownSecs(int Secs)	{ CountDown(Secs * 1000); }
		void CountUpSecs(int Secs = 0)  { CountUp(Secs * 1000); }
		int GetCountSecs()				{ return int(m_Count / 1000); }

		void Enabled(BOOL Val = TRUE)	{ m_Enabled = Val; }
		void Stop()						{ m_Enabled = FALSE; m_Done = TRUE; m_Count = 0; }
		void Pause()					{ m_Enabled = FALSE; }
		void Resume()					{ m_Enabled = TRUE; }

		BOOL IsEnabled()				{ return m_Enabled; }
		BOOL IsDone()					{ return m_Done; }


	protected:

		BOOL m_Created,
			 m_Done,
			 m_Enabled;

		int m_Count;

		int m_Type;


		static TIMER_ITEM * m_pFirst;
		static TIMER_ITEM * m_pLast;
		static DWORD m_LastTickCount;
	};



#endif