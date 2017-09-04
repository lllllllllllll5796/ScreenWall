// ModifyPswdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenWall.h"
#include "ModifyPswdDlg.h"
#include "afxdialogex.h"


// CModifyPswdDlg dialog

IMPLEMENT_DYNAMIC(CModifyPswdDlg, CDialogEx)

CModifyPswdDlg::CModifyPswdDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ModifyPswd, pParent)
{

}

CModifyPswdDlg::~CModifyPswdDlg()
{
}

void CModifyPswdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON2, m_btnShowOri);
	DDX_Control(pDX, IDC_EDIT1, m_edtOri);
	DDX_Control(pDX, IDC_EDIT2, m_edtNew);
	DDX_Control(pDX, IDC_BUTTON3, m_btnShowNew);
}


BEGIN_MESSAGE_MAP(CModifyPswdDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CModifyPswdDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CModifyPswdDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CModifyPswdDlg message handlers


BOOL CModifyPswdDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_btnShowOri.LoadBitmaps(IDB_Eye_24px);
	m_btnShowOri.SizeToContent();

	m_btnShowNew.LoadBitmaps(IDB_Eye_24px);
	m_btnShowNew.SizeToContent();

	//m_tip.Create(this);
	//m_tip.AddTool(&m_btnShow, _T("显示密码"));
	//m_tip.SetDelayTime(TTDT_INITIAL, 100);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CModifyPswdDlg::PreTranslateMessage(MSG* pMsg)
{
	//m_tip.RelayEvent(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}

#define Macro_ShowPswd(edt,bShow,btn)	\
	CString str;	\
	edt.GetWindowText(str);	\
	if (str.IsEmpty()) return;	\
	bShow = !bShow;	\
	if (bShow) {	\
		edt.ModifyStyle(ES_PASSWORD, 0);	\
		edt.SetPasswordChar(0);	\
		btn.LoadBitmaps(IDB_RedEye_24px);	\
	}	\
	else {	\
		edt.ModifyStyle(0, ES_PASSWORD);	\
		edt.SetPasswordChar(_T('●'));	\
		btn.LoadBitmaps(IDB_Eye_24px);	\
	}	\
	edt.SetWindowText(str);	\
	int len = str.GetLength();	\
	edt.SetSel(len, len);	\
	edt.SetFocus();	

void CModifyPswdDlg::OnBnClickedButton2()
{
	//优化：用宏简化代码
	Macro_ShowPswd(m_edtOri, m_bShowOri, m_btnShowOri);
	//CString str;
	//m_edtOri.GetWindowText(str);
	//if (str.IsEmpty()) return;
	//m_bShowOri = !m_bShowOri;
	//if (m_bShowOri) {
	//	m_edtOri.ModifyStyle(ES_PASSWORD, 0);
	//	m_edtOri.SetPasswordChar(0);
	//	//tooltip隐藏（改为换图片）
	//	m_btnShowOri.LoadBitmaps(IDB_RedEye_24px);
	//}
	//else {
	//	m_edtOri.ModifyStyle(0, ES_PASSWORD);
	//	m_edtOri.SetPasswordChar(_T('●'));
	//	m_btnShowOri.LoadBitmaps(IDB_Eye_24px);
	//}
	//
	//m_edtOri.SetWindowText(str);
	//int len = str.GetLength();
	//m_edtOri.SetSel(len, len);
	//m_edtOri.SetFocus();
}


void CModifyPswdDlg::OnBnClickedButton3()
{
	Macro_ShowPswd(m_edtNew, m_bShowNew, m_btnShowNew);
}
