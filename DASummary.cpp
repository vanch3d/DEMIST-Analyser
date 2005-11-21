// DASummary.cpp : implementation file
//

#include "stdafx.h"
#include "DEMIST Analyser.h"

#include "DADoc.h"

#include "DASummary.h"
#include "MemDC.h"

#include "LogUnit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDASummary

IMPLEMENT_DYNCREATE(CDASummary, CScrollView)

BEGIN_MESSAGE_MAP(CDASummary, CScrollView)
	//{{AFX_MSG_MAP(CDASummary)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_COMMAND(ID_SUMMARY_ACTIV, OnSummaryActiv)
	ON_COMMAND(ID_SUMMARY_ZMOINS, OnSummaryZmoins)
	ON_COMMAND(ID_SUMMARY_ZPLUS, OnSummaryZplus)
	ON_UPDATE_COMMAND_UI(ID_SUMMARY_ZPLUS, OnUpdateSummaryZoom)
	ON_WM_LBUTTONDBLCLK()
	ON_UPDATE_COMMAND_UI(ID_SUMMARY_ZMOINS, OnUpdateSummaryZoom)
	ON_UPDATE_COMMAND_UI(ID_SUMMARY_ACTIV, OnUpdateSummary)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SUMMARY_ACTION, ID_SUMMARY_RUN, OnUpdateSummary)
	ON_COMMAND_RANGE(ID_SUMMARY_ACTION, ID_SUMMARY_RUN, OnSummaryAction)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDASummary construction/destruction

CDASummary::CDASummary()
{
	m_bFirst=TRUE;
	m_bResize = TRUE;
	m_nScale = 1;
	m_bShowActiv = FALSE;
	m_bShowAction = 0;

	m_rUnitPos.RemoveAll();
	m_nUnitSel = -1;

}

CDASummary::~CDASummary()
{
}

BOOL CDASummary::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CScrollView::PreCreateWindow(cs);
	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CDASummary drawing

BOOL CDASummary::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return FALSE;//CScrollView::OnEraseBkgnd(pDC);
}

CRect CDASummary::DrawScenario(CDC* pDC,CPoint pt,CLogScenario *pScen,int nScen)
{ 
	CRect mrect;
	mrect.SetRectEmpty();

	if (!pScen) return mrect;

	int nStart = pScen->m_nStart;
	int nEnd = pScen->m_nStart;
	CTime nTime = pScen->n_nTime;
	CString strScen;

	mrect = CRect(pt,pt);
	//strScen.Format(_T("%.3d\tScenario %d :"),nStart,nScen);
	strScen.Format(_T("Scenario %d :"),nScen);
	pDC->DrawText(strScen,mrect,DT_CALCRECT|DT_EXPANDTABS);
	pDC->DrawText(strScen,mrect,DT_EXPANDTABS);

	CPoint nPt(mrect.left,mrect.bottom);

	for (int j=0;j<pScen->m_lUnits.GetSize();j++)
	{
		CLogUnit *pUnit = (CLogUnit *)pScen->m_lUnits.GetAt(j);
		if (!pUnit) continue;

		CRect rUnit = DrawUnit(pDC,nPt,pUnit,j);

		nPt = CPoint(rUnit.left,rUnit.bottom);
		mrect |= rUnit;

/*		for (int k=1;k<=5;k++)
		{
			CRect ttt(nPt,nPt);
			CString strScen;
			strScen.Format(_T("%d"),k);
			pDC->DrawText(strScen,ttt,DT_CALCRECT|DT_EXPANDTABS);
			pDC->DrawText(strScen,ttt,DT_EXPANDTABS);

			//CRect ttttt = rUnit;
	
			CTimeSpan nDur = pUnit->n_nTimeStop-pUnit->n_nTime;
			int nDDur = nDur.GetTotalSeconds();
			LONG nl = m_nScale*nDur.GetTotalSeconds();

			int ndX = rUnit.Height() / pUnit->m_cERs.GetSize();
	//		CRect ttttt(m_rectLimit.right+10,rUnit.bottom+(k-1)*ndX,m_rectLimit.right+10+nl,
	//			rUnit.bottom+(k)*ndX);
			CRect ttttt(m_rectLimit.right+10,rUnit.bottom,m_rectLimit.right+10,
				rUnit.bottom);

			int nCnt = pUnit->m_nCount.GetSize();
			for (int z=0;z<nCnt;z++)
			{
				CRect yt = ttttt;
				yt.bottom += ndX*(pUnit->m_nCount.GetAt(z));
				yt.left += m_nScale*z;
				yt.right += m_nScale*(z)+1;
				pDC->Rectangle(yt);
			}

	//		pDC->Rectangle(ttttt);

			mrect |= ttt;
			nPt = CPoint(mrect.left,mrect.bottom);



		}*/
	}


	return mrect;
}

