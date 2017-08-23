// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenWall.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


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
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CLoginDlg message handlers


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//ÉèÖÃÍ¼±ê
	SetIcon(g_GobalVariable.hIconApp, FALSE);
	//¿Í»§¶ËÇøÓò
	GetClientRect(&m_rcClient);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CLoginDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	
	Graphics gh(dc.GetSafeHdc());
	//Ìî³ä±³¾°É«
	//Rect rc(m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());
	//SolidBrush bgBrush(Color(0, 255, 255, 255));
	//gh.FillRectangle(&bgBrush, rc);
	int x(m_rcClient.left), y(m_rcClient.top);//×ø±ê
	int	w(m_rcClient.Width()), h(m_rcClient.Height()); //¿í¸ß

	Rect rcWelcome(x, y, w, h/4);
	LinearGradientBrush bgBrush(rcWelcome,
		Color(216, 254, 233), Color(255, 255, 255),
		LinearGradientModeVertical);
	gh.FillRectangle(&bgBrush, rcWelcome);

	//»­48*48Í¼±ê
	x += 20; y += 10;
	Bitmap bmpApp(g_GobalVariable.hIconApp);
	//UINT width = bmpApp.GetWidth();  32*32
	gh.DrawImage(&bmpApp, x, y, 48, 48);

	//Ð´×Ö¡°ÆÁÄ»Ç½µÇÂ¼¡±
	x += 48 + 5; y += 5;
	FontFamily fontFamily(_T("ËÎÌå"));//×ÖÑù
	Gdiplus::Font font(&fontFamily, 16, FontStyleRegular, UnitPixel);//×ÖºÅ
	PointF pt(x*1.0f, y*1.0f);
	SolidBrush txtBrush(Color(0, 51, 153));
	gh.DrawString(_T("ÆÁÄ»Ç½"), -1, &font, pt, &txtBrush);
	
	pt.Y += font.GetHeight(0.0f); //ÀÛ¼Ó×ÖÌå¸ß¶È
	Gdiplus::Font font2(&fontFamily, 20, FontStyleBold, UnitPixel);
	gh.DrawString(_T("µÇÂ¼"), -1, &font2, pt, &txtBrush);

	//»­Ïß
	Pen p(Color(216, 254, 233), 2);
	gh.DrawLine(&p, 0, rcWelcome.GetBottom(), rcWelcome.GetRight(), rcWelcome.GetBottom());

	//²¼¾Ö¹«¸æÀ¸
	y = rcWelcome.GetBottom() + 2;
	CRect rcLoginGroup; //µÇÂ¼ÉèÖÃ¿Ø¼þÎ»ÖÃ
	GetDlgItem(IDC_sts_LoginGroup)->GetWindowRect(&rcLoginGroup); //ÆÁÄ»×ø±ê
	ScreenToClient(&rcLoginGroup);
	CRect rcNotice(rcLoginGroup.left, y, rcLoginGroup.right, rcLoginGroup.top);
	GetDlgItem(IDC_sts_Notice)->MoveWindow(&rcNotice);


}
