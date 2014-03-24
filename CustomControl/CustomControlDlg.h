
// CustomControlDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "CustomBtn.h"
#include "TestButton.h"
// CCustomControlDlg dialog
class CCustomControlDlg : public CDialogEx
{
// Construction
public:
	CCustomControlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CUSTOMCONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CCustomBtn m_btn;
	CCustomBtn m_btn2;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CTestButton m_testBtn;
	CCustomBtn m_iconBtn;
};
