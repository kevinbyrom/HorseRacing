#ifndef __CMapCtl_H
#define __CMapCtl_H


#include "Control.h"
#include "Map.h"
#include "Sprite.h"


class CMapCtl : public CWnd
	{
	public:

		void Create(CWndStage * pWndStage, CWnd * pParentWnd, int x, int y, int width, int height, BOOL WrapX = FALSE, BOOL WrapY = FALSE, int BPP = 8, BOOL Transparent = TRUE);

		void SetMap(CMap * pMap)				{ m_pMap = pMap; }
		void SetSpriteArray(CSprite * pSprite)	{ m_pSprite = pSprite; }

		void SetEyePos(float x, float y);			
		void MoveEyePos(float xdelta, float ydelta);	


	protected:

		CMap	* m_pMap;
		CSprite * m_pSprite;

		BOOL m_WrapX,
			 m_WrapY;

		float m_EyeX, 
			  m_EyeY;


	public:

		virtual void OnDestroy();
		virtual void OnPaint();
	};



#endif