
// MP3PlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MP3Player.h"
#include "MP3PlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL    GetPath(TCHAR * strPath)
{
	TCHAR sDrive[_MAX_DRIVE];
	TCHAR sDir[_MAX_DIR];
	TCHAR sFilename[_MAX_FNAME],Filename[_MAX_FNAME];
	TCHAR sExt[_MAX_EXT];

	GetModuleFileName(NULL, Filename, _MAX_PATH);
	_tsplitpath(Filename, sDrive, sDir, sFilename, sExt);

	_tcscpy(strPath,sDrive);
	_tcscat(strPath,sDir);

	strPath[_tcslen(strPath)-1] = _T('\0');

	return TRUE;
}
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


// CMP3PlayerDlg dialog




CMP3PlayerDlg::CMP3PlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMP3PlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nCaptionHeight = INIT_CAPTION_HEIGHT;
// 	m_brBG = NULL;
// 	m_bmpCP = NULL;
// 	m_bmpGK = NULL;
}
CMP3PlayerDlg::~CMP3PlayerDlg()
{
	if (m_bmpGK.GetSafeHandle())
	{
		m_bmpGK.Detach();
	}
	if (m_bmpCP.GetSafeHandle())
	{
		m_bmpCP.Detach();
	}
	if (m_brBG.GetSafeHandle())
	{
		m_brBG.DeleteObject();
	}
}
void CMP3PlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMP3PlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCPAINT()
	ON_WM_NCACTIVATE()
	ON_WM_NCCALCSIZE()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
	ON_WM_NCMOUSEMOVE()
	ON_WM_INITMENUPOPUP()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////////
void	CMP3PlayerDlg::SetBkImage(const CString& strFileBK,const CString& strFileCaption)
{
	//若是标题栏图片路径无，则表示采用一体背景
	if (strFileBK.IsEmpty())
	{
		return;
	}
	HBITMAP	hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		strFileBK,IMAGE_BITMAP,0,0,LR_DEFAULTSIZE|LR_LOADFROMFILE);
	if (hbmp)
	{
		m_bmpGK.Detach();
		m_bmpGK.Attach(hbmp);
	}
	if (!strFileCaption.IsEmpty())
	{
		hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),strFileCaption,
			IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_DEFAULTSIZE);
		if (hbmp)
		{
			m_bmpCP.Detach();
			m_bmpCP.Attach(hbmp);
		}
	}
}
void	CMP3PlayerDlg::SetBkImage(UINT nResID_BK,UINT nResID_CP /*= 0*/)
{
	HBITMAP	hbmp = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(nResID_BK));
	if (hbmp)
	{
		m_bmpGK.Detach();
		m_bmpGK.Attach(hbmp);
	}
	if (nResID_CP>0)
	{
		hbmp = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(nResID_CP));
		if (hbmp)
		{
			m_bmpCP.Detach();
			m_bmpCP.Attach(hbmp);
		}
	}
}





// CMP3PlayerDlg message handlers

BOOL CMP3PlayerDlg::OnInitDialog()
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
	m_bNCActive=true;//初始NC区为活动.
	m_brBG.CreateSolidBrush(RGB(0, 0, 0)); //对话框背景颜色,在OnCtlColor中作为返回值.
	CString	str;
	TCHAR	path[MAX_PATH];
	GetPath(path);
	str=path;
	if (!str.IsEmpty())
	{
		str +=_T("//skin");
		SetBkImage(str+DLG_BK,str+DLG_TITLE);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMP3PlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMP3PlayerDlg::OnPaint()
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
		CPaintDC	dc(this);
		DrawBKBmp(&dc,m_rtWnd);
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMP3PlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMP3PlayerDlg::OnNcPaint()
{
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnNcPaint() for painting messages
	CDC* pWinDC=GetWindowDC();
	if (pWinDC)
		DrawNC(pWinDC);
	ReleaseDC(pWinDC);
}


BOOL CMP3PlayerDlg::OnNcActivate(BOOL bActive)
{
	// TODO: Add your message handler code here and/or call default
	m_bNCActive=bActive;
	//防止在任务栏右键图标时出现最大最小关闭
	if(bActive)
	{
		ModifyStyle(0, WS_SYSMENU);
		OnNcPaint();
	}
	else
	{
		ModifyStyle(WS_SYSMENU, 0);
		OnNcPaint();
	}
	return true;
// 	return CDialogEx::OnNcActivate(bActive);
}


void CMP3PlayerDlg::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: Add your message handler code here and/or call default

	int nCY = GetSystemMetrics(SM_CYCAPTION);
	lpncsp->rgrc[0].top+=m_nCaptionHeight-nCY;
	CDialogEx::OnNcCalcSize(bCalcValidRects, lpncsp);
}


