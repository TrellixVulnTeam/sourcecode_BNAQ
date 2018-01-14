// DBNew.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "DBNew.h"
#include "afxdialogex.h"


// CDBNew �Ի���

IMPLEMENT_DYNAMIC(CDBNew, CDialogEx)

CDBNew::CDBNew(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDBNew::IDD, pParent)
	, m_db_name(_T(""))
	, m_name_confirm(_T(""))
{

}

CDBNew::~CDBNew()
{
}

void CDBNew::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DB_NAME, m_db_name);
	DDX_Text(pDX, IDC_EDIT_NAME_CONFIRM, m_name_confirm);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
	//  DDX_Text(pDX, IDC_EDIT_DB_SAVE_PATH, m_db_save_path);
}


BEGIN_MESSAGE_MAP(CDBNew, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CDBNew::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDBNew::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_STARTTASK_DBNew, &CDBNew::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_DBNew, &CDBNew::OnEndTask)
END_MESSAGE_MAP()


// CDBNew ��Ϣ�������
BOOL CDBNew::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HICON hIcon=AfxGetApp()->LoadIcon(IDI_ICON_BMMAIN);
	
	this->SetIcon(hIcon,TRUE);
	this->SetIcon(hIcon,FALSE);

	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
			FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	((CStatic*)GetDlgItem(IDC_STATIC_TIP))->SetFont(&font);
	//((CStatic*)GetDlgItem(IDC_STATIC_TIPS))->SetFont(&font);
	font.Detach();
	return TRUE;
}

HBRUSH CDBNew::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)  
	{
		
		if(pWnd->GetDlgCtrlID() == IDC_STATIC_TIP)
		{
			pDC->SetTextColor(RGB(255,48,48));			
		}
		pDC->SetBkMode(TRANSPARENT);  
		//hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
		HBRUSH b_static=CreateSolidBrush(RGB(185,211,255));
		
		return b_static;
		
	}
	if(nCtlColor == CTLCOLOR_DLG){
		pDC->SetTextColor(RGB(0,0,0)); 
		pDC->SetBkColor(RGB(185,211,255)); 
		HBRUSH b=CreateSolidBrush(RGB(185,211,255)); 
		return b;
	}
	return hbr;
}


void CDBNew::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_db_name.IsEmpty())
	{
		MessageBox(_T("���ݿ����ֲ���Ϊ��"));
		return;
	}else if(m_db_name.GetLength()>20)
	{
		MessageBox(_T("���ݿ����ֲ��ܳ���20���ַ�"));
		return;
	}
	
	if(m_name_confirm.IsEmpty())
	{
		MessageBox(_T("���ݿ�����ȷ�ϲ���Ϊ��"));
		return;
	}else if(m_name_confirm != m_db_name)
	{
		MessageBox(_T("�½����ݿ����ƺ�����ȷ�ϲ�һ�£�������ȷ��"));
		return;
	}
	//SendMessage(WM_STARTTASK_DBNew,0,0);
	OnStartTask(0,0);
	WT;
	//CDBNew* p_dlg = (CDBNew*)pParam;
	CString ip = m_ip;
	CString port = m_port;
	SOCKET  s = INVALID_SOCKET;
	BOOL flag = CreateSocket(s);
	CString db_name = m_db_name;
	if(flag == FALSE)
	{
		OnEndTask(0,0);
		return;
	}
	hdr header;
	memset(&header,0,sizeof(header));
	header.type= DATABASE_NEW;				//�½����ݿ��ͷ
	char buff[MAX_PATH] = {0};
	strcpy_s(buff,T2A(db_name));
	int len = sizeof(buff);
	header.len = HEADLEN + len;
	int nErrCode;//����ֵ

	//���Ͱ�ͷ
	nErrCode = send(s, (char*)&header, HEADLEN, 0);
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("�����½����ݿ��������ݰ�ʧ�ܣ�"));
		OnEndTask(0,0);
		return;
	}
	
	//���Ͱ���
	nErrCode = send(s, buff, len, 0);
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("�����½����ݿ��������ݰ�ʧ�ܣ�"));
		OnEndTask(0,0);
		return ;
	}

	FD_SET readfd;//�ɶ�����
	//�����ļ�
	while (TRUE)
	{
		FD_ZERO(&readfd);								//��ռ���
		FD_SET(s, &readfd);					//���뼯��
		nErrCode = select(0, &readfd, NULL, NULL, NULL);//�ȴ�
		if (SOCKET_ERROR == nErrCode)					//����
		{
			AfxMessageBox(_T("�����½����ݿ��selcetʧ��"));
			closesocket(s);
			OnEndTask(0,0);
			return ;
		}

		if (nErrCode > 0)
		{
			if (FD_ISSET(s, &readfd))						//���Զ��ļ�
			{
				int nErr = RecvDBNewData(s);	//�����ļ�
				if (EXCEPT == nErr)
				{
					AfxMessageBox(_T("�����½����ݿ������selcetʧ��"));
					OnEndTask(0,0);
					closesocket(s);
					return ;
				}else if (FINISH == nErr)								//���ؽ���
				{
					closesocket(s);
					return ;
				}
			}
		}
		Sleep(THREAD_SLEEP);
	}
	return ;
	//DWORD dwThread;	
	//FileDownloadParam* pParam = new FileDownloadParam;
	//pParam->ptr = this;
    //HANDLE hThreadDBNew = CreateThread(NULL, 0, DBNewThread, pParam, 0, &dwThread);
	//WaitForSingleObject(hThreadDBNew,INFINITE);
	
	//CloseHandle(hThreadDBNew);
	//OnEndTask(0,0);
	
}

