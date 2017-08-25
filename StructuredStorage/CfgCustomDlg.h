#pragma once


// CCfgCustomDlg dialog

class CCfgCustomDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCfgCustomDlg)

public:
	CCfgCustomDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCfgCustomDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Cfg_Custom };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
