
// SocketDemoByKxlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SocketDemoByKxl.h"
#include "SocketDemoByKxlDlg.h"
#include "socketclient/Client.h"
#include "socketclient/CommucationProtocol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)

END_MESSAGE_MAP()


// CSocketDemoByKxlDlg �Ի���
DWORD WINAPI RecordOperationInfo(void *pParam)   //��д����������������־�� Ҳ���µ��������Ľ�����
{
	USES_CONVERSION;
	CString backspace =  _T("\r\n");
	SysLogInfo * p_info = (p_SysLogInfo)pParam;
	CSocketDemoByKxlDlg* p_dlg =(CSocketDemoByKxlDlg*)p_info->p_voidTemp;
	CString log = A2T(p_info->showInfo);

	if(p_info != NULL){
		delete p_info;
		p_info = NULL;
	}
	p_dlg->WriteInfoToSysLog(log);	
	return 0;
}

DWORD WINAPI AcceptAndHandleClientThread(void *pParam)   //���ܺʹ���ͻ������ӵ�����  ����������
{
	CSocketDemoByKxlDlg* pServer = (CSocketDemoByKxlDlg*)pParam;
	SOCKET sListen = pServer->GetSocket();//��÷����������׽���

	//FD_SET	m_allSockfd;				
	FD_ZERO(&CSocketDemoByKxlDlg::m_allSockfd);			//��ռ���
	FD_SET(sListen, &CSocketDemoByKxlDlg::m_allSockfd);	//�������׽��ּ���ü���

	FD_SET readfd;					//��������ɶ��׽��ּ���
	FD_SET	writefd;				//���������д�׽��ּ���

	while (pServer->IsRunning())//����������״̬
	{
		FD_ZERO(&readfd);			//��տɶ�����
		FD_ZERO(&writefd);			//��տ�д����
		readfd = CSocketDemoByKxlDlg::m_allSockfd;		//��ֵ
		writefd = CSocketDemoByKxlDlg::m_allSockfd;		//��ֵ

		//���½�����Ϣ
		pServer->ShowClientNumberInfor(CSocketDemoByKxlDlg::m_allSockfd.fd_count);

		//�����ڵȴ��׽�����������
		int nRet = select(0, &readfd, &writefd, NULL, NULL);	
		if (nRet > 0)
		{
			//���������׽��ּ���
			for (u_int i = 0; i < CSocketDemoByKxlDlg::m_allSockfd.fd_count; i++)		
			{
				//���ڿɶ����׽���
				if (FD_ISSET(CSocketDemoByKxlDlg::m_allSockfd.fd_array[i], &readfd) && pServer->IsRunning())
				{
					//���ܿͻ����������� 
					if (CSocketDemoByKxlDlg::m_allSockfd.fd_array[i] == sListen)		
					{
						SOCKADDR_IN	addrClient;
						int			nAddrLen = sizeof(addrClient);
						SOCKET	sClient = accept(sListen, (sockaddr*)&addrClient, &nAddrLen);
						//�½�һ�� CClient��ʵ��
						CClient *pClient = new CClient(sClient, pServer);	
						//����ͻ��˹���������
						pServer->AddClient(pClient);			
						//�����׽��ּ���
						FD_SET(sClient, &CSocketDemoByKxlDlg::m_allSockfd);		
						//���½�����Ϣ
						pServer->ShowClientNumberInfor(CSocketDemoByKxlDlg::m_allSockfd.fd_count);						 
					}else //���տͻ�������
					{	
						//�õ�CClient���ʵ��
						CClient* pClient = pServer->GetClient(CSocketDemoByKxlDlg::m_allSockfd.fd_array[i]);
						if (pClient != NULL)
						{
							//��������
							BOOL bRet = pClient->RecvData();				
							//�������ݴ�����߿ͻ��˹ر��׽���
							if (FALSE == bRet)							
							{
								//ȡ���׽���
								SOCKET sTemp = CSocketDemoByKxlDlg::m_allSockfd.fd_array[i];
								//�Ӽ�����ɾ��
								FD_CLR(CSocketDemoByKxlDlg::m_allSockfd.fd_array[i], &CSocketDemoByKxlDlg::m_allSockfd);
								//�ӿͻ��˹���������ɾ���ÿͻ���
								pServer->DeleteClient(sTemp);
								//���½�����Ϣ
								pServer->ShowClientNumberInfor(CSocketDemoByKxlDlg::m_allSockfd.fd_count);
							}			 
						}						 
					}//else					 
				}//if
				//���ڵĿ�д�׽���
				if (FD_ISSET(CSocketDemoByKxlDlg::m_allSockfd.fd_array[i], &writefd) && pServer->IsRunning())
				{
					//�õ�CClient���ʵ��
					CClient* pClient = pServer->GetClient(CSocketDemoByKxlDlg::m_allSockfd.fd_array[i]);
					if (pClient != NULL)
					{
						//��������
						BOOL bRet = pClient->SendData();
						if (FALSE == bRet)//��������ʧ��
						{
							//��ɾ�����׽���
							SOCKET sDelete = CSocketDemoByKxlDlg::m_allSockfd.fd_array[i];
							//�Ӽ�����ɾ�����׽���
							FD_CLR(CSocketDemoByKxlDlg::m_allSockfd.fd_array[i], &CSocketDemoByKxlDlg::m_allSockfd);
							//�ӿͻ��˹���������ɾ���ÿͻ���
							pServer->DeleteClient(sDelete);
							//���½�����Ϣ
							pServer->ShowClientNumberInfor(CSocketDemoByKxlDlg::m_allSockfd.fd_count);
						}			
					}							 
				}
			}//for
		}//if
		Sleep(50);//�߳�˯��
	}//while
	pServer->DeleteAllClient();//ɾ�����еĿͻ���	
	//pServer->OnClose();
	return 0;
}

