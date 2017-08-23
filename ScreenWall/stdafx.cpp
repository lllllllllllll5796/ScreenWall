
// stdafx.cpp : source file that includes just the standard includes
// ScreenWall.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"




CGobalVariable::CGobalVariable()
{
	//hIconApp = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_Grid64px));
	//GDI+初始化：使用之前，结束GDI+调用后GdiplusShutdown
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

bool CGobalVariable::Init()
{
	bool bRet = true;
	hIconApp = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_Grid64px));

	return bRet;
}