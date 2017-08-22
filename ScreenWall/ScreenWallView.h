
// ScreenWallView.h : interface of the CScreenWallView class
//

#pragma once


class CScreenWallView : public CView
{
protected: // create from serialization only
	CScreenWallView();
	DECLARE_DYNCREATE(CScreenWallView)

// Attributes
public:
	CScreenWallDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CScreenWallView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ScreenWallView.cpp
inline CScreenWallDoc* CScreenWallView::GetDocument() const
   { return reinterpret_cast<CScreenWallDoc*>(m_pDocument); }
#endif