FD_SET CSocketDemoByKxlDlg::m_allSockfd = {};

CSocketDemoByKxlDlg::CSocketDemoByKxlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSocketDemoByKxlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketDemoByKxlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MESSAGE, m_message);
	DDX_Control(pDX, IDC_EDIT_STATUS, m_status);
	DDX_Control(pDX, IDC_EDIT_PORT, m_port);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ip);
	DDX_Control(pDX, IDC_EDIT_SENDSTATUS, m_statusSend);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_text);
}

BEGIN_MESSAGE_MAP(CSocketDemoByKxlDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_LOG,&CSocketDemoByKxlDlg::OnRecordLog)
	ON_MESSAGE(WM_TEXT_MESSAGE, &CSocketDemoByKxlDlg::OnRecvTextMessage)
	ON_MESSAGE(WM_SEND_STATUS, &CSocketDemoByKxlDlg::OnRecvReplyFromClient)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_START, &CSocketDemoByKxlDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_CLEARMESSAGE, &CSocketDemoByKxlDlg::OnBnClickedBtnClearmessage)
	ON_BN_CLICKED(IDC_BTN_SEND, &CSocketDemoByKxlDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_STOP, &CSocketDemoByKxlDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_CLEAR_LOG, &CSocketDemoByKxlDlg::OnBnClickedBtnClearLog)
	ON_BN_CLICKED(IDC_BTN_SHOWLOG, &CSocketDemoByKxlDlg::OnBnClickedBtnShowlog)
END_MESSAGE_MAP()


LRESULT  CSocketDemoByKxlDlg::OnRecordLog(WPARAM wParam, LPARAM lParam)
{
	CString log = (LPCTSTR)lParam;
	RecordLog(log);
	return 0;
}


LRESULT  CSocketDemoByKxlDlg::OnRecvTextMessage(WPARAM wParam, LPARAM lParam)
{
	CString message = (LPCTSTR)lParam;
	CString text;
	m_message.GetWindowText(text);
    text += _T("\r\n")+message;
    m_message.SetWindowText(text);
	return 0;
}

LRESULT  CSocketDemoByKxlDlg::OnRecvReplyFromClient(WPARAM wParam, LPARAM lParam)
{
	CString message = (LPCTSTR)lParam;
	m_statusSend.SetWindowText(message);
	return 0;
}

// CSocketDemoByKxlDlg ��Ϣ�������

