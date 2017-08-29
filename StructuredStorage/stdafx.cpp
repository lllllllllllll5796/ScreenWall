
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

	int len;
	len = sizeof(StgNormalCfg);
	len = sizeof(StgRevisionCfg_AutoAmend);
	len = sizeof(StgRevisionCfg);
	len = sizeof(StgRevisionCfg_Operator);

	//读取配置
	vecCfg.resize(StgCfgEnumBuff);
	vecCfg[StgCfgEnumNormal] = new StgNormalCfg(sizeof(StgNormalCfg));
	vecCfg[StgCfgEnumRevision_AutoAmend] = new StgRevisionCfg_AutoAmend(sizeof(StgRevisionCfg_AutoAmend));
	vecCfg[StgCfgEnumRevision_Operator] = new StgRevisionCfg_Operator(sizeof(StgRevisionCfg_Operator));
	vecCfg[StgCfgEnumRevision] = new StgRevisionCfg(sizeof(StgRevisionCfg));
	vecCfg[StgCfgEnumSave] = new StgSaveCfg(sizeof(StgSaveCfg));

	return true;
}