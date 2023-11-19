#ifndef __VIEW_H
#define __VIEW_H


#include "Wnd.h"


#define MAX_LAYERS		5


class CLayer;


class CView : public CWnd
	{
	public:

		virtual void Create(CWndStage * m_pWndStage, CWnd * pParentWnd, int x, int y, int width, int height, int BPP = 8, BOOL Transparent = FALSE);
		
		void AddLayer(CLayer * pLayer);


	protected:

		int m_NumLayers;
		CLayer * m_pLayer[MAX_LAYERS];


	public:

		virtual void OnPaint();
	};


#endif