#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CCfgRevisionStyle dialog

class CCfgRevisionStyle : public CDialogEx
{
	DECLARE_DYNAMIC(CCfgRevisionStyle)

public:
	CCfgRevisionStyle(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCfgRevisionStyle();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CfgRevision_Style };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CComboBox m_cbo1;
public:
	virtual BOOL OnInitDialog();
protected:
	CListCtrl m_li1;
};