DWORD CDBNew::DBNewThread(void* pParam)
{

	WT;
	CDBNew* p_dlg = (CDBNew*)pParam;
	CString ip = p_dlg->m_ip;
	CString port = p_dlg->m_port;
	SOCKET  s = INVALID_SOCKET;
	BOOL flag = p_dlg->CreateSocket(s);
	//p_dlg->m_tip.SetWindowText(_T("hhe"));
	//return 1;
	CString m_db_name = p_dlg->m_db_name;
	if(flag == FALSE)
	{
		p_dlg->OnEndTask(0,0);
		return FALSE;
	}
	hdr header;
	memset(&header,0,sizeof(header));
	header.type= DATABASE_NEW;				//�½����ݿ��ͷ
	char buff[MAX_PATH] = {0};
	strcpy_s(buff,T2A(m_db_name));
	int len = sizeof(buff);
	header.len = HEADLEN + len;
	int nErrCode;//����ֵ

	//���Ͱ�ͷ
	nErrCode = send(s, (char*)&header, HEADLEN, 0);
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("�����½����ݿ��������ݰ�ʧ�ܣ�"));
		p_dlg->OnEndTask(0,0);
		return 0;
	}
	
	//���Ͱ���
	nErrCode = send(s, buff, len, 0);
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("�����½����ݿ��������ݰ�ʧ�ܣ�"));
		p_dlg->OnEndTask(0,0);
		return 0;
	}

	FD_SET readfd;//�ɶ�����
	//�����ļ�
	while (TRUE)
	{
		FD_ZERO(&readfd);								//��ռ���
		FD_SET(s, &readfd);					//���뼯��
		nErrCode = select(0, &readfd, NULL, NULL, NULL);//�ȴ�
		if (SOCKET_ERROR == nErrCode)					//����
		{
			AfxMessageBox(_T("�����½����ݿ��selcetʧ��"));
			p_dlg->OnEndTask(0,0);
			return 0;
		}

		if (nErrCode > 0)
		{
			if (FD_ISSET(s, &readfd))						//���Զ�����
			{
				int nErr = p_dlg->RecvDBNewData(s);	//�����½����ݿ���
				if (EXCEPT == nErr)
				{
					AfxMessageBox(_T("�����½����ݿ������selcetʧ��"));
					p_dlg->OnEndTask(0,0);
					return 0;
				}else if (FINISH == nErr)								//���ؽ���
				{
					closesocket(s);
					return 0;
				}
			}
		}
		Sleep(THREAD_SLEEP);
	}
	return 0;
}

