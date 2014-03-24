// CustomBtn.cpp : implementation file
//

#include "stdafx.h"
#include "CustomControl.h"
#include "CustomBtn.h"


// CCustomBtn

IMPLEMENT_DYNAMIC(CCustomBtn, CButton)

CCustomBtn::CCustomBtn()
{
	m_clrText=RGB(0,100,0);
	m_clrBack = RGB(192,151,51);
	m_clrLeft=RGB(97,244,78);
	m_clrRight=RGB(52,148,39);
	m_clrBorder = RGB(0,0,0);

	m_nButtonFace = 1;
	m_blnMouseOn	=	FALSE;
	m_nAlgin	=	8;
	m_clrFlatBack=GetSysColor(COLOR_3DFACE+1);
	m_BrushBack.CreateSolidBrush(m_clrFlatBack);
	m_nGradient = 10;
	m_nBtnStyle = 0;
	m_bFit = FALSE;

	m_hIcon = NULL;
	m_bSmall = FALSE;

	m_bFocus = m_bOver = m_bSelected = m_bTracking = FALSE;

}

CCustomBtn::~CCustomBtn()
{
	m_rgn.DeleteObject();
	m_BrushBack.DeleteObject();
}


BEGIN_MESSAGE_MAP(CCustomBtn, CButton)
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_MOUSEHOVER()
 END_MESSAGE_MAP()

void	CCustomBtn::PreSubclassWindow()
{
	CButton::PreSubclassWindow();//先确保原先样式
	ModifyStyle(0,BS_OWNERDRAW);	//打开自绘属性
	CRect	rect;
	GetClientRect(rect);
// 	//窗口的RGN的坐标体系不是屏幕坐标，而是以窗口的左上角开始的。所以不做坐标变换
// 	//The coordinates of a window's window region are relative to the upper-left corner of the window, not the client area of the window.
// 
// 	m_rgn.DeleteObject();
// 	//开始绘制区域
// 	SetWindowRgn(NULL,FALSE);
// 	if (m_nButtonFace == 0)
// 		m_rgn.CreateRectRgn(rect.left,rect.top,rect.right,rect.bottom);
// 	else if(m_nButtonFace == 1)
// 		m_rgn.CreateRoundRectRgn(rect.left,rect.top,rect.right,rect.bottom,ROUND_CORNER,ROUND_CORNER);
// 	else if(m_nButtonFace == 2)
// 		m_rgn.CreateEllipticRgn(rect.left,rect.top,rect.right,rect.bottom);
// 	SetWindowRgn(m_rgn,TRUE);
	//绘制区域结束
	//根据MSDN说法，在启用该函数之后，该区域的句柄已被系统接管，而无法被别人使用
	//the system owns the region specified by the region handle hRgn.
	//The system does not make a copy of the region. Thus, you should not make any further function 
	//calls with this region handle. In particular, do not delete this region handle. 
	//The system deletes the region handle when it no longer needed.
	ClientToScreen(rect);
	CWnd*	pWnd = GetParent();
	if(pWnd)	pWnd->ScreenToClient(rect);
	MoveWindow(rect,TRUE);
	//////////////////////////////////////////////////////////////////////////
	EnableToolTipOn();
 }

