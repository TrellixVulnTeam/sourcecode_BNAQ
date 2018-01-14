#pragma once
#include "afxcmn.h"
#include "afxdtctl.h"


// CPerformanceMgView ������ͼ
#include "EmpPerformanceSearch.h"
#include "DeductSet.h"
#include "afxwin.h"
class CPerformanceMgView : public CFormView
{
	DECLARE_DYNCREATE(CPerformanceMgView)

public:
	CPerformanceMgView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPerformanceMgView();

public:
	enum { IDD = IDD_FORMVIEW_PERFORMANCE_MG };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CExListCtrl			m_list;
	CDeductSet			m_deductSetDlg;
	CSplitButton		m_split;
	CStatic				m_tip;
	CString				m_keyword;
	int					m_time_take;
	CString             m_str_emp_performance_batch;
public:
	BOOL					IsItemValidity(CString _source,CString _item_name,BOOL bCheckEmpty,BOOL bCheckNum,BOOL bCheckDateFormat,int str_len_max);    //true  ��Ч ������Ч  
	void					TransferStrToArr(CString source,CStringArray &des);    //���ַ����⿪  ���array��ʽ������
	CString                 GetItemFromArray(CString source,int index);     //���ַ�����ȡ����������
	virtual		void		OnInitialUpdate();
	void					InitList();
	void					ShowTip();
	void					InitSplit();
	void					InitTipCtrl();
	void					FillDataToList();
	afx_msg		void		OnBnClickedBtnSearch();
	afx_msg		HBRUSH		OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	afx_msg		void		OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg		LRESULT		OnStartTask(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT		OnEndTask(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT		OnFillDatatoList(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnDeductSet();
	afx_msg void OnAddAllDeduct();
	afx_msg void OnGetDeduct();
	afx_msg void OnChooseAll();
	afx_msg void OnChooseNone();
	afx_msg void OnReverseChoose();
	afx_msg void OnClearCurList();
	afx_msg void OnDelFromList();
};


