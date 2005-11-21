// DADoc.cpp : implementation of the CDADocument class
//

#include "stdafx.h"
#include "DEMIST Analyser.h"

#include "DADoc.h"
#include "LogUnit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDADocument

IMPLEMENT_DYNCREATE(CDADocument, CDocument)

BEGIN_MESSAGE_MAP(CDADocument, CDocument)
	//{{AFX_MSG_MAP(CDADocument)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDADocument construction/destruction

CString INFOTYPE[]={
	"Time",
	"Parameters",
	"Ini. Values",
	"Variables",
	"Aggregates",
	"Pop Change"
};

CString CATEGORY[][2]={
	{"Animated Weevil","Concrete Animation"},
	{"Chart: dN/dT","Chart"},
	{"Chart: N","Chart"},
	{"Chart: N & P","Chart"},
	{"Chart: N and  K","Chart"},
	{"Chart: N and  P","Chart"},
	{"Chart: N and P","Chart"},
	{"Chart: Tdouble","Chart"},
	{"Controller","Controller"},
	{"Definition Per Capita Growth Rate","Dynamic Equation"},
	{"Dynamic Equation","Dynamic Equation"},
	{"Dynamic Equation for Limited Growth","Dynamic Equation"},
	{"Dynamic Equations","Dynamic Equation"},
	{"Equation Doubling Time","Dynamic Equation"},
	{"Simple Equation","Dynamic Equation"},
	{"Graph: dN/dT V N","PhasePlot"},
	{"Graph: dN/dT v T","Graph v Time"},
	{"Graph: EnvRes v N","PhasePlot"},
	{"Graph: Ln(N) v T","Graph v Time"},
	{"Graph: Ln(N) V T","Graph v Time"},
	{"Graph: N & P v Time","Graph v Time"},
	{"Graph: N and P v Time (Safe)","Graph v Time"},
	{"Graph: N v (dN/dT)","PhasePlot"},
	{"Graph: N v dN/dT","PhasePlot"},
	{"Graph: N v T","Graph v Time"},
	{"Graph: N V T","Graph v Time"},
	{"Graph: N V T (Log Scale)","Graph v Time (log)"},
	{"Graph: N v Time","Graph v Time"},
	{"Graph: P & N v T (poach)","Graph v Time"},
	{"Graph: P and N v Time","Graph v Time"},
	{"Graph: Per Capita Growth Rate v N","PhasePlot"},
	{"Graph: per Capita Growth Rate V N","PhasePlot"},
	{"Graph:r v T","Graph v Time"},
	{"New Terms","Terms"},
	{"Phaseplot explanation","Concrete Animation"},
	{"Phaseplot N V P (poach)","PhasePlot"},
	{"Phaseplot: N v P (Safe)","PhasePlot"},
	{"Phaseplot: P v N","PhasePlot"},
	{"Phaseplot:N v P","PhasePlot"},
	{"Pie Chart","Pie Chart"},
	{"Population Density","Concrete Animation"},
	{"Table: dN/DT","Table"},
	{"Table: dN/dT and dP/dT","Table"},
	{"Table: N","Table"},
	{"Table: N & P","Table"},
	{"Table: N and dN/dT","Table"},
	{"Table: N and P","Table"},
	{"Value: N","Value"},
	{"Value: N & P","Value"},
	{"Value: N and P","Value"}
};

CDADocument::CDADocument()
{
	// TODO: add one-time construction code here

}

CDADocument::~CDADocument()
{
	for (int i=0;i<m_lScenario.GetSize();i++)
	{
		CLogScenario *pScen = (CLogScenario *) m_lScenario.GetAt(i);
		delete pScen;
	}
	m_lScenario.RemoveAll();
}

BOOL CDADocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDADocument serialization

void CDADocument::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	//((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CDADocument diagnostics

#ifdef _DEBUG
void CDADocument::AssertValid() const
{
	CDocument::AssertValid();
}

void CDADocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDADocument commands

CTime CDADocument::StringToTime(CString mstr)
{
	CTime nTime;

	int nb = mstr.Find(':');
	int nHour = atoi(mstr.Left(nb));
	mstr.Delete(0,nb+1);

	nb = mstr.Find(':');
	int nMin = atoi(mstr.Left(nb));
	mstr.Delete(0,nb+1);

	nb = mstr.Find('.');
	int nSec = atoi(mstr.Left(nb));
	mstr.Delete(0,nb+1);

	int nMSec = atoi(mstr);

	SYSTEMTIME  nttt = {2001,11,5,30,nHour,nMin,nSec,nMSec};

	nTime = CTime(nttt,0);

	return nTime;
}

