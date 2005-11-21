// DEMIST Analyser.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DEMIST Analyser.h"

#include "MVDocTemplate.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "DADoc.h"
#include "DALogView.h"
#include "DAModelsView.h"
#include "DASummary.h"
#include "DATableERs.h"
#include "ViewCategories.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDEMISTAnalyserApp

BEGIN_MESSAGE_MAP(CDEMISTAnalyserApp, CWinApp)
	//{{AFX_MSG_MAP(CDEMISTAnalyserApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileNew)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDEMISTAnalyserApp construction

CDEMISTAnalyserApp::CDEMISTAnalyserApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDEMISTAnalyserApp object

CDEMISTAnalyserApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDEMISTAnalyserApp initialization

BOOL CDEMISTAnalyserApp::InitInstance()
{

	{	// BLOCK: doc template registration
		// Register the document template.  Document templates serve
		// as the connection between documents, frame windows and views.
		// Attach this form to another document or frame window by changing
		// the document or frame class in the constructor below.
/*		CMultiDocTemplate* pNewDocTemplate = new CMultiDocTemplate(
			IDR_VIEWCATEGORIES_TMPL,
			RUNTIME_CLASS(CDADocument),		// document class
			RUNTIME_CLASS(CMDIChildWnd),		// frame class
			RUNTIME_CLASS(CViewCategories));		// view class
		AddDocTemplate(pNewDocTemplate);*/
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("CREDIT"));

	LoadStdProfileSettings(8);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMvDocTemplate *pDocTemplate = new CMDIMVDocTemplate(
		IDR_DEMISTTYPE, 
		RUNTIME_CLASS( CDADocument ) );

	//// LOG FILE
	pDocTemplate->AddFrameTemplate(
		new CFrameTemplate(
			IDR_LOGFILE,					// menu & string ID 
			RUNTIME_CLASS(CChildFrame ),	// custom MDI child frame
			RUNTIME_CLASS(CDALogView ),	// custom MDI view
			ID_VIEW_LOGVIEW,					// command ID
			SW_SHOWNORMAL,					// default window statut
			TRUE,							// Load at startup
			FALSE) );						// Allow multiple view

	//// LOG FILE
	pDocTemplate->AddFrameTemplate(
		new CFrameTemplate(
			IDR_MODELSFILE,					// menu & string ID 
			RUNTIME_CLASS(CChildFrame ),	// custom MDI child frame
			RUNTIME_CLASS(CDAModelsView),	// custom MDI view
			ID_VIEW_SCENARIO,					// command ID
			SW_SHOWNORMAL,					// default window statut
			FALSE,							// Load at startup
			FALSE) );						// Allow multiple view

	//// REP CATEGORIES
	pDocTemplate->AddFrameTemplate(
		new CFrameTemplate(
			IDR_CATLIST,					// menu & string ID 
			RUNTIME_CLASS(CChildFrame ),	// custom MDI child frame
			RUNTIME_CLASS(CViewCategories),	// custom MDI view
			ID_VIEW_CATLIST,					// command ID
			SW_SHOWNORMAL,					// default window statut
			FALSE,							// Load at startup
			FALSE) );						// Allow multiple view

	//// SUMMARY
	pDocTemplate->AddFrameTemplate(
		new CFrameTemplate(
			IDR_SUMMARY_VIEW,					// menu & string ID 
			RUNTIME_CLASS(CChildFrame ),	// custom MDI child frame
			RUNTIME_CLASS(CDASummary),	// custom MDI view
			ID_VIEW_SUMMARY,					// command ID
			SW_SHOWNORMAL,					// default window statut
			FALSE,							// Load at startup
			FALSE) );						// Allow multiple view

	//// TABLE
	pDocTemplate->AddFrameTemplate(
		new CFrameTemplate(
			IDR_TABLE,					// menu & string ID 
			RUNTIME_CLASS(CChildFrame ),	// custom MDI child frame
			RUNTIME_CLASS(CDATableERs),	// custom MDI view
			ID_VIEW_TABLE,					// command ID
			SW_SHOWNORMAL,					// default window statut
			FALSE,							// Load at startup
			FALSE) );						// Allow multiple view

	//// TABLE
	pDocTemplate->AddFrameTemplate(
		new CFrameTemplate(
			IDR_AVAILABILITY,					// menu & string ID 
			RUNTIME_CLASS(CChildFrame ),	// custom MDI child frame
			RUNTIME_CLASS(CDATableAvail),	// custom MDI view
			ID_VIEW_AVAILABILITY,					// command ID
			SW_SHOWNORMAL,					// default window statut
			FALSE,							// Load at startup
			FALSE) );						// Allow multiple view

	//// TABLE
	pDocTemplate->AddFrameTemplate(
		new CFrameTemplate(
			IDR_CATEGORY,					// menu & string ID 
			RUNTIME_CLASS(CChildFrame ),	// custom MDI child frame
			RUNTIME_CLASS(CDATableCategory),	// custom MDI view
			ID_VIEW_CATEGORY,					// command ID
			SW_SHOWNORMAL,					// default window statut
			FALSE,							// Load at startup
			FALSE) );						// Allow multiple view

	//// TABLE
	pDocTemplate->AddFrameTemplate(
		new CFrameTemplate(
			IDR_INFORMATION,					// menu & string ID 
			RUNTIME_CLASS(CChildFrame ),	// custom MDI child frame
//			RUNTIME_CLASS(CDATableInformation),	// custom MDI view
			RUNTIME_CLASS(CDATableSwitchER),	// custom MDI view
			ID_VIEW_INFORMATION,					// command ID
			SW_SHOWNORMAL,					// default window statut
			FALSE,							// Load at startup
			FALSE) );						// Allow multiple view

	//// TABLE
	pDocTemplate->AddFrameTemplate(
		new CFrameTemplate(
			IDR_RUNREVIEW,					// menu & string ID 
			RUNTIME_CLASS(CChildFrame ),	// custom MDI child frame
			RUNTIME_CLASS(CDATableRunReview),	// custom MDI view
			ID_VIEW_RUNREVIEW,					// command ID
			SW_SHOWNORMAL,					// default window statut
			FALSE,							// Load at startup
			FALSE) );						// Allow multiple view


	AddDocTemplate(pDocTemplate);

/*	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_DEMISTTYPE,
		RUNTIME_CLASS(CDADocument),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CDALogView));
	AddDocTemplate(pDocTemplate);*/

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Don't open default document
	if(cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
  

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CDEMISTAnalyserApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDEMISTAnalyserApp message handlers

void CDEMISTAnalyserApp::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);
	
}

