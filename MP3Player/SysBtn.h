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
	UINT	m_nImageCount;	//���ص�ͼƬ�а�������ͼƬ״̬
	UINT	m_nID;			//��ԴID
	UINT	m_nStatus;
	UINT	m_nStyle;
	CString	m_strFilePath;	//��Դ·��
	CBitmap	m_bmp;
	CRect	m_rcBtn;		//��ťλ��

	BOOL	m_blnMouseOn	//�����ͣ�ڰ�ť��
		//����״̬
		,m_bOver		//���λ�ڰ�ť֮��ʱ��ֵΪtrue����֮Ϊflase
		,m_bTracking	//����갴��û���ͷ�ʱ��ֵΪtrue,ͨ��_TrackMouseEvent����ֵȷ��
		,m_bSelected	//��ť��ѡ��
		,m_bFocus		//��ť��ȡ����
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


