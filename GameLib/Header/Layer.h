#ifndef __LAYER_H
#define __LAYER_H


#include "View.h"
#include "Bitmap.h"


class CLayer
	{
	public:

		virtual void Create(CView * pParentView, int x, int y, int width, int height, int BPP = 8);

		virtual void SetEyePos(float x, float y);			
		virtual void MoveEyePos(float xdelta, float ydelta);


	protected:

		CView * m_pParentView;

		int m_ScreenX,
			m_ScreenY,
			m_X,
			m_Y,
			m_Width,
			m_Height,
			m_BPP;

		float m_EyeX, 
			  m_EyeY;


	public:

		virtual void DoGraphics(CBitmap * pBuffer){}
	};



#endif