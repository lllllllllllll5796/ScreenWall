#include "stdafx.h"
#include "Stg.h"


void StgCfgLoginUser::Read(LPSTREAM pStream)
{
	void* pv = this;
	ULONG len = sizeof(StgCfgLoginUser);

	ULONG ulOut = 0;
	HRESULT hr = pStream->Read(pv, len, &ulOut); //先读结构体
	if (FAILED(hr)) return;
	//读取用户名  和“写”对应
	pszUsername = new TCHAR[ccUsername + 1];
	pszUsername[ccUsername] = 0;
	hr = pStream->Read(pszUsername, ccUsername, &ulOut);
	//读取密码
	pszPswd = new TCHAR[ccPswd + 1];
	pszPswd[ccPswd] = 0;
	hr = pStream->Read(pszPswd, ccPswd, &ulOut);

	pStream->Release();

}

void StgCfgLoginUser::Write(LPSTREAM pStream)
{
	void* pv = this;
	ULONG len = sizeof(StgCfgLoginUser);

	ULONG ulOut = 0;
	//pszUsername = _T("hello,stg!");
	ccUsername = _tcslen(pszUsername);
	ccPswd = _tcslen(pszPswd);
	HRESULT hr = pStream->Write(pv, len, &ulOut);
	if (FAILED(hr)) return;

	hr = pStream->Write(pszUsername, 2 * ccUsername, &ulOut);
	hr = pStream->Write(pszPswd, 2 * ccPswd, &ulOut);

	pStream->Release();
}