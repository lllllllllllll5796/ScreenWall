
// ScreenWall.h : main header file for the ScreenWall application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CScreenWallApp:
// See ScreenWall.cpp for the implementation of this class
//

class CScreenWallApp : public CWinAppEx
{
public:
	CScreenWallApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CScreenWallApp theApp;


struct StgCfg;
class CGobalVariable {
public:
	HICON hIconApp;//标题栏图标
	//GDI+初始化
	ULONG_PTR gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;
	TCHAR szExePath[MAX_PATH];//exe路径
	TCHAR szStgCfgPath[MAX_PATH];//配置文档路径
	std::vector<StgCfg*> vecCfg;//配置
	HANDLE hEventReadStgCfg;//读取配置线程完成事件


public:
	CGobalVariable();
	~CGobalVariable();
	bool Init();
};
extern CGobalVariable g_GobalVariable; //全局变量