BOOL CSocketDemoByKxlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitSocket();  //��ʼ���׽��� ����������socket
	GetLocalIp();   //��ñ���IP��ַ ����ʾ����������
	CString port;
	port.Format(_T("%d"), g_iServerPort);
	m_port.SetWindowText(port);

	GetDlgItem(IDC_BTN_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSocketDemoByKxlDlg::GetLocalIp()
{
	//��ü������
	char hostName[256];
	memset(hostName,0,256);
	int nRetCode = gethostname(hostName,sizeof(hostName));
	if(nRetCode!=0)
	{
		//��������
		AfxMessageBox(_T("û��ȡ�ñ�������"));
		return ;
	}
	//ͨ����������ֻ�ñ���IP��ַ
	hostent* lpHostEnt = gethostbyname(hostName);
	if(lpHostEnt == NULL)
	{
		//��������
		AfxMessageBox(_T("û��ȡ�ñ���IP��"));
		return ;
	}
	//��ȡIP
	LPSTR lpAddr=lpHostEnt->h_addr_list[0];
	CString sIpAddress = NULL;
	if(lpAddr)
	{
		struct in_addr inAddr;
		memmove(&inAddr, lpAddr,4);
		//ת��Ϊ��׼��ʽ
		sIpAddress=inet_ntoa(inAddr);
		if(sIpAddress.IsEmpty()){
			AfxMessageBox(_T("û��ȡ�ñ���IP"));
		}
	}
	USES_CONVERSION;
	long IP=ntohl((u_long)inet_addr(T2A(sIpAddress)));  //���ַ��������͵�IP��ַת��Ϊlong�͵�

	m_ip.SetAddress(IP);   //����IP��ַ
	return;
}
void CSocketDemoByKxlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSocketDemoByKxlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


void CSocketDemoByKxlDlg::InitSocket()
{
	WORD	wVersionRequested;	//�����Windows Sockets ʵ�ְ汾
	WSADATA	wsaData;			//����Э�̽��
	int		nErrCode;			//����API�����ķ���ֵ

	wVersionRequested = MAKEWORD(2, 2);	
	nErrCode = WSAStartup( wVersionRequested, &wsaData );
	if ( 0 != nErrCode ) 
	{
		MessageBox(_T("����Windows Socketsʧ��"));
		return;
	}
	//�����׽���
	m_sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_sockServer)
	{
		MessageBox(_T("�����׽���ʧ��"));
		return;
	}
	//��ȡϵͳĬ�ϵķ������ݻ�������С
	unsigned int uiRcvBuf;
	int uiRcvBufLen = sizeof(uiRcvBuf);
	nErrCode= getsockopt(m_sockServer, SOL_SOCKET, SO_SNDBUF,(char*)&uiRcvBuf, &uiRcvBufLen);
	if (SOCKET_ERROR == nErrCode)
	{
		MessageBox(_T("��ȡϵͳĬ�ϵķ������ݻ�������Сʧ��"));
		return;
	}

	//����ϵͳ�������ݻ�����ΪĬ��ֵ��g_iBufTimes��
	uiRcvBuf *= g_iBufTimes;
	nErrCode = setsockopt(m_sockServer, SOL_SOCKET, SO_SNDBUF,(char*)&uiRcvBuf, uiRcvBufLen);
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("�޸�ϵͳ�������ݻ�����ʧ�ܣ�"));
	}


	//�������ϵͳ�������ݻ������Ƿ�ɹ�
	unsigned int uiNewRcvBuf;
	getsockopt(m_sockServer, SOL_SOCKET, SO_SNDBUF,(char*)&uiNewRcvBuf, &uiRcvBufLen);
	if (SOCKET_ERROR == nErrCode || uiNewRcvBuf != uiRcvBuf)
	{
		AfxMessageBox(_T("�޸�ϵͳ�������ݻ�����ʧ�ܣ�"));
	}
	return ;
}

void CSocketDemoByKxlDlg::ShowClientNumberInfor(int nNum)  //��ʾ�ͻ���������Ϣ
{
	CString strTip;
	strTip.Format(_T("Ŀǰ����%d�ͻ����ӡ�"),nNum -1);	
	m_status.SetWindowText(strTip);
}
//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSocketDemoByKxlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSocketDemoByKxlDlg::OnBnClickedBtnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);				//���¶Ի���
	
	int		reVal;					//����ֵ	
	DWORD	dwServIP;		
	m_ip.GetAddress(dwServIP);	//�õ�������IP
	CString port;
	m_port.GetWindowText(port);
	USES_CONVERSION;
	u_short servPort = atoi(T2A(port)); 
	//�������׽��ֵ�ַ
	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = htonl(dwServIP);
	servAddr.sin_port = htons(servPort);
	
	//�󶨷�����
	reVal = bind(m_sockServer,(sockaddr*)&servAddr,sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == reVal)
	{
		AfxMessageBox(_T("��������ʧ��"), MB_OK, 0);
		closesocket(m_sockServer);
		WSACleanup();
		return;
	}
	else 
	{
		//m_status.SetWindowText(_T("�������󶨳ɹ���"));
		CString _str = _T("�������󶨳ɹ���");
		RecordLog(_str);
	}
	//����
	reVal = listen(m_sockServer,SOMAXCONN);
	if (SOCKET_ERROR == reVal)
	{
		AfxMessageBox(_T("����������ʧ�ܣ�"), MB_OK, 0);
		closesocket(m_sockServer);
		WSACleanup();
		return;
	}	
	m_bRunning = TRUE;//�޸ķ�����״̬
	
	//�������ܺʹ���ͻ��������߳�
	DWORD dwThread;	
	m_hAcceptAndHandle = CreateThread(NULL, 0, AcceptAndHandleClientThread, this, 0, &dwThread);
	CloseHandle(m_hAcceptAndHandle);
	
	//���½���
	(CButton*)GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);	//������ť��Ч
	(CButton*)GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);	   //�˳���ť��Ч

	(CButton *)GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);  
    GetDlgItem(IDC_IPADDRESS1)->EnableWindow(FALSE);
	(CButton *)GetDlgItem(IDC_BTN_SEND)->EnableWindow(TRUE);
	
	m_ip.EnableWindow(FALSE);	//��������ַ�ؼ���Ч
	
	CString _str = _T("�����������ɹ�����ʼ���У�");
	//UpdateLog(_str);				 //��ʾ�ɹ���Ϣ
	//WriteLogToTxt(_str);
	RecordLog(_str);
}

