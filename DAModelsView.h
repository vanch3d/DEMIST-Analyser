#if !defined(AFX_DAMODELSVIEW_H__51D62107_E4EC_11D5_A2F5_9C17D03C0928__INCLUDED_)
#define AFX_DAMODELSVIEW_H__51D62107_E4EC_11D5_A2F5_9C17D03C0928__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DAModelsView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDAModelsView view

class CDAModelsView : public CEditView
{
protected:
	CDAModelsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDAModelsView)

// Attributes
public:
	int				m_nScenario;
	CToolBar		m_cToolBar;
	CFont		m_pFont;
	CDADocument* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDAModelsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDAModelsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDAModelsView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnScenarioNext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#ifndef _DEBUG  // debug version in DALogView.cpp
inline CDADocument* CDAModelsView::GetDocument()
   { return (CDADocument*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAMODELSVIEW_H__51D62107_E4EC_11D5_A2F5_9C17D03C0928__INCLUDED_)
