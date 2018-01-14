
// SocketDemoByKxlDlg.h : ͷ�ļ�
//
#include "Resource.h"
#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "socketclient/SyncLocker.h"
#include "socketclient/CommucationProtocol.h"
class CClient;

// CSocketDemoByKxlDlg �Ի���
class CSocketDemoByKxlDlg : public CDialog
{
// ����
public:
	CSocketDemoByKxlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SOCKETDEMOBYKXL_DIALOG };

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
	LRESULT OnRecordLog(WPARAM wParam, LPARAM lParam);
	LRESULT OnRecvTextMessage(WPARAM wParam, LPARAM lParam);
	LRESULT OnRecvReplyFromClient(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()


public:
   void			InitSocket(void);			//��ʼ��socket
   void         UnInitSocke();
   void         GetLocalIp();
   void         GetLogTime(CString &time);    //��ü�¼��־��ʱ��
   void         WriteInfoToSysLog(CString log); 
   void         RecordLog(CString log);
   void         ShowClientNumberInfor(int nNum);
   CClient*     GetClient(SOCKET s);
   void         AddClient(CClient *pClient);   //��ӿͻ��˽ڵ�
   void         DeleteAllClient(void);
   void         DeleteClient(SOCKET s);
   inline SOCKET GetSocket(void)				//����׽���
   {
	   return m_sockServer;
   }
   inline BOOL   IsRunning()
   {
	   return m_bRunning;
   }
   void  GetCurTime(CString& time);
 
public:
	SOCKET	    m_sockServer;					//�����������׽ӽ���
	BOOL		m_bRunning;					//����������״̬
	static	    FD_SET	m_allSockfd;             //�����������׽��ּ���
public:
	CEdit       m_message;
	CEdit       m_status;
	CEdit       m_port;
	CIPAddressCtrl m_ip;
	HANDLE		    m_hAcceptAndHandle;				//���պʹ���ͻ��������߳̾��
	CSyncLocker 	m_listLocker;				//����������ٽ�������	
	std::list<CClient*>		m_listClient;		//����ͻ��˵�����
    
    CEdit      m_statusSend;
    CEdit      m_text;
public:
	BOOL         PreTranslateMessage(MSG*   pMsg);
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnClearmessage();
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnClearLog();
	afx_msg void OnBnClickedBtnShowlog();
};
