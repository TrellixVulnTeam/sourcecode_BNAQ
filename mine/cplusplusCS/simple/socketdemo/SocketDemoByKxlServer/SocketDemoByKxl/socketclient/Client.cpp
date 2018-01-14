#include "stdafx.h"
#include "..\SocketDemoByKxlDlg.h"
#include "Client.h"
#include "CommucationProtocol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CClient::CClient(SOCKET s, CSocketDemoByKxlDlg* pServer):m_sClient(s),m_pServer(pServer)
{
	m_nReqCur = REQ_NONE;
}

CClient::~CClient()
{
	m_pServer = NULL;
	closesocket(m_sClient);
}

CClient::CClient()
{

}

BOOL CClient::RecvData(void)						//��������
{
	BOOL val = TRUE;
	hdr	header;		//��ͷ
	int	nReadData;	//�����ֽ���
	CString _str = NULL;
	//���հ�ͷ
	nReadData = recv(m_sClient, (char*)&header, g_iHeadLen, 0);
	if (SOCKET_ERROR == nReadData)					//����
	{
		_str = _T("�������ݰ�ͷ����");
		WriteSysLog(_str);
		val = FALSE;							 						 
	}
	else if (0 == nReadData)						//�ͻ��˹ر����׽���
	{
		_str = _T("�ͻ��˹ر����׽��֣�");
		WriteSysLog(_str);
		val = FALSE;
	}
	else if (nReadData > 0 && g_iHeadLen == nReadData)
	{
		switch(header.iReqType)//�ͻ������������
		{
		case ENUM_RECV_PACKET_TEXT_MESSAGE:
			{
				val = RecvTextMessage(header.usTotalLen - g_iHeadLen);
				break;
			}
		case ENUM_RECV_REPLY_FROM_CLIENT:
			{
				val = RecvReplyTextMessageFromClient(header.usTotalLen - g_iHeadLen);
				break;
			}
		default :
			{
				break;
			}
		}
	}	
	return val;
}


BOOL CClient::SendData(void)							//��������
{
	BOOL flag = TRUE;
	switch(m_nReqCur)
	{
	case REQ_MESSAGE:
		{
			if(FALSE == SendTextMessage(ENUM_REPLY_PACKET_TEXT_MESSAGE))
			{
				//AfxMessageBox(_T("�ظ���¼ʧ��"));
				flag = FALSE;
				m_nReqCur = REQ_NONE;
				return flag;
			}
			m_nReqCur = REQ_NONE;
			break;
		}
	case REQ_SEND_TEXT_MESSAGE_TO_CLINET:
		{
			if(FALSE == SendTextMessage(ENUM_SEND_MESSAGE_TO_CLIENT))
			{
				//AfxMessageBox(_T("�ظ���¼ʧ��"));
				flag = FALSE;
				m_nReqCur = REQ_NONE;
				return flag;
			}
			m_nReqCur = REQ_NONE;
			break;
		}

	default:
		break;
	}
	return TRUE;
}

BOOL CClient::SendTextMessage(int type)
{
	USES_CONVERSION;
	hdr header;
	memset(&header,0,sizeof(header));
	Package package;
    memset(&package,0,sizeof(Package));
	header.iReqType = type;
	int len = sizeof(Package);
	header.usTotalLen = g_iHeadLen + len;
	strcpy_s(package.buff,T2A(m_sSend));
	CString _err;
	if(!SendSocketMessageToClient(m_sClient,(char*)&header,g_iHeadLen,_err))
	{
		return FALSE;
	}
	if(!SendSocketMessageToClient(m_sClient,(char*)&package,len,_err))
	{
		return FALSE;
	}
	CString  _success = _T("�ɹ�������Ϣ���ͻ���");
	WriteSysLog(_success);
	return TRUE;
}



//�����û����͵��ı���Ϣ
BOOL CClient::RecvTextMessage(int len)     
{
	Package package;
	memset(&package,0,sizeof(package));
	int errCode = recv(m_sClient,(char *)&package,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����û����͵��ı���Ϣʧ��"));
		return FALSE;
	}
	USES_CONVERSION;
	m_sRecv = A2T(package.buff);
    CString ip;
	GetIPBySocket(m_sClient,ip);
	CString temp;
	CString time;
    GetCurTime(time);
	temp.Format(_T("%s   %s  ˵��\r\n %s"),time,ip, m_sRecv);
	m_pServer->SendMessage(WM_TEXT_MESSAGE, NULL, (LPARAM)(LPCTSTR)temp);
	m_sSend = _T("���ͳɹ�");  //���ǻظ��ͻ��˵�
	m_nReqCur = REQ_MESSAGE;
	return TRUE;
}

BOOL CClient::RecvReplyTextMessageFromClient(int len)
{
	Package package;
	memset(&package,0,sizeof(package));
	int errCode = recv(m_sClient,(char *)&package,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���տͻ��˻ظ���Ϣʧ��"));
		return FALSE;
	}
	USES_CONVERSION;
	m_sRecv = A2T(package.buff);
	CString time;
	GetCurTime(time);
    CString temp = time + _T("  ")+ m_sRecv;
	m_pServer->SendMessage(WM_SEND_STATUS, NULL, (LPARAM)(LPCTSTR)temp);
	m_sSend = _T("���ͳɹ�");  //���ǻظ��ͻ��˵�
	m_nReqCur = REQ_NONE;
	return TRUE;
}

BOOL CClient::SendSocketMessageToClient(SOCKET s,char* p_send,int data_len,CString _err_message)
{
	int nErroCode = send(s, (char*)p_send, data_len,0);
	if(SOCKET_ERROR == nErroCode)
	{
		WriteSysLog(_err_message);
		return FALSE;
	}
	return TRUE;
}

void CClient::WriteSysLog(CString message)
{
	m_pServer->SendMessage(WM_LOG,0,(LPARAM)(LPCTSTR)message);
}

void  CClient::GetCurTime(CString& time)
{
	SYSTEMTIME sys; 
	GetLocalTime(&sys); 
	time.Format(_T("%4d-%02d-%02d %02d:%02d:%02d"),sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond);
}

void CClient::GetIPBySocket(SOCKET socket,CString& ip)
{
	SOCKADDR_IN  address;
	memset(&address, 0, sizeof(address));
	int nAddrLen = sizeof(address);

	//�����׽��ֻ�ȡ��ַ��Ϣ
	if(::getpeername(socket, (SOCKADDR*)&address, &nAddrLen) != 0)
	{
		//printf("Get IP address by socket failed!n");
		return ;
	}
	//��ȡIP��Port
    ip = CString(::inet_ntoa(address.sin_addr));
	return ;
}
