
// SocketDemoByKxlClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SocketDemoByKxlClient.h"
#include "SocketDemoByKxlClientDlg.h"
#include "socket/SocketDefines.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT SendAndRecvClientThread(LPVOID pParam)		//���պͷ��������߳�
{
    CSocketDemoByKxlClientDlg* pMainDlg = (CSocketDemoByKxlClientDlg*)pParam;
	SOCKET	sockClient = pMainDlg->m_sockWhole;//�ͻ����׽���	
	if(INVALID_SOCKET == sockClient)
	{
		return 0;
	}
	FD_SET writefd;	//��д����
	FD_SET readfd;	//�ɶ�����

	while(pMainDlg->m_bIsRunning)
	{
		FD_ZERO(&writefd);		//����
		FD_ZERO(&readfd);		//����
		FD_SET(sockClient, &writefd);//��ӵ���д����
		FD_SET(sockClient, &readfd);	//��ӵ��ɶ�����

		int reVal = 0;
		reVal = select(0, &readfd, &writefd, NULL, NULL);//�ȴ��׽�����������
		if (SOCKET_ERROR == reVal)
		{
			AfxMessageBox(_T("select����"));
			return 0;
		}else if ( reVal > 0)
		{
			if (FD_ISSET(sockClient, &writefd))			//�����д������
			{
				if (FALSE == pMainDlg->SendReq())	//��������
				{
					pMainDlg->m_sockWhole = INVALID_SOCKET;
					AfxMessageBox(_T("��������ʧ��,�����µ�¼��"));
					pMainDlg->m_bIsRunning = FALSE;     //���ӶϿ� ���û����µ�¼
					pMainDlg->m_sockWhole = INVALID_SOCKET;   //�����������³�ʼ��socket
					return 0;
				}			
			}			

			if (FD_ISSET(sockClient, &readfd))			//����ɶ�������
			{
				if(FALSE == pMainDlg->RecvData())//��������
				{
					//AfxMessageBox(_T("����Ŀ¼��Ϣʧ�ܣ�"));
					pMainDlg->m_sockWhole = INVALID_SOCKET;
					AfxMessageBox(_T("��������ʧ��,�����µ�¼��"));
					pMainDlg->m_bIsRunning = FALSE;   //���ӶϿ� ���û����µ�¼
					//m_bReqAvailable = TRUE;   //ʹ���������
					pMainDlg->m_sockWhole = INVALID_SOCKET;  //�����������³�ʼ��socket
					return 0;
				}
			}			
		}
		Sleep(50);		
	}

	return 0;
}




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


// CSocketDemoByKxlClientDlg �Ի���




CSocketDemoByKxlClientDlg::CSocketDemoByKxlClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSocketDemoByKxlClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketDemoByKxlClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CHAT, m_chat);
	DDX_Control(pDX, IDC_EDIT_MESSAGE, m_message);
	DDX_Control(pDX, IDC_EDIT_STATUSSEND, m_statusSend);
	DDX_Control(pDX, IDC_EDIT_LINKSTATUS, m_statusLink);
	DDX_Control(pDX, IDC_EDIT_PORT, m_port);
	DDX_Control(pDX, IDC_IPADDRESS_IP, m_ip);
}

BEGIN_MESSAGE_MAP(CSocketDemoByKxlClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_LINK, &CSocketDemoByKxlClientDlg::OnBnClickedBtnLink)
	ON_BN_CLICKED(IDC_BTN_SEND, &CSocketDemoByKxlClientDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CSocketDemoByKxlClientDlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_STOP, &CSocketDemoByKxlClientDlg::OnBnClickedBtnStop)
END_MESSAGE_MAP()


// CSocketDemoByKxlClientDlg ��Ϣ�������

