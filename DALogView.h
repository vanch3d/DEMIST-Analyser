// DALogView.h : interface of the CDALogView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DALOGVIEW_H__51D620E4_E4EC_11D5_A2F5_9C17D03C0928__INCLUDED_)
#define AFX_DALOGVIEW_H__51D620E4_E4EC_11D5_A2F5_9C17D03C0928__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDALogView : public CEditView
{
protected: // create from serialization only
	CDALogView();
	DECLARE_DYNCREATE(CDALogView)

// Attributes
public:
	CFont		m_pFont;
	CDADocument* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDALogView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDALogView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDALogView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DALogView.cpp
inline CDADocument* CDALogView::GetDocument()
   { return (CDADocument*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DALOGVIEW_H__51D620E4_E4EC_11D5_A2F5_9C17D03C0928__INCLUDED_)
