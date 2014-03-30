#pragma once

/************************************************************************/
/* 
	 步骤：
	 1、属性设置：
		设置ownerdraw属性，在presubclasswindow中；
		设置不自动排序；
		接收键盘消息，使得键盘上下键起作用；
	 2、改造目标：
		滚动条自绘；
		图标显示；
		透明效果；

参考资料：	http://www.vckbase.com/index.php/wv/1656
			http://www.cppblog.com/sivan/archive/2011/03/06/141216.html

技术释疑：	http://bbs.csdn.net/topics/390326335?page=1#post-393293067
			http://www.codeproject.com/Articles/2634/Dynamically-re-creating-a-list-box

*/
/************************************************************************/
// CCustomListBox

class CCustomListBox : public CListBox
{
	DECLARE_DYNAMIC(CCustomListBox)

public:
	CCustomListBox();
	virtual ~CCustomListBox();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
};


