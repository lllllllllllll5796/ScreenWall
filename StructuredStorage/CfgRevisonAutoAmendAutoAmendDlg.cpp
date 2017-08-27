// CfgRevisonAutoAmendAutoAmendDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StructuredStorage.h"
#include "CfgRevisonAutoAmendAutoAmendDlg.h"
#include "afxdialogex.h"


// CCfgRevisonAutoAmendAutoAmendDlg dialog

IMPLEMENT_DYNAMIC(CCfgRevisonAutoAmendAutoAmendDlg, CDialogEx)

CCfgRevisonAutoAmendAutoAmendDlg::CCfgRevisonAutoAmendAutoAmendDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CfgRevisionAutoAmend_AutoAmend, pParent)
{

}

CCfgRevisonAutoAmendAutoAmendDlg::~CCfgRevisonAutoAmendAutoAmendDlg()
{
}

void CCfgRevisonAutoAmendAutoAmendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCfgRevisonAutoAmendAutoAmendDlg, CDialogEx)
END_MESSAGE_MAP()


// CCfgRevisonAutoAmendAutoAmendDlg message handlers


HRESULT CCfgRevisonAutoAmendAutoAmendDlg::GetStgCfgs()
{
	//读取Stg：pStgRoot放在全局，pStream作为成员，优化性能 ok
	//GetStgCfgs优化：m_cfg继承，此函数在父类实现

	//StgNormalCfg stCfg;//常规配置
	HRESULT hr = S_OK;
	auto pSSFile = g_GobalVariable.m_ssFile;
	CString strName(g_StgStreamNames[StgDetailedCfgs_Normal]);
	if (!pSSFile->OpenStream(strName, &m_pStream)) {
		if (!pSSFile->CreateStream(strName, &m_pStream)) {
			TRACE(_T("CGobalVariable::Init : CCfgNormalDlg::GetStgCfgs CreateStream Failed !"));
		}
	}
	else {
		hr = m_pStream->Read(&m_cfg, sizeof(m_cfg), 0);
		if (hr == S_OK)
			TRACE(_T("CCfgNormalDlg::GetStgCfgs OK."));
	}
	return hr;
}

HRESULT CCfgRevisonAutoAmendAutoAmendDlg::SetStgCfgs()
{
	HRESULT hr = S_OK;
	if (false == m_bDirty)
		return hr;

	hr = m_pStream->Write(&m_cfg, sizeof(m_cfg), 0);

	return hr;
}