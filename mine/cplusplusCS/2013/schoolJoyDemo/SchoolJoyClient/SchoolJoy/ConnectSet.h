#pragma once


// CConnectSet �Ի���

class CConnectSet : public CDialogEx
{
	DECLARE_DYNAMIC(CConnectSet)

public:
	CConnectSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConnectSet();

// �Ի�������
	enum { IDD = IDD_DIALOG_ConnectSet};


public:
	HWND m_hWnd;
	CString m_serverIp;
	int m_serverPort;
	static CString ServerIP;
	static int ServerPort;
	void OnOK();
	void OnCancel();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonOk();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
