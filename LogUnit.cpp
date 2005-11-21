// LogUnit.cpp: implementation of the CLogUnit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <afxcoll.h>

#include "DEMIST Analyser.h"
#include "LogUnit.h"

#include "ArrayEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CLogAction, CObject)

CLogAction::CLogAction()
{
	m_nSubType = 0;
}


CLogAction::CLogAction(const CLogAction&  stringSrc)
{
	m_tAction = stringSrc.m_tAction;
	m_nER = stringSrc.m_nER;
	m_nLog = stringSrc.m_nLog;
	m_nType = stringSrc.m_nType;
	m_nSubType = stringSrc.m_nSubType;
}


CLogAction::~CLogAction()
{

}

const CLogAction& CLogAction::operator=(const CLogAction& stringSrc)
{
	m_tAction = stringSrc.m_tAction;
	m_nER = stringSrc.m_nER;
	m_nLog = stringSrc.m_nLog;
	m_nType = stringSrc.m_nType;
	m_nSubType = stringSrc.m_nSubType;
	return (*this);
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CLogER, CObject)

CLogER::CLogER()
{
}


CLogER::CLogER(const CLogER&  stringSrc)
{
	m_nERName = stringSrc.m_nERName;
	m_strCategory = stringSrc.m_strCategory;
	m_bStartUp = stringSrc.m_bStartUp;
	m_nERTime.RemoveAll();
	m_strInfo.RemoveAll();
	
	for (int i=0;i<stringSrc.m_nERTime.GetSize();i++)
	{
		m_nERTime.Add(stringSrc.m_nERTime.GetAt(i));
	}
	for (i=0;i<stringSrc.m_strInfo.GetSize();i++)
	{
		m_strInfo.Add(stringSrc.m_strInfo.GetAt(i));
	}
	for (i=0;i<stringSrc.m_cCount.GetSize();i++)
	{
		m_cCount.Add(stringSrc.m_cCount.GetAt(i));
	}
	m_strCrossER.RemoveAll();
	m_strCrossER = stringSrc.m_strCrossER;
}


CLogER::~CLogER()
{
}

const CLogER& CLogER::operator=(const CLogER& stringSrc)
{
	m_nERName = stringSrc.m_nERName;
	m_nERTime.RemoveAll();
	m_strInfo.RemoveAll();
	m_bStartUp = stringSrc.m_bStartUp;
	m_strCategory = stringSrc.m_strCategory;
	for (int i=0;i<stringSrc.m_nERTime.GetSize();i++)
	{
		m_nERTime.Add(stringSrc.m_nERTime.GetAt(i));
	}
	
	for (i=0;i<stringSrc.m_strInfo.GetSize();i++)
	{
		m_strInfo.Add(stringSrc.m_strInfo.GetAt(i));
	}
	for (i=0;i<stringSrc.m_cCount.GetSize();i++)
	{
		m_cCount.Add(stringSrc.m_cCount.GetAt(i));
	}

	m_strCrossER.RemoveAll();
	m_strCrossER = stringSrc.m_strCrossER;

	return (*this);

}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CLogUnit, CObject)

CLogUnit::CLogUnit()
{
	m_nCMax = 0;

}

CLogUnit::~CLogUnit()
{
}


