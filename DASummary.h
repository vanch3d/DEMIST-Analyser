#if !defined(AFX_DASUMMARY_H__C4992D84_E5D7_11D5_A2F5_FCF538EF0928__INCLUDED_)
#define AFX_DASUMMARY_H__C4992D84_E5D7_11D5_A2F5_FCF538EF0928__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DASummary.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDASummary view

class CLogScenario;
class CLogUnit;
class CLogER;

class CDASummary : public CScrollView
{
protected:
	CDASummary();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDASummary)

// Attributes
public:

// Operations
public:
	CToolBar		m_cToolBar;
	BOOL		m_bShowActiv;
	BOOL		m_bShowAction;
	int			m_nScale;
	BOOL		m_bFirst;
	BOOL		m_bResize;
	CRect		m_rectLimit;
	CString		m_strSum;
	CFont		m_pFont;
	CDADocument* GetDocument();

	CArray<CRect,CRect>	m_rUnitPos;
	int					m_nUnitSel;


	CRect DrawScenario(CDC* pDC,CPoint pt,CLogScenario *pSc,int nScen);
	CRect DrawUnit(CDC* pDC,CPoint pt,CLogUnit *pSc,int nScen);
	CRect DrawER(CDC* pDC,CPoint pt,CLogER *pSc);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDASummary)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

	void PrintHeader(CDC *pDC, CPrintInfo *pInfo);
	void PrintFooter(CDC *pDC, CPrintInfo *pInfo);

// Implementation
protected:
	virtual ~CDASummary();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDASummary)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSummaryActiv();
	afx_msg void OnSummaryZmoins();
	afx_msg void OnSummaryZplus();
	afx_msg void OnUpdateSummaryZoom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSummary(CCmdUI* pCmdUI);
	afx_msg void OnSummaryAction(UINT nID);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEditCopy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DALogView.cpp
inline CDADocument* CDASummary::GetDocument()
   { return (CDADocument*)m_pDocument; }
#endif


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DASUMMARY_H__C4992D84_E5D7_11D5_A2F5_FCF538EF0928__INCLUDED_)
