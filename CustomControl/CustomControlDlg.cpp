
// CustomControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CustomControl.h"
#include "CustomControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCustomControlDlg dialog




CCustomControlDlg::CCustomControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCustomControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCustomControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btn);
	DDX_Control(pDX, IDC_BUTTON2, m_btn2);
	DDX_Control(pDX, IDC_BUTTON3, m_testBtn);
	DDX_Control(pDX, IDC_BUTTON4, m_iconBtn);
}

BEGIN_MESSAGE_MAP(CCustomControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CCustomControlDlg message handlers

BOOL CCustomControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
//   	m_btn.SubclassWindow(((CButton*)GetDlgItem(IDC_BUTTON1))->GetSafeHwnd());
// 		m_btn.SetButtonStyle(0);
 		m_btn.SetWindowText(_T("ashasdfdsafewrwegafgdsyry aer aerewara er er "));
    	m_btn.ExpentToFit();
		CRect	rcBtn;
		m_btn.GetWindowRect(rcBtn);
		TRACE2("OnInitDialog::rcItem.LeftTop (%d,%d).",rcBtn.left,rcBtn.top);
		TRACE2("OnInitDialog.RightBottom(%d,%d).",rcBtn.right,rcBtn.bottom);
		TRACE2("OnInitDialog.Width(%d),Height(%d).\n",rcBtn.Width(),rcBtn.Height());

// 	HBITMAP   hBitmap;   
// 	hBitmap = LoadBitmap(AfxGetInstanceHandle(),   
// 		MAKEINTRESOURCE(IDB_BITMAP1)); // IDB_BITMAP_TESTΪ��ԴͼƬID  
// 	DWORD	dwStyle = m_btn2.GetButtonStyle()|BS_BITMAP;//^BS_TEXT;
// 	m_btn2.SetButtonStyle(dwStyle,TRUE);
// 	m_btn2.SetBitmap(hBitmap);
//	m_btn2.LoadBtnImage(IDB_BITMAP1);
		m_iconBtn.LoadBtnIcon(IDR_MAINFRAME);
	m_btn2.LoadBtnImage(_T("D:\\Code_Lib\\SourceCode\\Test\\winbk.bmp"));
	m_testBtn.SetWindowText(_T("1546531546asdf4a6sd54fwear6a4f6ew"));
 	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCustomControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCustomControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCustomControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCustomControlDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
 	CDialogEx::OnMouseMove(nFlags, point);
}
