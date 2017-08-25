// CfgSaveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StructuredStorage.h"
#include "CfgSaveDlg.h"
#include "afxdialogex.h"


// CCfgSaveDlg dialog

IMPLEMENT_DYNAMIC(CCfgSaveDlg, CDialogEx)

CCfgSaveDlg::CCfgSaveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Cfg_Save, pParent)
{

}

CCfgSaveDlg::~CCfgSaveDlg()
{
}

void CCfgSaveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCfgSaveDlg, CDialogEx)
END_MESSAGE_MAP()


// CCfgSaveDlg message handlers
