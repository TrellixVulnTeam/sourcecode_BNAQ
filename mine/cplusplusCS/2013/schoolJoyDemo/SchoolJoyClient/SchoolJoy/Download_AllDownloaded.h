#pragma once
#include "afxcmn.h"


// CDownload_AllDownloaded �Ի���

class CDownload_AllDownloaded : public CDialogEx
{
	DECLARE_DYNAMIC(CDownload_AllDownloaded)

public:
	CDownload_AllDownloaded(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDownload_AllDownloaded();

// �Ի�������
	enum { IDD = IDD_DIALOG_Download_AllDownloaded };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List_Download_AllDownloaded;
	void InitDownload_AllDownloaded(void);
	BOOL OnInitDialog(void);
};
