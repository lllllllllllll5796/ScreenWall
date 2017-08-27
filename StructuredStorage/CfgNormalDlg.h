#pragma once
//#include <memory>
#include "Stg.h"
#include "afxwin.h"

//struct StgNormalCfg;
// CCfgNormalDlg dialog

class CCfgNormalDlg : public CDialogEx, public IStgOperator
{
	DECLARE_DYNAMIC(CCfgNormalDlg)

public:
	CCfgNormalDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCfgNormalDlg();
	//inline void SetCfg(StgNormalCfg& cfg) { 
	//	m_cfg = std::move(cfg);
	//	//StgNormalCfg&& st = std::move(cfg); //move不能是const
	//	/*StgNormalCfg& st2 = */;
	//	//*m_pCfg = st; //解引用是左值，右值赋给左值
	//}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Cfg_Normal };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//StgNormalCfg* m_pCfg;
	StgNormalCfg m_cfg;
	bool m_bDirty = false;
	LPSTREAM m_pStream = nullptr;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual HRESULT GetStgCfgs();
	virtual HRESULT SetStgCfgs();

protected:
	CButton m_ck_1;
	CButton m_ck_2;
	CButton m_ck_3;
	CComboBox m_cbo_1;
	CComboBox m_cbo_2;
	CEdit m_edt_2;
	CEdit m_edt_3;
public:
	afx_msg void OnClickedCheck1();
	afx_msg void OnClickedCheck2();
	afx_msg void OnClickedCheck3();
	afx_msg void OnSelChangeCombo1();
	afx_msg void OnSelChangeCombo2();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
};
