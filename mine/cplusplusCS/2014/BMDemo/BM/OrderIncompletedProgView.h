#pragma once
#include "afxcmn.h"
#include "afxwin.h"



// COrderIncompletedProgView ������ͼ

class COrderIncompletedProgView : public CFormView
{
	DECLARE_DYNCREATE(COrderIncompletedProgView)

public:
	COrderIncompletedProgView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~COrderIncompletedProgView();

public:
	enum { IDD = IDD_FORMVIEW_DEAL_INCOMPLETED };
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
	CExListCtrl		m_list;
	CStatic			m_tip;
	int				m_time_take;
	CString         m_list_IncompleteOrder;     //�����������ػ��ϴ���list����
	CStringArray    m_OrderToUpdateArr;       //��Ҫ���µ��������Ķ����б�
public:
	virtual		void		OnInitialUpdate();
	void					InitList();
	void					ShowTip();
	void                    InitSplit();
	void					FillDataToList();
	void					TransferStrToArr(CString source,CStringArray &des);    //���ַ����⿪  ���array��ʽ������
	void					InitTipCtrl();
	CString					GetItemFromArray(CString source,int index);    //���ַ�����ȡ����������
	afx_msg		HBRUSH		OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg		void		OnTimer(UINT_PTR nIDEvent);
protected:
	
	BOOL					IsOrderProgVality(CString source); 
	afx_msg		LRESULT		OnStartTask(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT		OnEndTask(WPARAM wParam, LPARAM lParam);
public:
	afx_msg		void		OnBnClickedBtnSave();
	afx_msg		void		OnBnClickedBtnFindDealIncomplete();
protected:
	afx_msg		LRESULT		OnFillList(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnChooseAll();
	CSplitButton m_split;
	afx_msg void OnReverseChoose();
	afx_msg void OnChooseNone();
	afx_msg void OnDelFromList();
	afx_msg void OnClearList();
};


