/ DATableERs.cpp : implementation file
//

#include <afxadv.h>            // For CSharedFile

#include "stdafx.h"
#include "DEMIST Analyser.h"
#include "DADoc.h"

#include "DATableERs.h"

#include "LogUnit.h"

#include "ArrayEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDATableERs

IMPLEMENT_DYNCREATE(CDATableERs, CView)

BEGIN_MESSAGE_MAP(CDATableERs, CView)
	//{{AFX_MSG_MAP(CDATableERs)
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CDASummary construction/destruction

CDATableERs::CDATableERs()
{
	m_pGridCtrl = NULL;
}

CDATableERs::~CDATableERs()
{
	if (m_pGridCtrl)
		delete m_pGridCtrl;
}

BOOL CDATableERs::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CView::PreCreateWindow(cs);
	return bPreCreated;
}

int CDATableERs::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CDATableERs drawing

void CDATableERs::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CDALogView printing

BOOL CDATableERs::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CView preparation
	return DoPreparePrinting(pInfo);
}

void CDATableERs::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	if (m_pGridCtrl)
		m_pGridCtrl->OnBeginPrinting(pDC, pInfo);
}

void CDATableERs::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	if (m_pGridCtrl)
		m_pGridCtrl->OnEndPrinting(pDC, pInfo);
}

void CDATableERs::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	if (m_pGridCtrl)
		m_pGridCtrl->OnPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CDATableERs diagnostics

#ifdef _DEBUG
void CDATableERs::AssertValid() const
{
	CView::AssertValid();
}

void CDATableERs::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDADocument* CDATableERs::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDADocument)));
	return (CDADocument*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDATableERs message handlers

void CDATableERs::InitTable()
{
	CDADocument *pDoc = GetDocument();

	m_pGridCtrl->SetColumnCount(9);

	int nRow = 2;
	int nCol = 5;

	CString mstr[]={
		_T("Unit"),
		_T("E.R."),
		_T("Length"),
		_T("Percent"),
		_T("Parts"),
		_T("Map Relation"),
		_T("Hypothesis"),
		_T("Action"),
		_T("D. of I.")
	};

	for (int i=0;i<m_pGridCtrl->GetColumnCount();i++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.row = 0;
		Item.col = i;
		Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
		Item.strText.Format(_T("%s"),mstr[i]);
		m_pGridCtrl->SetItem(&Item);
	}

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.row = 1;
	Item.col = 1;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
	Item.nFormat = DT_LEFT|DT_WORDBREAK;
	Item.strText.Format(_T("Session"));
	m_pGridCtrl->SetItem(&Item);
	for (int r=0;r<m_pGridCtrl->GetColumnCount();r++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_BKCLR;
		Item.row = 1;
		Item.col = r;
		Item.crBkClr = RGB(128,128,255);
		m_pGridCtrl->SetItem(&Item);
	}

	CStringArray m_strTableInfo;
	int nInfoCol=0;

	for (i=0;i<pDoc->m_lScenario.GetSize();i++)
	{
		CLogScenario *pScen = (CLogScenario *)pDoc->m_lScenario.GetAt(i);
		if (!pScen) continue;

		GV_ITEM Item;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.row = nRow;
		Item.col = 1;
		Item.nFormat = DT_CENTER|DT_WORDBREAK;
		Item.strText.Format(_T("Scenario %d"),i);

		m_pGridCtrl->SetItem(&Item);
		for (int r=0;r<m_pGridCtrl->GetColumnCount();r++)
		{
			GV_ITEM Item;
			Item.mask = GVIF_BKCLR;
			Item.row = nRow;
			Item.col = r;
			Item.crBkClr = RGB(93,195,93);
			m_pGridCtrl->SetItem(&Item);
		}
		nRow++;

		for (int j=0;j<pScen->m_lUnits.GetSize();j++)
		{
			CLogUnit *pUnit = (CLogUnit *)pScen->m_lUnits.GetAt(j);
			if (!pUnit) continue;

			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = nRow;
			Item.col = 0;
			Item.nFormat = DT_LEFT|DT_WORDBREAK;
			Item.strText.Format(_T("Unit %d"),j);
			m_pGridCtrl->SetItem(&Item);

			for (int r=0;r<m_pGridCtrl->GetColumnCount();r++)
			{
				GV_ITEM Item;
				Item.mask = GVIF_BKCLR;
				Item.row = nRow;
				Item.col = r;
				Item.crBkClr = RGB(180,255,180);
				m_pGridCtrl->SetItem(&Item);
			}

			CTimeSpan nd= pUnit->n_nTimeStop-pUnit->n_nTime;

			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = nRow;
			Item.col = 2;
			Item.nFormat = DT_RIGHT|DT_WORDBREAK;
			Item.strText.Format(_T("%.2d:%.2d"),nd.GetMinutes(),nd.GetSeconds());

			m_pGridCtrl->SetItem(&Item);
			nRow++;

			int nUnitERStart = nRow;
			for (int k=0;k<pUnit->m_cERs.GetSize();k++)
			{
				CLogER pER = pUnit->m_cERs.GetAt(k);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 1;
				Item.nFormat = DT_LEFT|DT_WORDBREAK;
				Item.strText.Format(_T("%s"),pER.m_nERName);

				m_pGridCtrl->SetItem(&Item);

				CTimeSpan nTot(0,0,0,0);
				CTime nStart;
		
				int nb = pER.m_nERTime.GetSize();
				if (nb%2!=1) for (int l=0;l<pER.m_nERTime.GetSize();l+=2)
				{
					CTime ndd = pER.m_nERTime.GetAt(l);
					if (!l)
						nStart = ndd;
					CTime ndd2 = pER.m_nERTime.GetAt(l+1);

					CTimeSpan nST = ndd-pUnit->n_nTime;
					CTimeSpan nDD = ndd2-ndd;
					nTot += nDD;
				}
				if (pER.m_bStartUp)
				{
					GV_ITEM Item;
					Item.mask = GVIF_IMAGE;
					Item.row = nRow;
					Item.col = 0;
					Item.iImage = 0;
					m_pGridCtrl->SetItem(&Item);
				}

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 2;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%.2d:%.2d"),nTot.GetMinutes(),nTot.GetSeconds());
				m_pGridCtrl->SetItem(&Item);

				int ns = nTot.GetTotalSeconds();
				int ns2 = nd.GetTotalSeconds();

				double nPrec = (100. * ns) / ns2;

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 3;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%.2f %%"),nPrec);
				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 4;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%d"),nb/2);
				m_pGridCtrl->SetItem(&Item);

				CString strInfoList;

				int nInfo = pER.m_strInfo.GetSize();
				for (int l=0;l<nInfo;l++)
				{
					CString strInfo = pER.m_strInfo.GetAt(l);
					int nnnn = strInfo.Find(_T("--"));
					CString strOut = strInfo.Left(nnnn);
					strInfo.Delete(0,nnnn+2);
					CString strExp = strInfo;

					strInfoList += strOut + _T("/") + strInfo + _T(" ");
/*

					BOOL bFound = FALSE;
					for (int m=0;m<m_strTableInfo.GetSize();m++)
					{
						CString strCol = m_strTableInfo.GetAt(m);
						if (strCol==strOut)
						{
							bFound = TRUE;

							m_pGridCtrl->RedrawCell(nRow,8+m);
							CString strff = m_pGridCtrl->GetItemText(nRow,8+m);

							Item.mask = GVIF_TEXT|GVIF_FORMAT;
							Item.row = nRow;
							Item.col = 8+m;
							Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
							if (strff.IsEmpty())
								Item.strText.Format(_T("%s"),strExp);
							else
								Item.strText.Format(_T("%s"),strff+_T("/")+strExp);
							m_pGridCtrl->SetItem(&Item);
							break;
						}

					}
					if (!bFound)
					{
						m_strTableInfo.Add(strOut);
						nInfoCol++;
						m_pGridCtrl->SetColumnCount(8+nInfoCol);
						Item.mask = GVIF_TEXT|GVIF_FORMAT;
						Item.row = 0;
						Item.col = 7+nInfoCol;
						Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
						Item.strText.Format(_T("%s"),strOut);
						m_pGridCtrl->SetItem(&Item);

						Item.mask = GVIF_TEXT|GVIF_FORMAT;
						Item.row = nRow;
						Item.col = 7+nInfoCol;
						Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
						Item.strText.Format(_T("%s"),strExp);
						m_pGridCtrl->SetItem(&Item);
					}*/

				}

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 8;
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
				Item.strText.Format(_T("%s"),strInfoList);
				m_pGridCtrl->SetItem(&Item);

				nRow++;

			}

			int nbAct = pUnit->m_cActions.GetSize();
			int nbER = pUnit->m_cERs.GetSize();
			int nbMapRel[20];
			int nbHypoth[20];
			int nbAction[20];
			for (int hh=0;hh<nbER;hh++)
			{
				nbMapRel[hh]=0;
				nbHypoth[hh]=0;
				nbAction[hh]=0;
			}
			for (hh=0;hh<nbAct;hh++)
			{
				CLogAction pAct = pUnit->m_cActions.GetAt(hh);
				if (pAct.m_nType == LOG_SHOW_MAPREL) nbMapRel[pAct.m_nER]++;
				if (pAct.m_nType == LOG_SHOW_HYP) nbHypoth[pAct.m_nER]++;
				if (pAct.m_nType == LOG_SHOW_ACT) nbAction[pAct.m_nER]++;
			}
			for (hh=0;hh<nbER;hh++)
			{
				Item.mask = GVIF_BKCLR;
				if (nbMapRel[hh])
				{
					Item.mask |= GVIF_FORMAT|GVIF_TEXT;
					Item.nFormat = DT_RIGHT|DT_WORDBREAK;
					Item.strText.Format(_T("%d"),nbMapRel[hh]);
				}
				Item.row = nUnitERStart+hh;
				Item.col = 5;
				Item.crBkClr = RGB(255,235,235);

				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_BKCLR;
				if (nbHypoth[hh])
				{
					Item.mask |= GVIF_FORMAT|GVIF_TEXT;
					Item.nFormat = DT_RIGHT|DT_WORDBREAK;
					Item.strText.Format(_T("%d"),nbHypoth[hh]);
				}
				Item.row = nUnitERStart+hh;
				Item.col = 6;
				Item.crBkClr = RGB(255,235,235);
				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_BKCLR;
				if (nbAction[hh])
				{
					Item.mask |= GVIF_FORMAT|GVIF_TEXT;
					Item.nFormat = DT_RIGHT|DT_WORDBREAK;
					Item.strText.Format(_T("%d"),nbAction[hh]);
				}
				Item.row = nUnitERStart+hh;
				Item.col = 7;
				Item.crBkClr = RGB(255,235,235);
				m_pGridCtrl->SetItem(&Item);
			}

		}
	}
	m_pGridCtrl->SetRowCount(nRow);
}

void CDATableERs::OnInitialUpdate()
{
	CView::OnInitialUpdate();

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


	if (m_pGridCtrl == NULL)
	{
		// Create the Gridctrl object
		m_pGridCtrl = new CGridCtrl;
		if (!m_pGridCtrl) return;
	
		m_pImageList.Create(IDB_TABLE_IDX,10,1,RGB(192,192,192));
	}

	// Create the Gridctrl window
	CRect rect;
	GetClientRect(rect);
	m_pGridCtrl->Create(rect, this, 100);

	// fill it up with stuff
	m_pGridCtrl->SetImageList(&m_pImageList);
	m_pGridCtrl->SetEditable(TRUE);
	m_pGridCtrl->EnableDragAndDrop(TRUE);
	m_pGridCtrl->SetRowCount(300);
	m_pGridCtrl->SetColumnCount(8);
	m_pGridCtrl->SetFixedRowCount(1);
	m_pGridCtrl->SetFixedColumnCount(2);
	m_pGridCtrl->EnableWysiwygPrinting(TRUE);
	m_pGridCtrl->SetEditable(FALSE);
	m_pGridCtrl->SetColumnResize(TRUE);
	m_pGridCtrl->SetRowResize(FALSE);

	CFont Font;
	Font.CreatePointFont(80,_T("Arial"));
	m_pGridCtrl->SetFont(&Font);
	Font.DeleteObject();	

	InitTable();

	m_pGridCtrl->AutoSize();

	int nb = m_pGridCtrl->GetRowHeight(1);
	for (int i=1;i<m_pGridCtrl->GetRowCount();i++)
	{
		m_pGridCtrl->SetRowHeight(i,nb-3);
	}
}

void CDATableERs::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if (m_pGridCtrl->GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(rect);
		m_pGridCtrl->MoveWindow(rect);
	}
	
}

