#pragma once
#include "afxcmn.h"
#include "ConnectSet.h"
//#include "ProcessList.h"
#include "ProListCtrl.h"
// CDownload_Downloading �Ի���
#define TIMER_SPEED   0     //ʱ�������ID ������´����ٶ�


class ThreadOperate;
class CDownload_Downloading : public CDialogEx
{
	DECLARE_DYNAMIC(CDownload_Downloading)

public:
	CDownload_Downloading(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDownload_Downloading();

// �Ի�������
	enum { IDD = IDD_DIALOG_Download_Downloading };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//CListCtrl m_Download_Downloading;
	CProListCtrl m_Download_Downloading;
	void InitDownload_Downloading(void);
	BOOL OnInitDialog(void);
	//void InsertFile(CString,CString,CString,CString,int);
	void NewDownLoad(CString &filename,CString &filetype, CString &filesize, CString &filepath,int &j);
	CString m_filename;
	CString m_filepath;
	//afx_msg void OnBnClickedButton1();
	afx_msg void OnDblclkListDownloadDownloading(NMHDR *pNMHDR, LRESULT *pResult);
	void StratToDownLoad(void);
	CConnectSet connectset;
	int m_NUMDownloading;
	//CProcessList processlist;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	ThreadOperate *_pthreadoperate;  
//protected:
//	afx_msg LRESULT OnOkSearch(WPARAM wParam, LPARAM lParam);
};
