#pragma once
 
/*************************************************
//  Copyright (C), 2014
//  File name:       SysBtn.h
//  Author:        Administrator     
//  Version:          1.0     
//  Date:              2014/03/27
//  Description: 
//  Others:
//  History:
//    <author>       XX 
//    <time>          2014/03/27
//    <version>     1.0 
//    <desc>          build this moudle     
*************************************************/// CSysBtn

class CSysBtn : public CButton
{
	DECLARE_DYNAMIC(CSysBtn)

public:
	CSysBtn();
	virtual ~CSysBtn();

	void	CreateSystemMenu(HWND	pParentWnd,UINT	nID,CRect	rcBtn,UINT	nImageCount = 3);
	void	CreateSystemMenu(HWND	pParentWnd,const	CString&	strPath,CRect	rcBtn,UINT	nImageCount = 3);


protected:
	HWND	m_hParent;
	UINT	m_nImageCount;	//加载的图片中包含几种图片状态
	UINT	m_nID;			//资源ID
	UINT	m_nStatus;
	UINT	m_nStyle;
	CString	m_strFilePath;	//资源路径
	CBitmap	m_bmp;
	CRect	m_rcBtn;		//按钮位置

	BOOL	m_blnMouseOn	//鼠标悬停于按钮上
		//四种状态
		,m_bOver		//鼠标位于按钮之上时该值为true，反之为flase
		,m_bTracking	//在鼠标按下没有释放时该值为true,通过_TrackMouseEvent返回值确认
		,m_bSelected	//按钮被选中
		,m_bFocus		//按钮获取焦点
		;
	void	DrawButton(CDC*	pDC);

	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void PreSubclassWindow();
};