BOOL CDATableERs::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if (nID!=ID_EDIT_COPY)
    if (m_pGridCtrl && IsWindow(m_pGridCtrl->m_hWnd))
        if (m_pGridCtrl->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
            return TRUE;

	
	return CView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CDATableERs::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
}

void CDATableERs::OnEditCopy() 
{
	// TODO: Add your command handler code here
	CCellRange All  = m_pGridCtrl->GetSelectedCellRange();
	int nna = m_pGridCtrl->GetFixedColumnCount();
	int nnb = m_pGridCtrl->GetColumnCount();
	int nnc = m_pGridCtrl->GetFixedRowCount();
	int nnd = m_pGridCtrl->GetRowCount();
    CCellRange Selection;
	if (All.GetMinCol()==m_pGridCtrl->GetFixedColumnCount() &&
		All.GetMaxCol()==m_pGridCtrl->GetColumnCount()-1 &&
		All.GetMinRow()==m_pGridCtrl->GetFixedRowCount() &&
		All.GetMaxRow()==m_pGridCtrl->GetRowCount()-1)
	{
		Selection = CCellRange(0,0,m_pGridCtrl->GetRowCount()-1,m_pGridCtrl->GetColumnCount()-1);
	}
	else
	{
		Selection = All;
	}

    if (!m_pGridCtrl->IsValid(Selection))
        return;

    // Write to shared file (REMEBER: CF_TEXT is ANSI, not UNICODE, so we need to convert)
    CSharedFile sf(GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT);

    // Get a tab delimited string to copy to cache
    CString str;
    CGridCellBase *pCell;
    for (int row = Selection.GetMinRow(); row <= Selection.GetMaxRow(); row++)
    {
        str.Empty();
        for (int col = Selection.GetMinCol(); col <= Selection.GetMaxCol(); col++)
        {
            pCell = m_pGridCtrl->GetCell(row, col);
			CString tmp = pCell->GetText();
			if (tmp.Find(_T(":")) != -1)
				str +=_T("00:");
            str += pCell->GetText();
			int nImage = pCell->GetImage();
			if (nImage!=-1)
				str += _T(">");

            if (col != Selection.GetMaxCol()) 
                str += _T("\t");
        }
        if (row != Selection.GetMaxRow()) 
            str += _T("\n");
        
        sf.Write(T2A(str.GetBuffer(1)), str.GetLength());
        str.ReleaseBuffer();
    }
    
    char c = '\0';
    sf.Write(&c, 1);

    DWORD dwLen = (DWORD) sf.GetLength();
    HGLOBAL hMem = sf.Detach();
    if (!hMem)
        return;

    hMem = ::GlobalReAlloc(hMem, dwLen, GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT);
    if (!hMem)
        return;

    // Cache data
    COleDataSource* pSource = new COleDataSource();
    pSource->CacheGlobalData(CF_TEXT, hMem);
    pSource->SetClipboard();

    return;
	
}


/////////////////////////////////////////////////////////////////////////////
// CDASummary construction/destruction
IMPLEMENT_DYNCREATE(CDATableAvail, CDATableERs)

CDATableAvail::CDATableAvail()
{
}

