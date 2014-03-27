// SysBtn.cpp : implementation file
//

#include "stdafx.h"
#include "MP3Player.h"
#include "SysBtn.h"


// CSysBtn

IMPLEMENT_DYNAMIC(CSysBtn, CButton)

CSysBtn::CSysBtn()
{

}

CSysBtn::~CSysBtn()
{
}


BEGIN_MESSAGE_MAP(CSysBtn, CButton)
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void	CSysBtn::CreateSystemMenu(HWND pParentWnd,const CString& strPath,CRect rcBtn,UINT nImageCount /* = 3 */)
{
	ASSERT(pParentWnd);
	ASSERT(!strPath.IsEmpty());
	if (!strPath.IsEmpty())
	{
 		HBITMAP	hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),strPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_DEFAULTSIZE);
		m_bmp.Attach(hbmp);
		m_hParent = pParentWnd;
		m_nImageCount = nImageCount;
		m_strFilePath = strPath;
		m_rcBtn = rcBtn;
	}
}
void	CSysBtn::CreateSystemMenu(HWND pParentWnd,UINT nID,CRect rcBtn,UINT nImageCount /* = 3 */)
{
	ASSERT(pParentWnd);
	ASSERT(nID>0);
	if (nID>0)
	{
		m_nID = nID;
		m_bmp.LoadBitmap(MAKEINTRESOURCE(nID));
		m_hParent = pParentWnd;
		m_nImageCount = nImageCount;
 		m_rcBtn = rcBtn;
	}
}
void	CSysBtn::DrawButton(CDC* pDC)
{
	if (pDC->GetSafeHdc()!=INVALID_HANDLE_VALUE)
	{
		CDC	dcTmp;
		dcTmp.CreateCompatibleDC(pDC);
		BITMAP	bm;
		m_bmp.GetBitmap(&bm);
		//按钮宽度——由于载入的是N种状态的按钮图，故在画图时，需要将图片大小先分割，然后根据状态切换其他位置的图
		int	nWidth = bm.bmWidth/m_nImageCount;
		int	nHeight = bm.bmHeight;

		UINT	nBtnIndex = 0;
		if (!m_nStyle&BS_NOTIFY)
		{
			if (m_nStatus&ODS_FOCUS)
			{
				m_bFocus = m_bSelected = TRUE;
			}
			else
			{
				m_bSelected = m_bFocus = FALSE;
			}
			if (m_nStatus&ODS_DEFAULT||m_nStatus&ODS_SELECTED)
			{
				m_bFocus = TRUE;
			}
			if(m_bFocus)	nBtnIndex =1;
			else if(m_bFocus && m_bSelected)	nBtnIndex = 2;
			else	nBtnIndex = 3;

			HBITMAP	hBit = (HBITMAP)dcTmp.SelectObject(m_bmp);
			int	nOldMode = dcTmp.SetBkMode(TRANSPARENT);
			pDC->StretchBlt(m_rcBtn.left,m_rcBtn.top,m_rcBtn.Width(),m_rcBtn.Height(),&dcTmp,
				nWidth*(nBtnIndex-1),0,nWidth*nBtnIndex,nHeight,SRCCOPY);
			dcTmp.SelectObject(hBit);
			dcTmp.SetBkMode(nOldMode);
		}
	}
}
// CSysBtn message handlers




void CSysBtn::DrawItem(LPDRAWITEMSTRUCT  lpDrawItemStruct )
{

	// TODO:  Add your code to draw the specified item
	CRect	rcWnd;
	rcWnd = m_rcBtn;
	HDC	hdc = lpDrawItemStruct->hDC;
	CDC	dc;
	dc.Attach(hdc);
	m_nStatus = lpDrawItemStruct->itemState;
	m_nStyle = GetStyle();
	DrawButton(&dc);
	dc.Detach();
}


void CSysBtn::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bOver = TRUE;
	InvalidateRect(NULL);

// 	CButton::OnMouseHover(nFlags, point);
}


void CSysBtn::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default
	m_blnMouseOn = FALSE;
	m_bTracking = FALSE;
	m_bOver = FALSE;
	Invalidate();

// 	CButton::OnMouseLeave();
}


void CSysBtn::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	TRACKMOUSEEVENT		csTME;
	if (!m_bTracking)
	{
		m_blnMouseOn = TRUE;
		m_bOver = TRUE;
		Invalidate();
		csTME.cbSize = sizeof(csTME);
		csTME.dwFlags = TME_LEAVE|TME_HOVER;
		csTME.hwndTrack = m_hWnd;
		m_bTracking = ::_TrackMouseEvent(&csTME);
	}

	CButton::OnMouseMove(nFlags, point);
}


void CSysBtn::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CButton::OnLButtonDown(nFlags, point);
}


void CSysBtn::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	CButton::PreSubclassWindow();//先确保原先样式
	ModifyStyle(0,BS_OWNERDRAW);	//打开自绘属性
	CRect	rect;
	GetClientRect(rect);
	ClientToScreen(rect);
	CWnd*	pWnd = GetParent();
	if(pWnd)	pWnd->ScreenToClient(rect);
	MoveWindow(rect,TRUE);

	CButton::PreSubclassWindow();
}
