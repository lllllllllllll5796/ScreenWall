
// stdafx.cpp : source file that includes just the standard includes
// ScreenWall.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"




CGobalVariable::CGobalVariable()
{
	//hIconApp = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_Grid64px));
}

bool CGobalVariable::Init()
{
	bool bRet = true;
	hIconApp = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_Grid64px));

	return bRet;
}