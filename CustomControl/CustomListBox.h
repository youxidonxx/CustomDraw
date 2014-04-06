#pragma once

/************************************************************************ 
  
	 步骤：
	 1、属性设置：
		设置ownerdraw属性，在presubclasswindow中；	——设置无用，若是采用拖入控件的方式，则还是使用全局函数来重建listbox
		//////////////////////////////////////////////////
		// for example
		m_list.ModifyStyle(0,LBS_OWNERDRAWVARIABLE|LBS_SORT|LBS_HASSTRINGS);
		RecreateListBox(&m_list,NULL);
		///////////////////////////////////////////////////
		设置不自动排序；
		接收键盘消息，使得键盘上下键起作用；
		滚动条效果：	首先，窗口样式需要添加ws_vscroll;
					其次，重载onvscroll消息，在其中添加刷新消息触发重绘；
					然后，若是需要鼠标滚动带动滚动条，则需要重写OnMouseWheel
	 2、改造目标：

		滚动条自绘；
		图标显示；
		透明效果；	m_bTransparent

参考资料：	http://www.vckbase.com/index.php/wv/1656
			http://www.cppblog.com/sivan/archive/2011/03/06/141216.html
			http://blog.csdn.net/lixiaomin_235/article/details/3938099

技术释疑：	http://bbs.csdn.net/topics/390326335?page=1#post-393293067  解释为何无法再运行时修改某些style
			http://www.codeproject.com/Articles/2634/Dynamically-re-creating-a-list-box 需要动态修改样式的某种方法
			http://www.cnitblog.com/zhkza99c/archive/2008/05/27/44442.html	解释measureitem被调用时机
			http://msdn.microsoft.com/zh-cn/library/bk2h3c6w(v=vs.100).aspx
			http://blog.csdn.net/qq2399431200/article/details/17336455		解释=WM_VSCROLL(消息反射) 和 WM_VSCROLL(消息响应)的区别——此处不需要
			http://bbs.csdn.net/topics/340078009							解释如何鼠标滚动带动滚动条

 setupapi 获取串口 http://blog.csdn.net/badboyccj/article/details/6718968
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
	/*	是与父窗口统一的背景，还是listbox内部自带背景图片
		若是设置与父窗口统一，即透明 == true，则SetBKBMP无效；
		当透明==false:看是否有背景图片，若无，则为白底色；
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
	COLORREF	m_clrFocus		//点击时背景色
				,m_clrBack		//普通背景色
				,m_clrText		//文本色
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


