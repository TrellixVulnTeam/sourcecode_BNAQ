
#pragma once
#include "afxwin.h"


// CDBNew �Ի���

class CDBNew : public CDialogEx
{
	DECLARE_DYNAMIC(CDBNew)

public:
	CDBNew(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDBNew();

// �Ի�������
	enum { IDD = IDD_DLG_DBNEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg		void		OnTimer(UINT_PTR nIDEvent);
	afx_msg		void		OnClose();
	void                    ShowTip();
	virtual		BOOL		OnInitDialog();
	afx_msg		HBRUSH		OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg		void		OnBnClickedOk();
	afx_msg		void		OnBnClickedCancel();
	int						RecvDBNewData(SOCKET s);
	static      DWORD WINAPI   DBNewThread(void* pParam);	//�½����ݿ��߳�
	afx_msg		LRESULT		OnStartTask(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT		OnEndTask(WPARAM wParam, LPARAM lParam);
	BOOL					CreateSocket(SOCKET &sock);
public:
	CString		m_db_name;
	CString		m_name_confirm;
	CStatic		m_tip;
	int			m_time_take;
	CString     m_ip;
	CString     m_port;
protected:
	
public:
	
//	CString m_db_save_path;
};
