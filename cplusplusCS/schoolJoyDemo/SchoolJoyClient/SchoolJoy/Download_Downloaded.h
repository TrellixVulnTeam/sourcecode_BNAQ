#pragma once
#include "afxcmn.h"


// CDownload_Downloaded �Ի���

class CDownload_Downloaded : public CDialogEx
{
	DECLARE_DYNAMIC(CDownload_Downloaded)

public:
	CDownload_Downloaded(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDownload_Downloaded();

// �Ի�������
	enum { IDD = IDD_DIALOG_Download_Downloaded };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Download_Downloaded;
	void InitDownload_Downloaded(void);
	BOOL OnInitDialog(void);
};