void CDATableAvail::InitTable()
{
	m_pGridCtrl->SetColumnCount(14);
	m_pGridCtrl->SetFixedColumnCount(1);

	CDADocument *pDoc = GetDocument();

	int nRow = 2;
	int nCol = 5;

	CString mstr[]={
		_T("Unit"),//_T("E.R."),
		_T("Length"),
		_T("R.Sp."),//_T("%"),
		_T("Limit"),//_T("%"),
		_T("Def."),//_T("%"),
		_T("Min"),
		_T("Max"),
		_T("Mean"),
		_T("0"),
		_T("1"),
		_T("2"),
		_T("3"),
		_T("4"),
		_T("5"),
		_T("6"),
		_T("7"),
		_T("8"),
		_T("9"),
		_T("10"),
		_T("11"),
		_T("12"),
		_T("13"),
		_T("14"),
		_T("15"),
		_T("16")
	};

	int nMaxCol = 0;
	for (int i=0;i<pDoc->m_lScenario.GetSize();i++)
	{
		CLogScenario *pScen = (CLogScenario *)pDoc->m_lScenario.GetAt(i);
		if (!pScen) continue;
		for (int j=0;j<pScen->m_lUnits.GetSize();j++)
		{
			CLogUnit *pUnit = (CLogUnit *)pScen->m_lUnits.GetAt(j);
			if (!pUnit) continue;

			nMaxCol = max(nMaxCol,pUnit->m_nMax);
		}
	}

	m_pGridCtrl->SetColumnCount(8+nMaxCol+1);

	for (i=0;i<m_pGridCtrl->GetColumnCount();i++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.row = 0;
		Item.col = i;
		Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
		Item.strText.Format(_T("%s"),mstr[i]);
		m_pGridCtrl->SetItem(&Item);
	}

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.row = 1;
	Item.col = 0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
	Item.nFormat = DT_LEFT|DT_WORDBREAK;
	Item.strText.Format(_T("Session"));
	m_pGridCtrl->SetItem(&Item);
	for (int r=0;r<m_pGridCtrl->GetColumnCount();r++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_BKCLR;
		Item.row = 1;
		Item.col = r;
		Item.crBkClr = RGB(128,128,255);
		m_pGridCtrl->SetItem(&Item);
	}

	for (i=0;i<pDoc->m_lScenario.GetSize();i++)
	{
		CLogScenario *pScen = (CLogScenario *)pDoc->m_lScenario.GetAt(i);
		if (!pScen) continue;

		GV_ITEM Item;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.row = nRow;
		Item.col = 0;
		Item.nFormat = DT_LEFT|DT_WORDBREAK;
		Item.strText.Format(_T("Scenario %d"),i);

		m_pGridCtrl->SetItem(&Item);
		for (int r=0;r<m_pGridCtrl->GetColumnCount();r++)
		{
			GV_ITEM Item;
			Item.mask = GVIF_BKCLR;
			Item.row = nRow;
			Item.col = r;
			Item.crBkClr = RGB(93,195,93);
			m_pGridCtrl->SetItem(&Item);
		}
		nRow++;

		for (int j=0;j<pScen->m_lUnits.GetSize();j++)
		{
			CLogUnit *pUnit = (CLogUnit *)pScen->m_lUnits.GetAt(j);
			if (!pUnit) continue;

			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = nRow;
			Item.col = 0;
			Item.nFormat = DT_LEFT|DT_WORDBREAK;
			Item.strText.Format(_T("Unit %d"),j);
			m_pGridCtrl->SetItem(&Item);

/*			for (int r=1;r<m_pGridCtrl->GetColumnCount();r++)
			{
				GV_ITEM Item;
				Item.mask = GVIF_BKCLR;
				Item.row = nRow;
				Item.col = r;
				Item.crBkClr = RGB(180,255,180);
				m_pGridCtrl->SetItem(&Item);
			}*/

			CTimeSpan nd= pUnit->n_nTimeStop-pUnit->n_nTime;
			int nbER = pUnit->m_cERs.GetSize();
			int ncol=1;

			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = nRow;
			Item.col = ncol++;
			Item.nFormat = DT_RIGHT|DT_WORDBREAK;
			Item.strText.Format(_T("%.2d:%.2d"),nd.GetMinutes(),nd.GetSeconds());
			m_pGridCtrl->SetItem(&Item);

			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = nRow;
			Item.col = ncol++;
			Item.nFormat = DT_RIGHT|DT_WORDBREAK;
			Item.strText.Format(_T("%d"),nbER-1);
			m_pGridCtrl->SetItem(&Item);

			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = nRow;
			Item.col = ncol++;
			Item.nFormat = DT_RIGHT|DT_WORDBREAK;
			Item.strText.Format(_T("%d"),pUnit->m_nCMax);
			m_pGridCtrl->SetItem(&Item);

			int nDef = 0;
			for (int k=1;k<nbER;k++)
			{
				CLogER pER = pUnit->m_cERs.GetAt(k);
				nDef += pER.m_bStartUp;
			}
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = nRow;
			Item.col = ncol++;
			Item.nFormat = DT_RIGHT|DT_WORDBREAK;
			Item.strText.Format(_T("%d"),nDef);
			m_pGridCtrl->SetItem(&Item);

			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = nRow;
			Item.col = ncol++;
			Item.nFormat = DT_RIGHT|DT_WORDBREAK;
			Item.strText.Format(_T("%d"),pUnit->m_nMin);
			m_pGridCtrl->SetItem(&Item);

			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = nRow;
			Item.col = ncol++;
			Item.nFormat = DT_RIGHT|DT_WORDBREAK;
			Item.strText.Format(_T("%d"),pUnit->m_nMax);
			m_pGridCtrl->SetItem(&Item);

			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = nRow;
			Item.col = ncol++;
			Item.nFormat = DT_RIGHT|DT_WORDBREAK;
			Item.strText.Format(_T("%.2f"),pUnit->m_nAver);
			m_pGridCtrl->SetItem(&Item);

			for (r=0;r<=nMaxCol;r++)
			{
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = ncol+r;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				CTimeSpan nttt(0,0,0,pUnit->m_nCountInd.GetAt(r));
				Item.strText.Format(_T("%.2d:%.2d"),nttt.GetMinutes(),nttt.GetSeconds());
				if (nttt.GetTotalSeconds())
					m_pGridCtrl->SetItem(&Item);
			}

			nRow++;
/*
			int nUnitERStart = nRow;
			for (int k=1;k<pUnit->m_cERs.GetSize();k++)
			{
				CLogER pER = pUnit->m_cERs.GetAt(k);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 0;
				Item.nFormat = DT_LEFT|DT_WORDBREAK;
				Item.strText.Format(_T("%s"),pER.m_strCategory);

				m_pGridCtrl->SetItem(&Item);

				CTimeSpan nTot(0,0,0,0);
				CTime nStart;
		
				int nb = pER.m_nERTime.GetSize();
				if (nb%2!=1) for (int l=0;l<pER.m_nERTime.GetSize();l+=2)
				{
					CTime ndd = pER.m_nERTime.GetAt(l);
					if (!l)
						nStart = ndd;
					CTime ndd2 = pER.m_nERTime.GetAt(l+1);

					CTimeSpan nST = ndd-pUnit->n_nTime;
					CTimeSpan nDD = ndd2-ndd;
					nTot += nDD;
				}
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 1;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%.2d:%.2d"),nTot.GetMinutes(),nTot.GetSeconds());
				m_pGridCtrl->SetItem(&Item);

				int ns = nTot.GetTotalSeconds();
				int ns2 = nd.GetTotalSeconds();

				double nPrec = (100. * ns) / ns2;

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 2;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%.2f %%"),nPrec);
				m_pGridCtrl->SetItem(&Item);

				nRow++;
			}

			int nbER = pUnit->m_cERs.GetSize();
			for (int hh=0;hh<nbER;hh++)
			{
				for (int i=0;i<9;i++)
				{
					Item.mask = GVIF_BKCLR;
					Item.row = nUnitERStart+hh;
					Item.col = 3+i;
					Item.crBkClr = ::GetSysColor(COLOR_3DSHADOW);

					m_pGridCtrl->SetItem(&Item);
				}

			}*/
		}
	}
	m_pGridCtrl->SetRowCount(nRow);
}

/*void CDATableAvail::OnInitialUpdate()
{
	CView::OnInitialUpdate();

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


	if (m_pGridCtrl == NULL)
	{
		// Create the Gridctrl object
		m_pGridCtrl = new CGridCtrl;
		if (!m_pGridCtrl) return;
	
		m_pImageList.Create(IDB_TABLE_IDX,10,1,RGB(192,192,192));
	}

	// Create the Gridctrl window
	CRect rect;
	GetClientRect(rect);
	m_pGridCtrl->Create(rect, this, 100);

	// fill it up with stuff
	m_pGridCtrl->SetImageList(&m_pImageList);
	m_pGridCtrl->SetEditable(TRUE);
	m_pGridCtrl->EnableDragAndDrop(TRUE);
	m_pGridCtrl->SetRowCount(300);
	m_pGridCtrl->SetColumnCount(13);
	m_pGridCtrl->SetFixedRowCount(1);
	m_pGridCtrl->SetFixedColumnCount(1);
	m_pGridCtrl->EnableWysiwygPrinting(TRUE);
	m_pGridCtrl->SetEditable(FALSE);
	m_pGridCtrl->SetColumnResize(TRUE);
	m_pGridCtrl->SetRowResize(FALSE);

	CFont Font;
	Font.CreatePointFont(80,_T("Arial"));
	m_pGridCtrl->SetFont(&Font);
	Font.DeleteObject();	

	m_pGridCtrl->AutoSize();

	int nb = m_pGridCtrl->GetRowHeight(1);
	for (int i=1;i<m_pGridCtrl->GetRowCount();i++)
	{
		m_pGridCtrl->SetRowHeight(i,nb-3);
	}
}*/

