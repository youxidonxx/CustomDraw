#pragma once

/************************************************************************/
/* 
	1.��������ѡ��
		��Ҫ������	���ͣ�	m_nButtonFace::0��ֱ������(Ĭ��)��1��Բ�����ͣ�2����Բ���ͣ�
					��״���飺	m_rgn;
					����ɫ��		m_clrBack	
					������ɫ��	m_clrText
					���뷽ʽ��	m_nAlgin	9��::9����
					��ť���ͣ�	m_nBtnStyle		::0:pushBtn��Ĭ�����ͣ�1������Ч�����ͣ�2������ͼƬ����;3��ͼ������
					���״̬��	m_blnMouseOn
					������ˢ��	m_BrushBack
					����ɫ�̶�	m_nGradient
					����ɫ��ɫ	m_clrLeft��m_clrRight �������ҽ�����ɫ����
					����Ӧ��С	m_bFit

		��Ҫ������	���������״������	setButtonFace(uint)
					��д������	PreSubclassWindow	
					�Ÿ�λ�û�ȡ������GetTextPos
					����Ӧ��С���� ExtentToFit
	2.��ʾ�����
		������	��ʾ�ࣺ	CToolTipCtrl m_tips;  
				��ʾ���֣�	m_strToolTip
	3.����ͼƬ��������ͼ�꣬���ǰ�ťͼƬ
				1��������Դ��ͼ�е�ͼƬ��2�������ļ����µ�ͼƬ
*/
/************************************************************************/
// CCustomBtn

#define		ROUND_CORNER		10		//����Բ�ǻ���

#define		ALGIN_CONST			10		//���뷽ʽʱʹ�õ�����

//�Ź�����沼��
/************************************************************************/
/* 
	-----------------------------
	|���Ͻ�		���Ͻ�	 ���Ͻ�	 |
	|________||________||_______||
	|�����		���м�	  ���ҽ�	 |
	|________||________||_______||
	|���½�		���½�	  ���½�	 |
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

	//�ڽ��������icon��ͬʱ��ʾ����
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
				,m_clrText		//�ַ�����ɫ
				,m_clrFlatBack
				,m_clrLeft,m_clrRight	//�ڱ߿�ѡ��/������ɫ
				,m_clrBorder	//��߿���ɫ
				;
	BOOL	m_blnMouseOn	//�����ͣ�ڰ�ť��
							//����״̬
			,m_bOver		//���λ�ڰ�ť֮��ʱ��ֵΪtrue����֮Ϊflase
			,m_bTracking	//����갴��û���ͷ�ʱ��ֵΪtrue,ͨ��_TrackMouseEvent����ֵȷ��
			,m_bSelected	//��ť��ѡ��
			,m_bFocus		//��ť��ȡ����
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

	void	DrawBorder(CDC*	pDC,CRgn*	rgnOut,CRgn	*	rgnIn);//���߿�
	void	DrawGradientFill(CDC*	pDC	,CRect	rcWnd);	//���ڲ�����ɫ
	void	DrawText(CDC*	pDC,CRect	rcWnd,const	CString&	str,DWORD	dwState);	//�ַ���

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


