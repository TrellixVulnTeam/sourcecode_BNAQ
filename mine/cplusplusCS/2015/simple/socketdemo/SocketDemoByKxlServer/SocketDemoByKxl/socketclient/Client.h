
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommucationProtocol.h"

class CSocketDemoByKxlDlg;
class CClient  
{
public:
	CClient(SOCKET s, CSocketDemoByKxlDlg* pServer);   //�вι��캯��
	virtual ~CClient();

protected:
	CClient();
	//CString m_user;                                 //���ڼ�¼�û��Ĳ���
	///////****���ڰ�ȫ�Ĵ洢��������� ������ֻʹ��һ��ָ�� ���������˳���������****/////////
public:
 
	//////***���ڰ�ȫ�Ĵ洢��������� ������ֻʹ��һ��ָ�� ���������˳���������******/////////
public:
	inline SOCKET	GetSocket(void)							//��ȡ�׽���
	{
		return m_sClient;	
	}

	CSocketDemoByKxlDlg* GetServer(void)						//��ȡCServerDlg��ָ��
	{
		return m_pServer;
	}
    

public:

	BOOL	SendData(void);							//��������
	BOOL	RecvData(void);							//��������
	BOOL    RecvTextMessage(int len);               //�����û����͵��ı���Ϣ
	BOOL    RecvReplyTextMessageFromClient(int len);
    BOOL    SendTextMessage(int type);                      //���û�������Ϣ
	///////******����ΪһЩ�����ĺ��� �����ͺͽ����ļ��޹�****************//////////
public:	
	BOOL    RecvDataFromClient(SOCKET s,char * p_recv,int len,CString wrong_message,CString success_message);
	BOOL    SendSocketMessageToClient(SOCKET s, char* p_send,int data_len,CString _err_message);

	void    GetCurTime(CString& time);
	void    GetIPBySocket(SOCKET socket,CString& IP);
	void	WriteSysLog(CString message);  //�������д��־
    
    void    SetReqType(int reqType)
	{
		m_nReqCur = reqType;
	}

	void    SetSendMessageBuff(const CString& newMessage)
	{
		m_sSend = newMessage;
	}

private:
	SOCKET                 m_sClient;         //�ͻ��������׽���
	CSocketDemoByKxlDlg*   m_pServer;         //������������ָ��
	int	                   m_nReqCur;		  //��ǰ��������

	CString                m_sRecv;          //���ջ���
	CString                m_sSend;          //���ͻ���
};