BOOL CDADocument::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO: Add your specialized creation code here
	FILE *fp = fopen(lpszPathName,"r");
	if (!fp) return FALSE;

	int nFile = 0;
	int nString = 0;

	CLogScenario *pCurrScen = NULL;
	CLogUnit *pCurrUnit = NULL;

//	CMapStringToString m_strCatER;
//
//	for (int cc=0;cc<50;cc++)
//	{
//		m_strCatER.SetAt(CATEGORY[cc][0],CATEGORY[cc][1]);
//
//	}

//	POSITION pos = m_strCatER.GetStartPosition();
//	while (pos)
//	{
//		CString strKey,strValue;
//		m_strCatER.GetNextAssoc(pos,strKey,strValue);
//		int t;
//		t++;
//	}

	CStdioFile f(fp);
	CString mstr;
	BOOL ret = TRUE;
	while (ret)
	{
		ret = f.ReadString(mstr);
		m_strLog.Add(mstr);
		int nb = mstr.Find(_T("LAUNCH UNIT")) ;
		if (nb !=-1)
		{
			m_Units.Add(nString);
			int nDel = mstr.Find('\t');
			CString strTime = mstr.Left(nDel);

			CTime nTime = StringToTime(strTime);

			if (pCurrUnit)
			{
				pCurrUnit->m_nEnd = nString-1;
				if (pCurrUnit->m_nEnd==pCurrUnit->m_nStart)
				{
					delete pCurrUnit;
					pCurrUnit = NULL;
				}
				else
				{
					pCurrUnit->n_nTimeStop = nTime;
					pCurrScen->m_lUnits.Add(pCurrUnit);
					pCurrUnit->SetUseTable();
				}

			}


			pCurrUnit = new CLogUnit();
			pCurrUnit->m_nStart = nString;
			pCurrUnit->n_nTime = nTime;

			CString msss = mstr;
			msss.MakeReverse();
			msss.Delete(0);
			int rr = msss.Find('(');
			msss.Delete(0,rr+2);
			rr = msss.Find('\t');

			msss = msss.Left(rr);
			msss.MakeReverse();


			int mn = m_strScenarios.GetSize();
			if (!m_strScenariosDet[mn-1].GetSize())
			{
				FILE *fp2 = fopen(m_strScenarios.GetAt(mn-1),"r");
				if (fp2)
				{
					CStdioFile f2(fp2);
					CString mstr2;
					BOOL ret2 = TRUE;
					while (ret2)
					{
						ret2 = f2.ReadString(mstr2);
						if (ret2) m_strScenariosDet[mn-1].Add(mstr2);
					}
					f2.Close();
				}
			}

			BOOL bUnitFd = FALSE;
			int nSM = -1;
			for (int jj=0;jj<m_strScenariosDet[mn-1].GetSize();jj++)
			{
				CString strMod = m_strScenariosDet[mn-1].GetAt(jj);
				if (!bUnitFd)
				{
					int gg = strMod.Find(msss);
					int gg2 = strMod.Find(_T("(LU="));
					if (gg!=-1 && gg2!=-1)
					{
						bUnitFd = TRUE;
						strMod.Delete(0,1);
						int ntt = strMod.Find(_T("\t"));
						strMod.Delete(0,ntt+4);
						ntt = strMod.Find(_T("\t"));
						nSM = atoi(strMod.Left(ntt));

						ntt = strMod.Find(_T("\t"));
						strMod.Delete(0,ntt+1);
						ntt = strMod.Find(_T("\t"));
						strMod.Delete(0,ntt+1);
						ntt = strMod.Find(_T("="));
						strMod.Delete(0,ntt+1);

						int nMAX = atoi(strMod);

						pCurrUnit->m_nCMax = nMAX;


					}
				}
				else
				{
					int gg2 = strMod.Find(_T("(LU="));
					if (gg2!=-1) break;

					if (strMod.GetLength()>=3 && strMod[2] != '\t')
					{
						CString strER=strMod;
						strER.Delete(0,2);
						//strER.MakeReverse();
						int ggg= strER.Find('\t');
						CLogER pER;
						pER.m_nERName = strER.Left(ggg);
						strER.Delete(0,ggg+1);
						ggg= strER.Find('\t');
						pER.m_strCategory = strER.Left(ggg);
						//strER.Delete(0,1);
						ggg= strER.Find('\t');
						strER.Delete(0,ggg+1);
						//strER.MakeReverse();
						//strER.TrimLeft();
						//pER.m_nERName = strER;
						pER.m_bStartUp = atoi(strER);

						int oldjj= jj;

						BOOL bERFd = TRUE;
						for (int hh=jj+1;hh<m_strScenariosDet[mn-1].GetSize() && bERFd;hh++)
						{
							CString strMod2 = m_strScenariosDet[mn-1].GetAt(hh);
							int ngh = strMod2.Find(_T("\t\t\t"));
							//CHAR fffff = strMod[2];
							//if (strMod.GetLength()>=3 && strMod[2] == '\t')
							if (ngh !=-1)
							{
								CString strInf = strMod2;
								strInf.Delete(0,3);
								ngh = strInf.Find(_T("\t"));
								if (ngh!=-1)
								{
									strInf = strInf.Left(ngh);
									int ntt = strInf.Find(_T("--"));
									CString strC = strInf.Left(ntt);
									int nf = atoi(strC);
									if (nf!=-1)
									{
										/*for (int kk=0;kk<m_strScenariosDet[mn-1].GetSize();kk++)
										{
											CString strMod3 = m_strScenariosDet[mn-1].GetAt(kk);
											CString strF;
											strF.Format(_T("(SM=%d)"),nSM);
											int ngh2 = strMod3.Find(strF);
											if (ngh2!=-1)
											{
												CString strNew = m_strScenariosDet[mn-1].GetAt(kk+1+nf);

												strNew.Delete(0,2);
												nf = strNew.Find(_T("\t"));

												CString strHedaer = strNew.Left(nf);
												int nf2 = strHedaer.Find(_T("- "));
												strHedaer.Delete(0,nf2+1);
												int nCat = atoi(strHedaer);

												strNew.Delete(0,nf+1);
	
												strInf.Delete(0,ntt);
												strInf = INFOTYPE[nCat] + strInf;
												break;
											}
										}*/
										pER.m_strInfo.Add(strInf);
									}
								}

								bERFd = TRUE;
							}
							else
							{
								bERFd = FALSE;
							}
						}

						//CString mstrTT;
						//BOOL bRet = m_strCatER.Lookup(pER.m_nERName,mstrTT);
						//pER.m_strCategory = mstrTT;
						pCurrUnit->m_cERs.Add(pER);
						//if (bRet==0)
						//{
						//	int rr=0;
						//	rr++;
						//}

					}
				}

			}

/*			FILE *fp2 = fopen(m_strScenarios.GetAt(mn-1),"r");
			if (fp2)
			{
				CStdioFile f2(fp2);
				CString mstr2;
				BOOL ret2 = TRUE;
				BOOL ret3 = TRUE;
				BOOL bRet4= FALSE;
				while (ret2)
				{
					ret2 = f2.ReadString(mstr2);
					int gg = mstr2.Find(msss);
					int gg2 = mstr2.Find(_T("(LU="));
					if (gg!=-1 && gg2!=-1)
					{
						ret3 = TRUE;
						break;
					}
				}
				if (ret3)
				{
					ret2 = TRUE;
					while (ret2)
					{
						ret2 = f2.ReadString(mstr2);
						int gg2 = mstr2.Find(_T("(LU="));
						if (gg2!=-1)
						{
							ret2 = FALSE;
							break;
						}
						if (mstr2.GetLength()>=3 && mstr2[2] != '\t')
						{
							CString strER=mstr2;
							strER.MakeReverse();
							int ggg= strER.Find('(');
							strER.Delete(0,ggg+2);
							strER.MakeReverse();
							strER.TrimLeft();
							CLogER pER;
							pER.m_nERName = strER;

							CString mstrTT;
							BOOL bRet = m_strCatER.Lookup(strER,mstrTT);
							pER.m_strCategory = mstrTT;
							pCurrUnit->m_cERs.Add(pER);
							if (bRet==0)
							{
								int rr=0;
								rr++;
							}
							//pCurrUnit->m_nERName.Add(strER);
						}
					}
				}
				f2.Close();
			}*/

		}

		nb = mstr.Find(_T("CLOSE FILE")) ;
		if (nb !=-1)
		{
			int nDel = mstr.Find('\t');
			CString strTime = mstr.Left(nDel);

			CTime nTime = StringToTime(strTime);
	
			if (pCurrScen)
			{
				pCurrScen->m_nEnd = nString;
			}
			if (pCurrUnit)
			{
				pCurrUnit->m_nEnd = nString;
				if (pCurrUnit->m_nEnd==pCurrUnit->m_nStart)
				{
					delete pCurrUnit;
					pCurrUnit = NULL;
				}
				else
				{
					pCurrUnit->n_nTimeStop = nTime;
					pCurrScen->m_lUnits.Add(pCurrUnit);
					pCurrUnit->SetUseTable();
				}

			}
			pCurrScen = NULL;
			pCurrUnit = NULL;
		}

		nb = mstr.Find(_T("OPEN FILE")) ;
		if (nb != -1)
		{
			TCHAR path_buffer[_MAX_PATH];
			TCHAR drive[_MAX_DRIVE];   
			TCHAR dir[_MAX_DIR];
			TCHAR name[_MAX_FNAME];
			TCHAR ext[_MAX_EXT];

			CString mstr2 = nb+11+mstr.GetBuffer(mstr.GetLength());

			_tsplitpath (lpszPathName, drive, dir, NULL, NULL);
			_tsplitpath (mstr2, NULL, NULL, name, ext);

			_tmakepath (path_buffer, drive, dir, name,  _T("log"));
			m_strScenarios.Add(path_buffer);

			m_Scenario.Add(nString);

			if (pCurrScen)
			{
				pCurrScen->m_nEnd = nString-1;
			}

			if (pCurrUnit)
			{
				pCurrUnit->m_nEnd = nString-1;
			}

			pCurrScen = new CLogScenario();
			pCurrScen->m_nStart = nString;

			int nDel = mstr.Find('\t');
			CString strTime = mstr.Left(nDel);

			CTime nTime = StringToTime(strTime);

			pCurrScen->n_nTime = nTime;

			//pCurrUnit = new CLogUnit();
			//pCurrUnit->m_nStart = nString;

			//pCurrScen->m_lUnits.Add(pCurrUnit);
			m_lScenario.Add(pCurrScen);

		}
		int nb2 = mstr.Find(_T("OPEN FILE")) ;
		nb = mstr.Find(_T("OPEN")) ;
		int nb3 = mstr.Find(_T("CLOSE FILE")) ;
		int nb4 = mstr.Find(_T("CLOSE")) ;
		if ((nb != -1 && nb2 == -1) || (nb4 != -1 && nb3 == -1))
		{
			int nER = pCurrUnit->m_cERs.GetSize();
			CString strER = mstr;
			strER.MakeReverse();
			int nvb = strER.Find('\t');
			strER = strER.Left(nvb);
			strER.MakeReverse();
			for (int k=0;k<nER;k++)
			{
				CLogER pER = pCurrUnit->m_cERs.GetAt(k);
				if (strER == pER.m_nERName)
				{
					int rrr = mstr.Find('\t');
					CString strT = mstr.Left(rrr);
					CTime nT = StringToTime(strT);
					pER.m_nERTime.Add(nT);
					pCurrUnit->m_cERs.SetAt(k,pER);

				}
			}
		}

		nb = mstr.Find(_T("MAP RELATION")) ;
		nb2= mstr.Find(_T("EXP-SET")) ;
		nb3 = mstr.Find(_T("HYPOTHESIS")) ;
		nb4 = mstr.Find(_T("ACTION")) ;
		int nb5 = mstr.Find(_T("RUN")) ;
		int nb6 = mstr.Find(_T("REVIEW")) ;
		int nb7 = mstr.Find(_T("INITAT"));
		int nb8 = mstr.Find(_T("STOPAT"));
		if (nb != -1 || nb2 !=-1 || nb3 !=-1 || nb4 !=-1 || nb5 !=-1 || nb6 !=-1 || nb7 !=-1
			 || nb8 !=-1)
		{
			CString strCopy = mstr;
			int nTime = strCopy.Find('\t');
			CString strTime = strCopy.Left(nTime);
			strCopy.Delete(0,nTime+1);
			int nAction = strCopy.Find('\t');
			strCopy.Delete(0,nAction+1);
			int nActiv = strCopy.Find('\t');
			CString strAct = strCopy.Left(nActiv);

			if (nb5!=-1 || nb6!=-1 || nb7!=-1|| nb8!=-1)
			{
				CLogAction pAction;
				CTime nT = StringToTime(strTime);
				if (nb5!=-1)
					pAction.m_nType = LOG_SHOW_RUN;
				if (nb6!=-1)
				{
					pAction.m_nType = LOG_SHOW_REVIEW;
					if (strCopy.Find(_T("next")) != -1)
						pAction.m_nSubType = 1;
					else if (strCopy.Find(_T("previous")) != -1)
						pAction.m_nSubType = 2;
					else if (strCopy.Find(_T("forward")) != -1)
						pAction.m_nSubType = 3;
					else if (strCopy.Find(_T("backward")) != -1)
						pAction.m_nSubType = 4;
					else pAction.m_nSubType = 0;

				}
				if (nb7!=-1)
					pAction.m_nType = LOG_SHOW_INITAT;
				if (nb8!=-1)
					pAction.m_nType = LOG_SHOW_STOPAT;
				pAction.m_nLog = nString;
				pAction.m_tAction = nT;
				pAction.m_nER = 0;
				pCurrUnit->m_cActions.Add(pAction);
			}
			else
			{

			int nER = pCurrUnit->m_cERs.GetSize();
			for (int k=0;k<nER;k++)
			{
				CLogER pER = pCurrUnit->m_cERs.GetAt(k);
				if (pER.m_nERName == strAct)
				{
					CTime nT = StringToTime(strTime);

					CLogAction pAction;
					if (nb2!=-1)
						pAction.m_nType = LOG_SHOW_EXPSET;
					else if (nb!=-1)
						pAction.m_nType = LOG_SHOW_MAPREL;
					else if (nb3!=-1)
						pAction.m_nType = LOG_SHOW_HYP;
					else //if (nb3!=-1)
						pAction.m_nType = LOG_SHOW_ACT;

					pAction.m_nLog = nString;
					pAction.m_tAction = nT;
					pAction.m_nER = k;
					pCurrUnit->m_cActions.Add(pAction);

				}
			}
			}
		}

		nb = mstr.Find(_T("ACTIV")) ;
		if (nb != -1)
		{
			int nER = pCurrUnit->m_cERs.GetSize();

			CString strCopy = mstr;
			int nTime = strCopy.Find('\t');
			CString strTime = strCopy.Left(nTime);
			strCopy.Delete(0,nTime+1);
			int nAction = strCopy.Find('\t');
			strCopy.Delete(0,nAction+1);
			int nActiv = strCopy.Find('\t');
			CString strAct;
			CString strDesac;
			if (nActiv==-1)
			{
				strAct = strCopy;
			}
			else
			{
				strAct = strCopy.Left(nActiv);
				strCopy.Delete(0,nActiv+1);
				strDesac = strCopy;
				int ff = strDesac.Find(_T("("));
				strDesac.Delete(ff);
				ff = strDesac.Find(_T(")"));
				strDesac.Delete(ff);
			}


			for (int k=0;k<nER;k++)
			{
				CLogER pER = pCurrUnit->m_cERs.GetAt(k);
				if (pER.m_nERName == strAct)
				{
					CTime nT = StringToTime(strTime);
					//pER.m_nERActive.Add(nT);
					//pCurrUnit->m_cERs.SetAt(k,pER);
					pCurrUnit->m_cActivID.Add(k);
					pCurrUnit->m_cActivTime.Add(nT);

				}
				if (pER.m_nERName == strDesac)
				{
					CTime nT = StringToTime(strTime);
					//pER.m_nERDesActive.Add(nT);
					//pCurrUnit->m_cERs.SetAt(k,pER);
				}
			}
		}

		nString++;
	}
	f.Close();


	for (int i=0;i<m_lScenario.GetSize();i++)
	{
		CLogScenario *pScen = (CLogScenario *)m_lScenario.GetAt(i);
		if (!pScen) continue;
		int nStart = pScen->m_nStart;
		int nEnd = pScen->m_nEnd;

		for (int j=0;j<pScen->m_lUnits.GetSize();j++)
		{
			CLogUnit *pUnit = (CLogUnit *)pScen->m_lUnits.GetAt(j);
			if (!pUnit) continue;
			int nnStart = pUnit->m_nStart;
			int nnEnd = pUnit->m_nEnd;
		}

	}

	
	return TRUE;
}