BOOL CSocketDemoByKxlClientDlg::OnInitDialog()
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
	m_sockWhole = INVALID_SOCKET;
	m_bIsRunning = FALSE;
	m_nCurReq = REQ_NONE;
	CString port;

	port.Format(_T("%d"),g_iPort);
	m_port.SetWindowText(port);
    InitSocket();
	GetLocalIp();
    
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SEND)->EnableWindow(FALSE);

	return TRUE;      // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BOOL  CSocketDemoByKxlClientDlg::PreTranslateMessage(MSG*   pMsg) 
{ 
	//   �޸Ļس����Ĳ�����Ӧ 
	if(pMsg-> message== WM_KEYDOWN  &&  pMsg-> wParam==VK_RETURN) 
	{ 
		return TRUE;
	} 
	return   CDialog::PreTranslateMessage(pMsg); 
}

void CSocketDemoByKxlClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSocketDemoByKxlClientDlg::OnPaint()
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSocketDemoByKxlClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSocketDemoByKxlClientDlg::OnBnClickedBtnLink()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

    m_statusLink.SetWindowText(_T("��ʼ���ӷ�����"));
	
	//��÷�������IP��ַ
	USES_CONVERSION;
	CString ip;
    m_ip.GetWindowText(ip);
	char *pIPTemp = T2A(ip);		//��CString���͵�IP��ַת��Ϊcharָ����ָ������	
	long IP = ntohl((u_long)inet_addr(pIPTemp));
	//ntohl()�ǽ�һ���޷��ų��������������ֽ�˳��ת��Ϊ�����ֽ�˳��
	if(IP == INADDR_NONE)
	{
		AfxMessageBox(_T("IP��ַ���Ϸ�������������"));
        m_statusLink.SetWindowText(_T("IP��ַ���Ϸ�������������"));
		return ;
	}

	//�������׽��ֵ�ַ
	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;

	servAddr.sin_addr.S_un.S_addr = htonl(IP);
	CString port;
	m_port.GetWindowText(port);
    
	servAddr.sin_port = htons(atoi(T2A(port)));
	if(m_sockWhole == INVALID_SOCKET)
	{
		InitSocket();
		if(m_sockWhole == INVALID_SOCKET)
		{
			AfxMessageBox(_T("��ó�ʼ�����׽���ʧ�ܣ�"));
            m_statusLink.SetWindowText(_T("��ó�ʼ�����׽���ʧ�ܣ�"));
			m_sockWhole = INVALID_SOCKET;		
			return ;
		}
	}
	int nErrCode = connect(m_sockWhole,(sockaddr*)&servAddr, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == nErrCode)
	{
        m_statusLink.SetWindowText(_T("���ӷ�����ʧ�ܣ�����IP��ַ�Ͷ˿��Ƿ���ȷ"));
		m_sockWhole = INVALID_SOCKET;
		AfxMessageBox(_T("���ӷ�����ʧ�ܣ�"),MB_OK, 0);
		return ;
	}
	m_statusLink.SetWindowText(_T("���ӷ������ɹ�"));
	m_bIsRunning = TRUE;
	AfxBeginThread(SendAndRecvClientThread,this);    //�������պͷ��������߳�
	GetDlgItem(IDC_BTN_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_LINK)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_IPADDRESS_IP)->EnableWindow(FALSE);
	return ;
}