CRect CDASummary::DrawUnit(CDC* pDC,CPoint pt,CLogUnit *pUnit,int nScen)
{
	CRect mrect;
	mrect.SetRectEmpty();

	if (!pUnit) return mrect;

	int nStart = pUnit->m_nStart;

	mrect = CRect(pt,pt);
	CString strScen;
//	strScen.Format(_T("\n%.3d\tUnit %d (%d:%d:%d / %d:%d:%d)"),nStart,nScen,
	strScen.Format(_T("\nUnit %d (%d:%d:%d / %d:%d:%d)"),nScen,
		pUnit->n_nTime.GetHour(),pUnit->n_nTime.GetMinute(),pUnit->n_nTime.GetSecond(),
		pUnit->n_nTimeStop.GetHour(),pUnit->n_nTimeStop.GetMinute(),pUnit->n_nTimeStop.GetSecond()		
		);

	pDC->DrawText(strScen,mrect,DT_CALCRECT|DT_EXPANDTABS);
	pDC->DrawText(strScen,mrect,DT_EXPANDTABS);

	CPoint nPt(mrect.left,mrect.bottom);
	CPoint nPt2(mrect.left,mrect.bottom);

	CRect rER;
	rER.SetRectEmpty();

	for (int j=0;j<pUnit->m_cERs.GetSize();j++)
	{
		CLogER pER = pUnit->m_cERs.GetAt(j);

		CRect rUnit = DrawER(pDC,nPt,&pER);

		nPt = CPoint(rUnit.left,rUnit.bottom);
		rER   |= rUnit;
		mrect |= rUnit;
	}
	if (m_bFirst)
	{
		return mrect;
	}

	int ndX = rER.Height() / pUnit->m_cERs.GetSize();

	CTimeSpan nDur = pUnit->n_nTimeStop-pUnit->n_nTime;
	int nDDur = nDur.GetTotalSeconds();
	LONG nl = m_nScale*nDur.GetTotalSeconds();

	nPt2.x = m_rectLimit.right+10;

	rER.left = nPt2.x;
	rER.right = nPt2.x+ nl;

	pUnit->m_rSumm = rER;
	
	CPen mPen(PS_INSIDEFRAME,1,RGB(192,192,192));
	CBrush mBrush(RGB(240,240,240));
	CPen *oldP = pDC->SelectObject(&mPen);
	CBrush *oldB = pDC->SelectObject(&mBrush);
	pDC->Rectangle(rER);
	pDC->SelectObject(oldB);
	pDC->SelectObject(oldP);

	int nLine = nl / (m_nScale*20);

	for (int jj=0;jj<=nLine;jj++)
	{
		
		CPen mPen(PS_INSIDEFRAME,(jj%3==0) ? 2 : 1,RGB(192,192,192));
		CPen *oldP = pDC->SelectObject(&mPen);
		pDC->MoveTo(rER.left+jj*(m_nScale*20),rER.top);
		pDC->LineTo(rER.left+jj*(m_nScale*20),rER.bottom);
		pDC->SelectObject(oldP);


	}



	mrect |= rER;

	for (j=0;j<pUnit->m_cERs.GetSize();j++)
	{
		CLogER pER = pUnit->m_cERs.GetAt(j);

		int nb = pER.m_nERTime.GetSize();
		if (nb%2==1) 
		{
			continue;
		}

		if (pER.m_bStartUp)
		{
			CPoint pt[]={
				CPoint(rER.left-6,rER.top+j*ndX+3),
				CPoint(rER.left-6,rER.top+(j+1)*ndX-3),
				CPoint(rER.left-2,rER.top+j*ndX+ndX/2),
			};

			CPen mPen(PS_SOLID,1,RGB(128,0,0));
			CBrush mBr(RGB(128,0,0));
			CPen *oldP = pDC->SelectObject(&mPen);
			CBrush  *oldB = pDC->SelectObject(&mBr);
			pDC->Polygon(pt,3);
			pDC->SelectObject(oldB);
			pDC->SelectObject(oldP);
		}
			
		for (int k=0;k<nb;k+=2)
		{
			CTime ndd = pER.m_nERTime.GetAt(k);
			CTime ndd2 = pER.m_nERTime.GetAt(k+1);

			CTimeSpan nST = ndd-pUnit->n_nTime;
			LONG nl1 = m_nScale*nST.GetTotalSeconds();

			CTimeSpan nDD = ndd2-ndd;
			LONG nl2 = m_nScale*nDD.GetTotalSeconds();

			CRect dfgf(rER.left+nl1,rER.top+j*ndX,rER.left+nl1+nl2,rER.top+(j+1)*ndX);
			dfgf.InflateRect(0,-3,0,-3);

			CPen mPen(PS_INSIDEFRAME,1,(j==0) ? RGB(0,206,0):RGB(255,128,111)); //RGB(128,128,255)
			CBrush mBrush((j==0) ? RGB(0,206,0):RGB(255,128,111));
			CPen *oldP = pDC->SelectObject(&mPen);
			CBrush *oldB = pDC->SelectObject(&mBrush);

			pDC->Rectangle(dfgf);
			pDC->SelectObject(oldB);
			pDC->SelectObject(oldP);

		}

		int nbA = pUnit->m_cActivID.GetSize();
		int nbB = pUnit->m_cActivTime.GetSize();
		if (nbA && nbB && m_bShowActiv) 
		{
			CTime oldT = pUnit->m_cActivTime.GetAt(0);
			int oldIdx = pUnit->m_cActivID.GetAt(0);

			for (k=1;k<nbA;k++)
			{
				CTime newT= pUnit->m_cActivTime.GetAt(k);
				int newIdx= pUnit->m_cActivID.GetAt(k);

				CTimeSpan nST = oldT-pUnit->n_nTime;
				LONG nl1 = m_nScale*nST.GetTotalSeconds();
	
				CTimeSpan nDD = newT-pUnit->n_nTime;
				LONG nl2 = m_nScale*nDD.GetTotalSeconds();
	
				CRect dfgf(rER.left+nl1,rER.top+oldIdx*ndX,rER.left+nl2,rER.top+(oldIdx+1)*ndX);
				dfgf.InflateRect(0,-3,0,-3);

				CPen mPen(PS_INSIDEFRAME,1,(oldIdx==0) ? RGB(170,255,170):RGB(255,200,200));
				CBrush mBrush((oldIdx==0) ? RGB(170,255,170):RGB(255,200,200));
				CPen *oldP = pDC->SelectObject(&mPen);
				CBrush *oldB = pDC->SelectObject(&mBrush);

				pDC->Rectangle(dfgf);
				pDC->SelectObject(oldB);
				pDC->SelectObject(oldP);

				oldT = newT;
				oldIdx = newIdx;
			}
		}

		
		nbA = pUnit->m_cActions.GetSize();

		if (m_bShowAction) for (k=0;k<nbA;k++)
		{
			CLogAction pAct = pUnit->m_cActions.GetAt(k);
			if (!(m_bShowAction & pAct.m_nType)) continue;

			CTime newT= pAct.m_tAction;
			int newIdx= pAct.m_nER;

			CTimeSpan nST = newT-pUnit->n_nTime;
			LONG nl1 = m_nScale*nST.GetTotalSeconds();

			CPoint pt(rER.left+nl1,rER.top+newIdx*ndX+ndX/2);
			CRect dfgf(pt,pt);
			dfgf.InflateRect(1,5,1,6);

			COLORREF mclr;
			if (pAct.m_nType == LOG_SHOW_EXPSET)
				mclr = RGB(0,0,255);
			else if (pAct.m_nType == LOG_SHOW_MAPREL)
				mclr = RGB(0,128,0);
			else if (pAct.m_nType == LOG_SHOW_HYP)
				mclr = RGB(128,64,64);
			else if (pAct.m_nType == LOG_SHOW_ACT)
				mclr = RGB(128,64,64);
			else //if (pAct.m_nType == LOG_SHOW_RUN)
				mclr = RGB(0,0,0);

			CPen mPen(PS_INSIDEFRAME,1,mclr);
			CBrush mBrush(mclr);
			CPen *oldP = pDC->SelectObject(&mPen);
			CBrush *oldB = pDC->SelectObject(&mBrush);

			pDC->Rectangle(dfgf);
			pDC->SelectObject(oldB);
			pDC->SelectObject(oldP);
		}


	}

	mrect.InflateRect(0,0,40,0);

	return mrect;
}

