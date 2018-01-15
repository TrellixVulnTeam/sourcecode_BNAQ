#pragma once
#include "afxwin.h"


// CPwdEdit �Ի���

class CPwdEdit : public CDialogEx
{
	DECLARE_DYNAMIC(CPwdEdit)

public:
	CPwdEdit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPwdEdit();

// �Ի�������
	enum { IDD = IDD_DLG_PWDEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	CComboBox			m_pos;
//	CComboBox			m_username;
	CString				m_password;
	CString				m_psw_new;
	CString				m_psw_confirm;
	CStatic				m_tip;
	int					m_time_take;
	CString             m_strPswEdit;
public:
	void					InitTipCtrl();
	//void					InitComb();
	afx_msg		void		OnBnClickedOk();
	virtual		BOOL		OnInitDialog();
	
	afx_msg		HBRUSH		OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg		void		OnBnClickedCancel();
	
	afx_msg		void		OnTimer(UINT_PTR nIDEvent);
	afx_msg		void		OnClose();
	void					ShowTip();
protected:
	afx_msg		LRESULT		OnStartTask(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT		OnEndTask(WPARAM wParam, LPARAM lParam);
};
