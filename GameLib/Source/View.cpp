#include <windows.h>
#include "..\Header\View.h"
#include "..\Header\Layer.h"




void CView::Create(CWndStage * pWndStage, CWnd * pParentWnd, int x, int y, int width, int height, int BPP, BOOL Transparent)
	{
	// Call the default create //

	CWnd::Create(pWndStage, pParentWnd, x, y, width, height, BPP, Transparent);


	// Set default property values //

	m_NumLayers = 0;
	}





void CView::AddLayer(CLayer * pLayer)
	{
	if (m_NumLayers >= MAX_LAYERS)
		return;


	m_pLayer[m_NumLayers] = pLayer;
	m_NumLayers++;
	}




void CView::OnPaint()
	{

	/////////////////////////
	//					   //
	// Paint event handler //
	//					   //
	/////////////////////////


	int i;


	m_Bmp.Fill8(170);

	for (i = 0; i < m_NumLayers; i++)
		m_pLayer[i]->DoGraphics(&m_Bmp);
	}