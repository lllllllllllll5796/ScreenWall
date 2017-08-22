
// ScreenWallView.cpp : implementation of the CScreenWallView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ScreenWall.h"
#endif

#include "ScreenWallDoc.h"
#include "ScreenWallView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScreenWallView

IMPLEMENT_DYNCREATE(CScreenWallView, CView)

BEGIN_MESSAGE_MAP(CScreenWallView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CScreenWallView construction/destruction

CScreenWallView::CScreenWallView()
{
	// TODO: add construction code here

}

CScreenWallView::~CScreenWallView()
{
}

BOOL CScreenWallView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CScreenWallView drawing

void CScreenWallView::OnDraw(CDC* /*pDC*/)
{
	CScreenWallDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CScreenWallView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CScreenWallView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CScreenWallView diagnostics

#ifdef _DEBUG
void CScreenWallView::AssertValid() const
{
	CView::AssertValid();
}

void CScreenWallView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CScreenWallDoc* CScreenWallView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScreenWallDoc)));
	return (CScreenWallDoc*)m_pDocument;
}
#endif //_DEBUG


// CScreenWallView message handlers
