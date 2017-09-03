#pragma once
#include "afxwin.h"
#include "Stg.h"


// CCfgRevisionAutoAmendOperatorDlg dialog

class CCfgRevisionAutoAmendOperatorDlg : public CDialogEx,public IStgCfgOperator
{
	DECLARE_DYNAMIC(CCfgRevisionAutoAmendOperatorDlg)

public:
	CCfgRevisionAutoAmendOperatorDlg(CSSFile* pSSFile, CWnd* pParent = NULL);   // standard constructor
	virtual ~CCfgRevisionAutoAmendOperatorDlg();
	//virtual HRESULT GetStgCfgs();
	//virtual HRESULT SetStgCfgs();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IDD_CfgRevisionAutoAmend_Operator };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	//CListBox m_li1;
	CCheckListBox m_li1;
	CButton m_ch1;

	//StgRevisionCfg_Operator m_cfg;
	//LPSTREAM m_pStream = nullptr;
	//bool m_bDirty = false;

public:
	virtual BOOL OnInitDialog();
	
};
