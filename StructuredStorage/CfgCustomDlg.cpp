// CfgCustomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StructuredStorage.h"
#include "CfgCustomDlg.h"
#include "afxdialogex.h"


// CCfgCustomDlg dialog

IMPLEMENT_DYNAMIC(CCfgCustomDlg, CDialogEx)

CCfgCustomDlg::CCfgCustomDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Cfg_Custom, pParent)
{

}

CCfgCustomDlg::~CCfgCustomDlg()
{
}

void CCfgCustomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCfgCustomDlg, CDialogEx)
END_MESSAGE_MAP()


// CCfgCustomDlg message handlers
