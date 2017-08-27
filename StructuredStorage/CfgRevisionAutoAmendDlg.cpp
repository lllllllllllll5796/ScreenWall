// CfgRevisionAutoAmendDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StructuredStorage.h"
#include "CfgRevisionAutoAmendDlg.h"
#include "afxdialogex.h"

namespace {
	enum AutoAmendDlgsEnum {
		AutoAmend,
		Operator,
		AutoAmendDlgsEnum_Buff
	};
}

// CCfgRevisionAutoAmendDlg dialog

IMPLEMENT_DYNAMIC(CCfgRevisionAutoAmendDlg, CDialogEx)

CCfgRevisionAutoAmendDlg::CCfgRevisionAutoAmendDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CfgRevison_AutoAmend, pParent)
{

}

CCfgRevisionAutoAmendDlg::~CCfgRevisionAutoAmendDlg()
{
}

void CCfgRevisionAutoAmendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}


BEGIN_MESSAGE_MAP(CCfgRevisionAutoAmendDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CCfgRevisionAutoAmendDlg::OnSelChangeTab1)
END_MESSAGE_MAP()


// CCfgRevisionAutoAmendDlg message handlers


BOOL CCfgRevisionAutoAmendDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//初始化tab页
	CRect rc;
	GetClientRect(&rc);
	int x = rc.left, y = rc.top;
	int w = rc.Width(), h = rc.Height();

	x += 4; y += 4; w -= 8; h -= 60;
	m_tab.SetWindowPos(nullptr, x, y, w, h, SWP_NOZORDER | SWP_NOACTIVATE);
	
	//m_tab.GetClientRect(&rc);
	const CString strTitle[] = { _T("自动更正"),_T("操作") };
	int len = sizeof(strTitle) / sizeof(strTitle[0]);
	for (int i = 0; i < len; ++i) {
		m_tab.InsertItem(i, strTitle[i]);
	}
	//m_tab.HighlightItem(AutoAmend, TRUE);

	m_autoAmendDlg.Create(IDD_CfgRevisionAutoAmend_AutoAmend, this);
	m_operatorDlg.Create(IDD_IDD_CfgRevisionAutoAmend_Operator, this);
	m_vecDlgPtr.resize(AutoAmendDlgsEnum_Buff);
	m_vecDlgPtr[AutoAmend] = &m_autoAmendDlg;
	m_vecDlgPtr[Operator] = &m_operatorDlg;

	y += 20;
	for (auto pDlg : m_vecDlgPtr) {
		pDlg->SetWindowPos(nullptr, x, y, w, h, SWP_NOZORDER | SWP_NOACTIVATE);
	}
	m_vecDlgPtr[AutoAmend]->ShowWindow(SW_NORMAL);

	//读取stg：封装一个stg操作类


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CCfgRevisionAutoAmendDlg::OnSelChangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{

	int nSel = m_tab.GetCurSel();
	auto pDlg = m_vecDlgPtr[nSel];
	if (pDlg->GetSafeHwnd() == nullptr)
		return;
	int n = AutoAmendDlgsEnum_Buff;
	for (int i = 0; i < n;++i) {
		if (i == nSel)
			m_vecDlgPtr[i]->ShowWindow(SW_NORMAL);
		else
			m_vecDlgPtr[i]->ShowWindow(SW_HIDE);
	}

	*pResult = 0;
}
