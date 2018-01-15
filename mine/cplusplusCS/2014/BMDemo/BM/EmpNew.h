#pragma once
#include "afxwin.h"


// CEmpNew �Ի���
class CEmpInfoView;
class CEmpNew : public CDialogEx
{
	DECLARE_DYNAMIC(CEmpNew)

public:
	CEmpNew(CWnd* pParent = NULL);   // ��׼���캯��
	CEmpNew(CEmpInfoView* p_emp,CWnd* pParent = NULL);   // �Զ��幹�캯��
	virtual ~CEmpNew();

// �Ի�������
	enum { IDD = IDD_DLG_EMP_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEmpInfoView* m_pEmpInfoView;
	CString m_addr_emp;
	CString m_name_emp;
	CString m_num_emp;
	CString m_phone_emp;
	CString m_ps_emp;
//	CString m_pos_emp;
	
	CString m_pos_emp;
	CStatic m_tip;
	int m_time_take;
public:
	afx_msg void OnBnClickedBtnNew();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnCancel();
	BOOL		 ContainsCharsRemain(CString str);     //����ַ����Ƿ�������ַ���
	BOOL		 IsNum(CString str,BOOL bCheckDot);
	BOOL		 IsItemValidity(CString _source,CString _item_name,BOOL bCheckEmpty,BOOL bCheckNum,BOOL bCheckDateFormat,int str_len_max,int data_min_len,BOOL bCheckDot = FALSE);
protected:
	afx_msg LRESULT OnReqEmpNewStart(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReqEmpNewEnd(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	void    ShowTip();
};
