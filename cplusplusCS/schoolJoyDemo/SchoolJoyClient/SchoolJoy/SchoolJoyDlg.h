
// SchoolJoyDlg.h : ͷ�ļ�
//

#pragma once
//#include "Downloaded.h"
//#include "AllDownload.h"
//#include "Downloading.h"

#include "afxcmn.h"
#include "afxwin.h"
#include "Set.h"
#include "LogIn.h"
#include "Download.h"
#include "Upload.h"
#include "Search.h"


// CSchoolJoyDlg �Ի���
class CSchoolJoyDlg : public CDialogEx
{
// ����
public:
	CSchoolJoyDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SCHOOLJOY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CSearch m_search;
	CDownload m_download;
	CUpload m_upload;
	CTabCtrl m_tab_main;
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonDownload();
	afx_msg void OnBnClickedButtonUpload();
//	CEdit m_Edit_Main_Show;
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
//	CString m_edit_main_show;
//	afx_msg void OnBnClickedButtonUpdatalogin();
//	afx_msg void OnBnClickedButtonUpdatalogin();
	CButton m_button_download;
	CButton m_button_upload;
	//afx_msg void OnBnClickedButtonStartdownload();
	void ShowTray();   //��ʾ���̣�������Ϣ��Ӧ����������afx_msg
	afx_msg LRESULT OnTray(WPARAM wParam, LPARAM lParam);//�����̵Ĵ�����
};
