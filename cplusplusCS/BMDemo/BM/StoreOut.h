#pragma once
#include "afxwin.h"


// CStoreOut �Ի���

class CStoreOut : public CDialogEx
{
	DECLARE_DYNAMIC(CStoreOut)

public:
	CStoreOut(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStoreOut();

// �Ի�������
	enum { IDD = IDD_DLG_STORE_OUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	CEdit m_id;
	int			m_time_take;
	int			m_numOut;
	CStatic		m_tip;
	CString		m_name_goods;
	StoreInfo   m_goods_out_struct;
protected:
	afx_msg		LRESULT		OnStartTask(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT		OnEndTask(WPARAM wParam, LPARAM lParam);
public:
	afx_msg		HBRUSH		OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg		void		OnTimer(UINT_PTR nIDEvent);
	afx_msg		void		OnClose();
	void					ShowTip();
	virtual     BOOL        OnInitDialog();
	afx_msg		void		OnBnClickedBtnStoreOut();
	afx_msg		void		OnBnClickedBtnCancle();
};
