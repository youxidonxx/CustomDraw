
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

	m_bNCHovering = FALSE;
	m_bNCTracking = FALSE;

	m_nDownIndex = m_nHoverIndex = System_Menu_Null;
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
	ON_WM_NCMOUSELEAVE()
	ON_WM_NCMOUSEHOVER()
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////////
 void	CMP3PlayerDlg::SetSysMenu()
 {
	 CRect	rcDlg;
	 rcDlg = m_rtWnd;
	 CRect	rcBtn;
	 rcBtn.left=  rcDlg.right - INIT_SYSTEM_MENU_SIZE -INIT_CAPTION_OFFSET;
	 rcBtn.top =  rcDlg.top +INIT_CAPTION_OFFSET/2;
	 rcBtn.right = rcBtn.left + INIT_SYSTEM_MENU_SIZE;
	 rcBtn.bottom = rcBtn.top+m_nCaptionHeight;
 	 m_rtButtExit = rcBtn;

	 rcBtn.left = rcBtn.left - INIT_SYSTEM_MENU_SIZE -1;
	 rcBtn.right = rcBtn.left + INIT_SYSTEM_MENU_SIZE;

	 m_rtButtMin = rcBtn;

	 rcBtn.left = rcBtn.left - INIT_SYSTEM_MENU_SIZE -1;
	 rcBtn.right = rcBtn.left + INIT_SYSTEM_MENU_SIZE;

	 m_rtButtMax = rcBtn;

	 rcBtn.left = rcBtn.left - INIT_SYSTEM_MENU_SIZE -1;
	 rcBtn.right = rcBtn.left + INIT_SYSTEM_MENU_SIZE;
	 m_rtButtMenu = rcBtn;
  }
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

	GetWindowRect(m_rtWnd);
	CString	str;
	TCHAR	path[MAX_PATH];
	GetPath(path);
	str=path;
	if (!str.IsEmpty())
	{
		str +=_T("\\skin");
		SetBkImage(str+DLG_BK,str+DLG_TITLE);
		m_strPath = str;
		SetSysMenu();
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
	CPoint	pt = point;
	ScreenToClient(&pt);
	pt.Offset(CSize(INIT_CAPTION_OFFSET,(m_nCaptionHeight+INIT_CAPTION_OFFSET)));
	GetPtOfSysmenu(pt);
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
	if (!m_bNCTracking)
	{
		CPoint	pt = point;
		ScreenToClient(&pt);
		pt.Offset(CSize(INIT_CAPTION_OFFSET,(m_nCaptionHeight+INIT_CAPTION_OFFSET)));
		if (m_rtButtMax.PtInRect(pt)
			|| m_rtButtMin.PtInRect(pt))
		{
			m_bNCHovering = TRUE;
		}
		TRACKMOUSEEVENT	tms;
		tms.cbSize = sizeof(tms);
		tms.hwndTrack = m_hWnd;
		tms.dwFlags = TME_NONCLIENT;
		tms.dwHoverTime = 1;
		m_bNCTracking = ::_TrackMouseEvent(&tms);
	}
	CDialogEx::OnNcMouseMove(nHitTest, point);
}
void CMP3PlayerDlg::OnNcMouseLeave()
{
	// This feature requires Windows 2000 or greater.
	// The symbols _WIN32_WINNT and WINVER must be >= 0x0500.
	// TODO: Add your message handler code here and/or call default
	m_bNCHovering = FALSE;
	m_bNCTracking = FALSE;

	// 	CDialogEx::OnNcMouseLeave();
}


