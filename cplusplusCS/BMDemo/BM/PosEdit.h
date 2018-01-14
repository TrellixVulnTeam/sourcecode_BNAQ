#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CPosEdit �Ի���

class CPosEdit : public CDialogEx
{
	DECLARE_DYNAMIC(CPosEdit)

public:
	CPosEdit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPosEdit();

// �Ի�������
	enum { IDD = IDD_DLG_POS_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic			m_tip;
	CString			m_emp_num;
	CString			m_password_confirm;
	CString			m_emp_ps;
	CString			m_emp_name;
	CString			m_emp_password;
	CComboBox		m_pos_name;
	int				m_time_take;
	CString         m_str_pos_name;
	CString         m_str_pos_authorities;     //�û�Ȩ��
	CString			m_str_pos_edit;
public:
	virtual		BOOL	OnInitDialog();
	void				InitTipCtrl();
	void				AddItemToString(CString &_source,CString item_new,int flag);
	void				InitUserAuthority();
	CString				GetItemFromArray(CString source,int index);     //���ַ�����ȡ����������
	void				InitComb();
	void				ShowTip();
	BOOL				IsItemValidity(CString _source,CString _item_name,BOOL bCheckEmpty,BOOL bCheckNum,BOOL bCheckDateFormat,int str_len_max);    //true  ��Ч ������Ч  
	void				LoadUser();   //�����û�Ȩ��
	afx_msg		HBRUSH	OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg		void	OnBnClickedBtnSavePos();
	afx_msg		void	OnTimer(UINT_PTR nIDEvent);
	afx_msg		void	OnClose();
	afx_msg		void	OnBnClickedBtnCancel();
protected:
	afx_msg		LRESULT OnStartTask(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT OnEndTask(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT OnInitUserAuthority(WPARAM wParam, LPARAM lParam);
};
