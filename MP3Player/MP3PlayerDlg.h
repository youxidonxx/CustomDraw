/************************************************************************/
/* 
	��������2��ģʽ����ʵ������ģʽ��Ȼ����ʵ��ħ��ģʽ��
	����Ч����
	ħ����http://blog.csdn.net/cometnet/article/details/6561912
	������http://bbs.csdn.net/topics/390634398
	�����ο���	http://blog.csdn.net/x_q_wang/article/details/21607835
				http://blog.csdn.net/u010105970/article/details/20901907
	һ������ģʽ��
		1���Ǳ������ͻ����Ի�
			1.1����ȡ������������ʵ�ֱ���������ʾ������Ч��
			��Ҫ���������:
				//�ǿͻ�������Ϣ
				ON_WM_NCPAINT()//��ǿͻ���ʱ��
				ON_WM_NCACTIVATE()//�ǿͻ����н����ʧȥ����ʱ��
				ON_WM_NCCALCSIZE()//���㴰��ߴ�ʱ��
				//�ı�������ߴ磺
				��дON_WM_NCCALCSIZE()��Ϣ��Ӧ������
				//�ǿͻ�������궯����
				�����Ϣ��
				ON_WM_NCLBUTTONDOWN()//����¡�
				ON_WM_NCLBUTTONUP()//����ϡ�
				ON_WM_NCMOUSEMOVE()//�����ͣ��
				//���������С�ر���Ϣ��
				WindowProc���������������С�ر���Ϣ.
*/
/************************************************************************/
// MP3PlayerDlg.h : header file
//

#pragma once


//���ֳ�ʼ����������
#define		INIT_CAPTION_HEIGHT		10		//�������߶�

#define		DLG_BUTTON_MIN			_T("//sys_dlg_min.bmp")
#define		DLG_BUTTON_MAX			_T("//sys_dlg_max.bmp")
#define		DLG_BUTTON_RES			_T("//sys_dlg_restore.bmp")
#define		DLG_BUTTON_MENU			_T("//sys_dlg_menu.bmp")
#define		DLG_BK					_T("//dlg_bk.bmp")
#define		DLG_TITLE				_T("//dlg_title.bmp")

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
	//���������ã���˵����Ҫ���ñ���ͼƬ�����Ǳ���·��Ϊ�ޣ����ʾ���ⲿ�ֲ���������ͼ������һ�屳��ͼ
	void	SetBkImage(const	CString&	strFileBK,const	CString&	strFileCaption);	
	void	SetBkImage(UINT	nResID_BK,UINT	nResID_CP = 0);	
// Implementation
protected:
	HICON m_hIcon;
	CBrush m_brBG;			//�Ի��򱳾���ɫ,��OnInitDialog �г�ʼ��,��OnCtlColor����Ϊ����ֵ.
	CString m_strCaption;	//����.
	CRect m_rtWnd;			//��������Rect.
	CBitmap	m_bmpGK			//����ͼƬ
		,m_bmpCP			//������
		;

	UINT	m_nCaptionHeight		//�������߶�	������Ӧ�ģ�Ҳ�к�����������
		;
//////////////////////////////////////////////////////////////////////////
	//��ť��������
	CRect m_rtButtons;//���,��С,�رհ�ť.
	CRect m_rtIcon;//ͼ��.
	CRect m_rtButtMin;//��С.
	CRect m_rtButtMax;//���.
	CRect m_rtButtExit;//�ر�.
	CRect m_rtButtMaxM;
	CRect m_rtButtMinM; 
	CRect m_rtButtExitM;
	CRect m_bmRt;//Bitmap���ڵ�Rect.
	BOOL    m_bNCActive;//����.


	void DrawNC(CDC* pDC);	//	���ǿͻ��� 
	void	DrawTitle(CDC*	pDC,CRect	rcTitle);
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
};