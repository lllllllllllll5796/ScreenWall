
// StructuredStorageDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include <vector>

class CCfgNormalDlg;
class CCfgRevisionDlg;
class CCfgSaveDlg;
class CCfgCustomDlg;

// CStructuredStorageDlg dialog
class CStructuredStorageDlg : public CDialogEx
{
// Construction
public:
	CStructuredStorageDlg(CWnd* pParent = NULL);	// standard constructor
	~CStructuredStorageDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STRUCTUREDSTORAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CRect m_rcClient;
	CCfgNormalDlg* m_cfgNormalDlg;
	CCfgRevisionDlg* m_cfgRevisionDlg;
	CCfgSaveDlg* m_cfgSaveDlg;
	CCfgCustomDlg* m_cfgCustomDlg;
	std::vector<CDialog*> m_vecCfgDlgPtr; /*= {//编译器还不知道它们是继承自CDialog的
		m_cfgNormalDlg, m_cfgRevisionDlg, m_cfgSaveDlg, m_cfgCustomDlg };*/ 

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CListCtrl m_lcCfgGuide;
public:
	afx_msg void OnItemChangedCfgGuide(NMHDR *pNMHDR, LRESULT *pResult);
};
