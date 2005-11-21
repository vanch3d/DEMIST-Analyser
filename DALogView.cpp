// DALogView.cpp : implementation of the CDALogView class
//

#include "stdafx.h"
#include "DEMIST Analyser.h"

#include "DADoc.h"
#include "DALogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDALogView

IMPLEMENT_DYNCREATE(CDALogView, CEditView)

BEGIN_MESSAGE_MAP(CDALogView, CEditView)
	//{{AFX_MSG_MAP(CDALogView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDALogView construction/destruction

CDALogView::CDALogView()
{
	// TODO: add construction code here

}

CDALogView::~CDALogView()
{
}

BOOL CDALogView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	//cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping
	cs.style |= ES_READONLY;

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CDALogView drawing

void CDALogView::OnDraw(CDC* pDC)
{
	CDADocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDALogView printing

BOOL CDALogView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CDALogView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CDALogView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CDALogView diagnostics

#ifdef _DEBUG
void CDALogView::AssertValid() const
{
	CEditView::AssertValid();
}

void CDALogView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CDADocument* CDALogView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDADocument)));
	return (CDADocument*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDALogView message handlers

void CDALogView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();

	CString strTitle;
	GetParentFrame()->GetWindowText(strTitle);

	CString strFile = GetDocument()->GetPathName();
	TCHAR path_buffer[_MAX_PATH];
	TCHAR name[_MAX_FNAME];
	TCHAR ext[_MAX_EXT];

	_tsplitpath (strFile, NULL, NULL,name,ext);
	_tmakepath (path_buffer, NULL,NULL,name,NULL);
	strFile = path_buffer;
	GetParentFrame()->SetWindowText(strFile + _T(" - ") + strTitle);

	m_pFont.CreatePointFont(80,"Arial");
	SetFont(&m_pFont, TRUE );

	int nTabStops = 2;
	int  rgTabStops[2] = {50,120};
	GetEditCtrl().SetTabStops(nTabStops,rgTabStops );

	
	// TODO: Add your specialized code here and/or call the base class
	CString mstr = GetDocument()->GetPathName();

	if (mstr.IsEmpty()) return;

	CFile mFile(mstr,CFile::modeRead);
	CArchive ar(&mFile,CArchive::load);
	SerializeRaw(ar);

}


void CDALogView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (lHint==DOC_SELECT_LOG_LINE)
	{
		int nLog = (int)pHint;
		CString strLine = GetDocument()->m_strLog.GetAt(nLog);
		if (!FindText(strLine))
			FindText(strLine,FALSE);
	}
	
}
