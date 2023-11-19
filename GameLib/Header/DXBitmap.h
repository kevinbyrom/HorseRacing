#ifndef __CDXBitmap_H
#define __CDXBitmap_H


#include "..\..\DirectX\Header\DDraw.h"
#include "Bitmap.h"


class CDXBitmap : public CBitmap
	{
	public:

		// Surface routines //

		void AttachToDDSurface(LPDIRECTDRAWSURFACE4 lpSurface);
		
		BOOL LockDDSurface();
		BOOL UnlockDDSurface();


	protected:

		LPDIRECTDRAWSURFACE4 m_lpSurface;
	};



#endif
