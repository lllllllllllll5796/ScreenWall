#pragma once
#include "afxwin.h"
#include "Stg.h"

// CCfgRevisionDlg dialog

class CCfgRevisionDlg : public CDialogEx, public IStgOperator
{
	DECLARE_DYNAMIC(CCfgRevisionDlg)

public:
	CCfgRevisionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCfgRevisionDlg();

	virtual HRESULT GetStgCfgs();
	virtual HRESULT SetStgCfgs();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Cfg_Revision };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

protected:
	CComboBox m_cbo1;
	CButton m_ck1;
	CButton m_ch2;
	StgRevision m_cfg;
	LPSTREAM m_pStream = nullptr;
	bool m_bDirty = false;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};
