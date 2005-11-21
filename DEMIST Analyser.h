// DEMIST Analyser.h : main header file for the DEMIST ANALYSER application
//

#if !defined(AFX_DEMISTANALYSER_H__51D620DA_E4EC_11D5_A2F5_9C17D03C0928__INCLUDED_)
#define AFX_DEMISTANALYSER_H__51D620DA_E4EC_11D5_A2F5_9C17D03C0928__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDEMISTAnalyserApp:
// See DEMIST Analyser.cpp for the implementation of this class
//

class CDEMISTAnalyserApp : public CWinApp
{
public:
	CDEMISTAnalyserApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDEMISTAnalyserApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDEMISTAnalyserApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMISTANALYSER_H__51D620DA_E4EC_11D5_A2F5_9C17D03C0928__INCLUDED_)
