// CfgRevisionAutoAmendOperatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StructuredStorage.h"
#include "CfgRevisionAutoAmendOperatorDlg.h"
#include "afxdialogex.h"


// CCfgRevisionAutoAmendOperatorDlg dialog

IMPLEMENT_DYNAMIC(CCfgRevisionAutoAmendOperatorDlg, CDialogEx)

CCfgRevisionAutoAmendOperatorDlg::CCfgRevisionAutoAmendOperatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IDD_CfgRevisionAutoAmend_Operator, pParent)
{

}

CCfgRevisionAutoAmendOperatorDlg::~CCfgRevisionAutoAmendOperatorDlg()
{
}

void CCfgRevisionAutoAmendOperatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_li1);
	DDX_Control(pDX, IDC_CHECK1, m_ch1);
}


BEGIN_MESSAGE_MAP(CCfgRevisionAutoAmendOperatorDlg, CDialogEx)
END_MESSAGE_MAP()


// CCfgRevisionAutoAmendOperatorDlg message handlers


BOOL CCfgRevisionAutoAmendOperatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//要在PreSubclassWindow 或者修改 LBS_HASSTRINGS | LBS_OWNERDRAWFIXED
	//有点小问题：点击时，会有一次重绘，导致item整体偏移，滚动一下就好
	//m_li1.ModifyStyle(0, LBS_HASSTRINGS | LBS_OWNERDRAWFIXED | LBS_OWNERDRAWVARIABLE);
	//m_li1.SetCheckStyle(BS_CHECKBOX);
	const CString opts[] = { _T("人名"),_T("即时消息联系人"),_T("地址"),_T("地点"),
		_T("度量单位转换器"),_T("日期"),_T("时间"),_T("电话号码") };
	int len = sizeof(opts) / sizeof(opts[0]);
	for (int i = 0; i < len; ++i) {
		m_li1.InsertString(i, opts[i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}





HRESULT CCfgRevisionAutoAmendOperatorDlg::GetStgCfgs()
{
	//读取Stg：pStgRoot放在全局，pStream作为成员，优化性能 ok
	//GetStgCfgs优化：m_cfg继承，此函数在父类实现

	//StgNormalCfg stCfg;//常规配置
	HRESULT hr = S_OK;
	/*auto pSSFile = g_GobalVariable.m_ssFile;
	CString strName(g_StgStreamNames[StgDetailedCfgs_Revision_Operator]);
	if (!pSSFile->OpenStream(strName, &m_pStream)) {
		if (!pSSFile->CreateStream(strName, &m_pStream)) {
			TRACE(_T("CGobalVariable::Init : CCfgNormalDlg::GetStgCfgs CreateStream Failed !"));
		}
	}
	else {
		hr = m_pStream->Read(&m_cfg, sizeof(m_cfg), 0);
		if (hr == S_OK)
			TRACE(_T("CCfgNormalDlg::GetStgCfgs OK."));
	}*/
	return hr;
}

HRESULT CCfgRevisionAutoAmendOperatorDlg::SetStgCfgs()
{
	HRESULT hr = S_OK;
	if (false == m_bDirty)
		return hr;

	hr = m_pStream->Write(&m_cfg, sizeof(m_cfg), 0);

	return hr;
}