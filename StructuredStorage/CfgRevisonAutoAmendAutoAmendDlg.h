#pragma once
#include "Stg.h"

// CCfgRevisonAutoAmendAutoAmendDlg dialog

class CCfgRevisonAutoAmendAutoAmendDlg : public CDialogEx, public IStgCfgOperator
{
	DECLARE_DYNAMIC(CCfgRevisonAutoAmendAutoAmendDlg)

public:
	CCfgRevisonAutoAmendAutoAmendDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCfgRevisonAutoAmendAutoAmendDlg();
	virtual HRESULT GetStgCfgs();
	virtual HRESULT SetStgCfgs();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CfgRevisionAutoAmend_AutoAmend };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	//StgRevisionCfg_AutoAmend m_cfg;
	//LPSTREAM m_pStream = false;
	//bool m_bDirty = false;
};
