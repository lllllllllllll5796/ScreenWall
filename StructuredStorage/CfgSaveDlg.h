#pragma once
#include "afxwin.h"


// CCfgSaveDlg dialog

class CCfgSaveDlg : public CDialogEx
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
protected:
	CComboBox m_cbo1;
};
