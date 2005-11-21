// DADoc.h : interface of the CDADocument class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DADOC_H__51D620E2_E4EC_11D5_A2F5_9C17D03C0928__INCLUDED_)
#define AFX_DADOC_H__51D620E2_E4EC_11D5_A2F5_9C17D03C0928__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DOC_SELECT_LOG_LINE			(WM_USER+300)


class CDADocument : public CDocument
{
protected: // create from serialization only
	CDADocument();
	DECLARE_DYNCREATE(CDADocument)

// Attributes
public:
	CStringArray	m_strScenariosDet[4];
	CStringArray	m_strScenarios;
	CStringArray	m_strLog;

	CUIntArray		m_Scenario;
	CUIntArray		m_Units;
	CPtrArray		m_lScenario;

	CMapStringToString	m_strCategories;

// Operations
public:
	CTime StringToTime(CString mstr);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDADocument)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDADocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDADocument)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DADOC_H__51D620E2_E4EC_11D5_A2F5_9C17D03C0928__INCLUDED_)