void CMP3PlayerDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnNcLButtonDown(nHitTest, point);
}


void CMP3PlayerDlg::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_rtButtExit.PtInRect(point))
		SendMessage(WM_CLOSE);
	else if (m_rtButtMin.PtInRect(point))
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, MAKELPARAM(point.x, point.y) );
	else if (m_rtButtMax.PtInRect(point))
	{
		if (IsZoomed())
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, MAKELPARAM(point.x, point.y));
		else
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, MAKELPARAM(point.x, point.y) );
	}
// 	CDialogEx::OnNcLButtonUp(nHitTest, point);
}


void CMP3PlayerDlg::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnNcMouseMove(nHitTest, point);
}


LRESULT CMP3PlayerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if (message == WM_NCHITTEST)
	{
		LRESULT	lr = CDialogEx::WindowProc(message, wParam, lParam);
		if (lr == HTZOOM || lr == HTMINBUTTON || lr == HTCLOSE)
		{
			return HTCAPTION;
		}
		else 
			return lr;
	}
	// 在OnNcActivate 和OnInitMenuPopup 中也处理最大和最小关闭误显示的问题.
	else if (message == WM_SETCURSOR || 
		message == WM_NCLBUTTONDOWN || 
		message == WM_NCLBUTTONUP ||
		message == WM_NCLBUTTONDBLCLK||
		message == WM_NCRBUTTONDOWN || 
		message == WM_NCRBUTTONDBLCLK ||
		message == 0x0125 /*WM_UNINITMENUPOPUP*/)
	{
		ModifyStyle(WS_SYSMENU, 0);//移除系统菜单.
		LRESULT lRet = CDialog::WindowProc(message, wParam, lParam); 
		//ModifyStyle(0, WS_SYSMENU);
		return lRet;
	}
 	return CDialogEx::WindowProc(message, wParam, lParam);
}

//对系统最大最小关闭图标依然出现的处理：
//虽然用户取消了NC区系统的重绘，但是系统仍然对最大最小关闭图标重绘（主要表现在用户右单击任务栏图标时）
void CMP3PlayerDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
// 	CDialogEx::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	// TODO: Add your message handler code here
	if (bSysMenu) OnNcPaint();//防止在任务栏右键图标时窗口出现最大最小关闭
}


LRESULT CMP3PlayerDlg::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CRect tst(2,2,m_nCaptionHeight+4,m_nCaptionHeight+4);
	tst.OffsetRect(m_rtWnd.TopLeft());//原图标屏幕位置
	if(tst.PtInRect(point))//最大最小关闭按钮位置.
		return HTCAPTION;
	else if(m_rtButtMin.PtInRect(point)||
		m_rtButtMax.PtInRect(point)||
		m_rtButtExit.PtInRect(point))
		return HTSYSMENU;//使此区域能够响应OnNcLButtonUp
	else
		return CDialog::OnNcHitTest(point);
// 	return CDialogEx::OnNcHitTest(point);
}

