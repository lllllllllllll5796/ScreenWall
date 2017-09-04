
// stdafx.cpp : source file that includes just the standard includes
// StructuredStorage.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "Stg.h"


//读取配置线程
unsigned int __stdcall ReadStgCfgThread(PVOID pv);


CGobalVariable::CGobalVariable()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//m_ssFile = new CSSFile;
	hEventReadStgCfg = CreateEvent(nullptr, TRUE, FALSE, nullptr);//手动未触发
}

CGobalVariable::~CGobalVariable()
{
	//pStgRoot->Release();
	//SAFE_DELETE(m_ssFile);

	for (auto& p : vecCfg) {
		SAFE_DELETE(p);
	}
	//strStgCfgname.ReleaseBuffer(); //内存泄露

	//_CrtDumpMemoryLeaks();
}


/*优化：不要在stdafx里写代码，改一下，依赖stdafx.h的文件全部重编！*/
bool CGobalVariable::Init()
{
	//_CrtMemState s1,s2,s3;
	//_CrtMemCheckpoint(&s1);

	//程序所在目录
	GetModuleFileName(AfxGetInstanceHandle(), szExePath, MAX_PATH);
	TCHAR* pFind = _tcsrchr(szExePath, '\\');
	szExePath[_tcslen(szExePath) - _tcslen(pFind) + 1] = '\0';

	//读取配置
	strStgCfgname = g_GobalVariable.szExePath;
	strStgCfgname += _T("STGCFG.stg");//配置文件名
	
	vecCfg.resize(StgCfgEnumBuff);
	vecCfg[StgCfgEnumNormal] = new StgNormalCfg;
	//vecCfg[StgCfgEnumRevision] = new StgRevisionCfg;
	//vecCfg[StgCfgEnumRevision_AutoAmend] = new StgRevisionCfg_AutoAmend;
	//vecCfg[StgCfgEnumRevision_Operator] = new StgRevisionCfg_Operator;
	//vecCfg[StgCfgEnumSave] = new StgSaveCfg(sizeof(StgSaveCfg));

	//_CrtMemCheckpoint(&s2);
	//_CrtMemDifference(&s3, &s1, &s2);
	//_CrtMemDumpStatistics(&s3);

	//读取配置线程
	unsigned int nThreadID(0);
	HANDLE hThread = (HANDLE)_beginthreadex(nullptr, 0, ReadStgCfgThread, nullptr, 0, &nThreadID);
	CloseHandle(hThread); hThread = nullptr;

	return true;
}


unsigned int __stdcall ReadStgCfgThread(PVOID pv)
{
	//_CrtMemState s1, s2, s3;
	//_CrtMemCheckpoint(&s1);

	unsigned int nRet = 0;

	//打开配置文档，读取配置
	CSSFile* pSSFile = new CSSFile(g_GobalVariable.strStgCfgname);
	nRet = pSSFile->GetAllCfg();
	SAFE_DELETE(pSSFile);
	//delete pSSFile; pSSFile = nullptr;
	//用户点击配置菜单在等待
	SetEvent(g_GobalVariable.hEventReadStgCfg);

	//_CrtMemCheckpoint(&s2);
	//_CrtMemDifference(&s3, &s1, &s2);
	//_CrtMemDumpStatistics(&s3);

	return nRet;
}