/////////////////////////////////////////////////////////////////////////////
// CDASummary construction/destruction
IMPLEMENT_DYNCREATE(CDATableCategory, CDATableERs)

BEGIN_MESSAGE_MAP(CDATableCategory, CDATableERs)
	//{{AFX_MSG_MAP(CDATableERs)
	ON_WM_CREATE()
	ON_COMMAND(ID_SCENARIO_NEXT, OnScenarioNext)
	ON_COMMAND(ID_SCENARIO_PREV, OnScenarioPrev)
	ON_COMMAND(ID_CATEGORY_ALPHA, OnSortAlpha)
	ON_COMMAND(ID_CATEGORY_PERCENT, OnSortNum)
	ON_UPDATE_COMMAND_UI(ID_SCENARIO_NEXT, OnUpdateScenario)
	ON_UPDATE_COMMAND_UI(ID_SCENARIO_PREV, OnUpdateScenario)
	ON_UPDATE_COMMAND_UI(ID_CATEGORY_ALPHA, OnUpdateScenario)
	ON_UPDATE_COMMAND_UI(ID_CATEGORY_PERCENT, OnUpdateScenario)
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

CDATableCategory::CDATableCategory()
{
	m_nLevel = 0;
	m_bSortedAlpha = TRUE;
}

void CDATableCategory::InitTable()
{
	m_pGridCtrl->SetColumnCount(8);
	m_pGridCtrl->SetFixedColumnCount(1);
	CDADocument *pDoc = GetDocument();

	int nRow = 2;
	CString mstr[]={
		_T("Unit"),//_T("E.R."),
		_T("Length"),
		_T("%"),//_T("%"),
		_T("Nb"),
		_T("Def."),
		_T("Map Rel"),
		_T("Hyp"),
		_T("Action"),
	};

	for (int i=0;i<m_pGridCtrl->GetColumnCount();i++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.row = 0;
		Item.col = i;
		Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
		Item.strText.Format(_T("%s"),mstr[i]);
		m_pGridCtrl->SetItem(&Item);
	}

	CStringArray strCat;
	CArray<CTimeSpan,CTimeSpan>	tCat;
	CUIntArray			nCat;
	CUIntArray			nDef;
	CUIntArray			nMap;
	CUIntArray			nHyp;
	CUIntArray			nAct;

	CTimeSpan nd(0,0,0,0);

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.row = 1;
	Item.col = 0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
	Item.nFormat = DT_LEFT|DT_WORDBREAK;
	Item.strText.Format(_T("Session"));
	m_pGridCtrl->SetItem(&Item);
	for (int r=0;r<m_pGridCtrl->GetColumnCount();r++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_BKCLR;
		Item.row = 1;
		Item.col = r;
		Item.crBkClr = RGB(128,128,255);
		m_pGridCtrl->SetItem(&Item);
	}

	for (i=0;i<pDoc->m_lScenario.GetSize();i++)
	{
		CLogScenario *pScen = (CLogScenario *)pDoc->m_lScenario.GetAt(i);
		if (!pScen) continue;

		if (m_nLevel != 2) 
		{
			nd = CTimeSpan(0,0,0,0);

			GV_ITEM Item;
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = nRow;
			Item.col = 0;
			Item.nFormat = DT_LEFT|DT_WORDBREAK;
			Item.strText.Format(_T("Scenario %d"),i);

			m_pGridCtrl->SetItem(&Item);
			for (int r=0;r<m_pGridCtrl->GetColumnCount();r++)
			{
				GV_ITEM Item;
				Item.mask = GVIF_BKCLR;
				Item.row = nRow;
				Item.col = r;
				Item.crBkClr = RGB(93,195,93);
				m_pGridCtrl->SetItem(&Item);
			}
			nRow++;
		}

		if (m_nLevel==1)
		{
			strCat.RemoveAll();
			tCat.RemoveAll();
			nCat.RemoveAll();
			nDef.RemoveAll();
			nMap.RemoveAll();
			nHyp.RemoveAll();
			nAct.RemoveAll();
		}


		int nUnitERStart = nRow;
		for (int j=0;j<pScen->m_lUnits.GetSize();j++)
		{
			CLogUnit *pUnit = (CLogUnit *)pScen->m_lUnits.GetAt(j);
			if (!pUnit) continue;

			int nbAct = pUnit->m_cActions.GetSize();
			int nbER = pUnit->m_cERs.GetSize();
			int nbMapRel[20];
			int nbHypoth[20];
			int nbAction[20];
			for (int hh=0;hh<nbER;hh++)
			{
				nbMapRel[hh]=0;
				nbHypoth[hh]=0;
				nbAction[hh]=0;
			}
			for (hh=0;hh<nbAct;hh++)
			{
				CLogAction pAct = pUnit->m_cActions.GetAt(hh);
				if (pAct.m_nType == LOG_SHOW_MAPREL) nbMapRel[pAct.m_nER]++;
				if (pAct.m_nType == LOG_SHOW_HYP) nbHypoth[pAct.m_nER]++;
				if (pAct.m_nType == LOG_SHOW_ACT) nbAction[pAct.m_nER]++;
			}

			CTimeSpan nbT = pUnit->n_nTimeStop-pUnit->n_nTime;

			if (m_nLevel==0)
			{
				nd = nbT;

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 0;
				Item.nFormat = DT_LEFT|DT_WORDBREAK;
				Item.strText.Format(_T("Unit %d"),j);
				m_pGridCtrl->SetItem(&Item);

				for (int r=0;r<m_pGridCtrl->GetColumnCount();r++)
				{
					GV_ITEM Item;
					Item.mask = GVIF_BKCLR;
					Item.row = nRow;
					Item.col = r;
					Item.crBkClr = RGB(180,255,180);
					m_pGridCtrl->SetItem(&Item);
				}

				int nbER = pUnit->m_cERs.GetSize();
				int ncol=1;

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = ncol++;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%.2d:%.2d"),nd.GetMinutes(),nd.GetSeconds());
				m_pGridCtrl->SetItem(&Item);

				nRow++;

				strCat.RemoveAll();
				tCat.RemoveAll();
				nCat.RemoveAll();
				nDef.RemoveAll();
				nMap.RemoveAll();
				nHyp.RemoveAll();
				nAct.RemoveAll();
			}
			else
			{
				nd += nbT;
			}

			nUnitERStart = nRow;
			for (int k=1;k<pUnit->m_cERs.GetSize();k++)
			{
				CLogER pER = pUnit->m_cERs.GetAt(k);

				CTimeSpan nTot(0,0,0,0);
				CTime nStart;
		
				int nb = pER.m_nERTime.GetSize();
				if (nb%2!=1) for (int l=0;l<pER.m_nERTime.GetSize();l+=2)
				{
					CTime ndd = pER.m_nERTime.GetAt(l);
					if (!l)	nStart = ndd;
					CTime ndd2 = pER.m_nERTime.GetAt(l+1);

					CTimeSpan nST = ndd-pUnit->n_nTime;
					CTimeSpan nDD = ndd2-ndd;
					nTot += nDD;
				}

				BOOL bFound = FALSE;
				CString strERtemp= pER.m_strCategory;
				for (int i=0;i<strCat.GetSize();i++)
				{
					if (strCat.GetAt(i)==strERtemp)
					{
						tCat.SetAt(i,tCat.GetAt(i)+nTot);
						nCat.SetAt(i,nCat.GetAt(i)+1);
						nDef.SetAt(i,nDef.GetAt(i)+pER.m_bStartUp);

						nMap.SetAt(i,nMap.GetAt(i)+nbMapRel[k]);
						nHyp.SetAt(i,nHyp.GetAt(i)+nbHypoth[k]);
						nAct.SetAt(i,nAct.GetAt(i)+nbAction[k]);
						bFound = TRUE;
						break;
					}

				}
				if (!bFound)
				{
					strCat.Add(strERtemp);
					tCat.Add(nTot);
					nCat.Add(1);
					nDef.Add(pER.m_bStartUp);

					nMap.Add(nbMapRel[k]);
					nHyp.Add(nbHypoth[k]);
					nAct.Add(nbAction[k]);

				}
			}

			if (m_nLevel==0)
			{
				CUIntArray	nSortItem;
				for (int k=0;k<strCat.GetSize();k++)
				{
					CString t1 = strCat.GetAt(k);
					CTimeSpan nT1 = tCat.GetAt(k);
					BOOL bInserted = FALSE;
					for (int j=0;j<nSortItem.GetSize();j++)
					{
						CString t2 = strCat.GetAt(nSortItem.GetAt(j));
						CTimeSpan nT2 = tCat.GetAt(nSortItem.GetAt(j));
						if (m_bSortedAlpha && t1<t2)
						{
							nSortItem.InsertAt(j,k);
							bInserted = TRUE;
							break;
						}
						else if (!m_bSortedAlpha && nT1<nT2)
						{
							nSortItem.InsertAt(j,k);
							bInserted = TRUE;
							break;
						}
					}
					if (!bInserted)
						nSortItem.Add(k);
				}

			
			for (k=0;k<strCat.GetSize();k++)
			{
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 0;
				Item.nFormat = DT_LEFT|DT_WORDBREAK;
				Item.strText.Format(_T("%s"),strCat.GetAt(nSortItem.GetAt(k)));
				m_pGridCtrl->SetItem(&Item);

				CTimeSpan nTot = tCat.GetAt(nSortItem.GetAt(k));

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 1;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%.2d:%.2d"),nTot.GetMinutes(),nTot.GetSeconds());
				m_pGridCtrl->SetItem(&Item);

				int ns = nTot.GetTotalSeconds();
				int ns2 = nd.GetTotalSeconds();

				double nPrec = (1. * ns) / ns2;

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 2;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%.4f"),nPrec);
				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 3;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%d"),nCat.GetAt(nSortItem.GetAt(k)));
				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 4;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%d"),nDef.GetAt(nSortItem.GetAt(k)));
				m_pGridCtrl->SetItem(&Item);


				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 5;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%d"),nMap.GetAt(nSortItem.GetAt(k)));
				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 6;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%d"),nHyp.GetAt(nSortItem.GetAt(k)));
				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 7;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%d"),nAct.GetAt(nSortItem.GetAt(k)));
				m_pGridCtrl->SetItem(&Item);
				
				nRow++;
			}
			}

		}
		if (m_nLevel==1) 
		{
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = nUnitERStart-1;
			Item.col = 1;
			Item.nFormat = DT_RIGHT|DT_WORDBREAK;
			Item.strText.Format(_T("%.2d:%.2d"),nd.GetMinutes(),nd.GetSeconds());
			m_pGridCtrl->SetItem(&Item);

			CUIntArray	nSortItem;
			for (int k=0;k<strCat.GetSize();k++)
			{
				CString t1 = strCat.GetAt(k);
				CTimeSpan nT1 = tCat.GetAt(k);
				BOOL bInserted = FALSE;
				for (int j=0;j<nSortItem.GetSize();j++)
				{
					CString t2 = strCat.GetAt(nSortItem.GetAt(j));
					CTimeSpan nT2 = tCat.GetAt(nSortItem.GetAt(j));
					if (m_bSortedAlpha && t1<t2)
					{
						nSortItem.InsertAt(j,k);
						bInserted = TRUE;
						break;
					}
					else if (!m_bSortedAlpha && nT1<nT2)
					{
						nSortItem.InsertAt(j,k);
						bInserted = TRUE;
						break;
					}
				}
				if (!bInserted)
					nSortItem.Add(k);

			}


			for (k=0;k<strCat.GetSize();k++)
			{

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 0;
				Item.nFormat = DT_LEFT|DT_WORDBREAK;
				Item.strText.Format(_T("%s"),strCat.GetAt(nSortItem.GetAt(k)));

				m_pGridCtrl->SetItem(&Item);

				CTimeSpan nTot = tCat.GetAt(nSortItem.GetAt(k));

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 1;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%.2d:%.2d"),nTot.GetMinutes(),nTot.GetSeconds());
				m_pGridCtrl->SetItem(&Item);

				int ns = nTot.GetTotalSeconds();
				int ns2 = nd.GetTotalSeconds();

				double nPrec = (1. * ns) / ns2;

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 2;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%.4f"),nPrec);
				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 3;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%d"),nCat.GetAt(nSortItem.GetAt(k)));
				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 4;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%d"),nDef.GetAt(nSortItem.GetAt(k)));
				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 5;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%d"),nMap.GetAt(nSortItem.GetAt(k)));
				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 6;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%d"),nHyp.GetAt(nSortItem.GetAt(k)));
				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 7;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%d"),nAct.GetAt(nSortItem.GetAt(k)));
				m_pGridCtrl->SetItem(&Item);

				nRow++;
			}
		}

	}
		if (m_nLevel==2) 
		{
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = 1;
				Item.col = 1;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;

				int nH = nd.GetTotalHours();
				int nM = nd.GetMinutes();
				int nS = nd.GetSeconds();
			Item.strText.Format(_T("%.2d:%.2d"),nH*60+nM,nS);
	m_pGridCtrl->SetItem(&Item);

			CUIntArray	nSortItem;
			for (int k=0;k<strCat.GetSize();k++)
			{
				CString t1 = strCat.GetAt(k);
				CTimeSpan nT1 = tCat.GetAt(k);
				BOOL bInserted = FALSE;
				for (int j=0;j<nSortItem.GetSize();j++)
				{
					CString t2 = strCat.GetAt(nSortItem.GetAt(j));
					CTimeSpan nT2 = tCat.GetAt(nSortItem.GetAt(j));
					if (m_bSortedAlpha && t1<t2)
					{
						nSortItem.InsertAt(j,k);
						bInserted = TRUE;
						break;
					}
					else if (!m_bSortedAlpha && nT1<nT2)
					{
						nSortItem.InsertAt(j,k);
						bInserted = TRUE;
						break;
					}
				}
				if (!bInserted)
					nSortItem.Add(k);

			}


			for (k=0;k<strCat.GetSize();k++)
			{

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 0;
				Item.nFormat = DT_LEFT|DT_WORDBREAK;
				Item.strText.Format(_T("%s"),strCat.GetAt(nSortItem.GetAt(k)));

				m_pGridCtrl->SetItem(&Item);

				CTimeSpan nTot = tCat.GetAt(nSortItem.GetAt(k));

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 1;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				int nH = nTot.GetTotalHours();
				int nM = nTot.GetMinutes();
				int nS = nTot.GetSeconds();
				Item.strText.Format(_T("%.2d:%.2d"),nH*60+nM,nS);
				m_pGridCtrl->SetItem(&Item);

				int ns = nTot.GetTotalSeconds();
				int ns2 = nd.GetTotalSeconds();

				double nPrec = (1. * ns) / ns2;

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 2;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%.4f"),nPrec);
				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 3;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%d"),nCat.GetAt(nSortItem.GetAt(k)));
				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 4;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%d"),nDef.GetAt(nSortItem.GetAt(k)));
				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 5;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%d"),nMap.GetAt(nSortItem.GetAt(k)));
				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 6;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%d"),nHyp.GetAt(nSortItem.GetAt(k)));
				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 7;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%d"),nAct.GetAt(nSortItem.GetAt(k)));
				m_pGridCtrl->SetItem(&Item);

				nRow++;
			}
		}			

	m_pGridCtrl->SetRowCount(nRow);
}