/************************************************************************/
/* 
*/
/************************************************************************/
void	CMP3PlayerDlg::DrawNC(CDC* pDC)
{
	if (pDC)
	{
		GetWindowRect(m_rtWnd);
		ScreenToClient(m_rtWnd);
		m_rtWnd.OffsetRect(-m_rtWnd.left,-m_rtWnd.top);
		CRect	rcTitle;
		//绘制标题栏的大小
		rcTitle.left = 0;//m_rtWnd.left;
		rcTitle.top = 0;//m_rtWnd.top;
		rcTitle.right = m_rtWnd.Width()+ 3;
		rcTitle.bottom = rcTitle.top + m_nCaptionHeight+4 ;
		TRACE2("m_rtWnd::left == %d,right == %d\n",m_rtWnd.left,m_rtWnd.right);
		TRACE2("m_rtWnd::top == %d,bottom == %d\n",m_rtWnd.top,m_rtWnd.bottom);
		//////////////////////////////////////////////////////////////////
 		int  cx   =   GetSystemMetrics(   SM_CXSCREEN   );   
		int  cy   =   GetSystemMetrics(   SM_CYSCREEN   );
		TRACE2("Screen::cx == %d,cy == %d\n",cx,cy);

// 		CDC	dcTmp;
// 		dcTmp.CreateCompatibleDC(pDC);
// 		if (m_bmpCP.GetSafeHandle())
// 		{
// 			CBitmap *pOldBitmap=dcTmp.SelectObject(&m_bmpCP);
// 			BITMAP	bm;
// 			m_bmpGK.GetBitmap(&bm);
// 			TRACE0("*************************************************************************\n");
// 			TRACE2("rcTitle::width == %d,height == %d\n",rcTitle.Width(),rcTitle.Height());
// 			TRACE2("bm::width == %d,height == %d\n",bm.bmWidth,bm.bmHeight);
// 			pDC->SetStretchBltMode(HALFTONE);
// 			pDC->StretchBlt(
// //				0,0,
// 				rcTitle.left,rcTitle.top,
// 				m_rtWnd.Width(),
// 				rcTitle.Height(),
// // 				400,200,
// 				&dcTmp,
// 				0,0,
// 				bm.bmWidth,
// 				bm.bmHeight,
// 				SRCCOPY);
// // 			pDC->BitBlt(rcTitle.left,rcTitle.top,rcTitle.Width(),rcTitle.Height(),&dcTmp,0,0,SRCCOPY);
// 			dcTmp.SelectObject(pOldBitmap);
// 			pOldBitmap->DeleteObject();
// 		} 
  		DrawTitle(pDC,rcTitle);
		DrawBorder(pDC,m_rtWnd);
 	}
}
void	CMP3PlayerDlg::DrawBorder(CDC* pDC,CRect rcWnd)
{
	if (pDC->GetSafeHdc()!=INVALID_HANDLE_VALUE)
	{
		CPen	penBorder(PS_SOLID,1,RGB(100,20,50));
		CPen*	pOldpen = pDC->SelectObject(&penBorder);
		for (int i = 0;i<4;i++)
		{
			//左边框
			pDC->MoveTo(rcWnd.left+i,rcWnd.top + 14);
			pDC->LineTo(rcWnd.left+i,rcWnd.bottom);
			//下边框
			pDC->MoveTo(rcWnd.left,rcWnd.bottom-i);
			pDC->LineTo(rcWnd.right,rcWnd.bottom-i);
			//右边框
			pDC->MoveTo(rcWnd.right-i,rcWnd.top + 14);
			pDC->LineTo(rcWnd.right-i,rcWnd.bottom+14);
		}
		pDC->SelectObject(pOldpen);
	}
}
void	CMP3PlayerDlg::DrawTitle(CDC* pDC,CRect	rcTitle)
{
 		CDC	dcTmp;
		dcTmp.CreateCompatibleDC(pDC);
		if (m_bmpCP.GetSafeHandle())
		{
			CBitmap *pOldBitmap=dcTmp.SelectObject(&m_bmpCP);
			BITMAP	bm;
			m_bmpGK.GetBitmap(&bm);
			int nOldMode = pDC->SetStretchBltMode(HALFTONE);
			pDC->StretchBlt(
 				0,0,
//				rcTitle.left,rcTitle.top,
				rcTitle.Width(),
				rcTitle.Height(),
// 				400,200,
				&dcTmp,
 				0,0,
				bm.bmWidth,
				bm.bmHeight,
				SRCCOPY);
////			pDC->BitBlt(rcTitle.left,rcTitle.top,rcTitle.Width(),rcTitle.Height(),&dcTmp,0,0,SRCCOPY);
			dcTmp.SelectObject(pOldBitmap);
			pOldBitmap->DeleteObject();
			pDC->SetStretchBltMode(nOldMode);
			TRACE2("rcTitle::width == %d,height == %d\n",rcTitle.Width(),rcTitle.Height());
			TRACE2("bm::width == %d,height == %d\n",bm.bmWidth,bm.bmHeight);
		} 
}
void	CMP3PlayerDlg::DrawBKBmp(CDC* pDC,CRect rcWnd)
{
	if (m_bmpGK.GetSafeHandle()!=INVALID_HANDLE_VALUE)
	{
		CDC	dcTmp;
		dcTmp.CreateCompatibleDC(pDC);
		BITMAP	bmpBK;
		m_bmpGK.GetBitmap(&bmpBK);
		CBitmap*	pOldBmp = dcTmp.SelectObject(&m_bmpGK);
		pDC->StretchBlt(0,0,rcWnd.Width(),rcWnd.Height(),&dcTmp,
			0,0,bmpBK.bmWidth,bmpBK.bmHeight,SRCCOPY);
	}
}