BOOL CSocketDemoByKxlClientDlg::InitSocket()
{
	WORD	wVersionRequested;			//����socket�汾
	WSADATA	wsaData;					//wsaData�ṹ
	int		nErrCode;					//����ֵ

	wVersionRequested = MAKEWORD( 2, 2 );//����windows Sockets 2.2�汾	
	nErrCode = WSAStartup( wVersionRequested, &wsaData );
	if ( 0 != nErrCode )
	{
		return FALSE;
	}

	//�����׽���
	m_sockWhole = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_sockWhole)
	{
		AfxMessageBox(_T("�����׽���ʧ��"));
		return FALSE;
	}

	//����ϵͳ��������ΪĬ�ϵ�BUF_TIMES��
	unsigned int uiRcvBuf;
	int uiRcvBufLen = sizeof(uiRcvBuf);
	nErrCode= getsockopt(m_sockWhole, SOL_SOCKET, SO_RCVBUF,(char*)&uiRcvBuf, &uiRcvBufLen);
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("��ȡϵͳĬ�Ϸ������ݻ�����ʧ�ܣ�"));
		return FALSE;
	}
	uiRcvBuf *= g_iBufTimes;
	nErrCode = setsockopt(m_sockWhole, SOL_SOCKET, SO_RCVBUF,(char*)&uiRcvBuf, uiRcvBufLen);
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("�޸�ϵͳ�������ݻ�����ʧ�ܣ�"));
		return FALSE;
	}

	//�������ϵͳ�������ݻ������Ƿ�ɹ�
	unsigned int uiNewRcvBuf;
	getsockopt(m_sockWhole, SOL_SOCKET, SO_RCVBUF,(char*)&uiNewRcvBuf, &uiRcvBufLen);
	if (SOCKET_ERROR == nErrCode || uiNewRcvBuf != uiRcvBuf)
	{
		AfxMessageBox(_T("�޸�ϵͳ�������ݻ�����ʧ�ܣ�"));;
		return FALSE;
	}
    
	return TRUE;
}

void CSocketDemoByKxlClientDlg::GetLocalIp()
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

BOOL CSocketDemoByKxlClientDlg::SendReq()		//���������������
{
	BOOL reVal = TRUE;			//����ֵ
	switch(m_nCurReq)	//��������
	{
	case REQ_TEXT_MESSAGE:
		{
			reVal = SendTextMessage();
			m_nCurReq = REQ_NONE;
			break;
		}
	case REQ_REPLY_MESSAGE_FROM_SERVER:
		{
			reVal = SendReplyMessageToServer();
			m_nCurReq = REQ_NONE;
			break;
		}
	default:
		{
			break;
		}
	}
	return reVal;
}

BOOL CSocketDemoByKxlClientDlg::RecvData()		//���մӷ��������ص�����
{
	BOOL	reVal = TRUE;	//����ֵ	
	int		nErrCode;		//����ֵ
	//��ȡ��ͷ
	hdr header;
	nErrCode = recv(m_sockWhole,(char*)&header, HEADLEN,0);		
	if (SOCKET_ERROR == nErrCode || 0 == nErrCode)//�������ر���
	{
		AfxMessageBox(_T("�������رգ�"));
		reVal = FALSE;	
		return reVal;
	}	

	//��ȡ����
	int nDataLen = header.usTotalLen - HEADLEN;//����ĳ���	
	switch(header.iReqType)					//�������ݰ������ͷ��� �ٶ�ȡ����
	{
	case ENUM_PACKET_RECV_TEXT_MESSAGE:				//�յ��Ļظ���Ϣ ��¼�Ƿ�ɹ�
		{
			reVal = RecvTextMessage(nDataLen);
			break;
		}
	case ENUM_PACKET_RECV_MESSAGE_FROM_SERVER:				//�յ��Ļظ���Ϣ ��¼�Ƿ�ɹ�
		{
			reVal = RecvMessageFromServer(nDataLen);
			break;
		}
	default:
		break;						
	}	
	if(FALSE == reVal)
	{
		AfxMessageBox(_T("�������Է������Ļظ���Ϣʧ��,��������Ͽ����ӣ����������ӣ�"));
	}
	return reVal;	
}

BOOL CSocketDemoByKxlClientDlg::SendTextMessage()   //�������������Ϣ
{
	int nflag;
	hdr header;
	Package package;
	memset(&header, 0, sizeof(header));
	memset(&package, 0, sizeof(package));
	USES_CONVERSION;
    strcpy_s(package.buff,T2A(m_sSendMessage));
	header.iReqType = ENUM_PACKET_SEND_TEXT_MESSAGE;
	header.usTotalLen = HEADLEN + sizeof(package);
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���Ͱ�ͷʧ�ܣ������Ի���������"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char *)&package,sizeof(package),0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����ı���Ϣʧ�ܣ������Ի���������"));
		return FALSE;
	}
	return TRUE;
}

