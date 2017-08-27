// CfgRevisionStyle.cpp : implementation file
//

#include "stdafx.h"
#include "StructuredStorage.h"
#include "CfgRevisionStyle.h"
#include "afxdialogex.h"

#include <vector>
using std::vector;

// CCfgRevisionStyle dialog

IMPLEMENT_DYNAMIC(CCfgRevisionStyle, CDialogEx)

CCfgRevisionStyle::CCfgRevisionStyle(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CfgRevision_Style, pParent)
{

}

CCfgRevisionStyle::~CCfgRevisionStyle()
{
}

void CCfgRevisionStyle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbo1);
	DDX_Control(pDX, IDC_LIST1, m_li1);
}


BEGIN_MESSAGE_MAP(CCfgRevisionStyle, CDialogEx)
END_MESSAGE_MAP()


// CCfgRevisionStyle message handlers


BOOL CCfgRevisionStyle::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//CRect rcClient;
	//GetClientRect(&rcClient);

	const CString strItems[] = { _T("标准"),_T("自定义") };
	int len = sizeof(strItems) / sizeof(strItems[0]);
	for (int i = 0; i < len; ++i) {
		m_cbo1.AddString(strItems[i]);
	}
	m_cbo1.SetCurSel(0);

	m_li1.ModifyStyle(0, LVS_NOCOLUMNHEADER);
	m_li1.SetExtendedStyle(m_li1.GetExtendedStyle() | LVS_EX_CHECKBOXES);
	EnableWindowTheme(m_li1.m_hWnd, L"ListView", L"Explorer", NULL);
	//m_li1.SetExtendedStyle(m_li1.GetExtendedStyle() | LVS_NOCOLUMNHEADER);


	m_li1.SetRedraw(FALSE);
	CString strGroup[] = { _T("语法"),_T("分类词典")};
	vector<CString> vec = { _T("非标准度量单位"),_T("非标准数字格式"),_T("忽略引用内容") ,
			 _T("医学类"),_T("生物类"),_T("电子、计算机类"),_T("基础物理类"),
			_T("化学、化工类"), _T("数学类"), _T("农林、地质类") };
	len = vec.size();
	//LVITEM lvItem;
	//lvItem.mask = LVIF_TEXT;
	
	CRect rc;
	m_li1.GetClientRect(&rc);
	m_li1.InsertColumn(0, _T(""), LVCFMT_LEFT, rc.Width() - 30);//添加一列，不然不会显示item;

	for (int k = 0; k < len; ++k) {
		m_li1.InsertItem(k, vec[k]);
	}

	len = sizeof(strGroup) / sizeof(strGroup[0]);
	m_li1.EnableGroupView(TRUE);
	const CPoint nItemsPerGroup[] = { CPoint(0,3),CPoint(3,vec.size()) }; //组范围
	for (int i = 0; i < len; ++i) {
		LVGROUP lg = { 0 };
		lg.cbSize = sizeof(lg);
		lg.mask = LVGF_GROUPID | LVGF_HEADER | LVGF_STATE;
		lg.iGroupId = i;
		lg.pszHeader = strGroup[i].GetBuffer();
		lg.cchHeader = strGroup[i].GetLength();
		lg.state = LVGS_COLLAPSIBLE;

		int nGroupId = m_li1.InsertGroup(i, &lg);
		if (-1 == nGroupId) {
			return FALSE;
		}
		//绑定元素
		LVITEM lvItem = { 0 };
		lvItem.mask = LVIF_GROUPID;
		//memset(&lvItem, 0, sizeof(LVITEM));
		//lvItem.mask = LVIF_GROUPID;
		const CPoint& range = nItemsPerGroup[i];
		for (int k = range.x; k < range.y; ++k) {
			lvItem.iItem = k;
			//lvItem.iSubItem = 0;
			lvItem.iGroupId = nGroupId;
			m_li1.SetItem(&lvItem);
		}
	}
	m_li1.SetRedraw(TRUE);
	//马上匹配item或事先记录
	//len = vec.size();
	////const int nItemsPerGroup[] = { 3,len - 3 };
	//for (int nRow = 0; nRow < len; ++nRow)
	//{
	//	LVITEM lvItem = { 0 };
	//	lvItem.mask = LVIF_GROUPID;
	//	lvItem.iItem = nRow;
	//	if (nRow < 3)
	//		lvItem.iGroupId = 0;
	//	else
	//		lvItem.iGroupId = 1;
	//	m_li1.SetItem(&lvItem);
	//}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
