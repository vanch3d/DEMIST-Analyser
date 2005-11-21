#if !defined(AFX_DATABLEERS_H__100A0600_E72B_11D5_A2F5_A23C28590B28__INCLUDED_)
#define AFX_DATABLEERS_H__100A0600_E72B_11D5_A2F5_A23C28590B28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DATableERs.h : header file
//

#include "GridCtrl/GridCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDATableERs view

class CDATableERs : public CView
{
protected:
	CDATableERs();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDATableERs)

// Attributes
public:

// Operations
public:
	CDADocument* GetDocument();
	CGridCtrl*		m_pGridCtrl;
	CImageList		m_pImageList;
	CToolBar		m_cToolBar;

	virtual void InitTable();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDATableERs)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDATableERs();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDATableERs)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditCopy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DALogView.cpp
inline CDADocument* CDATableERs::GetDocument()
   { return (CDADocument*)m_pDocument; }
#endif


class CDATableAvail : public CDATableERs
{
protected:
	CDATableAvail();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDATableAvail)

// Attributes
public:
	virtual void InitTable();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDATableAvail)
	public:
//	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

};

class CDATableCategory : public CDATableERs
{
protected:
	int		m_nLevel;
	BOOL	m_bSortedAlpha;
	CDATableCategory();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDATableCategory)

// Attributes
public:
	virtual void InitTable();
	afx_msg void OnScenarioNext();
	afx_msg void OnScenarioPrev();
	afx_msg void OnSortAlpha();
	afx_msg void OnSortNum();
	afx_msg void OnUpdateScenario(CCmdUI* pCmdUI);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDATableCategory)
	public:
//	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CDATableCategory)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CDATableInformation : public CDATableERs
{
protected:
	CDATableInformation();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDATableInformation)

// Attributes
public:
	virtual void InitTable();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDATableInformation)
	public:
//	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

};

class CDATableSwitchER : public CDATableERs
{
protected:
	CDATableSwitchER();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDATableSwitchER)

// Attributes
public:
	virtual void InitTable();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDATableSwitchER)
	public:
//	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

};

class CDATableRunReview : public CDATableERs
{
protected:
	CDATableRunReview();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDATableRunReview)

// Attributes
public:
	virtual void InitTable();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDATableRunReview)
	public:
//	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATABLEERS_H__100A0600_E72B_11D5_A2F5_A23C28590B28__INCLUDED_)
