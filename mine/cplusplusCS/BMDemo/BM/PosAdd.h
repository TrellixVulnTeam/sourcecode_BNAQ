#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CPosAdd �Ի���

class CPosAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CPosAdd)

public:
	CPosAdd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPosAdd();

// �Ի�������
	enum { IDD = IDD_DLG_POS_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic		m_tip;
	CString		m_emp_num;
	CString		m_password_confirm;
	CString		m_emp_ps;
	CString		m_emp_name;
	CString		m_emp_password;
	int			m_time_take;
	CComboBox	m_pos_name;
	CString     m_str_pos_new;    //���ڽ��½���ɫ����Ϣװ������ַ�����
public:
	void				ShowTip();
	void				InitTipCtrl();
	BOOL				IsItemValidity(CString _source,CString _item_name,BOOL bCheckEmpty,BOOL bCheckNum,BOOL bCheckDateFormat,int str_len_max);    //true  ��Ч ������Ч  
	BOOL				ContainsCharsRemain(CString str);     //����ַ����Ƿ�������ַ���
	void				InitPosCombox();
	BOOL                IsNum(CString str);    //����һ���ַ��� ������Ƿ�Ϊ����
	void				AddItemToString(CString &_source,CString item_new,int flag);
	virtual		BOOL	OnInitDialog();
	afx_msg		HBRUSH	OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg		void	OnBnClickedBtnSavePos();
	afx_msg		void	OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg		LRESULT OnStartTask(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT OnEndTask(WPARAM wParam, LPARAM lParam);
public:

	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnCancel();
};