void	CCustomBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ASSERT(NULL!=lpDrawItemStruct);
	//获取DC
	CDC*	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect	rcItem = lpDrawItemStruct->rcItem;
	UINT	uState	=	lpDrawItemStruct->itemState;
	UINT	nStyle	=	GetStyle();
	CRgn	rgn1,rgn2;
	int		r1,b1,g1;
	//////////////////////////////////////////////////////////////////////////
	//裁剪窗口边界区域
 	if (m_nButtonFace == 0)
	{
		rgn1.CreateRectRgn(rcItem.left,rcItem.top,rcItem.right,rcItem.bottom);			//绘制外框
		rgn2.CreateRectRgn(rcItem.left+1,rcItem.top+1,rcItem.right-1,rcItem.bottom-1);//绘制内框
	}
	else if (m_nButtonFace == 1)
	{
		rgn1.CreateRoundRectRgn(rcItem.left,rcItem.top,rcItem.right,rcItem.bottom,ROUND_CORNER,ROUND_CORNER);
		rgn2.CreateRoundRectRgn(rcItem.left+1,rcItem.top+1,rcItem.right-1,rcItem.bottom-1,ROUND_CORNER,ROUND_CORNER);//绘制内框
	}
	else if (m_nButtonFace	==	2)
	{
		rgn1.CreateEllipticRgn(rcItem.left,rcItem.top,rcItem.right,rcItem.bottom);
		rgn2.CreateEllipticRgn(rcItem.left+1,rcItem.top+1,rcItem.right-1,rcItem.bottom-1);//绘制内框
	}
	pDC->SelectClipRgn(&rgn1);
	//////////////////////////////////////////////////////////////////////////
	int	nSaveDC	=	pDC->SaveDC();
	CBrush	brush1,brush2;
	if (!(nStyle&BS_NOTIFY))
	{
		//按照状态进行分类
		if(uState&ODS_FOCUS)
		{
			m_bFocus = TRUE;
			m_bSelected = TRUE;
		}
		else
		{
			m_bSelected = m_bFocus = FALSE;
		}


		if (uState&ODS_SELECTED || uState&ODS_DEFAULT)
		{
			m_bFocus = TRUE;
		}
		if(m_nButtonFace!=2)
		{
			DrawGradientFill(pDC,rcItem);
			DrawBorder(pDC,&rgn1,&rgn2);
		}
// 		if ((uState&ODS_FOCUS)||(uState&ODS_SELECTED))//当前状态
// 		{
// 			if(m_nBtnStyle!=2)
// 			{
// 				m_nAlgin = 7;
// // 				r1	=	GetRValue(m_clrBack);
// // 				g1	=	GetGValue(m_clrBack);
// // 				b1	=	GetBValue(m_clrBack);
// // 				//此处为渐变色处理，由两边向中间渐变
// // 				for (int i = rcItem.Height()/2;i>0;i--)
// // 				{
// // 					r1=(r1+m_nGradient)>255?255:(r1+m_nGradient);
// // 					g1=(g1+m_nGradient)>255?255:(g1+m_nGradient);
// // 					b1=(b1+m_nGradient)>255?255:(b1+m_nGradient);
// // 					CPen pen(PS_SOLID, 1, RGB(r1, g1, b1));
// // 					CPen *old = pDC->SelectObject(&pen);
// // 					pDC->MoveTo(rcItem.left,rcItem.top+i);
// // 					pDC->LineTo(rcItem.right,rcItem.top+i);
// // 					pDC->MoveTo(rcItem.left,rcItem.bottom-i);
// // 					pDC->LineTo(rcItem.right,rcItem.bottom-i);
// // 					pDC->SelectObject(old);
// // 				}
// 				r1=GetRValue(m_clrLeft);
// 				g1=GetGValue(m_clrLeft);
// 				b1=GetBValue(m_clrLeft);
// 				r1=(r1+m_nGradient)>255?255:(r1+m_nGradient);
// 				g1=(g1+m_nGradient)>255?255:(g1+m_nGradient);
// 				b1=(b1+m_nGradient)>255?255:(b1+m_nGradient);
// 				brush2.CreateSolidBrush(m_clrLeft);
// 				brush1.CreateSolidBrush(RGB(r1,g1,b1));
// // 				pDC->FrameRgn(&rgn1,&brush1,1,1);
// // 				pDC->FrameRgn(&rgn2,&brush2,1,1);
// 			}
//  		}
// 		else if(m_blnMouseOn)
// 		{
// // 			m_nAlgin = 4;
// // 			if(m_nBtnStyle!=2)
// // 			{
// // // 				r1	=	GetRValue(m_clrBack);
// // // 				g1	=	GetGValue(m_clrBack);
// // // 				b1	=	GetBValue(m_clrBack);
// // // 				//此处为渐变色处理，由两边向中间渐变
// // // 				for (int i = rcItem.Height()/2;i>0;i--)
// // // 				{
// // // 					r1=(r1+m_nGradient)>255?255:(r1+m_nGradient);
// // // 					g1=(g1+m_nGradient)>255?255:(g1+m_nGradient);
// // // 					b1=(b1+m_nGradient)>255?255:(b1+m_nGradient);
// // // 					CPen pen(PS_SOLID, 1, RGB(r1, g1, b1));
// // // 					CPen *old = pDC->SelectObject(&pen);
// // // 					pDC->MoveTo(rcItem.left,rcItem.top+i);
// // // 					pDC->LineTo(rcItem.right,rcItem.top+i);
// // // 					pDC->MoveTo(rcItem.left,rcItem.bottom-i);
// // // 					pDC->LineTo(rcItem.right,rcItem.bottom-i);
// // // 					pDC->SelectObject(old);
// // // 				}
// // 				//////////////////////////////////////////////////////////////////////////
// // 				//绘制内外边框的颜色
// // 				r1= GetRValue(m_clrRight);
// // 				g1= GetGValue(m_clrRight);
// // 				b1= GetBValue(m_clrRight);
// // 				r1=(r1+m_nGradient)>255?255:(r1+m_nGradient);
// // 				g1=(g1+m_nGradient)>255?255:(g1+m_nGradient);
// // 				b1=(b1+m_nGradient)>255?255:(b1+m_nGradient);
// // 				brush1.CreateSolidBrush(RGB(r1,g1,b1));
// // 				brush2.CreateSolidBrush (m_clrRight);
// // // 				pDC->FrameRgn(&rgn1,&brush1,1,1);
// // // 				pDC->FrameRgn(&rgn2,&brush2,1,1);
// // 				//////////////////////////////////////////////////////////////////////////
// //  			}
// 		}
// 		else
// 		{
// 
// // 			brush1.CreateSolidBrush(m_clrBorder);
// // 			pDC->FrameRgn(&rgn1,&brush1,2,1);
// 			TRACE0("DrawItem::m_blnMouseOn == false .\n");
// 		}
 	}
	else
	{
		pDC->FillSolidRect(rcItem,m_clrText);
		TRACE0("DrawItem::other\n");
	}
	//输出文字	
