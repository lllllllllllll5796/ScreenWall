
#include "stdafx.h"
#include "Utility.h"



LRESULT EnableWindowTheme(HWND hwnd, LPCWSTR classList, LPCWSTR subApp, LPCWSTR idlist)
{
	LRESULT lResult = S_FALSE;

	HRESULT(__stdcall *pSetWindowTheme)(HWND hwnd, LPCWSTR pszSubAppName, LPCWSTR pszSubIdList);
	HANDLE(__stdcall *pOpenThemeData)(HWND hwnd, LPCWSTR pszClassList);
	HRESULT(__stdcall *pCloseThemeData)(HANDLE hTheme);

	HMODULE hinstDll = ::LoadLibrary(_T("UxTheme.dll"));
	if (hinstDll)
	{
		(FARPROC&)pOpenThemeData = ::GetProcAddress(hinstDll, "OpenThemeData");
		(FARPROC&)pCloseThemeData = ::GetProcAddress(hinstDll, "CloseThemeData");
		(FARPROC&)pSetWindowTheme = ::GetProcAddress(hinstDll, "SetWindowTheme");
		if (pSetWindowTheme && pOpenThemeData && pCloseThemeData)
		{
			HANDLE theme = pOpenThemeData(hwnd, classList);
			if (theme != NULL)
			{
				VERIFY(pCloseThemeData(theme) == S_OK);
				lResult = pSetWindowTheme(hwnd, subApp, idlist);
			}
		}
		::FreeLibrary(hinstDll);
	}
	return lResult;
}