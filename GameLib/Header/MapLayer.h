#ifndef __MAPLAYER_H
#define __MAPLAYER_H


#include "Layer.h"
#include "Map.h"
#include "Sprite.h"


class CMapLayer : public CLayer
	{
	public:

		void Create(CView * pParentView, int x, int y, int width, int height, BOOL WrapX = FALSE, BOOL WrapY = FALSE, int BPP = 8);

		void SetMap(CMap * pMap)				{ m_pMap = pMap; }
		void SetSpriteArray(CSprite * pSprite)	{ m_pSprite = pSprite; }	

		virtual void SetEyePos(float x, float y);			
		virtual void MoveEyePos(float xdelta, float ydelta);


	protected:

		CMap	* m_pMap;
		CSprite * m_pSprite;

		BOOL m_WrapX,
			 m_WrapY;


	public:

		virtual void DoGraphics(CBitmap * pBuffer);
	};



#endif