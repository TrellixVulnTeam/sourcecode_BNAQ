#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CStoreHistory �Ի���

class CStoreHistory : public CDialogEx
{
	DECLARE_DYNAMIC(CStoreHistory)

public:
	CStoreHistory(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStoreHistory();

// �Ի�������
	enum { IDD = IDD_DLG_STORE_HISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
public:
	virtual		BOOL		OnInitDialog();
	void					InitList();
	afx_msg		HBRUSH		OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg		void		OnBnClickedBtnFindAll();
	
	afx_msg		void		OnBnClickedBtnDelHistory();
	afx_msg		void		OnTimer(UINT_PTR nIDEvent);
	afx_msg		void		OnClose();
	void					ShowTip();
protected:
	afx_msg		LRESULT		OnStartTask(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT		OnEndTask(WPARAM wParam, LPARAM lParam);
public:
	CStatic		m_tip;
	int			m_time_take; 
	CString     m_strToDelHistory;    //��Ҫ��ɾ������ʷ��¼
protected:
	afx_msg LRESULT OnDelHistory(WPARAM wParam, LPARAM lParam);
};