void CSocketDemoByKxlDlg::RecordLog(CString log)
{
	USES_CONVERSION;
	SysLogInfo* p_info = new SysLogInfo;
	p_info->p_voidTemp = this;
	strcpy_s(p_info->showInfo,T2A(log));
	DWORD dwThread;	
	HANDLE hRecordOperation = CreateThread(NULL, 0, RecordOperationInfo, p_info, 0, &dwThread);
	CloseHandle(hRecordOperation);
}

void CSocketDemoByKxlDlg::WriteInfoToSysLog(CString log)    //����־��Ϣд��ϵͳ��־
{
	USES_CONVERSION;
	CString curTime = _T("");
	GetLogTime(curTime);
	CString backspace = _T("\r\n");
	CStdioFile mFile;
	CFileException mExcept;
	CString writeToPath = _T(".//ServerOperationLog.txt");
	while(!mFile.Open(writeToPath, CFile::typeText|CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate|CFile::shareDenyWrite, &mExcept))
	{
		Sleep(500);	
	}

	mFile.SeekToEnd();
	curTime = backspace + curTime;
	curTime = curTime + backspace;
	CString _strToWrite = curTime;

	_strToWrite = _strToWrite + log;
	_strToWrite = _strToWrite + backspace;
	char *p = T2A(_strToWrite);
	mFile.Write(p,strlen(p));
	mFile.Close();
}

void CSocketDemoByKxlDlg::GetLogTime(CString &time)    //��ü�¼��־��ʱ��
{
	SYSTEMTIME sys; 
	GetLocalTime(&sys); 
	CString dayOfWeek = _T("����");
	time.Empty();
	switch (sys.wDayOfWeek)
	{
	case 1:
		{
			dayOfWeek+= _T("һ");
			break;
		}
	case 2:
		{
			dayOfWeek+= _T("��");
			break;
		}
	case 3:
		{
			dayOfWeek+= _T("��");
			break;
		}
	case 4:
		{
			dayOfWeek+= _T("��");
			break;
		}
	case 5:
		{
			dayOfWeek+= _T("��");
			break;
		}
	case 6:
		{
			dayOfWeek+= _T("��");
			break;
		}
	case 0:
		{
			dayOfWeek+= _T("��");
			break;

		}
	default:
		break;
	}
	time.Format(_T("%4d/%02d/%02d %s %02d:%02d:%02d "),(int)sys.wYear,(int)sys.wMonth,(int)sys.wDay,dayOfWeek,(int)sys.wHour,(int)sys.wMinute,(int)sys.wSecond);
}

void CSocketDemoByKxlDlg::UnInitSocke()   //�ر��׽���
{
	closesocket(m_sockServer);
	m_sockServer = INVALID_SOCKET;
	WSACleanup();
}

void CSocketDemoByKxlDlg::AddClient(CClient *pClient)//��ӿͻ��˽ڵ�
{	
	m_listLocker.Lock();
	m_listClient.push_back(pClient);
	m_listLocker.UnLock();
}

void CSocketDemoByKxlDlg::DeleteClient(SOCKET s)		//ɾ���ͻ��˽ڵ�
{
	m_listLocker.Lock();
	//����������
	list<CClient*>::iterator it = m_listClient.begin();
	for (it; it != m_listClient.end();)
	{
		CClient *pClient = (CClient*)*it;
		if (pClient->GetSocket() == s)//��ͬ���׽���
		{
			CString _str = NULL;
			//_str.Format(_T("�û�\"%s\"����������Ͽ����ӡ�"),pClient->m_user);
			//pClient->m_pServer->SendMessage(WM_LOG,0,(LPARAM)(LPCTSTR)_str);
			m_listClient.erase(it++);//��������ɾ��
			delete pClient;			//�ͷ��ڴ�
			pClient = NULL;
			break;
		}else
		{
			it++;
		}
	}
	m_listLocker.UnLock();
}

