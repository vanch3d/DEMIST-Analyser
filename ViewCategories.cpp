// ViewCategories.cpp : implementation file
//

#include "stdafx.h"
#include "DEMIST Analyser.h"
#include "ViewCategories.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewCategories

IMPLEMENT_DYNCREATE(CViewCategories, CFormView)

CViewCategories::CViewCategories()
	: CFormView(CViewCategories::IDD)
{
	//{{AFX_DATA_INIT(CViewCategories)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CViewCategories::~CViewCategories()
{
}

void CViewCategories::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewCategories)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_GridControl(pDX, IDC_CAT_LIST, m_wndCatlist);
}


BEGIN_MESSAGE_MAP(CViewCategories, CFormView)
	//{{AFX_MSG_MAP(CViewCategories)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewCategories diagnostics

#ifdef _DEBUG
void CViewCategories::AssertValid() const
{
	CFormView::AssertValid();
}

void CViewCategories::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewCategories message handlers

void CViewCategories::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
	// fill it up with stuff
	//m_wndCatlist.SetImageList(&m_pImageList);
	m_wndCatlist.SetEditable(TRUE);
	m_wndCatlist.EnableDragAndDrop(FALSE);
	m_wndCatlist.SetRowCount(300);
	m_wndCatlist.SetColumnCount(2);
	m_wndCatlist.SetFixedRowCount(1);
	m_wndCatlist.SetFixedColumnCount(2);
	m_wndCatlist.EnableWysiwygPrinting(TRUE);
	m_wndCatlist.SetEditable(FALSE);
	m_wndCatlist.SetColumnResize(TRUE);
	m_wndCatlist.SetRowResize(FALSE);

	CFont Font;
	Font.CreatePointFont(80,_T("Arial"));
	m_wndCatlist.SetFont(&Font);
	Font.DeleteObject();	
}

void CViewCategories::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
//	if (m_wndCatlist.GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(rect);
		rect.top +=40;
		rect.left +=3;
		rect.right -=3;
		rect.bottom -=3;
		m_wndCatlist.MoveWindow(rect);
	}
	
}
