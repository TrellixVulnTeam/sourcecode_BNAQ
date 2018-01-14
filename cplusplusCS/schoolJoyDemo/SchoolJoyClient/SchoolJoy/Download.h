#pragma once
#include "afxcmn.h"
#include "download_downloading.h"
#include "download_downloaded.h"
#include "download_alldownloaded.h"


// CDownload �Ի���

class CDownload : public CDialogEx
{
	DECLARE_DYNAMIC(CDownload)

public:
	CDownload(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDownload();

// �Ի�������
	enum { IDD = IDD_DIALOG_Download };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	CListCtrl m_List_Download;
	BOOL OnInitDialog(void);
	void InitDownload(void);
	CTabCtrl m_tab_download;
	CDownload_Downloading m_download_downloading;
	CDownload_Downloaded m_download_downloaded;
	CDownload_AllDownloaded m_download_alldownloaded;
	afx_msg void OnSelchangeTabDownload(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonStartdownload();
};
