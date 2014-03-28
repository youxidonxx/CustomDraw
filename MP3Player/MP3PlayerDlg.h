/************************************************************************/
/* 
	播放器：2种模式，先实现完整模式，然后再实现魔方模式；
	类似效果：
	魔方：http://blog.csdn.net/cometnet/article/details/6561912
	完整：http://bbs.csdn.net/topics/390634398
	其他参考：	http://blog.csdn.net/x_q_wang/article/details/21607835
				http://blog.csdn.net/u010105970/article/details/20901907
	一、完整模式：
		1、非标题栏客户区自绘
			1.1、先取出标题栏，并实现标题栏与显示区分离效果
			需要步骤与变量:
				//非客户区的消息
				ON_WM_NCPAINT()//绘非客户区时。
				ON_WM_NCACTIVATE()//非客户区有焦点和失去焦点时。
				ON_WM_NCCALCSIZE()//计算窗体尺寸时。
				//改变标题栏尺寸：
				重写ON_WM_NCCALCSIZE()消息响应函数。
				//非客户区的鼠标动作：
				相关消息：
				ON_WM_NCLBUTTONDOWN()//鼠标下。
				ON_WM_NCLBUTTONUP()//鼠标上。
				ON_WM_NCMOUSEMOVE()//鼠标悬停。
				//屏蔽最大最小关闭消息：
				WindowProc中屏蔽屏蔽最大最小关闭消息.
*/
/************************************************************************/
// MP3PlayerDlg.h : header file
//

#pragma once
#include "SysBtn.h"


//部分初始量常量设置
#define		INIT_CAPTION_HEIGHT		20		//标题栏高度
#define		INIT_CAPTION_OFFSET		4		//偏移量

#define		INIT_SYSTEM_MENU_SIZE	24		//自绘的最大最小化按钮的大小

#define		SYSTEM_MENU_STATE_NUM	3		//加载的最大最小化图标类型：悬浮、焦点、正常

#define		BTN_MIN_ID			1001

#define		DLG_BUTTON_CLOSE			_T("\\sys_dlg_close.bmp")
#define		DLG_BUTTON_MIN			_T("\\sys_dlg_min.bmp")
#define		DLG_BUTTON_MAX			_T("\\sys_dlg_max.bmp")
#define		DLG_BUTTON_RES			_T("\\sys_dlg_restore.bmp")
#define		DLG_BUTTON_MENU			_T("\\sys_dlg_menu.bmp")
#define		DLG_BK					_T("\\dlg_bk.bmp")
#define		DLG_TITLE				_T("\\dlg_title.bmp")

enum	enumSystemMenuIndex
{
	System_Menu_Normal = 0
	,System_Menu_Hover 
	,System_Menu_Pressed
	,System_Menu_State_Num

};
/************************************************************************/
/* 
*/
/************************************************************************/
// CMP3PlayerDlg dialog
class CMP3PlayerDlg : public CDialogEx
{
// Construction
public:
	CMP3PlayerDlg(CWnd* pParent = NULL);	// standard constructor
	~CMP3PlayerDlg();
// Dialog Data
	enum { IDD = IDD_MP3PLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	void	SetCaptionHeight(UINT	nHeight){	m_nCaptionHeight = nHeight>0?nHeight:INIT_CAPTION_HEIGHT;	}
	//若是有设置，则说明需要设置背景图片；若是标题路径为无，则表示标题部分不用另外贴图，采用一体背景图
	void	SetBkImage(const	CString&	strFileBK,const	CString&	strFileCaption);	
	void	SetBkImage(UINT	nResID_BK,UINT	nResID_CP = 0);	
	void	SetSysMenu();
// Implementation
protected:
	HICON m_hIcon;
	CBrush m_brBG;			//对话框背景颜色,在OnInitDialog 中初始化,在OnCtlColor中作为返回值.
	CString m_strCaption;	//标题.
	CRect m_rtWnd;			//整个窗体Rect.
	CString	m_strPath;
	CBitmap	m_bmpGK			//背景图片——需要在OnPaint中绘画，否则不起作用
		,m_bmpCP			//标题栏
		,m_bmpMenu
		;

	UINT	m_nCaptionHeight		//标题栏高度	——相应的，也有函数进行设置
		;
//////////////////////////////////////////////////////////////////////////
	//按钮区域设置
	CRect m_rtButtons;//最大,最小,关闭按钮.
	CRect m_rtIcon;//图标.
	CRect m_rtButtMin;//最小.
	CRect m_rtButtMax;//最大.
	CRect m_rtButtExit;//关闭.
	CRect m_rtButtMaxM;
	CRect m_rtButtMinM; 
	CRect m_rtButtExitM;
	CRect m_bmRt;//Bitmap所在的Rect.
	BOOL    m_bNCActive;//窗体活动.
	CRect	m_rtButtMenu;	// 设置

	CSysBtn	m_btnMin
		,m_btnMax
		,m_btnExit
		,m_btnRes
		;
	//////////////////////////////////////////////////////////////////////////
	BOOL	m_bNCTracking
			,m_bNCHovering
			;
	int		m_nDownIndex		//鼠标按下时是否在systemmenu上，若是的话，记录下此时尾椎索引
			,m_nHoverIndex		//鼠标是否悬浮在systemmenu上，若是的话，记录下此时位置索引
			;
	/////////////////////////////////////////////////////////////////////////////////
protected:
	void	GetPtOfSysmenu(CPoint	pt);

	void DrawNC(CDC* pDC);	//	画非客户区 
	void	DrawTitle(CDC*	pDC,CRect	rcTitle);
	void	DrawBorder(CDC*	pDC,CRect	rcWnd);
	void	DrawBKBmp(CDC*	pDC,CRect	rcWnd);
	void	DrawSysMenu(CDC*	pDC);
	void	DrawMenuBtn(CDC*	pDC,CRect	rcBtn,CString	strFile);
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNcPaint();
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcMouseLeave();
	afx_msg void OnNcMouseHover(UINT nFlags, CPoint point);
};