// 	CFont*	pFt = GetFont();
// 	LOGFONT	lg;
// 	pFt->GetLogFont(&lg);
//  	CPoint m_ptCentre=rcItem.CenterPoint();
	CString strText;
	GetWindowText(strText);
	if (!strText.IsEmpty())
	{
		if (strText.CompareNoCase(m_strToolTip) != 0)//完全匹配，部分大小写
		{
			m_tip.UpdateTipText(strText.GetBuffer(),this);
			strText.ReleaseBuffer();
			m_strToolTip = strText;
		}
		if(m_nBtnStyle!=2)
		{
			DrawText(pDC,rcItem,strText,uState);
			if(m_nBtnStyle == 3)
				DrawIcon(pDC,uState);
		}
// 		pDC->SetTextColor(m_clrText);
// 		CSize	size = pDC->GetTextExtent(strText);
// 		//文字位置进行设置，以九宫格为根据
// 		CPoint	pt = GetTextPos(pDC,m_nAlgin,rcItem,strText);
// 		if(m_nBtnStyle!=2)
// 		{
// 			if(uState&ODS_SELECTED)
// 				pt.Offset(1,1);
// 			pDC->SetBkMode(TRANSPARENT);
// 			if((uState&ODS_DISABLED)&&!(nStyle&BS_NOTIFY))
// 				pDC->DrawState(pt,size,strText,DSS_DISABLED,TRUE,0,(HBRUSH)NULL);
// 			else if(uState&BS_NOTIFY)
// 			{
// 				pDC->FillRect(rcItem,&m_BrushBack);
// 				if(uState&ODS_FOCUS || uState&ODS_SELECTED)
// 				{
// 					pDC->SetTextColor(m_clrText);
// 					pDC->TextOut(pt.x+2,pt.y,strText);
// 				}
// 				else
// 				{
// 					pDC->TextOut(pt.x, pt.y, strText);		
// 				}
// 			}
// 			else
// 			{
// 				if(m_nBtnStyle!=2)
// 					pDC->TextOut(pt.x, pt.y, strText);
// 				else
// 					DrawTextOnBmp(pDC,strText);
// 			}
// 			TRACE0("DrawItem::Text Drawing Without Bitmap .\n");
// 		}
		else
		{
			DrawBitmap(pDC);
			TRACE0("DrawItem::Text Drawing On Bitmap .\n");
		}
	}
	pDC->SelectClipRgn(NULL);
	pDC->RestoreDC(nSaveDC);
	rgn1.DeleteObject();
	rgn2.DeleteObject();
}
void	CCustomBtn::DrawBorder(CDC* pDC,CRgn*	rgnOut,CRgn*	rgnIn)
{
	CBrush	brush1,brush2;
	brush1.CreateSolidBrush(m_clrBorder);
 	//brush1 用于外边框，brush2用于内边框
	if (pDC)
	{
		pDC->FrameRgn(rgnOut,&brush1,2,2);
		//根据当前鼠标状态绘制内边框
		if(m_bOver || m_bSelected)
		{
			if (m_bOver&&!m_bSelected)//1、当前悬浮而未被选中
			{
				brush2.CreateSolidBrush(m_clrLeft);
			}
			else if (m_bSelected)	//2、被点击选中
			{
				brush2.CreateSolidBrush(m_clrRight);
			}
			pDC->FrameRgn(rgnIn,&brush2,1,1);
		}
	}
}
void	CCustomBtn::DrawGradientFill(CDC* pDC ,CRect rcWnd)
{
	if(!pDC)
		return;
	int		r1,b1,g1;
	COLORREF	clrBack;
	//根据当前鼠标状态绘制内边框
	if(m_bOver || m_bSelected)
	{
		if (m_bOver&&!m_bSelected)//1、当前悬浮而未被选中
			clrBack = m_clrLeft;
		else if(m_bSelected)
			clrBack = m_clrRight;
		else
			clrBack  = RGB(255,255,255);
	}
	else	//说明鼠标与焦点未在窗口上，故显示纯白底色
	{
		clrBack = RGB(255,255,255);
	}
		r1	=	GetRValue(clrBack);
		g1	=	GetGValue(clrBack);
		b1	=	GetBValue(clrBack);
		//此处为渐变色处理，由两边向中间渐变
		for (int i = rcWnd.Height()/2;i>0;i--)
		{
			r1=(r1+m_nGradient)>255?255:(r1+m_nGradient);
			g1=(g1+m_nGradient)>255?255:(g1+m_nGradient);
			b1=(b1+m_nGradient)>255?255:(b1+m_nGradient);
			CPen pen(PS_SOLID, 1, RGB(r1, g1, b1));
			CPen *old = pDC->SelectObject(&pen);
			pDC->MoveTo(rcWnd.left,rcWnd.top+i);
			pDC->LineTo(rcWnd.right,rcWnd.top+i);
			pDC->MoveTo(rcWnd.left,rcWnd.bottom-i);
			pDC->LineTo(rcWnd.right,rcWnd.bottom-i);
			pDC->SelectObject(old);
	}
}
void	CCustomBtn::DrawText(CDC* pDC,CRect rcWnd,const CString& str,DWORD	dwState)
{
	if (pDC)
	{
		CFont*	pFt = GetFont();
		LOGFONT	lg;
		CPoint	center = rcWnd.CenterPoint();
		CSize	size = pDC->GetTextExtent(str);
		CPoint	pt = GetTextPos(pDC,m_nAlgin,rcWnd,str);
		pFt->GetLogFont(&lg);
		pDC->SetTextColor(m_clrText);
		pDC->SetBkMode(TRANSPARENT);
 		if (m_bSelected)	//当被选中时，字体下压效果
		{
			pt.Offset(1,1);
		}
 		if (( dwState& ODS_DISABLED) && !(dwState&BS_NOTIFY))//不可用时
		{
			pDC->DrawState(pt,size,str,DSS_DISABLED,TRUE,0,(HBRUSH)NULL);
		}
		else if ( dwState&BS_NOTIFY)
		{
			pDC->FillRect(rcWnd,&m_BrushBack);
			if (m_bFocus || m_bSelected)
			{
				pDC->SetTextColor(m_clrText);
				pDC->TextOut(pt.x + 2,pt.y,str);
			}
			else
				pDC->TextOut(pt.x,pt.y,str);
		}
		else 
			pDC->TextOut(pt.x,pt.y,str);
	}
}
void	CCustomBtn::EnableToolTipOn()
{
	EnableToolTips(TRUE);
	if(m_tip.GetSafeHwnd())
		return;
	m_tip.Create(this);
	GetWindowText(m_strToolTip);
	m_tip.AddTool(this,m_strToolTip);
	m_tip.SetMaxTipWidth(MAX_PATH);
	m_tip.Activate(TRUE);
}
CPoint	CCustomBtn::GetTextPos(CDC* pDC,UINT nAlginType,CRect rcBtn,CString	strText)
{
	CPoint	pt = CPoint(0,0);
	ASSERT(pDC!=NULL);
	ASSERT(nAlginType>=0 && nAlginType<Algin_Type_Num);
	if (pDC)
	{
		CSize	size = pDC->GetTextExtent(strText);
		CPoint	center = rcBtn.CenterPoint();
		switch (nAlginType)
		{
		case Algin_Left_Top:
			{
				pt.x = rcBtn.left+ALGIN_CONST;
				pt.y = rcBtn.top + ALGIN_CONST;
			}
			break;
		case Algin_Center_Top:
			{
				pt.x = rcBtn.left+size.cx/2;
				pt.y = rcBtn.top+ALGIN_CONST;
			}
			break;
		case Algin_Right_Top:
			{
				pt.x = rcBtn.right - ALGIN_CONST -size.cx;
				pt.y = rcBtn.top+ALGIN_CONST;
			}
			break;
		case Algin_Left_Middle:
			{
				pt.x = rcBtn.left+10;
				pt.y = center.y - size.cy/2;
			}
			break;
		case Algin_Center:
			{
				pt.x = center.x-size.cx/2;
				pt.y = center.y - size.cy/2;
			}
			break;
		case Algin_Right_Middle:
			{
				pt.x =rcBtn.right - ALGIN_CONST - size.cx;
				pt.y = center.y - size.cy/2;
			}
			break;
		case Algin_Left_Bottom:
			{
				pt.x = rcBtn.left + ALGIN_CONST;
				pt.y = rcBtn.bottom -size.cy-ALGIN_CONST;
			}
			break;
		case Algin_Center_Bottom:
			{
				pt.x = center.x - size.cx/2;
				pt.y = rcBtn.bottom -size.cy-ALGIN_CONST;
			}
			break;
		case Algin_Right_Bottom:
			{
				pt.x = rcBtn.right -ALGIN_CONST - size.cx;
				pt.y = rcBtn.bottom-size.cy - ALGIN_CONST;
			}
			break;
		default://默认以中间进行排位
			{
				pt.x = center.x-size.cx/2;
				pt.y = center.y - size.cy/2;
			}
			break;
 		}
	}
	return pt;
}
// CCustomBtn message handlers
void	CCustomBtn::SetMouseMove(BOOL bOn /* = TRUE */)
{
	m_blnMouseOn = bOn;	 
 	Invalidate();
}
void	CCustomBtn::SetButtonFace(UINT nType /* = 0 */)
{
	ASSERT(nType>=0);
	m_nButtonFace = nType;
	this->Invalidate();
}
void	CCustomBtn::SetButtonAlgin(UINT nAlgin /* = 0 */)
{
	ASSERT(nAlgin>=0);
	m_nAlgin = nAlgin;
	this->Invalidate();
}
void	CCustomBtn::ExpentToFit(BOOL bFit /* = TRUE */)
{
	m_bFit = bFit;
	if(bFit == TRUE)
	{
		//若是需要铺满按钮窗口，则此时居中显示，外形取得文字大小
		m_nAlgin = Algin_Center+1;
		CString	str;
		GetWindowText(str);
		CDC*	pDC = GetDC();
		CSize size = pDC->GetTextExtent(str);
		
		CRect	rcBtn;
		GetWindowRect(rcBtn);
		int nHeight = rcBtn.Height();
		int	nWidth = rcBtn.Width();
		CPoint	pt = rcBtn.CenterPoint();
		//对窗口大小与字体大小进行比较
		if (size.cx<nWidth || size.cy <nHeight)
		{
			CRect	newRC;
			newRC.left = rcBtn.left;
			newRC.top = rcBtn.top;
			newRC.right = rcBtn.left+size.cx +ALGIN_CONST;
			newRC.bottom = rcBtn.top+size.cy  + ALGIN_CONST;
			MoveWindow(newRC,TRUE);
		}
	}
	Invalidate();
}
/************************************************************************/
/*    //相互转换：
CBitmap bmp;
HBITMAP hBmp;
  hBmp=(HBITMAP)bmp.GetSafeHandle();
  bmp.Attach(hBmp);
*/
/************************************************************************/
void	CCustomBtn::LoadBtnIcon(UINT nResourceID,BOOL	bSmall /*= TRUE*/)
{
	ASSERT(nResourceID>0);
	HICON icon =  LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(nResourceID));
	if(icon)
	{
		//先释放icon
		::DestroyIcon(m_hIcon);
		m_hIcon =icon;
		m_bSmall = bSmall;
		m_nBtnStyle = 3;
		ModifyStyle(0,BS_ICON);
	}
}
void	CCustomBtn::LoadBtnIcon(const CString& strPath,BOOL	bSmall /*= TRUE*/)
{
	if (!strPath.IsEmpty())
	{
		 HICON icon = (HICON)::LoadImage(AfxGetInstanceHandle(),strPath,IMAGE_ICON,0,0,LR_DEFAULTSIZE|LR_LOADFROMFILE);
		 if(icon)
		 {
			 ::DestroyIcon(m_hIcon);
			 m_hIcon = icon;
			 m_bSmall = bSmall;
			 m_nBtnStyle = 3;
			 ModifyStyle(0,BS_ICON);
		 }
	}
}
void	CCustomBtn::LoadBtnImage(UINT nResourceID)
{
	ASSERT(nResourceID>0);
// 	CBitmap	bmp;
	m_bmp.LoadBitmap(nResourceID);
	m_nBtnStyle = 2;
// 	m_BrushBack.DeleteObject();
// 	m_BrushBack.CreatePatternBrush(&bmp);
// 	Invalidate();
//  	SetBitmap((HBITMAP)bmp);
}
void	CCustomBtn::LoadBtnImage(CString strPath)
{
	if (!strPath.IsEmpty())
	{
		HBITMAP	hBmp = (HBITMAP)::LoadImage(NULL,strPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		if (hBmp)
		{
			m_bmp.Attach(hBmp);
			m_nBtnStyle = 2;
		}
 	}
}
void	CCustomBtn::DrawBitmap(CDC* pDC)
{
	if(pDC == NULL)
		return;
	CDC	dcBmp;
	dcBmp.CreateCompatibleDC(pDC);
	HBITMAP	hBit = (HBITMAP)dcBmp.SelectObject(m_bmp);
	CRect	rcItem;
	GetClientRect(rcItem);
	if (m_bmp.GetSafeHandle() == NULL)
	{
		return;
	}
	BITMAP	bm;
	m_bmp.GetBitmap(&bm);
	//原始大小
// 	pDC->BitBlt(rcItem.left,rcItem.top,rcItem.right,rcItem.bottom,&dcBmp,0,0,SRCCOPY);
	//图片拉伸
	CFont*	pFt = GetFont();
	CFont l_font; 
//	l_font.CreatePointFont(150,_T("宋体"));  
 	l_font.CreateFont(rcItem.Height()-14, 0, 0, 0, FW_NORMAL,
  		FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,   DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("宋体"));
	 CFont* l_old_font = dcBmp.SelectObject(&l_font);
	CString	strText;
	dcBmp.SetBkMode(TRANSPARENT);
	GetWindowText(strText);
  	dcBmp.DrawText(strText,&rcItem,DT_SINGLELINE|DT_LEFT);
	if (m_bSelected)
	{
		pDC->StretchBlt(rcItem.left+1,rcItem.top+1,rcItem.Width(),rcItem.Height(),&dcBmp,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	}
	else
	   	pDC->StretchBlt(rcItem.left,rcItem.top,rcItem.Width(),rcItem.Height(),&dcBmp,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
  	dcBmp.SelectObject(hBit);
}
void	CCustomBtn::DrawIcon(CDC* pDC,UINT	uState)
{
	ASSERT(pDC->GetSafeHdc());
	if(m_hIcon!=NULL)
	{
		ICONINFO	ici;
		BITMAP	bmp;
		::GetIconInfo(m_hIcon,&ici);
		::GetObject(ici.hbmColor,sizeof(BITMAP),&bmp);

		int nWidth = bmp.bmWidth;
		int	nHeight = bmp.bmHeight;

		::DeleteObject(ici.hbmColor);
		::DeleteObject(ici.hbmMask);

		UINT	uFlag = DST_ICON|DSS_NORMAL;
		int		nCxIcon = (m_bSelected? 5+1:5);
		int		nCyIcon = m_bSelected? 2+1:2;
		::DrawState(pDC->GetSafeHdc(),NULL,NULL,(LPARAM)m_hIcon,NULL,
			nCxIcon,nCyIcon,nWidth,nHeight,uFlag);
 	}
 }
void	CCustomBtn::DrawTextOnBmp(CDC* pDC,CString strText)
{
	if (pDC)
	{
		CDC	dcText;
		dcText.CreateCompatibleDC(pDC);
		dcText.SetBkMode(TRANSPARENT);
// 		CFont*	pFt = GetFont();
// 		LOGFONT	lg;
// 		pFt->GetLogFont(&lg);
// 		dcText.SelectObject(pFt);
		CRect	rect;
		GetClientRect(rect);
		dcText.DrawText(strText,&rect,DT_SINGLELINE|DT_LEFT);
		dcText.DeleteDC();
	}
}
/************************************************************************/
/* 
*/
/************************************************************************/
void CCustomBtn::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default
	m_blnMouseOn = FALSE;
	m_bTracking = FALSE;
	m_bOver = FALSE;
	Invalidate();
 //	CButton::OnMouseLeave();
}

void CCustomBtn::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bOver = TRUE;
	InvalidateRect(NULL);
// 	CButton::OnMouseHover(nFlags, point);
 }

void CCustomBtn::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

// 	CWnd*				wndUnderMouse = NULL;
// 	CWnd*				wndActive = this;
	TRACKMOUSEEVENT		csTME;
// 	ClientToScreen(&point);
// 	wndUnderMouse = WindowFromPoint(point);
// 	if(nFlags&MK_LBUTTON)	return;
// 	wndActive = GetActiveWindow();
// 	if (wndUnderMouse && wndUnderMouse->GetSafeHwnd() == m_hWnd && wndActive)
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


BOOL CCustomBtn::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	//增加tooltip所需
	if(m_tip.GetSafeHwnd()!=NULL)
		m_tip.RelayEvent(pMsg);
	//////////////////////////////////////////////////////////////////////////
	return CButton::PreTranslateMessage(pMsg);
}


int CCustomBtn::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	//////////////////////////////////////////////////////////////////////////
	EnableToolTips(TRUE);
	m_tip.Create(this);
	GetWindowText(m_strToolTip);
	m_tip.AddTool(this,m_strToolTip);
	m_tip.SetMaxTipWidth(MAX_PATH);
	// 	m_tip.SetDelayTime(100);
	m_tip.Activate(TRUE);
	//////////////////////////////////////////////////////////////////////////

	return 0;
}


BOOL CCustomBtn::Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: Add your specialized code here and/or call the base class

	return CButton::Create(lpszCaption, dwStyle, rect, pParentWnd, nID);
}


BOOL CCustomBtn::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
//	return TRUE;

	return CButton::OnEraseBkgnd(pDC);
}


void CCustomBtn::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CButton::OnPaint() for painting messages
 	CWnd::DefWindowProc(WM_PAINT,(WPARAM)dc.GetSafeHdc(),0);
// 	DrawBitmap(&dc);
}


