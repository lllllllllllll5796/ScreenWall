#pragma once


// CCfgRevisionDlg dialog

class CCfgRevisionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCfgRevisionDlg)

public:
	CCfgRevisionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCfgRevisionDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Cfg_Revision };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
