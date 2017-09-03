#pragma once
#include "Stg.h"
#include "afxwin.h"

// CCfgRevisonAutoAmendAutoAmendDlg dialog

class CCfgRevisonAutoAmendAutoAmendDlg : public CDialogEx, public IStgCfgOperator
{
	DECLARE_DYNAMIC(CCfgRevisonAutoAmendAutoAmendDlg)

public:
	CCfgRevisonAutoAmendAutoAmendDlg(CSSFile* pSSFile, CWnd* pParent = NULL);   // standard constructor
	virtual ~CCfgRevisonAutoAmendAutoAmendDlg();
	//virtual HRESULT GetStgCfgs();
	//virtual HRESULT SetStgCfgs();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CfgRevision_AutoAmend };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	StgRevisionCfg_AutoAmend* m_pCfg;
	//LPSTREAM m_pStream = false;
	//bool m_bDirty = false;
public:
	virtual BOOL OnInitDialog();
protected:
	CButton m_ck1;
	CButton m_ck2;
	CButton m_ck4;
	CButton m_ck5;
public:
	afx_msg void OnClickedCheck1();
	afx_msg void OnClickedCheck2();
	afx_msg void OnClickedCheck4();
};
