// LogUnit.h: interface for the CLogUnit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGUNIT_H__5CB5F405_E5B4_11D5_A2F5_EB015E520828__INCLUDED_)
#define AFX_LOGUNIT_H__5CB5F405_E5B4_11D5_A2F5_EB015E520828__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ArrayEx.h"

#define LOG_SHOW_EXPSET		1
#define LOG_SHOW_HYP		2
#define LOG_SHOW_ACT		4
#define LOG_SHOW_MAPREL		8
#define LOG_SHOW_RUN		16
#define LOG_SHOW_REVIEW		32
#define LOG_SHOW_INITAT		64
#define LOG_SHOW_STOPAT		128

class CLogAction : public CObject  
{
	DECLARE_DYNAMIC(CLogAction)
public:
	CLogAction();
	CLogAction(const CLogAction&  stringSrc);
	virtual ~CLogAction();

	const CLogAction& operator=(const CLogAction& stringSrc);

	int				m_nType;	// 0: EXPSET, 1: MAPRELATION, 2: HYPOTHESIS
	int				m_nSubType;	// 
	CTime			m_tAction;
	int				m_nER;
	int				m_nLog;
};



class CLogER : public CObject  
{
	DECLARE_DYNAMIC(CLogER)
public:
	CLogER();
	CLogER(const CLogER&  stringSrc);
	virtual ~CLogER();

	const CLogER& operator=(const CLogER& stringSrc);


	BOOL			m_bStartUp;
	CString			m_nERName;
	CString			m_strCategory;
	CArray<CTime,CTime>	m_nERTime;
	CStringArray	m_strInfo;
	CArray<int,int>			m_cCount;
	
	typedef CArrayEx<CString,CString> CStrArray;
	CArrayEx<CStrArray, CStrArray &> m_strCrossER;
};


class CLogUnit : public CObject  
{
	DECLARE_DYNAMIC(CLogUnit)
public:
	CLogUnit();
	virtual ~CLogUnit();

	int						m_nStart;
	int						m_nEnd;
	CTime					n_nTime;
	CTime					n_nTimeStop;
	CArray<CLogER,CLogER>	m_cERs;

	CArray<CLogAction,CLogAction>	m_cActions;

	CArray<int,int>			m_cActivID;
	CArray<CTime,CTime>		m_cActivTime;

	CRect			m_rSumm;

	CArray<int,int>			m_nCount;
	CArray<int,int>			m_nCountInd;

	int		m_nCMax;
	int		m_nMin,m_nMax;
	double	m_nAver;

	void SetUseTable();
};


class CLogScenario : public CObject  
{
	DECLARE_DYNAMIC(CLogScenario)
public:
	CLogScenario();
	virtual ~CLogScenario();

	CPtrArray		m_lUnits;
	int				m_nStart;
	int				m_nEnd;
	CTime			n_nTime;

};


#endif // !defined(AFX_LOGUNIT_H__5CB5F405_E5B4_11D5_A2F5_EB015E520828__INCLUDED_)
