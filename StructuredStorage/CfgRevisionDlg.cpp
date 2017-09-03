// CfgRevisionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StructuredStorage.h"
#include "CfgRevisionDlg.h"
#include "afxdialogex.h"

#include "CfgRevisionAutoAmendDlg.h"
#include "CfgRevisionStyle.h"
// CCfgRevisionDlg dialog

IMPLEMENT_DYNAMIC(CCfgRevisionDlg, CDialogEx)

CCfgRevisionDlg::CCfgRevisionDlg(CSSFile* pSSFile, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Cfg_Revision, pParent)
{
	m_pSSFile = pSSFile;
}

CCfgRevisionDlg::~CCfgRevisionDlg()
{
}

void CCfgRevisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbo1);
	DDX_Control(pDX, IDC_CHECK1, m_ck1);
	DDX_Control(pDX, IDC_CHECK2, m_ck2);
}


BEGIN_MESSAGE_MAP(CCfgRevisionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCfgRevisionDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCfgRevisionDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CCfgRevisionDlg message handlers


void CCfgRevisionDlg::OnBnClickedButton1()
{
	CCfgRevisionAutoAmendDlg dlg(m_pSSFile);
	if (IDOK == dlg.DoModal()) {

	}
}

void CCfgRevisionDlg::OnBnClickedButton2()
{
	CCfgRevisionStyle dlg;
	if (IDOK == dlg.DoModal()) {
		//设置的样式，写入流
	}
	else {

	}
}


BOOL CCfgRevisionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_pSSFile->IsOpen())
		m_pSSFile->GetCfg(StgCfgEnumRevision, &m_pStream);
	else return FALSE;
	const auto pcfg = (StgRevisionCfg*)g_GobalVariable.vecCfg[StgCfgEnumRevision];

	const CString strItems[] = { _T("标准"),_T("自定义") };
	int len = sizeof(strItems) / sizeof(strItems[0]);
	for (int i = 0; i < len; ++i) {
		m_cbo1.AddString(strItems[i]);
	}
	m_cbo1.SetCurSel(pcfg->nStyle);
	m_ck1.SetCheck(pcfg->nCheckWhenInput);
	m_ck2.SetCheck(pcfg->nUseContextCheck);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}