CRect CDASummary::DrawER(CDC* pDC,CPoint pt,CLogER *pER)
{
	CRect mrect;
	mrect.SetRectEmpty();

	if (!pER) return mrect;

	mrect = CRect(pt,pt);
	CString strScen;
//	strScen.Format(_T("\t\t%s"),pER->m_nERName);
	strScen.Format(_T("\t%s"),pER->m_nERName);

	pDC->DrawText(strScen,mrect,DT_CALCRECT|DT_EXPANDTABS);
	pDC->DrawText(strScen,mrect,DT_EXPANDTABS);

	return mrect;
}


void CDASummary::OnDraw(CDC* pDC)
{
	// TODO: add draw code here
	CDADocument *pDoc = GetDocument();

	CMemDC memDC(pDC);

	m_pFont.CreatePointFont(80,"Arial");
	CFont *pOldF = memDC.SelectObject(&m_pFont);

	int nMode = memDC.SetBkMode(TRANSPARENT);

	CRect mrect(10,10,10,10);
	if (m_bFirst) 
	{
		m_rectLimit.SetRectEmpty();

		for (int i=0;i<pDoc->m_lScenario.GetSize();i++)
		{
			CLogScenario *pScen = (CLogScenario *)pDoc->m_lScenario.GetAt(i);
			if (!pScen) continue;
			mrect |= DrawScenario(&memDC,CPoint(mrect.left,mrect.bottom),pScen,i);
		}

		m_rectLimit = mrect;
		m_bFirst = FALSE;
	}
	mrect = CRect(10,10,10,10);
	for (int i=0;i<pDoc->m_lScenario.GetSize();i++)
	{
		CLogScenario *pScen = (CLogScenario *)pDoc->m_lScenario.GetAt(i);
		if (!pScen) continue;
		mrect |= DrawScenario(&memDC,CPoint(mrect.left,mrect.bottom),pScen,i);
	}

	memDC.SetBkMode(nMode);
	memDC.SelectObject(pOldF);
	m_pFont.DeleteObject();

	if (m_bResize)
	{
		CSize ms= mrect.Size();
		ms.cx += 20;
		ms.cy += 20;
		SetScrollSizes(MM_TEXT, ms);
		m_bResize = FALSE;
		m_bFirst = FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDALogView printing

BOOL CDASummary::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	//return CScrollView::OnPreparePrinting(pInfo);
	return DoPreparePrinting(pInfo);
}

void CDASummary::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CDADocument *pDoc = GetDocument();
	int nPage = pDoc->m_lScenario.GetSize() / 2;
	if (pDoc->m_lScenario.GetSize() % 2 == 1) nPage++;
	pInfo->SetMaxPage(nPage);
	CScrollView::OnBeginPrinting(pDC, pInfo);
}