void CMP3PlayerDlg::OnNcMouseHover(UINT nFlags, CPoint point)
{
	// This feature requires Windows 2000 or greater.
	// The symbols _WIN32_WINNT and WINVER must be >= 0x0500.
	// TODO: Add your message handler code here and/or call default
	m_bNCHovering = TRUE;
	// 	CDialogEx::OnNcMouseHover(nFlags, point);
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

	CRect tst(2,2,m_nCaptionHeight+INIT_CAPTION_OFFSET,m_nCaptionHeight+INIT_CAPTION_OFFSET);
// 	tst.OffsetRect(m_rtWnd.TopLeft());//原图标屏幕位置
	CPoint	pt = point;
	ScreenToClient(&pt);
  	pt.Offset(CSize(INIT_CAPTION_OFFSET,(m_nCaptionHeight+INIT_CAPTION_OFFSET)));
	//x需要偏移(-4,-24)
//  	TRACE2("OnHitTest::x == %d,y == %d\n",point.x,point.y);
 	if(tst.PtInRect(pt))//最大最小关闭按钮位置.
		return HTCAPTION;
	else if(m_rtButtMin.PtInRect(pt)||
		m_rtButtMax.PtInRect(pt)||
		m_rtButtExit.PtInRect(pt))
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
		pDC->SetBkMode(TRANSPARENT);
		GetWindowRect(m_rtWnd);
		ScreenToClient(m_rtWnd);
		m_rtWnd.OffsetRect(-m_rtWnd.left,-m_rtWnd.top);
		CRect	rcTitle;
		//绘制标题栏的大小
		rcTitle.left = 0;//m_rtWnd.left;
		rcTitle.top = 0;//m_rtWnd.top;
		rcTitle.right = m_rtWnd.Width()+ 3;
		rcTitle.bottom = rcTitle.top + m_nCaptionHeight+INIT_CAPTION_OFFSET ;
  		DrawTitle(pDC,rcTitle);
		DrawBorder(pDC,m_rtWnd);
		DrawSysMenu(pDC);
 	}
}
void	CMP3PlayerDlg::DrawBorder(CDC* pDC,CRect rcWnd)
{
	if (pDC->GetSafeHdc()!=INVALID_HANDLE_VALUE)
	{
		CPen	penBorder(PS_SOLID,1,RGB(100,20,50));
		CPen*	pOldpen = pDC->SelectObject(&penBorder);
		for (int i = 0;i<INIT_CAPTION_OFFSET;i++)
		{
			//左边框
			pDC->MoveTo(rcWnd.left+i,rcWnd.top + INIT_CAPTION_HEIGHT+INIT_CAPTION_OFFSET);
			pDC->LineTo(rcWnd.left+i,rcWnd.bottom);
			//下边框
			pDC->MoveTo(rcWnd.left,rcWnd.bottom-i);
			pDC->LineTo(rcWnd.right,rcWnd.bottom-i);
			//右边框
			pDC->MoveTo(rcWnd.right-i,rcWnd.top + INIT_CAPTION_HEIGHT+INIT_CAPTION_OFFSET);
			pDC->LineTo(rcWnd.right-i,rcWnd.bottom+INIT_CAPTION_HEIGHT+INIT_CAPTION_OFFSET);
		}
		pDC->SelectObject(pOldpen);
	}
}
void	CMP3PlayerDlg::DrawTitle(CDC* pDC,CRect	rcTitle)
{
 		CDC	dcTmp;
		dcTmp.CreateCompatibleDC(pDC);
		if (m_bmpCP.GetSafeHandle())
		{//标题栏绘制
			CBitmap *pOldBitmap=dcTmp.SelectObject(&m_bmpCP);
			BITMAP	bm;
			m_bmpCP.GetBitmap(&bm);
			int nOldMode = pDC->SetStretchBltMode(HALFTONE);
			pDC->StretchBlt(
 				0,0,
				rcTitle.Width(),
				rcTitle.Height(),
 				&dcTmp,
 				0,0,
				bm.bmWidth,
				bm.bmHeight,
				SRCCOPY);
 			dcTmp.SelectObject(pOldBitmap);
			pOldBitmap->DeleteObject();
			pDC->SetStretchBltMode(nOldMode);

		} 
		//首先查看是否有icon显示
		if (m_hIcon)
		{
			ICONINFO	icc;
			GetIconInfo(m_hIcon,&icc);
			rcTitle.left = rcTitle.left + INIT_CAPTION_OFFSET;
			rcTitle.top = rcTitle.top + INIT_CAPTION_OFFSET/2;
			rcTitle.right = rcTitle.left + icc.xHotspot;
			rcTitle.bottom = rcTitle.top + icc.yHotspot;
			pDC->DrawIcon(rcTitle.left,rcTitle.top,m_hIcon);
			//若是有icon，则将坐标右移一段，以方便下一步标题文字坐标确定
			rcTitle.left += INIT_SYSTEM_MENU_SIZE;
		}
		//标题文字
		CString	str;
		GetWindowText(str);
		if (!str.IsEmpty())
		{
			CSize	szText = pDC->GetTextExtent(str);
// 			rcTitle.left += INIT_SYSTEM_MENU_SIZE;
			rcTitle.right =  rcTitle.left + szText.cx;
			CFont*	pOld = GetFont();
			pDC->SetTextColor(RGB(0,0,255));
			pDC->SelectObject(pOld);
			pDC->DrawText(str,&rcTitle,DT_SINGLELINE|DT_LEFT);
		}
}
void	CMP3PlayerDlg::DrawSysMenu(CDC* pDC)
{
 	DrawMenuBtn(pDC,m_rtButtMin,m_strPath+DLG_BUTTON_MIN);
	DrawMenuBtn(pDC,m_rtButtMax,m_strPath+DLG_BUTTON_MAX);
	DrawMenuBtn(pDC,m_rtButtExit,m_strPath+DLG_BUTTON_CLOSE);
	DrawMenuBtn(pDC,m_rtButtMenu,m_strPath+DLG_BUTTON_MENU);
}
void	CMP3PlayerDlg::DrawMenuBtn(CDC* pDC,CRect rcBtn,CString strFile)
{
	if (!strFile.IsEmpty())
	{
		CDC	dcTmp;
		dcTmp.CreateCompatibleDC(pDC);
		CBitmap	bmp;
		CString	strPath =strFile;
		HBITMAP	hbit = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),strPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_DEFAULTSIZE);
		BOOL	bRet = bmp.Attach(hbit);//bmp.LoadBitmap(_T("D:\\Code_Lib\\SourceCode\\Test\\CustomControl\\Debug\\skin\\sys_dlg_min.bmp"));
		if(!bRet)
		{
			DWORD	dwErr = GetLastError();
			TRACE1("GetLastError:%d\n",dwErr);
			return;
		}
		BITMAP	bm;
		bmp.GetBitmap(&bm);
		CBitmap*	pTmp = dcTmp.SelectObject(&bmp);
		int	nWidth = bm.bmWidth/SYSTEM_MENU_STATE_NUM;
		int	nIndex = 3;
		if (m_bNCHovering)
		{
			nIndex = 2;
		}
		bRet = pDC->StretchBlt(rcBtn.left,rcBtn.top,rcBtn.Width(),rcBtn.Height(),&dcTmp,nWidth*(3-nIndex),0,
			nWidth*(4-nIndex),bm.bmHeight,SRCCOPY);
		if(!bRet)
		{
			DWORD	dwErr = GetLastError();
			TRACE1("GetLastError:%d\n",dwErr);
		}
		dcTmp.SelectObject(pTmp);
		pTmp->DeleteObject();
		bmp.Detach();
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
		dcTmp.SelectObject(pOldBmp);
		pOldBmp->DeleteObject();
	}
}
void	CMP3PlayerDlg::GetPtOfSysmenu(CPoint pt)
{
	if (m_rtButtMax.PtInRect(pt))
	{

	}
}