BOOL CSocketDemoByKxlClientDlg::SendReplyMessageToServer()   //�������������Ϣ
{
	int nflag;
	hdr header;
	Package package;
	memset(&header, 0, sizeof(header));
	memset(&package, 0, sizeof(package));
	USES_CONVERSION;
    m_sSendMessage = _T("�ɹ��յ�");
	strcpy_s(package.buff,T2A(m_sSendMessage));
	header.iReqType = ENUM_PACKER_SEND_RELPY_MESSAGE_TO_SERVER;
	header.usTotalLen = HEADLEN + sizeof(package);
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���Ͱ�ͷʧ�ܣ������Ի���������"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char *)&package,sizeof(package),0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����ı���Ϣʧ�ܣ������Ի���������"));
		return FALSE;
	}
	return TRUE;
}


BOOL CSocketDemoByKxlClientDlg::RecvTextMessage(int len)		////���ջظ���Ϣ ���ڵ�¼�Ƿ�ɹ���
{
	Package package;
	memset(&package,0,sizeof(package));
	int errCode = recv(m_sockWhole,(char *)&package,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���շ������ظ���Ϣʧ��"));
		return FALSE;
	}
	CString time;
	GetCurTime(time);
	m_statusSend.SetWindowText(time+_T("  ")+CString(package.buff));
	return TRUE;
}


BOOL CSocketDemoByKxlClientDlg::RecvMessageFromServer(int len)		////���ջظ���Ϣ ���ڵ�¼�Ƿ�ɹ���
{
	Package package;
	memset(&package,0,sizeof(package));
	int errCode = recv(m_sockWhole,(char *)&package,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���շ�������Ϣʧ��"));
		return FALSE;
	}
	m_sRecvMessage = CString(package.buff);
	UpdateChatEdit(m_sRecvMessage);    //���´�����Ϣ
	m_nCurReq = REQ_REPLY_MESSAGE_FROM_SERVER;
	return TRUE;
}


void CSocketDemoByKxlClientDlg::OnBnClickedBtnSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString text;
	m_message.GetWindowText(text);
	m_sSendMessage = text;
	m_nCurReq = REQ_TEXT_MESSAGE;

	CString time;
	GetCurTime(time);
	CString temp;
	CString chat;
	m_chat.GetWindowText(chat);
	temp.Format(_T("%s\r\n%s  ��˵��\r\n%s"), chat,time,text);
	m_chat.SetWindowText(temp);
	return ;
}


void CSocketDemoByKxlClientDlg::UpdateChatEdit(CString &newMessgae)    //���´�����Ϣ
{
	CString text;
	m_chat.GetWindowText(text);
	CString time;
	GetCurTime(time);
    text += _T("\r\n")+ time + _T("������˵��") + _T("\r\n") + newMessgae;
	m_chat.SetWindowText(text);
	return ;
}

void  CSocketDemoByKxlClientDlg::GetCurTime(CString& time)
{
	SYSTEMTIME sys; 
	GetLocalTime(&sys); 
	time.Format(_T("%4d-%02d-%02d %02d:%02d:%02d"),sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond);
}
void CSocketDemoByKxlClientDlg::OnBnClickedBtnClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_chat.SetWindowText(_T(""));
}

void CSocketDemoByKxlClientDlg::OnBnClickedBtnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bIsRunning = FALSE;
    UnInitSocke();
	Sleep(200);
	m_statusLink.SetWindowText(_T("��������Ͽ�����"));
	GetDlgItem(IDC_BTN_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_LINK)->EnableWindow(TRUE);
    GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_IPADDRESS_IP)->EnableWindow(TRUE);
	InitSocket();
}

void CSocketDemoByKxlClientDlg::UnInitSocke()   //�ر��׽���
{
	closesocket(m_sockWhole);
	m_sockWhole = INVALID_SOCKET;
	WSACleanup();
}