void CDASummary::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CScrollView::OnEndPrinting(pDC, pInfo);
}

void CDASummary::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDC *pCurrentDC = GetDC();        // will have dimensions of the client area
	if (!pCurrentDC) return;
	
	CSize PaperPixelsPerInch(pDC->GetDeviceCaps(LOGPIXELSX), pDC->GetDeviceCaps(LOGPIXELSY));
	CSize ScreenPixelsPerInch(pCurrentDC->GetDeviceCaps(LOGPIXELSX), pCurrentDC->GetDeviceCaps(LOGPIXELSY));
	CSize m_CharSize = pDC->GetTextExtent(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSATUVWXYZ"),52);
	m_CharSize.cx /= 52;
	
	// Get the page sizes (physical and logical)
	CSize m_PaperSize = CSize(pDC->GetDeviceCaps(HORZRES), pDC->GetDeviceCaps(VERTRES));
	CSize m_LogicalPageSize;
	m_LogicalPageSize.cx = 0.6 * ScreenPixelsPerInch.cx * m_PaperSize.cx / PaperPixelsPerInch.cx * 3 ;
	m_LogicalPageSize.cy = 0.6 * ScreenPixelsPerInch.cy * m_PaperSize.cy / PaperPixelsPerInch.cy * 3 ;

	pDC->SetMapMode(MM_ISOTROPIC);
	//pDC->SetWindowExt(CSize(1200,600));//m_DocSize);
	pDC->SetWindowExt(m_LogicalPageSize);
	pDC->SetViewportExt(pInfo->m_rectDraw.Width(),pInfo->m_rectDraw.Height());

	CPoint mp1 = pDC->GetViewportOrg();
	CPoint mp2 = pDC->GetWindowOrg();
	//COLORREF bcolor = ::GetSysColor(COLOR_WINDOW/*COLOR_3DFACE*/); 
	COLORREF bcolor = RGB(255,255,255);
	CBrush FixedBack(bcolor);
	CRect ClipRect;
	if (pDC->GetClipBox(ClipRect) != ERROR)
	{
		ClipRect.InflateRect(1, 1); // avoid rounding to nothing
		pDC->FillRect(ClipRect,&FixedBack);
	}

	CFont mTextFont;
	mTextFont.CreatePointFont (80, _T ("Arial"));

	CFont *oldF = NULL;
	oldF  = pDC->SelectObject(&mTextFont);

	CDADocument *pDoc = GetDocument();

	CMemDC memDC(pDC);

	BOOL bTT = pDC->IsPrinting();
	CSize ttt = GetTotalSize();

	pInfo->m_rectDraw.top    = 0;
	pInfo->m_rectDraw.left   = 0;
    pInfo->m_rectDraw.right  = m_LogicalPageSize.cx ;
    pInfo->m_rectDraw.bottom = 30;

	int nCurPage = (pInfo->m_nCurPage-1)*2;



	PrintHeader(&memDC, pInfo);

	int nMode = memDC.SetBkMode(TRANSPARENT);
	CRect mrect(10,10,10,10);
	for (int i=nCurPage;i<pDoc->m_lScenario.GetSize();i++)
	{
		if (i-nCurPage>=2) break;
		CLogScenario *pScen = (CLogScenario *)pDoc->m_lScenario.GetAt(i);
		if (!pScen) continue;
		mrect |= DrawScenario(&memDC,CPoint(mrect.left,mrect.bottom),pScen,i);
	}

    // Footer
    pInfo->m_rectDraw.bottom = 0.3*m_CharSize.cy;
    pDC->SetWindowOrg( 0,
        -m_LogicalPageSize.cy + 0.2*m_CharSize.cy);

	PrintFooter(&memDC, pInfo);
    pDC->SetWindowOrg(0,0);

	if (oldF) pDC->SelectObject(oldF);
}


