#pragma once
#include "afxcmn.h"


// CStoreAlert �Ի���

class CStoreAlert : public CDialogEx
{
	DECLARE_DYNAMIC(CStoreAlert)

public:
	CStoreAlert(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStoreAlert();

// �Ի�������
	enum { IDD = IDD_DLG_STORE_ALERT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