/*void CDATableCategory::OnInitialUpdate()
{
	CView::OnInitialUpdate();

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


	if (m_pGridCtrl == NULL)
	{
		// Create the Gridctrl object
		m_pGridCtrl = new CGridCtrl;
		if (!m_pGridCtrl) return;
	
		m_pImageList.Create(IDB_TABLE_IDX,10,1,RGB(192,192,192));
	}

	// Create the Gridctrl window
	CRect rect;
	GetClientRect(rect);
	m_pGridCtrl->Create(rect, this, 100);

	// fill it up with stuff
	m_pGridCtrl->SetImageList(&m_pImageList);
	m_pGridCtrl->SetEditable(TRUE);
	m_pGridCtrl->EnableDragAndDrop(TRUE);
	m_pGridCtrl->SetRowCount(300);
	m_pGridCtrl->SetColumnCount(4);
	m_pGridCtrl->SetFixedRowCount(1);
	m_pGridCtrl->SetFixedColumnCount(1);
	m_pGridCtrl->EnableWysiwygPrinting(TRUE);
	m_pGridCtrl->SetEditable(FALSE);
	m_pGridCtrl->SetColumnResize(TRUE);
	m_pGridCtrl->SetRowResize(FALSE);

	CFont Font;
	Font.CreatePointFont(80,_T("Arial"));
	m_pGridCtrl->SetFont(&Font);
	Font.DeleteObject();	

	m_pGridCtrl->AutoSize();

	int nb = m_pGridCtrl->GetRowHeight(1);
	for (i=1;i<m_pGridCtrl->GetRowCount();i++)
	{
		m_pGridCtrl->SetRowHeight(i,nb-3);
	}
}*/

