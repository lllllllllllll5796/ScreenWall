
// StructuredStorageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StructuredStorage.h"
#include "StructuredStorageDlg.h"
#include "afxdialogex.h"

#include "Stg.h"
#include "CfgNormalDlg.h"
#include "CfgRevisionDlg.h"
#include "CfgSaveDlg.h"
#include "CfgCustomDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStructuredStorageDlg dialog


CStructuredStorageDlg::CStructuredStorageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STRUCTUREDSTORAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_cfgNormalDlg = new CCfgNormalDlg(this);
	m_cfgRevisionDlg = new CCfgRevisionDlg(this);
	m_cfgSaveDlg = new CCfgSaveDlg(this);
	m_cfgCustomDlg = new CCfgCustomDlg(this);

	m_vecCfgDlgPtr.resize(StgCfgs_Buff);
	m_vecCfgDlgPtr[StgCfgs_Normal] = m_cfgNormalDlg;
	m_vecCfgDlgPtr[StgCfgs_Revision] = m_cfgRevisionDlg;
	m_vecCfgDlgPtr[StgCfgs_Save] = m_cfgSaveDlg;
	m_vecCfgDlgPtr[StgCfgs_Custom] = m_cfgCustomDlg;

	//m_ssFile = new CSSFile;
}

CStructuredStorageDlg::~CStructuredStorageDlg()
{
	for (auto pDlg : m_vecCfgDlgPtr) {
		SAFE_DELETE(pDlg);//虚析构安全
	}
	//SAFE_DELETE(m_ssFile);
	//SAFE_DELETE(m_cfgNormalDlg);
	//SAFE_DELETE(m_cfgRevisionDlg);
	//SAFE_DELETE(m_cfgSaveDlg);
	//SAFE_DELETE(m_cfgCustomDlg);
}

void CStructuredStorageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CfgGuide, m_lcCfgGuide);
}

BEGIN_MESSAGE_MAP(CStructuredStorageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CfgGuide, &CStructuredStorageDlg::OnItemChangedCfgGuide)
	ON_BN_CLICKED(IDOK, &CStructuredStorageDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CStructuredStorageDlg message handlers

BOOL CStructuredStorageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	//test
	/*TCHAR* szPath = _T("C:\\Users\\dmxjMao\\Desktop\\屏幕墙文档\\abc");
	LPSTORAGE pStgRoot = nullptr;
	HRESULT hr = ::StgCreateDocfile(szPath,
		STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE,
		0, &pStgRoot);

	TCHAR* szStreamName = _T("常规");
	LPSTREAM pStream = NULL;
	hr = pStgRoot->CreateStream(szStreamName,
		STGM_CREATE | STGM_READWRITE |
		STGM_SHARE_EXCLUSIVE,
		0, 0, &pStream);

	pStream->Release();
	pStgRoot->Release();*/



	GetClientRect(&m_rcClient);
	int x = m_rcClient.left, y = m_rcClient.top;
	int w = m_rcClient.Width(), h = m_rcClient.Height();

	//左边CListCtrl
	const CString cfgNames[] = { _T("常规"),_T("校对"),_T("保存"),_T("自定义") };
	int nCfgCnts = sizeof(cfgNames) / sizeof(cfgNames[0]);
	for (int i = 0; i < nCfgCnts; ++i) {
		m_lcCfgGuide.InsertItem(i,cfgNames[i]);
	}
	
	x += 10;
	y += 30;/*GetDlgItem(IDC_sts_Notice)->getwind*/
	//m_lcCfgGuide.ModifyStyle
	EnableWindowTheme(m_lcCfgGuide.GetSafeHwnd(), L"ListView", L"Explorer", NULL);
	m_lcCfgGuide.SetWindowPos(nullptr, x, y, w / 5, h - 80, SWP_NOZORDER | SWP_NOACTIVATE);
	m_lcCfgGuide.SetItemState(StgCfgs_Normal, LVIS_SELECTED, LVIS_SELECTED);

	//创建配置对话框
	m_cfgNormalDlg->Create(IDD_Cfg_Normal, this); //属性style=Child,Border=Thin
	m_cfgRevisionDlg->Create(IDD_Cfg_Revision, this);
	m_cfgSaveDlg->Create(IDD_Cfg_Save, this);
	m_cfgCustomDlg->Create(IDD_Cfg_Custom, this);
	
	CRect rcTmp;//对话框布局
	m_lcCfgGuide.GetClientRect(&rcTmp);
	x += rcTmp.Width() + 5; /*y = rcTmp.top;*/ w -= x + 5; h -= 80;
	for (auto pDlg : m_vecCfgDlgPtr) {
		pDlg->SetWindowPos(nullptr, x, y, w, h, SWP_NOZORDER | SWP_NOACTIVATE);
	}

	////初始显示常规配置
	//m_cfgNormalDlg->SetCfg(stDefaultCfg);
	m_cfgNormalDlg->ShowWindow(SW_NORMAL);
	m_cfgRevisionDlg->ShowWindow(SW_HIDE);
	m_cfgSaveDlg->ShowWindow(SW_HIDE);
	m_cfgCustomDlg->ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStructuredStorageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStructuredStorageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStructuredStorageDlg::OnItemChangedCfgGuide(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int nItem = pNMLV->iItem;
	auto pDlg = m_vecCfgDlgPtr[nItem];
	if (pDlg->GetSafeHwnd() == nullptr)
		return;

	for (int i = 0; i < StgCfgs_Buff;++i) {
		if (i == nItem)
			m_vecCfgDlgPtr[i]->ShowWindow(SW_NORMAL);
		else
			m_vecCfgDlgPtr[i]->ShowWindow(SW_HIDE);
	}

	*pResult = 0;
}


void CStructuredStorageDlg::OnBnClickedOk()
{
	for (auto pDlg : m_vecCfgDlgPtr) {
		IStgOperator* pStg = dynamic_cast<IStgOperator*>(pDlg);
		pStg->SetStgCfgs();	
	}

	CDialogEx::OnOK();
}
