#pragma once

/************************************************************************ 
  
	 ���裺
	 1���������ã�
		����ownerdraw���ԣ���presubclasswindow�У�	�����������ã����ǲ�������ؼ��ķ�ʽ������ʹ��ȫ�ֺ������ؽ�listbox
		//////////////////////////////////////////////////
		// for example
		m_list.ModifyStyle(0,LBS_OWNERDRAWVARIABLE|LBS_SORT|LBS_HASSTRINGS);
		RecreateListBox(&m_list,NULL);
		///////////////////////////////////////////////////
		���ò��Զ�����
		���ռ�����Ϣ��ʹ�ü������¼������ã�
		������Ч����	���ȣ�������ʽ��Ҫ���ws_vscroll;
					��Σ�����onvscroll��Ϣ�����������ˢ����Ϣ�����ػ棻
					Ȼ��������Ҫ����������������������Ҫ��дOnMouseWheel
	 2������Ŀ�꣺

		�������Ի棻
		ͼ����ʾ��
		͸��Ч����	m_bTransparent

�ο����ϣ�	http://www.vckbase.com/index.php/wv/1656
			http://www.cppblog.com/sivan/archive/2011/03/06/141216.html
			http://blog.csdn.net/lixiaomin_235/article/details/3938099

�������ɣ�	http://bbs.csdn.net/topics/390326335?page=1#post-393293067  ����Ϊ���޷�������ʱ�޸�ĳЩstyle
			http://www.codeproject.com/Articles/2634/Dynamically-re-creating-a-list-box ��Ҫ��̬�޸���ʽ��ĳ�ַ���
			http://www.cnitblog.com/zhkza99c/archive/2008/05/27/44442.html	����measureitem������ʱ��
			http://msdn.microsoft.com/zh-cn/library/bk2h3c6w(v=vs.100).aspx
			http://blog.csdn.net/qq2399431200/article/details/17336455		����=WM_VSCROLL(��Ϣ����) �� WM_VSCROLL(��Ϣ��Ӧ)�����𡪡��˴�����Ҫ
			http://bbs.csdn.net/topics/340078009							�����������������������

 setupapi ��ȡ���� http://blog.csdn.net/badboyccj/article/details/6718968
				 http://www.codeproject.com/script/Articles/ViewDownloads.aspx?aid=293273
 ************************************************************************/
// CCustomListBox
#define		LISTBOX_ITEM_HEIGHT		10


class CCustomListBox : public CListBox
{
	DECLARE_DYNAMIC(CCustomListBox)

public:
	CCustomListBox();
	virtual ~CCustomListBox();

	/************************************************************************/
	/*	���븸����ͳһ�ı���������listbox�ڲ��Դ�����ͼƬ
		���������븸����ͳһ����͸�� == true����SetBKBMP��Ч��
		��͸��==false:���Ƿ��б���ͼƬ�����ޣ���Ϊ�׵�ɫ��
	*/
	/************************************************************************/
	void	SetBKTransparent(BOOL	bTransparent = TRUE){	m_bTransparent = bTransparent;	}
	BOOL	IsBKTransparent(){	return	m_bTransparent;	}
	void	SetBKBMP(CONST	CString&	strFile);
	void	SetBKBMP(UINT	nResourceID);
	//////////////////////////////////////////////////////////////////////////
	void	SetFocusClr(COLORREF	clr){	m_clrFocus = clr;	}
	void	SetBackClr(COLORREF	clr){	m_clrBack	=	clr;	}
	void	SetTextClr(COLORREF	clr){	m_clrText	=	clr;	}
	//////////////////////////////////////////////////////////////////////////

protected:
	BOOL	m_bTransparent;
	CBitmap	m_bmp;
	COLORREF	m_clrFocus		//���ʱ����ɫ
				,m_clrBack		//��ͨ����ɫ
				,m_clrText		//�ı�ɫ
				;
	CBrush		m_brush;		//
	CRect		m_rcList;
protected:

	void	DrawItem(CDC*	pDC,CRect	&rect,int	nIndex,BOOL 	bSelected);

	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
// 	afx_msg void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
// 	afx_msg int CompareItem(LPCOMPAREITEMSTRUCT /*lpCompareItemStruct*/);
	afx_msg void OnPaint();
	afx_msg void OnLbnSelchange();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
};


