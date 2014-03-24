// TestButton.cpp : implementation file
//

#include "stdafx.h"
#include "CustomControl.h"
#include "TestButton.h"


// CTestButton

IMPLEMENT_DYNAMIC(CTestButton, CButton)

CTestButton::CTestButton()
{
	m_blnMouseOn = FALSE;
}

CTestButton::~CTestButton()
{
}


BEGIN_MESSAGE_MAP(CTestButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// CTestButton message handlers

void	CTestButton::PreSubclassWindow()
{
	CButton::PreSubclassWindow();

	ModifyStyle(0,BS_OWNERDRAW);
	CRect	rect;
	GetClientRect(rect);
	ClientToScreen(rect);
	CWnd*	pWnd = GetParent();
	if(pWnd)	pWnd->ScreenToClient(rect);
	MoveWindow(rect,TRUE);
}
void	CTestButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//////////////////////////////////////////////////////////////////////////
	// if using attach func, this dc should be non-pointer,and when it's done,need to be release by detach() func
// 	CDC	pDC ;
// 	pDC.Attach(lpDrawItemStruct->hDC);
	//////////////////////////////////////////////////////////////////////////
	//if using getdc() func to get dc , when it's done,it need to be releasedc() to destory the resource
// 	CDC*	pDC = GetDC();
	//////////////////////////////////////////////////////////////////////////
	// 1. this is a temp dc using fromhandle func,so it needn't  release.
	CDC*	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect	rcBtn = lpDrawItemStruct->rcItem;
	CString	str;
	GetWindowText(str);
	if (!str.IsEmpty())
	{
		CSize	size = pDC->GetTextExtent(str);
		if(rcBtn.right!= rcBtn.left + size.cx + 10 || rcBtn.bottom != rcBtn.top + size.cy + 5)
		{
			rcBtn.right = rcBtn.left + size.cx + 10;
			rcBtn.bottom = rcBtn.top + size.cy + 5 ;
		}
	}
	CRgn	rgn;
	rgn.CreateRectRgn(rcBtn.left,rcBtn.top,rcBtn.right,rcBtn.bottom);
	pDC->SelectClipRgn(&rgn);
	int	nSaveDC =	pDC->SaveDC();
	CBrush	brush;
	brush.CreateSolidBrush(RGB(100,100,20));
	pDC->FrameRgn(&rgn,&brush,2,2);

// 	CString	str;
// 	GetWindowText(str);
	if (!str.IsEmpty())
	{
		CSize	size = pDC->GetTextExtent(str);
		if(rcBtn.right!= rcBtn.left + size.cx + 10 || rcBtn.bottom != rcBtn.top + size.cy + 5)
		{
			rcBtn.right = rcBtn.left + size.cx + 10;
			rcBtn.bottom = rcBtn.top + size.cy + 5 ;
 		}
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(12,125,32));
		pDC->TextOut(rcBtn.left+3,rcBtn.top,str);
	}

	pDC->SelectClipRgn(NULL);
	pDC->RestoreDC(nSaveDC);
	rgn.DeleteObject();
	//////////////////////////////////////////////////////////////////////////
	// it's used when attach func occurs
//   	pDC->Detach();
	// it's used when getdc func occurs
//	ReleaseDC(pDC);
}

void CTestButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd*				wndUnderMouse = NULL;
	CWnd*				wndActive = this;
	TRACKMOUSEEVENT		csTME;
	CButton::OnMouseMove(nFlags, point);
	ClientToScreen(&point);
	wndUnderMouse = WindowFromPoint(point);
	if(nFlags&MK_LBUTTON)	return;
	wndActive = GetActiveWindow();
	if (wndUnderMouse && wndUnderMouse->GetSafeHwnd() == m_hWnd && wndActive)
	{
		if (!m_blnMouseOn)
		{
			TRACE0("\CTestButton::OnMouseMove m_blnMouseOn == FALSE\n");
			m_blnMouseOn = TRUE;
			Invalidate();
			csTME.cbSize = sizeof(csTME);
			csTME.dwFlags = TME_LEAVE;
			csTME.hwndTrack = m_hWnd;
			::_TrackMouseEvent(&csTME);
		}
	}
	else
	{
		TRACE0("\CTestButton::OnMouseMove m_blnMouseOn == TRUE\n");
		m_blnMouseOn = FALSE;
		Invalidate();
	}
}


void CTestButton::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default
// 	m_blnMouseOn = FALSE;
// 	Invalidate();

	CButton::OnMouseLeave();
}