void CDASummary::PrintHeader(CDC *pDC, CPrintInfo *pInfo)
{
	    // print App title on top right margin
    CString strRight;
    strRight.LoadString(AFX_IDS_APP_TITLE);

    // print parent window title in the centre (Gert Rijs)
    CString strCenter;
    CWnd *pParentWnd = GetParent();
    while (pParentWnd)
    {
        pParentWnd->GetWindowText(strCenter);
        if (strCenter.GetLength())  // can happen if it is a CView, CChildFrm has the title
            break;
        pParentWnd = pParentWnd->GetParent();
    }

    CFont   BoldFont;
    LOGFONT lf;

    //create bold font for header and footer
    // Create the printer font
    int nFontSize = -12;
    CString strFontName = "Arial";
    CFont m_PrinterFont;
	m_PrinterFont.CreateFont(nFontSize, 0,0,0, FW_NORMAL, 0,0,0, DEFAULT_CHARSET,
                             OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
                             DEFAULT_PITCH | FF_DONTCARE, strFontName);

    VERIFY(m_PrinterFont.GetLogFont(&lf));
    lf.lfWeight = FW_BOLD;
    VERIFY(BoldFont.CreateFontIndirect(&lf));

    CFont *pNormalFont = pDC->SelectObject(&BoldFont);
    int nPrevBkMode = pDC->SetBkMode(TRANSPARENT);

    CRect   rc(pInfo->m_rectDraw);
    if( !strCenter.IsEmpty() )
	{
        //pDC->DrawText( strCenter, &rc, DT_CALCRECT | DT_CENTER | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER);
        pDC->DrawText( strCenter, &rc, DT_CENTER | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER);
	}
    if( !strRight.IsEmpty() )
        pDC->DrawText( strRight, &rc, DT_RIGHT | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER);

    pDC->SetBkMode(nPrevBkMode);
    pDC->SelectObject(pNormalFont);
    BoldFont.DeleteObject();

    // draw ruled-line across top
    pDC->SelectStockObject(BLACK_PEN);
    pDC->MoveTo(rc.left, 30);
    pDC->LineTo(rc.right, 30);

    // Gap between header and column headings
    pDC->OffsetWindowOrg(0, -30);


}

