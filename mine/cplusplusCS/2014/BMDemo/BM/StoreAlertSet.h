#pragma once
#include "afxwin.h"


// CStoreAlertSet �Ի���

class CStoreAlertSet : public CDialogEx
{
	DECLARE_DYNAMIC(CStoreAlertSet)

public:
	CStoreAlertSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStoreAlertSet();

// �Ի�������
	enum { IDD = IDD_DLG_STORE_ALERT_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg		void		OnBnClickedBtnCancel();
	afx_msg		void		OnBnClickedBtnSave();
	void					ShowTip();
	virtual		BOOL		OnInitDialog();
	afx_msg		void		OnTimer(UINT_PTR nIDEvent);
	afx_msg		void		OnClose();
	afx_msg		HBRUSH		OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	afx_msg		LRESULT		OnStartTask(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT		OnEndTask(WPARAM wParam, LPARAM lParam);
public:
	CStatic		m_tip;
	CString		m_goods_name;
	int			m_goods_alert_num;
	int			m_time_take;
	StoreInfo   m_goods_alert_num_set_strutct;
	
};
