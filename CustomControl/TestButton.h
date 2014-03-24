#pragma once


// CTestButton

class CTestButton : public CButton
{
	DECLARE_DYNAMIC(CTestButton)

public:
	CTestButton();
	virtual ~CTestButton();

	virtual	void	DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual	void	PreSubclassWindow();

protected:
	BOOL	m_blnMouseOn;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};


