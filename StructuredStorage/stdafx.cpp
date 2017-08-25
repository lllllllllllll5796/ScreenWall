
// stdafx.cpp : source file that includes just the standard includes
// StructuredStorage.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


bool CGobalVariable::Init()
{
	//程序所在目录
	GetModuleFileName(AfxGetInstanceHandle(), szExePath, MAX_PATH);
	TCHAR* pFind = _tcsrchr(szExePath, '\\');
	szExePath[_tcslen(szExePath) - _tcslen(pFind) + 1] = '\0';

	//结构化存储
	const TCHAR* pStgFilename = _T("ScreenWallStructuredStorage");
	_tcscpy_s(szStgFilename, szExePath);
	_tcscat_s(szStgFilename, pStgFilename);

	return true;
}