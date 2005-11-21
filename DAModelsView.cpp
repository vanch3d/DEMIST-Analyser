// DAModelsView.cpp : implementation file
//

#include "stdafx.h"
#include "DADoc.h"

#include "DEMIST Analyser.h"
#include "DAModelsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDAModelsView

IMPLEMENT_DYNCREATE(CDAModelsView, CEditView)

BEGIN_MESSAGE_MAP(CDAModelsView, CEditView)
	//{{AFX_MSG_MAP(CDAModelsView)
	ON_WM_CREATE()
	ON_COMMAND(ID_SCENARIO_NEXT, OnScenarioNext)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDALogView construction/destruction

CDAModelsView::CDAModelsView()
{
	m_nScenario = -1;
}

CDAModelsView::~CDAModelsView()
{
}

BOOL CDAModelsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	//cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping
	cs.style |= ES_READONLY;

	return bPreCreated;
}


/////////////////////////////////////////////////////////////////////////////
// CDAModelsView drawing

void CDAModelsView::OnDraw(CDC* pDC)
{
	CDADocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CDALogView printing

BOOL CDAModelsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CDAModelsView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CDAModelsView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}


/////////////////////////////////////////////////////////////////////////////
// CDAModelsView diagnostics

#ifdef _DEBUG
void CDAModelsView::AssertValid() const
{
	CEditView::AssertValid();
}

void CDAModelsView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CDADocument* CDAModelsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDADocument)));
	return (CDADocument*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDAModelsView message handlers

void CDAModelsView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();

	m_pFont.CreatePointFont(80,"Arial");
	SetFont(&m_pFont, TRUE );

	int nTabStops = 2;
	int  rgTabStops[2] = {1,50};
	GetEditCtrl().SetTabStops(nTabStops,rgTabStops );

	// TODO: Add your specialized code here and/or call the base class
	OnScenarioNext() ;
}

int CDAModelsView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if (!m_cToolBar.CreateEx(GetParent(), TBSTYLE_FLAT | TBSTYLE_TOOLTIPS, 
			WS_CHILD | WS_VISIBLE | CBRS_TOP | 
			/*CBRS_GRIPPER | */CBRS_TOOLTIPS | CBRS_FLYBY | CCS_ADJUSTABLE,
			CRect(0, 0, 0, 0), 120) ||
		!m_cToolBar.LoadToolBar(IDR_MODELSFILE))
	{
		TRACE0("Failed to create toolbar1\n");
		return -1;      // fail to create  
	}
	
	
	return 0;
}

void CDAModelsView::OnScenarioNext() 
{
	// TODO: Add your command handler code here
	int nb = GetDocument()->m_strScenarios.GetSize();

	if (!nb) return;

	m_nScenario++;
	if (m_nScenario==nb) m_nScenario = 0;

	CFile mFile(GetDocument()->m_strScenarios.GetAt(m_nScenario),CFile::modeRead);
	CArchive ar(&mFile,CArchive::load);
	SerializeRaw(ar);
}