void CDASummary::PrintFooter(CDC *pDC, CPrintInfo *pInfo)
{
	    // page numbering on left
    CString strLeft;
    strLeft.Format(_T("Page %d of %d"), pInfo->m_nCurPage, pInfo->GetMaxPage() );

    // date and time on the right
    CString strRight;
    COleDateTime t = COleDateTime::GetCurrentTime();
    strRight = t.Format(_T("%c"));
    
    CRect rc(pInfo->m_rectDraw);

    // draw ruled line on bottom
    pDC->SelectStockObject(BLACK_PEN);
    pDC->MoveTo(rc.left, rc.top);
    pDC->LineTo(rc.right, rc.top);

    CFont BoldFont;
    LOGFONT lf;

    //create bold font for header and footer
    int nFontSize = -12;
    CString strFontName = "Arial";
    CFont m_PrinterFont;
	m_PrinterFont.CreateFont(nFontSize, 0,0,0, FW_BOLD, 0,0,0, DEFAULT_CHARSET,
                             OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
                             DEFAULT_PITCH | FF_DONTCARE, strFontName);

    CFont *pNormalFont = pDC->SelectObject(&m_PrinterFont);
    int nPrevBkMode = pDC->SetBkMode(TRANSPARENT);

    // EFW - Bug fix - Force text color to black.  It doesn't always
    // get set to a printable color when it gets here.
    pDC->SetTextColor(RGB(0, 0, 0));

    if( !strLeft.IsEmpty() )
        pDC->DrawText( strLeft, &rc, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER);
    if( !strRight.IsEmpty() )
        pDC->DrawText( strRight, &rc, DT_RIGHT | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER);

    pDC->SetBkMode(nPrevBkMode);
    pDC->SelectObject(pNormalFont);
    BoldFont.DeleteObject();

}



/////////////////////////////////////////////////////////////////////////////
// CDASummary diagnostics

#ifdef _DEBUG
void CDASummary::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDASummary::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDADocument* CDASummary::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDADocument)));
	return (CDADocument*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDASummary message handlers

void CDASummary::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
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


	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	m_strSum.Empty();

	return;

	CDADocument *pDoc = GetDocument();

	for (int i=0;i<pDoc->m_lScenario.GetSize();i++)
	{

		CLogScenario *pScen = (CLogScenario *)pDoc->m_lScenario.GetAt(i);
		if (!pScen) continue;

		int nStart = pScen->m_nStart;

		CTime nTime = pScen->n_nTime;
		CString rrrr;
		for (int j=0;j<pScen->m_lUnits.GetSize();j++)
		{
			CLogUnit *pUnit = (CLogUnit *)pScen->m_lUnits.GetAt(j);
			if (!pUnit) continue;

			CTimeSpan nSpan = pUnit->n_nTime - nTime;
			CString dddd;
			int nnStart = pUnit->m_nStart;
			int nnEnd = pUnit->m_nEnd;
			dddd.Format(_T("%.3d\t\tUnit %d : \t\t%.2d:%.2d:%.2d (%d:%d)\r\n"),
				nnStart,j,
				pUnit->n_nTime.GetHour(),pUnit->n_nTime.GetMinute(),pUnit->n_nTime.GetSecond(),
				nSpan.GetMinutes(),nSpan.GetSeconds());
			rrrr += dddd;
			for (int k=0;k<pUnit->m_cERs.GetSize();k++)
			{
				CLogER pER = pUnit->m_cERs.GetAt(k);

				rrrr += pER.m_nERName;//.GetAt(k);//+ _T("\r\n");
				for (int ggg=0;ggg<pER.m_nERTime.GetSize();ggg++)
				{
					CTime nrt= pER.m_nERTime.GetAt(ggg);
					CString ttt;
					ttt.Format(_T("%d:%d.%d\t"),nrt.GetHour(),nrt.GetMinute(),nrt.GetSecond());
					rrrr += ttt;
				}
				rrrr += _T("\r\n");
			}
		}

		int nEnd = pScen->m_nEnd;

		CString dfff;
		dfff.Format(_T("%.3d\tScenario %d : \t\t\t%.2d:%.2d:%.2d\r\n%s\r\n\r\n"),
			nStart,i,
			pScen->n_nTime.GetHour(),pScen->n_nTime.GetMinute(),pScen->n_nTime.GetSecond(),
			rrrr);
		m_strSum += dfff;
	}
}

