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

CCfgRevisionDlg::CCfgRevisionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Cfg_Revision, pParent)
{

}

CCfgRevisionDlg::~CCfgRevisionDlg()
{
}

void CCfgRevisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbo1);
	DDX_Control(pDX, IDC_CHECK1, m_ck1);
	DDX_Control(pDX, IDC_CHECK2, m_ch2);
}


BEGIN_MESSAGE_MAP(CCfgRevisionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCfgRevisionDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCfgRevisionDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CCfgRevisionDlg message handlers


void CCfgRevisionDlg::OnBnClickedButton1()
{
	CCfgRevisionAutoAmendDlg dlg;
	if (IDOK == dlg.DoModal()) {

	}
	else {

	}
}

void CCfgRevisionDlg::OnBnClickedButton2()
{
	CCfgRevisionStyle dlg;
	if (IDOK == dlg.DoModal()) {

	}
	else {

	}
}


BOOL CCfgRevisionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	const CString strItems[] = { _T("标准"),_T("自定义") };
	int len = sizeof(strItems) / sizeof(strItems[0]);
	for (int i = 0; i < len; ++i) {
		m_cbo1.AddString(strItems[i]);
	}
	m_cbo1.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}





HRESULT CCfgRevisionDlg::GetStgCfgs()
{
	//读取Stg：pStgRoot放在全局，pStream作为成员，优化性能 ok
	//GetStgCfgs优化：m_cfg继承，此函数在父类实现

	//StgNormalCfg stCfg;//常规配置
	HRESULT hr = S_OK;
	/*auto pSSFile = g_GobalVariable.m_ssFile;
	CString strName(g_StgStreamNames[StgDetailedCfgs_Revision]);
	if (!pSSFile->OpenStream(strName, &m_pStream)) {
		if (!pSSFile->CreateStream(strName, &m_pStream)) {
			TRACE(_T("CGobalVariable::Init : CCfgRevisionDlg::GetStgCfgs CreateStream Failed !"));
		}
	}
	else {
		hr = m_pStream->Read(&m_cfg, sizeof(m_cfg), 0);
		if (hr == S_OK)
			TRACE(_T("CCfgRevisionDlg::GetStgCfgs OK."));
	}*/
	return hr;
}

HRESULT CCfgRevisionDlg::SetStgCfgs()
{
	HRESULT hr = S_OK;
	if (false == m_bDirty)
		return hr;

	hr = m_pStream->Write(&m_cfg, sizeof(m_cfg), 0);

	return hr;
}