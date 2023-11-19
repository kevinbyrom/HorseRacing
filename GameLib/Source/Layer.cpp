#include <windows.h>
#include "..\Header\Layer.h"




void CLayer::Create(CView * pParentView, int x, int y, int width, int height, int BPP)
	{
	m_pParentView = pParentView;

	m_ScreenX	= m_pParentView->GetScreenX() + x;
	m_ScreenY	= m_pParentView->GetScreenY() + y;
	m_X			= x;
	m_Y			= y;
	m_Width		= width;
	m_Height	= height;
	m_BPP		= BPP;

	m_pParentView->AddLayer(this);
	}





void CLayer::SetEyePos(float x, float y)		
	{ 
	m_EyeX = x; 
	m_EyeY = y;
	}





void CLayer::MoveEyePos(float xdelta, float ydelta)	
	{ 
	m_EyeX += xdelta; 
	m_EyeY += ydelta; 
	}