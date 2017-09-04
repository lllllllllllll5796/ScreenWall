#pragma once

#define SAFE_DELETE(p)	\
if((p)){	\
delete (p); (p) = nullptr;	\
}


LRESULT EnableWindowTheme(HWND hwnd, LPCWSTR classList, LPCWSTR subApp, LPCWSTR idlist);
