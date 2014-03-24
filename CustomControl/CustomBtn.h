#pragma once

/************************************************************************/
/* 
	1.外形类型选择：
		需要变量：	类型：	m_nButtonFace::0、直角类型(默认)；1、圆角类型；2、椭圆类型；
					形状数组：	m_rgn;
					背景色：		m_clrBack	
					字体颜色：	m_clrText
					对齐方式：	m_nAlgin	9种::9宫格
					按钮类型：	m_nBtnStyle		::0:pushBtn，默认类型；1：渐变效果类型；2：背景图片类型;3、图标类型
					鼠标状态：	m_blnMouseOn
					背景画刷：	m_BrushBack
					渐变色程度	m_nGradient
					渐变色颜色	m_clrLeft，m_clrRight 从左往右渐变颜色设置
					自适应大小	m_bFit

		需要函数：	设置外观形状函数：	setButtonFace(uint)
					重写函数：	PreSubclassWindow	
					九格位置获取函数：GetTextPos
					自适应大小函数 ExtentToFit
	2.提示框添加
		变量：	提示类：	CToolTipCtrl m_tips;  
				提示文字：	m_strToolTip
	3.加载图片——不是图标，而是按钮图片
				1、加载资源视图中的图片；2、加载文件夹下的图片
*/
/************************************************************************/
// CCustomBtn

#define		ROUND_CORNER		10		//定义圆角弧度

#define		ALGIN_CONST			10		//对齐方式时使用的余量

//九宫格界面布局
/************************************************************************/
/* 
	-----------------------------
	|左上角		中上角	 右上角	 |
	|________||________||_______||
	|中左边		正中间	  中右角	 |
	|________||________||_______||
	|左下角		中下角	  右下角	 |
	|________||________||_______||		 	
	------------------------------
*/
/************************************************************************/
enum	enumAlginType
{
	Algin_Left_Top	=	0,
	Algin_Center_Top	=	1,
	Algin_Right_Top,
	Algin_Left_Middle,
 	Algin_Center	 ,
	Algin_Right_Middle		 ,
	Algin_Left_Bottom,
	Algin_Center_Bottom,
	Algin_Right_Bottom
	,Algin_Type_Num
};
//////////////////////////////////////////////////////////////////////////
class CCustomBtn : public CButton
{
	DECLARE_DYNAMIC(CCustomBtn)

public:
	
	CCustomBtn();
	virtual ~CCustomBtn();
	virtual	void	DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//method
	void	SetButtonFace(UINT	nType = 0);
	void	SetButtonAlgin(UINT	nAlgin = 0);
	void	SetBtnGradient(UINT	nGrad){	m_nGradient = ((nGrad>=0&&nGrad<256)?nGrad:10);}
 
	void	LoadBtnImage(UINT	nResourceID);
	void	LoadBtnImage(CString	strPath);

	//在界面上添加icon，同时显示字体
	void	LoadBtnIcon(UINT	nResourceID,BOOL	bSmall = TRUE);
	void	LoadBtnIcon(const	CString&	strPath,BOOL	bSmall = TRUE);


	void	ExpentToFit(BOOL	bFit = TRUE);

	void	SetMouseMove(BOOL	bOn = TRUE);

	void	SetTextColor(COLORREF	clrText){	m_clrText = clrText;	}
	void	SetBkClr(COLORREF	clrBack){	m_clrBack = clrBack;	}
	void	SetBtnGradColor(COLORREF	clrLeft,COLORREF	clrRight);

protected:
	UINT	m_nButtonFace;
	CRgn	m_rgn;
	CBrush	m_BrushBack;
	COLORREF	m_clrBack
				,m_clrText		//字符串颜色
				,m_clrFlatBack
				,m_clrLeft,m_clrRight	//内边框选中/悬浮颜色
				,m_clrBorder	//外边框颜色
				;
	BOOL	m_blnMouseOn	//鼠标悬停于按钮上
							//四种状态
			,m_bOver		//鼠标位于按钮之上时该值为true，反之为flase
			,m_bTracking	//在鼠标按下没有释放时该值为true,通过_TrackMouseEvent返回值确认
			,m_bSelected	//按钮被选中
			,m_bFocus		//按钮获取焦点
 			;
	UINT	m_nAlgin,m_nBtnStyle;
	UINT	m_nGradient;	
	//////////////////////////////////////////////////////////////////////////
	HICON	m_hIcon;
	BOOL	m_bSmall;
	void	DrawIcon(CDC*	pDC,UINT	uState);
	//////////////////////////////////////////////////////////////////////////
	CBitmap	m_bmp;
	void	DrawBitmap(CDC*	pDC);
	void	DrawTextOnBmp(CDC*	pDC,CString	strText);
	//////////////////////////////////////////////////////////////////////////
	///
	CToolTipCtrl	m_tip;
	CString	m_strToolTip;
	void	EnableToolTipOn();
	//////////////////////////////////////////////////////////////////////////
	BOOL	m_bFit;
	//////////////////////////////////////////////////////////////////////////
	CPoint	GetTextPos(CDC*	pDC,UINT	nAlginType,CRect	rcBtn,CString	strText);

	void	DrawBorder(CDC*	pDC,CRgn*	rgnOut,CRgn	*	rgnIn);//画边框
	void	DrawGradientFill(CDC*	pDC	,CRect	rcWnd);	//画内部渐变色
	void	DrawText(CDC*	pDC,CRect	rcWnd,const	CString&	str,DWORD	dwState);	//字符串

	virtual	void	PreSubclassWindow();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
 };