void CLogUnit::SetUseTable()
{
	int nb = m_cERs.GetSize();

	CTimeSpan nDur = n_nTimeStop-n_nTime;
	int nTT = nDur.GetTotalSeconds();

	m_nCount.RemoveAll();
	for (int i=0;i<nTT;i++)
		m_nCount.Add(0);

	for (i=1;i<nb;i++)
	{
		CLogER pER = m_cERs.GetAt(i);
		int nt = pER.m_nERTime.GetSize();
		if (!nt) continue;
		if (nt%2==1) 
		{
			continue;
		}

		pER.m_cCount.RemoveAll();
		pER.m_cCount.RemoveAll();
		for (int r=0;r<nTT;r++)
			pER.m_cCount.Add(0);

		LONG Tnl=0;
		for (int k=0;k<nt;k+=2)
		{
			CTime ndd = pER.m_nERTime.GetAt(k);
			CTime ndd2 = pER.m_nERTime.GetAt(k+1);

			CTimeSpan nST = ndd-n_nTime;
			LONG nl1 = nST.GetTotalSeconds();

			CTimeSpan nDD = ndd2-n_nTime;
			LONG nl2 = nDD.GetTotalSeconds();

			Tnl += (nl2-nl1);

			for (int j=nl1;j<nl2;j++)
			{
				m_nCount.SetAt(j,m_nCount.GetAt(j)+1);
				pER.m_cCount.SetAt(j,pER.m_cCount.GetAt(j)+1);
			}

			CLogER::CStrArray strTTTT;
			CString strInit;
			strInit.Format(_T("%s\t%d %d"),pER.m_nERName,nl1,nl2);
			strTTTT.Add(strInit);
			for (int i1=1;i1<nb;i1++)
			{
				if (i1==i) continue;
				CLogER pER2 = m_cERs.GetAt(i1);
				int nt2 = pER2.m_nERTime.GetSize();
				if (!nt2) continue;
				if (nt2%2==1) continue;
				for (int k1=0;k1<nt2;k1+=2)
				{
					CTime ndd = pER2.m_nERTime.GetAt(k1);
					CTime ndd2 = pER2.m_nERTime.GetAt(k1+1);

					CTimeSpan nST = ndd-n_nTime;
					LONG nl1a = nST.GetTotalSeconds();
	
					CTimeSpan nDD = ndd2-n_nTime;
					LONG nl2a = nDD.GetTotalSeconds();
	
					CRect mr1(nl1,0,nl2,1);
					CRect mr2(nl1a,0,nl2a,1);
					mr1.NormalizeRect();
					mr2.NormalizeRect();
					CRect mr3 = mr1 & mr2; 
					if (!mr3.IsRectEmpty())
					{
						CString strF;
						strF.Format(_T("%s\t%d %d"),pER2.m_nERName,mr3.left,mr3.right);
						strTTTT.Add(strF);
					}
				}
			}
			pER.m_strCrossER.Add(strTTTT);
			m_cERs.SetAt(i,pER);
		}
	}

	m_nCountInd.RemoveAll();
	m_nCountInd.Add(0);
	m_nCountInd.Add(0);
	m_nCountInd.Add(0);
	m_nCountInd.Add(0);
	m_nCountInd.Add(0);
	m_nCountInd.Add(0);
	m_nCountInd.Add(0);
	m_nCountInd.Add(0);
	m_nCountInd.Add(0);
	m_nCountInd.Add(0);
	m_nCountInd.Add(0);
	m_nCountInd.Add(0);
	m_nCountInd.Add(0);
	m_nCountInd.Add(0);
	m_nCountInd.Add(0);
	m_nCountInd.Add(0);
	m_nCountInd.Add(0);
	for (i=0;i<nTT;i++)
	{
		int bb = m_nCount.GetAt(i);
		m_nCountInd.SetAt(bb,m_nCountInd.GetAt(bb)+1);

	}
	m_nMin = 1000;
	m_nMax = -1000;
	m_nAver = 0.0;
	int nCount = 0;
	for (i=0;i<m_nCountInd.GetSize();i++)
	{
		int bb = m_nCountInd.GetAt(i);
		if (bb!=0)
		{
			m_nMax = max(m_nMax,i);
			m_nMin = min(m_nMin,i);
			m_nAver += i*bb;
			nCount+= bb;
		}
	}
	m_nAver /= nCount;



}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CLogScenario, CObject)

CLogScenario::CLogScenario()
{

}

CLogScenario::~CLogScenario()
{
	for (int i=0;i<m_lUnits.GetSize();i++)
	{
		CLogUnit *pUnit = (CLogUnit *)m_lUnits.GetAt(i);
		delete pUnit;
	}
	m_lUnits.RemoveAll();

}