CClient* CSocketDemoByKxlDlg::GetClient(SOCKET s)		//�����׽��ֵõ��ͻ���
{
	CClient* pClient = NULL;
	m_listLocker.Lock();
	list<CClient*>::iterator it = m_listClient.begin();
	for (it; it != m_listClient.end(); ++it)
	{
		pClient = *it;
		if (s == pClient->GetSocket())//�ҵ�
		{
			break;
		}
	}
	m_listLocker.UnLock();
	return pClient;	
}

void CSocketDemoByKxlDlg::DeleteAllClient(void)		//ɾ�����пͻ��˽ڵ�
{
	//EnterCriticalSection(&m_cs);
	//����������
	list<CClient*>::iterator it = m_listClient.begin();
	for (it; it != m_listClient.end();)
	{
		CClient *pClient = (CClient*)*it;
		m_listClient.erase(it++);

		delete pClient;
		pClient = NULL;		
	}
	m_listClient.clear();
	//LeaveCriticalSection(&m_cs); 
}

void CSocketDemoByKxlDlg::OnBnClickedBtnClearmessage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_message.SetWindowText(_T(""));
}

void CSocketDemoByKxlDlg::OnBnClickedBtnSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString text;
	m_text.GetWindowText(text);
	m_listLocker.Lock();
	std::list<CClient*>::iterator it = m_listClient.begin();
	CClient* pClient = *it;
	if(pClient)
	{
        pClient->SetSendMessageBuff(text);
		pClient->SetReqType(REQ_SEND_TEXT_MESSAGE_TO_CLINET);
	}
    m_listLocker.Lock();
    
	CString time;
    GetCurTime(time);
    CString temp;
	CString chat;
	m_message.GetWindowText(chat);
	temp.Format(_T("%s\r\n%s  ��˵��\r\n%s"),chat,time,text);
    m_message.SetWindowText(temp);

	return;
}

void  CSocketDemoByKxlDlg::GetCurTime(CString& time)
{
	SYSTEMTIME sys; 
	GetLocalTime(&sys); 
	time.Format(_T("%4d-%02d-%02d %02d:%02d:%02d"),sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond);
}
void CSocketDemoByKxlDlg::OnBnClickedBtnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bRunning = FALSE;								//���÷�����״̬
	//m_status.SetWindowText(_T("�������˳���"));		 //���½���
	CString _str = _T("�����������˳��У�");
	RecordLog(_str);

	//DeleteAllClient();
	UnInitSocke();
	(CButton*)GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);	//������ť��Ч
	(CButton*)GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);	   //�˳���ť��Ч

	(CButton *)GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);  
	GetDlgItem(IDC_IPADDRESS1)->EnableWindow(TRUE);
	(CButton *)GetDlgItem(IDC_BTN_SEND)->EnableWindow(FALSE);
	m_status.SetWindowText(_T("�����������˳���"));
	Sleep(200);
	InitSocket();
}

BOOL  CSocketDemoByKxlDlg::PreTranslateMessage(MSG*   pMsg) 
{ 
	//   �޸Ļس����Ĳ�����Ӧ 
	if(pMsg-> message== WM_KEYDOWN  &&  pMsg-> wParam==VK_RETURN) 
	{ 
		return TRUE;
	} 
	return   CDialog::PreTranslateMessage(pMsg); 
}

void CSocketDemoByKxlDlg::OnBnClickedBtnClearLog()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileFind fileFind;
	if(fileFind.FindFile(_T(".//ServerOperationLog.txt")))
	{
		DeleteFile(_T(".//ServerOperationLog.txt"));
	}else
	{
		CString _str = _T("��Ǹ�޷�ɾ��ϵͳ��ϸ��������־����Ϊ���Ѿ���ɾ����");
	}
}

void CSocketDemoByKxlDlg::OnBnClickedBtnShowlog()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileFind fileFind;

	if(fileFind.FindFile(_T(".//ServerOperationLog.txt")))
	{
		HINSTANCE h = ShellExecute(NULL,_T("open"),_T("ServerOperationLog.txt"),NULL,NULL,SW_SHOWNORMAL);
		int i = (int)h;

	}
}
