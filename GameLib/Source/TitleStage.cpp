#include <windows.h>
#include <stdio.h> 
#include "..\Header\TitleStage.h"
#include "..\Header\Pong.h"



void CTitleStage::Opening()
	{
	TitleBmp.LoadBMP("Title.Bmp");
	//Pong.SetPalette(TitleBmp.GetPalette());
	}



void CTitleStage::Closing(CStage * pStage)
	{
	TitleBmp.Destroy();
	}



void CTitleStage::DoInput(CInput & Input)	
	{
	if (Input.Mouse.Button[1])
		Pong.SetStage(&MainStage);
	}



void CTitleStage::DoLogic()	
	{
	}



void CTitleStage::DoGraphics(CBitmap & Buffer)
	{
	Buffer.Blit8(TitleBmp, 0, 0, 320, 240, 0, 0);
	}

