// CfgNormalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StructuredStorage.h"
#include "CfgNormalDlg.h"
#include "afxdialogex.h"

//#include "Stg.h"

// CCfgNormalDlg dialog

IMPLEMENT_DYNAMIC(CCfgNormalDlg, CDialogEx)

CCfgNormalDlg::CCfgNormalDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Cfg_Normal, pParent)
{
	//m_spCfg = std::make_shared<StgNormalCfg>();
	//m_pCfg = new StgNormalCfg();
	m_cfg = new StgNormalCfg;
}

CCfgNormalDlg::~CCfgNormalDlg()
{
	//SAFE_DELETE(m_pCfg);
	m_pStream->Release();
}

void CCfgNormalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_ck_1);
	DDX_Control(pDX, IDC_CHECK2, m_ck_2);
	DDX_Control(pDX, IDC_CHECK3, m_ck_3);
	DDX_Control(pDX, IDC_COMBO1, m_cbo_1);
	DDX_Control(pDX, IDC_COMBO2, m_cbo_2);
	DDX_Control(pDX, IDC_EDIT2, m_edt_2);
	DDX_Control(pDX, IDC_EDIT3, m_edt_3);
}


BEGIN_MESSAGE_MAP(CCfgNormalDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CCfgNormalDlg::OnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CCfgNormalDlg::OnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CCfgNormalDlg::OnClickedCheck3)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CCfgNormalDlg::OnSelChangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CCfgNormalDlg::OnSelChangeCombo2)
	ON_EN_CHANGE(IDC_EDIT2, &CCfgNormalDlg::OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CCfgNormalDlg::OnChangeEdit3)
END_MESSAGE_MAP()


// CCfgNormalDlg message handlers


BOOL CCfgNormalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	/*CString strStreamName(g_StgStreamNames[StgDetailedCfgs_Normal]);
	auto pSSFile = g_GobalVariable.m_ssFile;
	if (pSSFile->OpenStream(strStreamName, &m_pStream)) {
		ULONG ulRead = 0;
		m_pStream->Read(m_cfg, sizeof(StgNormalCfg), &ulRead);
	}*/

	GetStgCfgs();
	const auto cfg = (StgNormalCfg*)m_cfg;
	m_ck_1.SetCheck(cfg->bfloatToolbar);
	m_ck_2.SetCheck(cfg->bRealtimePreview);
	const CString strColorSchemes[] = { _T("红色"), _T("绿色"), _T("蓝色") };
	int nSchemeCnts = sizeof(strColorSchemes) / sizeof(strColorSchemes[0]);
	for (int i = 0; i < nSchemeCnts; ++i) {
		m_cbo_1.InsertString(i, strColorSchemes[i]);
	}
	m_cbo_1.SetCurSel(cfg->nColorScheme);

	const CString strTips[] = { _T("打但家里发卡机"), _T("且偶剧"), _T("蓝色") };
	int nTipCnts = sizeof(strTips) / sizeof(strTips[0]);
	for (int i = 0; i < nTipCnts; ++i) {
		m_cbo_2.InsertString(i, strTips[i]);
	}
	m_cbo_2.SetCurSel(cfg->nScreenTipStyle);

	m_edt_2.SetWindowText(cfg->strUsername);
	m_edt_3.SetWindowText(cfg->strShortname);

	m_ck_3.SetCheck(cfg->bOpenEmailWhenInReadView);

	return TRUE; 
}


HRESULT CCfgNormalDlg::GetStgCfgs()
{
	//读取Stg：pStgRoot放在全局，pStream作为成员，优化性能 ok
	//GetStgCfgs优化：m_cfg继承，此函数在父类实现
	
	//StgNormalCfg stCfg;//常规配置
	HRESULT hr = S_OK;
	/*auto pSSFile = g_GobalVariable.m_ssFile;
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
	}*/
	return hr;
}

HRESULT CCfgNormalDlg::SetStgCfgs()
{
	HRESULT hr = S_OK;
	if (false == m_bDirty)
		return hr;
	
	hr = m_pStream->Write(&m_cfg, sizeof(m_cfg), 0);

	return hr;
}

//bool CCfgNormalDlg::IsDirty()
//{
//	return m_bDirty;
//}

void CCfgNormalDlg::OnClickedCheck1()
{
	m_bDirty = true;
	//m_cfg->bfloatToolbar = m_ck_1.GetCheck();
}


void CCfgNormalDlg::OnClickedCheck2()
{
	m_bDirty = true;
	//m_cfg.bRealtimePreview = m_ck_2.GetCheck();
}


void CCfgNormalDlg::OnClickedCheck3()
{
	m_bDirty = true;
	//m_cfg.bOpenEmailWhenInReadView = m_ck_3.GetCheck();
}


void CCfgNormalDlg::OnSelChangeCombo1()
{
	m_bDirty = true;
	//m_cfg.nColorScheme = m_cbo_1.GetCurSel();
}


void CCfgNormalDlg::OnSelChangeCombo2()
{
	m_bDirty = true;
	//m_cfg.nScreenTipStyle = m_cbo_2.GetCurSel();
}


void CCfgNormalDlg::OnChangeEdit2()
{
	//m_bDirty = true; 一开始就收到
	static CString str;
	m_edt_2.GetWindowText(str);
	//if (str != m_cfg.strUsername) {
	//	m_bDirty = true;
	//	m_cfg.strUsername = std::move(str);
	//}
}


void CCfgNormalDlg::OnChangeEdit3()
{
	//m_bDirty = true;
	static CString str;
	m_edt_3.GetWindowText(str);
	//if (str != m_cfg.strShortname) {
	//	m_bDirty = true;
	//	m_cfg.strShortname = std::move(str);
	//}
}
