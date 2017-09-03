#pragma once

#include "afxcmn.h"
#include "Stg.h"
#include <vector>

// CCfgRevisionAutoAmendDlg dialog
class CCfgRevisonAutoAmendAutoAmendDlg;
class CCfgRevisionAutoAmendOperatorDlg;
class CCfgRevisionAutoAmendDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCfgRevisionAutoAmendDlg)

public:
	CCfgRevisionAutoAmendDlg(CSSFile* pSSFile, CWnd* pParent = NULL);   // standard constructor
	virtual ~CCfgRevisionAutoAmendDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CfgRevison_AutoAmend };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CCfgRevisonAutoAmendAutoAmendDlg* m_autoAmendDlg;
	CCfgRevisionAutoAmendOperatorDlg* m_operatorDlg;
	std::vector<CDialog*> m_vecDlgPtr;
	//CSSFile* m_pSSFile;

	CTabCtrl m_tab;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	
public:
	afx_msg void OnSelChangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