int CDASummary::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if (!m_cToolBar.CreateEx(GetParent(), TBSTYLE_FLAT | TBSTYLE_TOOLTIPS, 
			WS_CHILD | WS_VISIBLE | CBRS_TOP | 
			/*CBRS_GRIPPER | */CBRS_TOOLTIPS | CBRS_FLYBY | CCS_ADJUSTABLE,
			CRect(0, 0, 0, 0), 120) ||
		!m_cToolBar.LoadToolBar(IDR_SUMMARY_VIEW))
	{
		TRACE0("Failed to create toolbar1\n");
		return -1;      // fail to create  
	}
	
	return 0;
}

void CDASummary::OnSummaryActiv() 
{
	// TODO: Add your command handler code here
	m_bShowActiv = !m_bShowActiv;
	Invalidate();
	UpdateWindow();
}

void CDASummary::OnSummaryZmoins() 
{
	// TODO: Add your command handler code here
	m_nScale--;
	if (!m_nScale) m_nScale=1;
	m_bResize = TRUE;
	Invalidate();
	UpdateWindow();
}

void CDASummary::OnSummaryZplus() 
{
	// TODO: Add your command handler code here
	m_nScale++;
	if (m_nScale>=7) m_nScale=6;
	m_bResize = TRUE;
	Invalidate();
	UpdateWindow();
	
}

void CDASummary::OnUpdateSummaryZoom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	BOOL bEnab = FALSE;
	switch (pCmdUI->m_nID){
	case ID_SUMMARY_ZPLUS:
		bEnab = m_nScale<6;
		break;
	case ID_SUMMARY_ZMOINS:
		bEnab = m_nScale>1;
		break;
	}
	pCmdUI->Enable(bEnab);

}

void CDASummary::OnSummaryAction(UINT nID) 
{
	// TODO: Add your command handler code here
	switch (nID){
	case ID_SUMMARY_ACTION:
		if (m_bShowAction & LOG_SHOW_ACT) 
			m_bShowAction &= ~LOG_SHOW_ACT;
		else
			m_bShowAction |= LOG_SHOW_ACT;
		break;
	case ID_SUMMARY_HYP:
		if (m_bShowAction & LOG_SHOW_HYP) 
			m_bShowAction &= ~LOG_SHOW_HYP;
		else
			m_bShowAction |= LOG_SHOW_HYP;
		break;
	case ID_SUMMARY_REL:
		if (m_bShowAction & LOG_SHOW_MAPREL) 
			m_bShowAction &= ~LOG_SHOW_MAPREL;
		else
			m_bShowAction |= LOG_SHOW_MAPREL;
		break;
	case ID_SUMMARY_EXPSET:
		if (m_bShowAction & LOG_SHOW_EXPSET) 
			m_bShowAction &= ~LOG_SHOW_EXPSET;
		else
			m_bShowAction |= LOG_SHOW_EXPSET;
		break;
	case ID_SUMMARY_RUN:
		if (m_bShowAction & LOG_SHOW_RUN) 
			m_bShowAction &= ~LOG_SHOW_RUN;
		else
			m_bShowAction |= LOG_SHOW_RUN;
		break;
	}
	Invalidate();
	UpdateWindow();
	
}