int CDBNew::RecvDBNewData(SOCKET s)
{
	int nErrCode;	//���ش���
	hdr header;		//��ͷ
	CString tip;
	//���հ�ͷ
	nErrCode = recv(s, (char*)&header, HEADLEN, 0);
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("�����������½����ݿ�Ļظ�ʧ�ܣ�"));
		return EXCEPT;
	}	
	if (REPLY_DATABASE_NEW != header.type)
	{
		AfxMessageBox(_T("�����������½����ݿ�Ļظ�ʧ�ܣ�"));
		return EXCEPT;
	}
	int flag = -100;
	nErrCode = recv(s, (char *)&flag, sizeof(int), 0);//׼������1024*20���ֽڳ���
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("�����������½����ݿ�Ļظ�ʧ�ܣ�"));
		return EXCEPT;
	}else if (0 == nErrCode)
	{
		int err = WSAGetLastError();
		return EXCEPT;
	}else{
		switch (flag)
		{
		case -1:
			{
				tip = _T("���ݿ�����ʧ�ܣ����������������");
				break;
			}
		case 0:
			{
				tip = _T("����ʧ�ܣ������ݿ��Ѿ����ڣ��뻻һ������");
				break;
			}
		case -2:
			{
				tip = _T("δ֪ԭ����ɵĴ��������Ի�����ϵ����Ա");
				break;
			}
		case 1:
			{
				tip = _T("��ϲ�������ɹ������ڿ����ù���Ա�����¼��");
				break;
			}
		default:
			break;
		}
		OnEndTask(0,0);
		m_tip.SetWindowText(tip);
		return FINISH;
	}
	return NORMAL;
}


void CDBNew::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CDBNew::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
		{
			ShowTip();
			break;
		}
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CDBNew::ShowTip()
{
	m_time_take++;
	CString time =NULL;
	time.Format(_T("��ʱ��%d��"),m_time_take);
	m_tip.SetWindowText(time);
	if(m_time_take == 120)
	{
		OnEndTask(0,0);
		m_tip.SetWindowText(_T("����ʱ�������Ի����������ӷ�����"));
	}
}

void CDBNew::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnClose();
}


afx_msg LRESULT CDBNew::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}

BOOL CDBNew::CreateSocket(SOCKET &sock)
{
	WT;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sock)
	{
		return FALSE;
	}

	//����ϵͳ��������ΪĬ�ϵ�BUF_TIMES��
	int nErrCode;
	unsigned int uiRcvBuf;
	int uiRcvBufLen = sizeof(uiRcvBuf);
	nErrCode= getsockopt(sock, SOL_SOCKET, SO_RCVBUF,(char*)&uiRcvBuf, &uiRcvBufLen);
	if (SOCKET_ERROR == nErrCode)
	{
		return FALSE;
	}
	uiRcvBuf *= BUF_TIMES;
	nErrCode = setsockopt(sock, SOL_SOCKET, SO_RCVBUF,(char*)&uiRcvBuf, uiRcvBufLen);
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("�޸�ϵͳ�������ݻ�����ʧ�ܣ�"));
	}
	//�������ϵͳ�������ݻ������Ƿ�ɹ�
	getsockopt(sock, SOL_SOCKET, SO_RCVBUF,(char*)&uiRcvBuf, &uiRcvBufLen);	

	
	//�����׽���
//	UpdateData(TRUE);
	

    //�������׽��ֵ�ַ
	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;
	char *pIPTemp = T2A(m_ip);		//��CString���͵�IP��ַת��Ϊcharָ����ָ������	
	long IP = ntohl((u_long)inet_addr(pIPTemp));
	servAddr.sin_addr.S_un.S_addr = htonl(IP);
	char *p = T2A(m_port);
	servAddr.sin_port = htons(atoi(p));
	//���ӷ�����

	nErrCode = connect(sock,(sockaddr*)&servAddr, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("���ӷ�����ʧ��,����ip��ַ�Ͷ˿��Ƿ���ȷ��"),MB_OK, 0);	
		return FALSE;
	}
	
	//��ʾ���ӷ������ɹ���Ϣ
	m_tip.SetWindowText(_T("���ӷ������ɹ�!"));

	return TRUE;
}


afx_msg LRESULT CDBNew::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}



