#pragma once
#include "afxwin.h"


// CDeductSet �Ի���

class CDeductSet : public CDialogEx
{
	DECLARE_DYNAMIC(CDeductSet)

public:
	CDeductSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeductSet();

// �Ի�������
	enum { IDD = IDD_DLG_DEDUCT_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	void         ShowTip();
protected:
	afx_msg LRESULT OnLoadSetOver(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStartTask(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEndTask(WPARAM wParam, LPARAM lParam);
public:
	DeductInfo   m_deductInfo;
	int m_time_take;
	CStatic m_tip;
	double m_decorate_company;
	double m_discuss_deal_person;
	double m_emp;
	double m_exact_test_person;
	double m_has_inner_modify;
	double m_measure;
	double m_no_inner_modify;
public:
	void         InitTipCtrl();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnCancal();
};
