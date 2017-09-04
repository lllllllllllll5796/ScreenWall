// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenWall.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "ModifyPswdDlg.h" //修改密码


// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Login, pParent)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Login_ModifyPswd, m_btnModifyPswd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_Login_ModifyPswd, &CLoginDlg::OnBnClickedLoginModifypswd)
	ON_BN_CLICKED(IDLogin, &CLoginDlg::OnClickedIDLogin)
END_MESSAGE_MAP()


// CLoginDlg message handlers


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//设置图标
	SetIcon(g_GobalVariable.hIconApp, FALSE);
	//客户端区域
	GetClientRect(&m_rcClient);
	//登录图标
	CStatic* pWndLoginPic = (CStatic*)GetDlgItem(IDC_Login_Pic);
	pWndLoginPic->ModifyStyle(0, SS_ICON);//自动适应图片大小
	pWndLoginPic->SetIcon(g_GobalVariable.hIconApp);

	//修改密码按钮 
	m_btnModifyPswd.LoadBitmaps(IDB_Pen2_24px); //只能bmp，风格owndraw
	m_btnModifyPswd.SizeToContent();

	//tooltip
	m_tip.Create(this);
	m_tip.AddTool(&m_btnModifyPswd, _T("修改密码"));
	m_tip.SetDelayTime(TTDT_INITIAL, 100);//100ms显示

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CLoginDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	
	Graphics gh(dc.GetSafeHdc());
	//布局坐标、宽高
	int x(m_rcClient.left), y(m_rcClient.top);
	int	w(m_rcClient.Width()), h(m_rcClient.Height());

	//背景色
	//Rect rc(m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());
	//SolidBrush bgBrush(Color(0, 255, 255, 255));
	//gh.FillRectangle(&bgBrush, rc);

	//渐变区
	CRect rcLoginGroup; //"登录设置"控件位置
	GetDlgItem(IDC_sts_LoginGroup)->GetWindowRect(&rcLoginGroup); //屏幕坐标
	ScreenToClient(&rcLoginGroup);
	
	Rect rcWelcome(x, y, w, /*h/4*/rcLoginGroup.top - 2);
	LinearGradientBrush bgBrush(rcWelcome,
		Color(216, 254, 233), Color(255, 255, 255),
		LinearGradientModeVertical);
	gh.FillRectangle(&bgBrush, rcWelcome);

	//画48*48图标
	x += 20; y += 10;
	Bitmap bmpApp(g_GobalVariable.hIconApp);
	//UINT width = bmpApp.GetWidth();  32*32
	gh.DrawImage(&bmpApp, x, y, 48, 48);

	//写字“屏幕墙登录”
	x += 48 + 5; y += 5;
	FontFamily fontFamily(_T("宋体"));//字样
	Gdiplus::Font font(&fontFamily, 16, FontStyleRegular, UnitPixel);//字号
	PointF pt(x*1.0f, y*1.0f);
	SolidBrush txtBrush(Color(0, 51, 153));
	gh.DrawString(_T("屏幕墙"), -1, &font, pt, &txtBrush);
	
	pt.Y += font.GetHeight(0.0f); //累加字体高度
	Gdiplus::Font font2(&fontFamily, 20, FontStyleBold, UnitPixel);
	gh.DrawString(_T("登录"), -1, &font2, pt, &txtBrush);

	//画线
	Pen p(Color(216, 254, 233), 2);
	gh.DrawLine(&p, 0, rcWelcome.GetBottom(), m_rcClient.right, rcWelcome.GetBottom());

	//布局公告栏
	//y = rcWelcome.GetBottom() + 2;
	//CRect rcLoginGroup; //"登录设置"控件位置
	//GetDlgItem(IDC_sts_LoginGroup)->GetWindowRect(&rcLoginGroup); //屏幕坐标
	//ScreenToClient(&rcLoginGroup);
	//CRect rcNotice(rcLoginGroup.left, y, rcLoginGroup.right, rcLoginGroup.top);
	//GetDlgItem(IDC_sts_Notice)->MoveWindow(&rcNotice);
	GetDlgItem(IDC_sts_Notice)->ShowWindow(SW_HIDE);
}


void CLoginDlg::OnBnClickedLoginModifypswd()
{
	CModifyPswdDlg dlg;
	dlg.DoModal();
}


void CLoginDlg::OnClickedIDLogin()
{
	AfxMessageBox(_T("登录ss"));
}


BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	m_tip.RelayEvent(pMsg);//将鼠标消息先转给m_tip

	return CDialogEx::PreTranslateMessage(pMsg);
}
