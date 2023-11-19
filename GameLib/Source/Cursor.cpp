#include <windows.h>
#include "..\Header\Cursor.h"
#include "..\Header\Bitmap.h"
#include "..\Header\Sprite.h"
#include "..\Header\Input.h"





void CCursor::Draw(CBitmap * pBuffer)
	{

	/////////////////////////////
	//						   //
	// Used to draw the cursor //
	//						   //
	/////////////////////////////


	if (m_pSprite != NULL)
		{
		m_pSprite->Draw(pBuffer, m_X, m_Y);
		}
	else
		{
		pBuffer->DrawLine(m_X - 5, m_Y, m_X - 1, m_Y, m_Color);
		pBuffer->DrawLine(m_X + 1, m_Y, m_X + 5, m_Y, m_Color);
		pBuffer->DrawLine(m_X, m_Y - 5, m_X, m_Y - 1, m_Color);
		pBuffer->DrawLine(m_X, m_Y + 1, m_X, m_Y + 5, m_Color);
		}
	}






void CCursor::Move(CInput * pInput)
	{

	/////////////////////////////
	//						   //
	// Used to move the cursor //
	//						   //
	/////////////////////////////


	m_X += (pInput->Mouse.X * m_Speed);
	m_Y += (pInput->Mouse.Y * m_Speed);
	m_Z += (pInput->Mouse.Z * m_Speed);


	if (m_X < m_MinX)	m_X = m_MinX;
	if (m_Y < m_MinY)	m_Y = m_MinY;
	if (m_Z < m_MinZ)	m_Z = m_MinZ;

	if (m_X > m_MaxX)	m_X = m_MaxX;
	if (m_Y > m_MaxY)	m_Y = m_MaxY;
	if (m_Z > m_MaxZ)	m_Z = m_MaxZ;
	}






void CCursor::SetSprite(CSprite * pSprite)
	{

	///////////////////////////////////
	//								 //
	// Used to set the cursor sprite //
	//								 //
	///////////////////////////////////


	m_pSprite = pSprite;
	}






void CCursor::SetXPos(int Val)
	{

	/////////////////////////////////////////
	//									   //
	// Used to set the cursor's X position //
	//									   //
	/////////////////////////////////////////


	m_X = Val;

	if (m_X < m_MinX)	m_X = m_MinX;
	if (m_X > m_MaxX)	m_X = m_MaxX;
	}






void CCursor::SetYPos(int Val)
	{

	/////////////////////////////////////////
	//									   //
	// Used to set the cursor's Y position //
	//									   //
	/////////////////////////////////////////


	m_Y = Val;

	if (m_Y < m_MinY)	m_Y = m_MinY;
	if (m_Y > m_MaxY)	m_Y = m_MaxY;
	}







void CCursor::SetZPos(int Val)
	{

	/////////////////////////////////////////
	//									   //
	// Used to set the cursor's Z position //
	//									   //
	/////////////////////////////////////////


	m_Z = Val;

	if (m_Z < m_MinZ)	m_Z = m_MinZ;
	if (m_Z > m_MaxZ)	m_Z = m_MaxZ;
	}







void CCursor::SetPos(int x, int y, int z)
	{

	////////////////////////////////////////////////////
	//												  //
	// Used to set the cursor at a specified position //
	//												  //
	////////////////////////////////////////////////////


	SetXPos(x);
	SetYPos(y);
	SetZPos(z);
	}







void CCursor::SetPosLimits(int x1, int y1, int x2, int y2, int z1, int z2)
	{

	////////////////////////////////////////////////////
	//												  //
	// Used to set the position limits for the cursor //
	//												  //
	////////////////////////////////////////////////////


	m_MinX = x1;
	m_MinY = y1;
	m_MinZ = z1;

	m_MaxX = x2;
	m_MaxY = y2;
	m_MaxZ = z2;


	if (m_X < m_MinX)	m_X = m_MinX;
	if (m_Y < m_MinY)	m_Y = m_MinY;
	if (m_Z < m_MinZ)	m_Z = m_MinZ;

	if (m_X > m_MaxX)	m_X = m_MaxX;
	if (m_Y > m_MaxY)	m_Y = m_MaxY;
	if (m_Z > m_MaxZ)	m_Z = m_MaxZ;
	}