int CDATableCategory::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDATableERs::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if (!m_cToolBar.CreateEx(GetParent(), TBSTYLE_FLAT | TBSTYLE_TOOLTIPS, 
			WS_CHILD | WS_VISIBLE | CBRS_TOP | 
			/*CBRS_GRIPPER | */CBRS_TOOLTIPS | CBRS_FLYBY | CCS_ADJUSTABLE,
			CRect(0, 0, 0, 0), 120) ||
		!m_cToolBar.LoadToolBar(IDR_CATEGORY))
	{
		TRACE0("Failed to create toolbar1\n");
		return -1;      // fail to create  
	}
	
	
	return 0;
}

void CDATableCategory::OnScenarioNext()
{
	m_nLevel++;
	m_pGridCtrl->SetRowCount(1);
	m_pGridCtrl->SetRowCount(300);
	m_pGridCtrl->SetColumnCount(1);
	InitTable();
	m_pGridCtrl->AutoSize();

	int nb = m_pGridCtrl->GetRowHeight(1);
	for (int i=1;i<m_pGridCtrl->GetRowCount();i++)
	{
		m_pGridCtrl->SetRowHeight(i,nb-3);
	}
}

void CDATableCategory::OnScenarioPrev()
{
	m_nLevel--;
	m_pGridCtrl->SetRowCount(1);
	m_pGridCtrl->SetRowCount(300);
	m_pGridCtrl->SetColumnCount(1);
	InitTable();
	m_pGridCtrl->AutoSize();

	int nb = m_pGridCtrl->GetRowHeight(1);
	for (int i=1;i<m_pGridCtrl->GetRowCount();i++)
	{
		m_pGridCtrl->SetRowHeight(i,nb-3);
	}
}

void CDATableCategory::OnUpdateScenario(CCmdUI* pCmdUI)
{
	BOOL bEnb = FALSE;
	BOOL bCheck = FALSE;
	switch (pCmdUI->m_nID){
	case ID_SCENARIO_NEXT:
		bEnb = (BOOL)(m_nLevel!=2);
		break;
	case ID_SCENARIO_PREV:
		bEnb = (BOOL)m_nLevel;
		break;
	case ID_CATEGORY_ALPHA:
		bEnb = TRUE;
		bCheck = m_bSortedAlpha;
		break;
	case ID_CATEGORY_PERCENT:
		bEnb = TRUE;
		bCheck = !m_bSortedAlpha;
		break;
	}
	pCmdUI->Enable(bEnb);
	pCmdUI->SetCheck(bCheck);

}

void CDATableCategory::OnSortAlpha()
{
	if (m_bSortedAlpha) return;
	m_bSortedAlpha = !m_bSortedAlpha;
	m_pGridCtrl->SetRowCount(1);
	m_pGridCtrl->SetRowCount(300);
	m_pGridCtrl->SetColumnCount(1);
	InitTable();
	m_pGridCtrl->AutoSize();

	int nb = m_pGridCtrl->GetRowHeight(1);
	for (int i=1;i<m_pGridCtrl->GetRowCount();i++)
	{
		m_pGridCtrl->SetRowHeight(i,nb-3);
	}
}

