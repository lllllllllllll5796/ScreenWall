#pragma once
#include "afxwin.h"


// CModifyPswdDlg dialog

class CModifyPswdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModifyPswdDlg)

public:
	CModifyPswdDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CModifyPswdDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ModifyPswd };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CBitmapButton m_btnShowOri;
	CBitmapButton m_btnShowNew;
	CEdit m_edtOri;
	bool m_bShowOri = false;//‘≠√‹¬Î «∑Òœ‘ æ
	CEdit m_edtNew;
	bool m_bShowNew = false;
	//CToolTipCtrl m_tip;

public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();

	
};
