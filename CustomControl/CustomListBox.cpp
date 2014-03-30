// CustomListBox.cpp : implementation file
//

#include "stdafx.h"
#include "CustomControl.h"
#include "CustomListBox.h"


// CCustomListBox

IMPLEMENT_DYNAMIC(CCustomListBox, CListBox)

CCustomListBox::CCustomListBox()
{

}

CCustomListBox::~CCustomListBox()
{
}


BEGIN_MESSAGE_MAP(CCustomListBox, CListBox)
END_MESSAGE_MAP()



// CCustomListBox message handlers




void CCustomListBox::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	CListBox::PreSubclassWindow();
	ModifyStyle(LBS_OWNERDRAWFIXED|LBS_SORT|LBS_HASSTRINGS,LBS_OWNERDRAWFIXED);
	CRect	rect;
	GetWindowRect(rect);
 	CWnd*	pWnd = GetParent();
	if (pWnd)
	{
		pWnd->ScreenToClient(rect);
	}
	MoveWindow(rect,TRUE);
}
