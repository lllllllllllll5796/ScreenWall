
// stdafx.cpp : source file that includes just the standard includes
// StructuredStorage.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "Stg.h"

CGobalVariable::CGobalVariable()
{
	//m_ssFile = new CSSFile;
}

CGobalVariable::~CGobalVariable()
{
	//pStgRoot->Release();
	//SAFE_DELETE(m_ssFile);
}


bool CGobalVariable::Init()
{
	//程序所在目录
	GetModuleFileName(AfxGetInstanceHandle(), szExePath, MAX_PATH);
	TCHAR* pFind = _tcsrchr(szExePath, '\\');
	szExePath[_tcslen(szExePath) - _tcslen(pFind) + 1] = '\0';

	//根存储
	//const TCHAR* pStgFilename = _T("StructuredStorage");
	//TCHAR szStgFilename[MAX_PATH];
	//_tcscpy_s(szStgFilename, szExePath);
	//_tcscat_s(szStgFilename, pStgFilename);
	//CString strFilename(szExePath);
	//strFilename += _T("StructuredStorage");

	//if(!m_ssFile->OpenSSFile(strFilename)) {
	//	if(!m_ssFile->CreateSSFile(strFilename)) {
	//		TRACE(_T("CGobalVariable::Init : m_ssFile->CreateSSFile Failed !"));
	//		return false;
	//	}
	//	//else {
	//	//	//创建流
	//	//	for (int i = 0; i < StgDetailedCfgs_Buff; ++i) {
	//	//		CString strStreamName(g_StgStreamNames[i]);
	//	//		if (!m_ssFile->CreateStream(strStreamName)) {
	//	//			TRACE(_T("CGobalVariable::Init : m_ssFile->CreateStream Failed !"));
	//	//			break;
	//	//		}

	//	//	}
	//	//}
	//}
	//HRESULT hr = ::StgOpenStorage(szStgFilename, nullptr,
	//	STGM_READ | STGM_SHARE_EXCLUSIVE/*拒绝其他程序读写*/, nullptr, 0, &pStgRoot);
	//if (FAILED(hr)) {
	//	TRACE(_T("CGobalVariable::Init : StgOpenStorage Failed !"));
	//	//创建文件
	//	hr = ::StgCreateDocfile(szStgFilename, 
	//		STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE, 0, &pStgRoot);
	//	if (FAILED(hr)) {
	//		TRACE(_T("CGobalVariable::Init : StgCreateDocfile Failed !"));
	//		return false;
	//	}
	//}


	return true;
}