void CDASummary::OnUpdateSummary(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	BOOL bCheck = FALSE;
	switch (pCmdUI->m_nID){
	case ID_SUMMARY_ACTIV:
		bCheck = m_bShowActiv;
		break;
	case ID_SUMMARY_ACTION:
		bCheck = (m_bShowAction & LOG_SHOW_ACT);
		break;
	case ID_SUMMARY_HYP:
		bCheck = (m_bShowAction & LOG_SHOW_HYP);
		break;
	case ID_SUMMARY_REL:
		bCheck = (m_bShowAction & LOG_SHOW_MAPREL);
		break;
	case ID_SUMMARY_EXPSET:
		bCheck = (m_bShowAction & LOG_SHOW_EXPSET);
		break;
	case ID_SUMMARY_RUN:
		bCheck = (m_bShowAction & LOG_SHOW_RUN);
		break;
	}
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(bCheck!=0);
}

void CDASummary::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDADocument *pDoc = GetDocument();

	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);


	for (int i=0;i<pDoc->m_lScenario.GetSize();i++)
	{
		CLogScenario *pScen = (CLogScenario *)pDoc->m_lScenario.GetAt(i);
		if (!pScen) continue;

		for (int j=0;j<pScen->m_lUnits.GetSize();j++)
		{
			CLogUnit *pUnit = (CLogUnit *)pScen->m_lUnits.GetAt(j);
			if (!pUnit) continue;

			
			CRect rER = pUnit->m_rSumm;
			int ndX = rER.Height() / pUnit->m_cERs.GetSize();

			int nb = pUnit->m_cActions.GetSize();
			if (m_bShowAction) for (int li=0;li<nb;li++)
			{
				CLogAction pAct = pUnit->m_cActions.GetAt(li);

				if (!(m_bShowAction & pAct.m_nType)) continue;
				CTime newT= pAct.m_tAction;
				int newIdx= pAct.m_nER;

				CTimeSpan nST = newT-pUnit->n_nTime;
				LONG nl1 = m_nScale*nST.GetTotalSeconds();

				CPoint pt(rER.left+nl1,rER.top+newIdx*ndX+ndX/2);
				CRect dfgf(pt,pt);
				dfgf.InflateRect(2,5,2,6);

				if (dfgf.PtInRect(point))
				{
					//CLogAction pAct = pUnit->m_cActions.GetAt(0);
					pDoc->UpdateAllViews(this,DOC_SELECT_LOG_LINE,(CObject*)pAct.m_nLog);
					CScrollView::OnLButtonDblClk(nFlags, point);
					return;
				}
			}

			for (int k=1;k<pUnit->m_cERs.GetSize();k++)
			{
				CLogER pER = pUnit->m_cERs.GetAt(k);

			}
		}
	}

	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CDASummary::OnEditCopy() 
{
	// TODO: Add your command handler code here
	CMetaFileDC * m_pMetaDC = new CMetaFileDC();
	m_pMetaDC->CreateEnhanced(GetDC(),NULL,NULL,"whatever");

	CClientDC clientDC(this) ; 
	m_pMetaDC->m_hAttribDC = clientDC.m_hDC; 

	//m_pMetaDC->SetMapMode(MM_TEXT   );
	//m_pMetaDC->SetViewportExt(m_pMetaDC->GetDeviceCaps(LOGPIXELSX),
	//	m_pMetaDC->GetDeviceCaps(LOGPIXELSY));
	//m_pMetaDC->SetWindowExt(100, -100);
	//draw meta file
	CDADocument *pDoc = GetDocument();

	m_pFont.CreatePointFont(80,"Arial");
	CFont *pOldF = m_pMetaDC->SelectObject(&m_pFont);

	int nMode = m_pMetaDC->SetBkMode(TRANSPARENT);

	CRect mrect(10,10,10,10);
	for (int i=0;i<pDoc->m_lScenario.GetSize();i++)
	{
		CLogScenario *pScen = (CLogScenario *)pDoc->m_lScenario.GetAt(i);
		if (!pScen) continue;
		mrect |= DrawScenario(m_pMetaDC,CPoint(mrect.left,mrect.bottom),pScen,i);
	}

	m_pMetaDC->SetBkMode(nMode);
	m_pMetaDC->SelectObject(pOldF);
	m_pFont.DeleteObject();


	//close meta file dc and prepare for clipboard;
	HENHMETAFILE hMF = m_pMetaDC->CloseEnhanced();

	//copy to clipboard
	OpenClipboard();
	EmptyClipboard();
	::SetClipboardData(CF_ENHMETAFILE,hMF);
	CloseClipboard();
	//DeleteMetaFile(hMF);
	delete m_pMetaDC;
	
}
