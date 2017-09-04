// CfgNormalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StructuredStorage.h"
#include "CfgNormalDlg.h"
#include "afxdialogex.h"

//#include "Stg.h"

// CCfgNormalDlg dialog

IMPLEMENT_DYNAMIC(CCfgNormalDlg, CDialogEx)

CCfgNormalDlg::CCfgNormalDlg(CSSFile* pSSFile, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Cfg_Normal, pParent)
{
	//m_spCfg = std::make_shared<StgNormalCfg>();
	//m_pCfg = new StgNormalCfg();
	//m_cfg = new StgNormalCfg;
	m_pCfg = (StgNormalCfg*)g_GobalVariable.vecCfg[StgCfgEnumNormal];
	m_pSSFile = pSSFile;
}

CCfgNormalDlg::~CCfgNormalDlg()
{
	//SAFE_DELETE(m_pCfg);
	if(m_pStream) m_pStream->Release();
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
	//获取LPSTREAM
	//CSSFile* pSSFile = new CSSFile(g_GobalVariable.strStgCfgname);
	//pSSFile->GetCfg(StgCfgEnumNormal, m_pStream);  //根存储Release了，m_pStream也释放！ 
	//SAFE_DELETE(pSSFile);
	if(m_pSSFile->IsOpen())
		m_pSSFile->GetCfg(StgCfgEnumNormal, &m_pStream);
	else return FALSE;

	//GetStgCfgs();
	const auto cfg = (StgNormalCfg*)g_GobalVariable.vecCfg[StgCfgEnumNormal];
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

	m_edt_2.SetWindowText(cfg->pszUsername);
	//m_edt_3.SetWindowText(cfg->szShortname);

	m_ck_3.SetCheck(cfg->bOpenEmailWhenInReadView);

	return TRUE; 
}


void CCfgNormalDlg::OnClickedCheck1()
{
	m_pCfg->bfloatToolbar = m_ck_1.GetCheck();
	//ULONG ulWritten = 0;
	//找到位置写
	MACRO_StgWrite2Pos(StgNormalCfg, bfloatToolbar);
	//size_t pos = offsetof(StgNormalCfg, bfloatToolbar);
	//LARGE_INTEGER li;
	//li.QuadPart = pos;
	//HRESULT hr = m_pStream->Seek(li, STREAM_SEEK_SET, nullptr);
	//hr = m_pStream->Write(&m_pCfg->bfloatToolbar, sizeof(m_pCfg->bfloatToolbar), &ulWritten);

}


void CCfgNormalDlg::OnClickedCheck2()
{
	m_pCfg->bRealtimePreview = m_ck_2.GetCheck();
	//找到位置写
	MACRO_StgWrite2Pos(StgNormalCfg, bRealtimePreview);
	/*size_t pos = offsetof(StgNormalCfg, bRealtimePreview);
	LARGE_INTEGER li;
	li.QuadPart = pos;
	HRESULT hr = m_pStream->Seek(li, STREAM_SEEK_SET, nullptr);
	hr = m_pStream->Write(&m_pCfg->bRealtimePreview, sizeof(m_pCfg->bRealtimePreview), nullptr);*/
}


void CCfgNormalDlg::OnClickedCheck3()
{
	//m_cfg.bOpenEmailWhenInReadView = m_ck_3.GetCheck();
}


void CCfgNormalDlg::OnSelChangeCombo1()
{
	//m_cfg.nColorScheme = m_cbo_1.GetCurSel();
}


void CCfgNormalDlg::OnSelChangeCombo2()
{

	//m_cfg.nScreenTipStyle = m_cbo_2.GetCurSel();
}


void CCfgNormalDlg::OnChangeEdit2()
{
	//m_bDirty = true; 一开始就收到
	CString str;
	m_edt_2.GetWindowText(str);
	//if (str != CString(m_pCfg->szUsername)) {
		//_tcscpy_s(m_pCfg->szUsername, str.GetBuffer());
		////m_pCfg->szUsername = str;

		//MACRO_StgWrite2Pos(StgNormalCfg, szUsername);
		//size_t pos = offsetof(StgNormalCfg, szUsername);
		//LARGE_INTEGER li;
		//li.QuadPart = pos;
		//HRESULT hr = m_pStream->Seek(li, STREAM_SEEK_SET, nullptr);
		//hr = m_pStream->Write(&m_pCfg->szUsername, sizeof(m_pCfg->szUsername), nullptr);
	//}
}


void CCfgNormalDlg::OnChangeEdit3()
{
	//m_bDirty = true;
	CString str;
	m_edt_3.GetWindowText(str);
	//if (str != m_cfg.strShortname) {
	//	m_bDirty = true;
	//	m_cfg.strShortname = std::move(str);
	//}
}
