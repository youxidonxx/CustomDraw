#pragma once

/************************************************************************/
/* 
	 ���裺
	 1���������ã�
		����ownerdraw���ԣ���presubclasswindow�У�
		���ò��Զ�����
		���ռ�����Ϣ��ʹ�ü������¼������ã�
	 2������Ŀ�꣺
		�������Ի棻
		ͼ����ʾ��
		͸��Ч����

�ο����ϣ�	http://www.vckbase.com/index.php/wv/1656
			http://www.cppblog.com/sivan/archive/2011/03/06/141216.html

�������ɣ�	http://bbs.csdn.net/topics/390326335?page=1#post-393293067
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


