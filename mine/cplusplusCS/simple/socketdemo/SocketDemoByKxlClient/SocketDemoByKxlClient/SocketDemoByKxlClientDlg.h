
// SocketDemoByKxlClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "socket/SocketDefines.h"

// CSocketDemoByKxlClientDlg �Ի���
class CSocketDemoByKxlClientDlg : public CDialog
{
// ����
public:
	CSocketDemoByKxlClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SOCKETDEMOBYKXLCLIENT_DIALOG };

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
    BOOL    InitSocket();
    void    GetLocalIp();
	BOOL	SendReq();			//���������������  
	BOOL	RecvData();			//���մӷ��������ص�����


	
public:
	BOOL PreTranslateMessage(MSG* pMsg);
	BOOL SendTextMessage();	
	void UnInitSocke();
	BOOL RecvTextMessage(int len);
	BOOL RecvMessageFromServer(int len);	
	BOOL SendReplyMessageToServer();
public:
	enumREQTYPE   m_nCurReq;    //��ǰ��������
    SOCKET   m_sockWhole;
    BOOL     m_bIsRunning;

	CString  m_sSendMessage;    //���͵���Ϣ����  ��ʱ��ôд���� ʵ��Ӧ��ʹ��map����
	CString  m_sRecvMessage;    //���յ���Ϣ   ��ʱ��ô�洢���� ʵ��Ӧ�ÿ�����map
	CEdit m_chat;
	CEdit m_message;
	CEdit m_statusSend;
	CEdit m_statusLink;
	CEdit m_port;
	CIPAddressCtrl m_ip;
public:
	afx_msg void OnBnClickedBtnLink();
	afx_msg void OnBnClickedBtnSend();
	void   UpdateChatEdit(CString &newMessage);    //���´�����Ϣ
	void   GetCurTime(CString& time);
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnStop();
};