void CDATableCategory::OnSortNum()
{
	if (!m_bSortedAlpha) return;
	m_bSortedAlpha = !m_bSortedAlpha;
	m_pGridCtrl->SetRowCount(1);
	m_pGridCtrl->SetRowCount(300);
	m_pGridCtrl->SetColumnCount(1);
	InitTable();
	m_pGridCtrl->AutoSize();

	int nb = m_pGridCtrl->GetRowHeight(1);
	for (int i=1;i<m_pGridCtrl->GetRowCount();i++)
	{
		m_pGridCtrl->SetRowHeight(i,nb-3);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDASummary construction/destruction
IMPLEMENT_DYNCREATE(CDATableInformation, CDATableERs)

CDATableInformation::CDATableInformation()
{
}

void CDATableInformation::InitTable()
{
	m_pGridCtrl->SetColumnCount(3);
	m_pGridCtrl->SetFixedColumnCount(1);

	CDADocument *pDoc = GetDocument();

	int nRow = 2;
	int nCol = 5;

	CString mstr[]={
		_T("Unit"),
		_T("E.R."),
		_T("Length")
	};

	for (int i=0;i<m_pGridCtrl->GetColumnCount();i++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.row = 0;
		Item.col = i;
		Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
		Item.strText.Format(_T("%s"),mstr[i]);
		m_pGridCtrl->SetItem(&Item);
	}

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.row = 1;
	Item.col = 1;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
	Item.nFormat = DT_LEFT|DT_WORDBREAK;
	Item.strText.Format(_T("Session"));
	m_pGridCtrl->SetItem(&Item);
	for (int r=0;r<m_pGridCtrl->GetColumnCount();r++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_BKCLR;
		Item.row = 1;
		Item.col = r;
		Item.crBkClr = RGB(128,128,255);
		m_pGridCtrl->SetItem(&Item);
	}

	CStringArray m_strTableInfo;
	int nInfoCol=0;

	for (i=0;i<pDoc->m_lScenario.GetSize();i++)
	{
		CLogScenario *pScen = (CLogScenario *)pDoc->m_lScenario.GetAt(i);
		if (!pScen) continue;

		GV_ITEM Item;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.row = nRow;
		Item.col = 1;
		Item.nFormat = DT_CENTER|DT_WORDBREAK;
		Item.strText.Format(_T("Scenario %d"),i);

		m_pGridCtrl->SetItem(&Item);
		for (int r=0;r<m_pGridCtrl->GetColumnCount();r++)
		{
			GV_ITEM Item;
			Item.mask = GVIF_BKCLR;
			Item.row = nRow;
			Item.col = r;
			Item.crBkClr = RGB(93,195,93);
			m_pGridCtrl->SetItem(&Item);
		}
		nRow++;

		for (int j=0;j<pScen->m_lUnits.GetSize();j++)
		{
			CLogUnit *pUnit = (CLogUnit *)pScen->m_lUnits.GetAt(j);
			if (!pUnit) continue;

			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = nRow;
			Item.col = 0;
			Item.nFormat = DT_LEFT|DT_WORDBREAK;
			Item.strText.Format(_T("Unit %d"),j);
			m_pGridCtrl->SetItem(&Item);

			for (int r=0;r<m_pGridCtrl->GetColumnCount();r++)
			{
				GV_ITEM Item;
				Item.mask = GVIF_BKCLR;
				Item.row = nRow;
				Item.col = r;
				Item.crBkClr = RGB(180,255,180);
				m_pGridCtrl->SetItem(&Item);
			}

			CTimeSpan nd= pUnit->n_nTimeStop-pUnit->n_nTime;

			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = nRow;
			Item.col = 2;
			Item.nFormat = DT_RIGHT|DT_WORDBREAK;
			Item.strText.Format(_T("%.2d:%.2d"),nd.GetMinutes(),nd.GetSeconds());

			m_pGridCtrl->SetItem(&Item);
			nRow++;

			int nUnitERStart = nRow;
			for (int k=0;k<pUnit->m_cERs.GetSize();k++)
			{
				CLogER pER = pUnit->m_cERs.GetAt(k);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 1;
				Item.nFormat = DT_LEFT|DT_WORDBREAK;
				Item.strText.Format(_T("%s"),pER.m_nERName);

				m_pGridCtrl->SetItem(&Item);

				CTimeSpan nTot(0,0,0,0);
				CTime nStart;
		
				int nb = pER.m_nERTime.GetSize();
				if (nb%2!=1) for (int l=0;l<pER.m_nERTime.GetSize();l+=2)
				{
					CTime ndd = pER.m_nERTime.GetAt(l);
					if (!l)
						nStart = ndd;
					CTime ndd2 = pER.m_nERTime.GetAt(l+1);

					CTimeSpan nST = ndd-pUnit->n_nTime;
					CTimeSpan nDD = ndd2-ndd;
					nTot += nDD;
				}
				if (pER.m_bStartUp)
				{
					GV_ITEM Item;
					Item.mask = GVIF_IMAGE;
					Item.row = nRow;
					Item.col = 0;
					Item.iImage = 0;
					m_pGridCtrl->SetItem(&Item);
				}

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 2;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%.2d:%.2d"),nTot.GetMinutes(),nTot.GetSeconds());
				m_pGridCtrl->SetItem(&Item);

				int nbCER = pER.m_strCrossER.GetSize();
				for (int j=0;j<nbCER;j++)
				{

					CLogER::CStrArray pAR = pER.m_strCrossER.GetAt(j);
					for (int l=0;l<pAR.GetSize();l++)
					{
						CString strF = pAR.GetAt(l);
						int nlim = strF.Find(_T("\t"));
						CString strCat = strF.Left(nlim);
						CString strVal = strF;
						strVal.Delete(0,nlim+1);

						BOOL bFound=FALSE;
						for (int h=0;h<m_strTableInfo.GetSize();h++)
						{
							CString strTable = m_strTableInfo.GetAt(h);
							if (strCat==strTable)
							{
								bFound = TRUE;
								break;
							}
						}
						int npos=-1;
						if (!bFound)
						{
							npos = m_strTableInfo.Add(strCat);
							m_pGridCtrl->SetColumnCount(3+npos+1);
							Item.mask = GVIF_TEXT|GVIF_FORMAT;
							Item.row = 0;
							Item.col = 2+npos+1;
							Item.nFormat = DT_RIGHT|DT_WORDBREAK;
							Item.strText.Format(_T("%s"),strCat);
							m_pGridCtrl->SetItem(&Item);
						}
						else
							npos = h;

						int nItem = strVal.Find(_T(" "));
						int nDeb = atoi(strVal.Left(nItem));
						CString strG = strVal;
						strG.Delete(0,nItem+1);
						int nFin = atoi(strG);

						//npos = m_strTableInfo.Add(strCat);
						//m_pGridCtrl->SetColumnCount(3+npos+1);
						Item.mask = GVIF_TEXT|GVIF_FORMAT;
						Item.row = nRow;
						Item.col = 2+npos+1;
						Item.nFormat = DT_RIGHT|DT_WORDBREAK;

						CString strCell;
						strCell.Format(_T("%d"),nFin-nDeb);
						m_pGridCtrl->RedrawCell(2+npos+1);
						CString strold = m_pGridCtrl->GetItemText(nRow,2+npos+1);
						if (strold.IsEmpty())
							Item.strText.Format(_T("%s"),strCell);
						else
							Item.strText.Format(_T("%s+%s"),strold,strCell);
						m_pGridCtrl->SetItem(&Item);

					}
/*					nInfoCol = max(nInfoCol,4+l);
					m_pGridCtrl->SetColumnCount(nInfoCol);

					CString strF = pAR.GetAt(l);
	
					Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 4+l-1;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				if (j)
				{
					m_pGridCtrl->RedrawCell(nRow,4+l-1);
					Item.strText.Format(_T("%s\t%s"),m_pGridCtrl->GetItemText(nRow,4+l-1),strF);
				}
				else
					Item.strText.Format(_T("%s"),strF);
				m_pGridCtrl->SetItem(&Item);


				}*/
				}

/*				int nInfo = pER.m_strInfo.GetSize();
				for (int l=0;l<nInfo;l++)
				{
					CString strInfo = pER.m_strInfo.GetAt(l);
					int nnnn = strInfo.Find(_T("--"));
					CString strOut = strInfo.Left(nnnn);
					strInfo.Delete(0,nnnn+2);
					CString strExp = strInfo;
					BOOL bFound = FALSE;
					for (int m=0;m<m_strTableInfo.GetSize();m++)
					{
						CString strCol = m_strTableInfo.GetAt(m);
						if (strCol==strOut)
						{
							bFound = TRUE;

							m_pGridCtrl->RedrawCell(nRow,3+m);
							CString strff = m_pGridCtrl->GetItemText(nRow,3+m);

							Item.mask = GVIF_TEXT|GVIF_FORMAT;
							Item.row = nRow;
							Item.col = 3+m;
							Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
							if (strff.IsEmpty())
								Item.strText.Format(_T("%s"),strExp);
							else
								Item.strText.Format(_T("%s"),strff+_T("/")+strExp);
							m_pGridCtrl->SetItem(&Item);
							break;
						}

					}
					if (!bFound)
					{
						m_strTableInfo.Add(strOut);
						nInfoCol++;
						m_pGridCtrl->SetColumnCount(3+nInfoCol);
						Item.mask = GVIF_TEXT|GVIF_FORMAT;
						Item.row = 0;
						Item.col = 2+nInfoCol;
						Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
						Item.strText.Format(_T("%s"),strOut);
						m_pGridCtrl->SetItem(&Item);

						Item.mask = GVIF_TEXT|GVIF_FORMAT;
						Item.row = nRow;
						Item.col = 2+nInfoCol;
						Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
						Item.strText.Format(_T("%s"),strExp);
						m_pGridCtrl->SetItem(&Item);
					}
				}*/

				nRow++;
			}
		}
	}
	m_pGridCtrl->SetRowCount(nRow);
	m_pGridCtrl->SetFixedColumnCount(3);
}


/////////////////////////////////////////////////////////////////////////////
// CDASummary construction/destruction
IMPLEMENT_DYNCREATE(CDATableSwitchER, CDATableERs)

CDATableSwitchER::CDATableSwitchER()
{
}

void CDATableSwitchER::InitTable()
{
	m_pGridCtrl->SetColumnCount(4);
	m_pGridCtrl->SetFixedColumnCount(2);

	CDADocument *pDoc = GetDocument();

	int nRow = 2;
	int nCol = 5;

	CString mstr[]={
		_T("Unit"),
		_T("E.R."),
		_T("Start"),
		_T("Length")
	};

	for (int i=0;i<m_pGridCtrl->GetColumnCount();i++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.row = 0;
		Item.col = i;
		Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
		Item.strText.Format(_T("%s"),mstr[i]);
		m_pGridCtrl->SetItem(&Item);
	}

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.row = 1;
	Item.col = 1;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
	Item.nFormat = DT_LEFT|DT_WORDBREAK;
	Item.strText.Format(_T("Session"));
	m_pGridCtrl->SetItem(&Item);
	for (int r=0;r<m_pGridCtrl->GetColumnCount();r++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_BKCLR;
		Item.row = 1;
		Item.col = r;
		Item.crBkClr = RGB(128,128,255);
		m_pGridCtrl->SetItem(&Item);
	}

	CStringArray m_strTableInfo;
	int nInfoCol=0;

	for (i=0;i<pDoc->m_lScenario.GetSize();i++)
	{
		CLogScenario *pScen = (CLogScenario *)pDoc->m_lScenario.GetAt(i);
		if (!pScen) continue;

		GV_ITEM Item;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.row = nRow;
		Item.col = 1;
		Item.nFormat = DT_CENTER|DT_WORDBREAK;
		Item.strText.Format(_T("Scenario %d"),i);

		m_pGridCtrl->SetItem(&Item);
		for (int r=0;r<m_pGridCtrl->GetColumnCount();r++)
		{
			GV_ITEM Item;
			Item.mask = GVIF_BKCLR;
			Item.row = nRow;
			Item.col = r;
			Item.crBkClr = RGB(93,195,93);
			m_pGridCtrl->SetItem(&Item);
		}
		nRow++;

		for (int j=0;j<pScen->m_lUnits.GetSize();j++)
		{
			CLogUnit *pUnit = (CLogUnit *)pScen->m_lUnits.GetAt(j);
			if (!pUnit) continue;

			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = nRow;
			Item.col = 0;
			Item.nFormat = DT_LEFT|DT_WORDBREAK;
			Item.strText.Format(_T("Unit %d"),j);
			m_pGridCtrl->SetItem(&Item);

			for (int r=0;r<m_pGridCtrl->GetColumnCount();r++)
			{
				GV_ITEM Item;
				Item.mask = GVIF_BKCLR;
				Item.row = nRow;
				Item.col = r;
				Item.crBkClr = RGB(180,255,180);
				m_pGridCtrl->SetItem(&Item);
			}

			CTimeSpan nd= pUnit->n_nTimeStop-pUnit->n_nTime;

			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = nRow;
			Item.col = 2;
			Item.nFormat = DT_RIGHT|DT_WORDBREAK;
			Item.strText.Format(_T("%.2d:%.2d"),nd.GetMinutes(),nd.GetSeconds());

			m_pGridCtrl->SetItem(&Item);

			nRow++;


			int nStartRow = nRow;
			CTimeSpan nOldTime(0,0,0,0);
			for (int k=0;k<pUnit->m_cActivID.GetSize();k++)
			{
				int nbID = pUnit->m_cActivID.GetAt(k);
				CTime pT1 = pUnit->m_cActivTime.GetAt(k);
				CLogER pER = pUnit->m_cERs.GetAt(nbID);

				
				CTimeSpan nST = pT1-pUnit->n_nTime;

				CTimeSpan nd2= nST - nOldTime;

				nOldTime = nST;

				//if (nd2.GetTotalSeconds() >=1)
				{

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 1;
				Item.nFormat = DT_LEFT|DT_WORDBREAK;
				Item.strText.Format(_T("%s"),pER.m_nERName);

				m_pGridCtrl->SetItem(&Item);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 2;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%.2d:%.2d"),nST.GetMinutes(),nST.GetSeconds());
				m_pGridCtrl->SetItem(&Item);

				if (nStartRow != nRow)
				{
					Item.mask = GVIF_TEXT|GVIF_FORMAT;
					Item.row = nRow-1;
					Item.col = 3;
					Item.nFormat = DT_RIGHT|DT_WORDBREAK;
					Item.strText.Format(_T("%.2d:%.2d"),nd2.GetMinutes(),nd2.GetSeconds());

					m_pGridCtrl->SetItem(&Item);
				}


				nRow++;
				}
			}

/*			int nUnitERStart = nRow;
			for (int k=0;k<pUnit->m_cERs.GetSize();k++)
			{
				CLogER pER = pUnit->m_cERs.GetAt(k);

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 1;
				Item.nFormat = DT_LEFT|DT_WORDBREAK;
				Item.strText.Format(_T("%s"),pER.m_nERName);

				m_pGridCtrl->SetItem(&Item);

				CTimeSpan nTot(0,0,0,0);
				CTime nStart;
		
				int nb = pER.m_nERTime.GetSize();
				if (nb%2!=1) for (int l=0;l<pER.m_nERTime.GetSize();l+=2)
				{
					CTime ndd = pER.m_nERTime.GetAt(l);
					if (!l)
						nStart = ndd;
					CTime ndd2 = pER.m_nERTime.GetAt(l+1);

					CTimeSpan nST = ndd-pUnit->n_nTime;
					CTimeSpan nDD = ndd2-ndd;
					nTot += nDD;
				}
				if (pER.m_bStartUp)
				{
					GV_ITEM Item;
					Item.mask = GVIF_IMAGE;
					Item.row = nRow;
					Item.col = 0;
					Item.iImage = 0;
					m_pGridCtrl->SetItem(&Item);
				}

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 2;
				Item.nFormat = DT_RIGHT|DT_WORDBREAK;
				Item.strText.Format(_T("%.2d:%.2d"),nTot.GetMinutes(),nTot.GetSeconds());
				m_pGridCtrl->SetItem(&Item);


				nRow++;
			}*/
		}
	}
	m_pGridCtrl->SetRowCount(nRow);
}

/////////////////////////////////////////////////////////////////////////////
// CDATableRunReview construction/destruction
IMPLEMENT_DYNCREATE(CDATableRunReview, CDATableERs)

CDATableRunReview::CDATableRunReview()
{
}

void CDATableRunReview::InitTable()
{
	m_pGridCtrl->SetColumnCount(15);
	m_pGridCtrl->SetFixedColumnCount(1);

	m_pGridCtrl->SetRowCount(500);
	CDADocument *pDoc = GetDocument();

	int nRow = 2;
	int nCol = 3;

	CString mstr[]={
		_T("Unit"),
		_T("Controller"),
		_T("Time"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs"),
		_T("ERs")
	};

	for (int i=0;i<m_pGridCtrl->GetColumnCount();i++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.row = 0;
		Item.col = i;
		Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
		Item.strText.Format(_T("%s"),mstr[i]);
		m_pGridCtrl->SetItem(&Item);
	}

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.row = 1;
	Item.col = 0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK;
	Item.nFormat = DT_LEFT|DT_WORDBREAK;
	Item.strText.Format(_T("Session"));
	m_pGridCtrl->SetItem(&Item);
	for (int r=0;r<m_pGridCtrl->GetColumnCount();r++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_BKCLR;
		Item.row = 1;
		Item.col = r;
		Item.crBkClr = RGB(128,128,255);
		m_pGridCtrl->SetItem(&Item);
	}

	for (i=0;i<pDoc->m_lScenario.GetSize();i++)
	{
		CLogScenario *pScen = (CLogScenario *)pDoc->m_lScenario.GetAt(i);
		if (!pScen) continue;

		GV_ITEM Item;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.row = nRow;
		Item.col = 0;
		Item.nFormat = DT_CENTER|DT_WORDBREAK;
		Item.strText.Format(_T("Scenario %d"),i);

		m_pGridCtrl->SetItem(&Item);
		for (int r=0;r<m_pGridCtrl->GetColumnCount();r++)
		{
			GV_ITEM Item;
			Item.mask = GVIF_BKCLR;
			Item.row = nRow;
			Item.col = r;
			Item.crBkClr = RGB(93,195,93);
			m_pGridCtrl->SetItem(&Item);
		}
		nRow++;

		for (int j=0;j<pScen->m_lUnits.GetSize();j++)
		{
			CLogUnit *pUnit = (CLogUnit *)pScen->m_lUnits.GetAt(j);
			if (!pUnit) continue;

			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = nRow;
			Item.col = 0;
			Item.nFormat = DT_LEFT|DT_WORDBREAK;
			Item.strText.Format(_T("Unit %d"),j);
			m_pGridCtrl->SetItem(&Item);

			for (int r=0;r<m_pGridCtrl->GetColumnCount();r++)
			{
				GV_ITEM Item;
				Item.mask = GVIF_BKCLR;
				Item.row = nRow;
				Item.col = r;
				Item.crBkClr = RGB(180,255,180);
				m_pGridCtrl->SetItem(&Item);
			}
			nRow++;

			int nbAct = pUnit->m_cActions.GetSize();
			for (r=0;r<nbAct;r++)
			{
				CLogAction pAct = pUnit->m_cActions.GetAt(r);
				if (pAct.m_nType < LOG_SHOW_MAPREL) continue;


				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 1;
				Item.nFormat = DT_LEFT|DT_WORDBREAK;

				switch (pAct.m_nType){
				case LOG_SHOW_MAPREL:
					Item.strText = _T("MAP REL.");
					break;
				case LOG_SHOW_RUN:
					Item.strText = _T("RUN");
					break;
				case LOG_SHOW_REVIEW:
					{
						if (pAct.m_nSubType==1)
							Item.strText = _T("REVIEW NEXT");
						else if (pAct.m_nSubType==2)
							Item.strText = _T("REVIEW PREV");
						else if (pAct.m_nSubType==3)
							Item.strText = _T("REVIEW FORW");
						else if (pAct.m_nSubType==4)
							Item.strText = _T("REVIEW BACK");
						else 						
							Item.strText = _T("REVIEW");

					}
					break;
				case LOG_SHOW_INITAT:
					Item.strText = _T("INITAT");
					break;
				case LOG_SHOW_STOPAT:
					Item.strText = _T("STOPAT");
					break;
				default:
					Item.strText = _T("");
					break;
				}
				//Item.strText.Format(_T("%d"),pAct.m_nType);
				m_pGridCtrl->SetItem(&Item);

				CTime mtAction = pAct.m_tAction;
				CTimeSpan nST = mtAction-pUnit->n_nTime;
				LONG nl1 = nST.GetTotalSeconds();

				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = 2;
				Item.nFormat = DT_LEFT|DT_WORDBREAK;
				//Item.strText.Format(_T("%d"),nl1);
				Item.strText.Format(_T("%.2d:%.2d"),nST.GetMinutes(),nST.GetSeconds());
				BOOL bres = m_pGridCtrl->SetItem(&Item);


				int nbER = pUnit->m_cERs.GetSize();
				int nlocC = 0;
				for (int r=0;r<nbER;r++)
				{
					CLogER pER = pUnit->m_cERs.GetAt(r);


					int nS = pER.m_cCount.GetSize();
					if (nS && nS>nl1)
					{
						int nn = pER.m_cCount.GetAt(nl1);
						if (nn)
						{
							Item.mask = GVIF_TEXT|GVIF_FORMAT;
							Item.row = nRow;
							Item.col = 3+nlocC++;
							Item.nFormat = DT_LEFT|DT_WORDBREAK;
							//Item.strText.Format(_T("%d"),nl1);
							Item.strText.Format(_T("%s"),pER.m_nERName);
							if (pER.m_bStartUp)
							{
								Item.crFgClr = RGB(255,0,0);
								Item.mask |= GVIF_TEXT|GVIF_FGCLR;
							}
							bres = m_pGridCtrl->SetItem(&Item);
							nCol = max(nCol,Item.col+1);

						}
					}

				}



				nRow++;
			}

		}
	}
	m_pGridCtrl->SetColumnCount(nCol);
	m_pGridCtrl->SetRowCount(nRow);
}
