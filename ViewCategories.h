#if !defined(AFX_VIEWCATEGORIES_H__C460C1E0_DACB_11D6_B8E1_00D0B71C8709__INCLUDED_)
#define AFX_VIEWCATEGORIES_H__C460C1E0_DACB_11D6_B8E1_00D0B71C8709__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewCategories.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewCategories form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "GridCtrl/GridCtrl.h"

class CViewCategories : public CFormView
{
protected:
	CViewCategories();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewCategories)

// Form Data
public:
	//{{AFX_DATA(CViewCategories)
	enum { IDD = IDD_CATEGORIES };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CGridCtrl	m_wndCatlist;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewCategories)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewCategories();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CViewCategories)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWCATEGORIES_H__C460C1E0_DACB_11D6_B8E1_00D0B71C8709__INCLUDED_)
