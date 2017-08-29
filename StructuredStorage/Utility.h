#pragma once

#define SAFE_DELETE(p)	\
if((p)){	\
delete (p); (p) = nullptr;	\
}

typedef unsigned(__stdcall* PTHREAD_START)(void*);//__beginthreadex

LRESULT EnableWindowTheme(HWND hwnd, LPCWSTR classList, LPCWSTR subApp, LPCWSTR idlist);
