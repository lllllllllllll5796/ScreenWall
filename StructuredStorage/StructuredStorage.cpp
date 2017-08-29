
// StructuredStorage.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "StructuredStorage.h"
#include "StructuredStorageDlg.h"

#include "Stg.h"
//#include <vector>
//#include <list>
//#include <hash_map>
//using std::vector;
//using std::list;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStructuredStorageApp

BEGIN_MESSAGE_MAP(CStructuredStorageApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CStructuredStorageApp construction

CStructuredStorageApp::CStructuredStorageApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CStructuredStorageApp object

CStructuredStorageApp theApp;
CGobalVariable g_GobalVariable;

//读取配置线程
unsigned int __stdcall ReadStgCfgThread(PVOID pv);

// CStructuredStorageApp initialization
//#include <map>
//#include <string>
//struct TEST {
//	//std::map<int, int> mapTest;
//	//int a;
//	std::string s;
//};

enum TestEnum {
	TestEnum_Buff
};

BOOL CStructuredStorageApp::InitInstance()
{
	//size_t len = sizeof(TEST);

	//size_t  len = sizeof(TestEnum);


	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	if (false == g_GobalVariable.Init())
		return FALSE;
	//读取配置线程
	unsigned int nThreadID(0);
	HANDLE hThread = (HANDLE)_beginthreadex(nullptr, 0, ReadStgCfgThread, nullptr, 0, &nThreadID);
	CloseHandle(hThread); hThread = nullptr;

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CStructuredStorageDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


unsigned int __stdcall ReadStgCfgThread(PVOID pv)
{
	unsigned int nRet = 0;

	CSSFile* pSSFile = new CSSFile;
	CString strFilename = g_GobalVariable.szExePath;
	strFilename += _T("STGCFG");//配置文件名
	if (pSSFile->OpenSSFile(strFilename, STGM_READ | STGM_SHARE_EXCLUSIVE)) {
		//读取配置
	}
	else {
		//创建默认配置文件

	}

	SAFE_DELETE(pSSFile);

	return nRet;
}