// CfgRevisonAutoAmendAutoAmendDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StructuredStorage.h"
#include "CfgRevisonAutoAmendAutoAmendDlg.h"
#include "afxdialogex.h"


// CCfgRevisonAutoAmendAutoAmendDlg dialog

IMPLEMENT_DYNAMIC(CCfgRevisonAutoAmendAutoAmendDlg, CDialogEx)

CCfgRevisonAutoAmendAutoAmendDlg::CCfgRevisonAutoAmendAutoAmendDlg(CSSFile* pSSFile, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CfgRevisionAutoAmend_AutoAmend, pParent)
{
	m_pSSFile = pSSFile;
	m_pCfg = (StgRevisionCfg_AutoAmend*)g_GobalVariable.vecCfg[StgCfgEnumRevision_AutoAmend];
}

CCfgRevisonAutoAmendAutoAmendDlg::~CCfgRevisonAutoAmendAutoAmendDlg()
{
}

void CCfgRevisonAutoAmendAutoAmendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_BUTTON1, m_ck1);
	//  DDX_Control(pDX, IDC_BUTTON2, m_ck2);
	DDX_Control(pDX, IDC_CHECK1, m_ck1);
	DDX_Control(pDX, IDC_CHECK2, m_ck2);
	DDX_Control(pDX, IDC_CHECK4, m_ck4);
	DDX_Control(pDX, IDC_CHECK5, m_ck5);
}


BEGIN_MESSAGE_MAP(CCfgRevisonAutoAmendAutoAmendDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CCfgRevisonAutoAmendAutoAmendDlg::OnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CCfgRevisonAutoAmendAutoAmendDlg::OnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK4, &CCfgRevisonAutoAmendAutoAmendDlg::OnClickedCheck4)
END_MESSAGE_MAP()


// CCfgRevisonAutoAmendAutoAmendDlg message handlers




//HRESULT CCfgRevisonAutoAmendAutoAmendDlg::SetStgCfgs()
//{
//	HRESULT hr = S_OK;
//
//	hr = m_pStream->Write(&m_cfg, sizeof(m_cfg), 0);
//
//	return hr;
//}

BOOL CCfgRevisonAutoAmendAutoAmendDlg::OnInitDialog()
{
	__super::OnInitDialog();

	if (m_pSSFile->IsOpen())
		m_pSSFile->GetCfg(StgCfgEnumRevision_AutoAmend, &m_pStream);
	else return FALSE;
	//const auto pcfg = (StgRevisionCfg_AutoAmend*)g_GobalVariable.vecCfg[StgCfgEnumRevision_AutoAmend];

	m_ck1.SetCheck(m_pCfg->nShowAutoAmendBtn);
	m_ck2.SetCheck(m_pCfg->nUpcaseFirst2Char);
	m_ck4.SetCheck(m_pCfg->nAmend3);
	m_ck5.SetCheck(m_pCfg->nAutoReplace);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}




void CCfgRevisonAutoAmendAutoAmendDlg::OnClickedCheck1()
{
	m_pCfg->nShowAutoAmendBtn = m_ck1.GetCheck();
	MACRO_StgWrite2Pos(StgRevisionCfg_AutoAmend, nShowAutoAmendBtn);
}


void CCfgRevisonAutoAmendAutoAmendDlg::OnClickedCheck2()
{
	m_pCfg->nUpcaseFirst2Char = m_ck2.GetCheck();
	MACRO_StgWrite2Pos(StgRevisionCfg_AutoAmend, nUpcaseFirst2Char);
}


void CCfgRevisonAutoAmendAutoAmendDlg::OnClickedCheck4()
{
	m_pCfg->nAmend3 = m_ck4.GetCheck();
	MACRO_StgWrite2Pos(StgRevisionCfg_AutoAmend, nAmend3);
}
