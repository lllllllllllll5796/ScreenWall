#pragma once
#include "afxwin.h"
#include "Stg.h"

// CCfgSaveDlg dialog

class CCfgSaveDlg : public CDialogEx, public IStgCfgOperator
{
	DECLARE_DYNAMIC(CCfgSaveDlg)

public:
	CCfgSaveDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCfgSaveDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Cfg_Save };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual HRESULT GetStgCfgs();
	virtual HRESULT SetStgCfgs();

protected:
	CComboBox m_cbo1;
};
