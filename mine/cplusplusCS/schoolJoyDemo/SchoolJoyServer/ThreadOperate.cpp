// ThreadOperate.cpp: implementation of the ThreadOperate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ThreadServer.h"
#include "ThreadOperate.h"
#include "ADOConn.h"
#include "ThreadServerDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
CString IP_Address_Require;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ThreadOperate::ThreadOperate()
{

}

ThreadOperate::~ThreadOperate()
{

}



//�����Ĵ����߳�
UINT SearchHandleThread(LPVOID clientSocket)
{
	AfxSocketInit(NULL);
	SOCKET client = (SOCKET)clientSocket;
	CSocket SearchHandle;
	SearchHandle.Attach(client);//ת��ΪCsocket

	char readSearchFile[150]={0};//
	SearchHandle.Receive(readSearchFile,sizeof(readSearchFile),0);
	//AfxMessageBox(readSearchFile);
	ADOConn adoconn;
	adoconn.OnInitConnect();
	CString sql;
	sql.Format(_T("select * from fileinfo where filename like '%%%s%%'"),readSearchFile);//��ѯ�Ƚ��Ƿ��ظ�����
	_bstr_t vSQL;
	vSQL=(_bstr_t)sql;
	_RecordsetPtr m_pRecordSet;
	m_pRecordSet=adoconn.GetRecordSet(vSQL);
	
	FILEINFO FileInfoSearchSend;
	
	CString FileType,FileName,FilePathName;

	int n=0;//��ȡ���ݿ��������ļ��ĸ���
	while(!m_pRecordSet->adoEOF)
	{
		n++;
		m_pRecordSet->MoveNext();
	}

	m_pRecordSet->Close();
	//adoconn.ExitConnect();
	SearchHandle.Send(&n,sizeof(n),0);
	CString sql1;
	//AfxMessageBox(readSearchFile);
	sql1.Format(_T("select * from fileinfo where filename like '%%%s%%'"),readSearchFile);//��ѯ�Ƚ��Ƿ��ظ�����
	_bstr_t vSQL1;
	vSQL1=(_bstr_t)sql1;
	_RecordsetPtr m_pRecordSet1;
	m_pRecordSet1=adoconn.GetRecordSet(vSQL1);
	int nCount =0; //����һ�в���
	while(!m_pRecordSet1->adoEOF)  //ѭ���������ݿ��ļ���Ϣ
	{
		memset(&FileInfoSearchSend,0,sizeof(FileInfoSearchSend));
		FileType = m_pRecordSet1->GetCollect("filetype");

		FileInfoSearchSend.fileSize = m_pRecordSet1->GetCollect("filesize");
		FileName= m_pRecordSet1->GetCollect("filename");
		FilePathName=m_pRecordSet1->GetCollect("filepathname");
		strcpy_s(FileInfoSearchSend.fileType,FileType);
		strcpy_s(FileInfoSearchSend.fileName,FileName);
		strcpy_s(FileInfoSearchSend.filepath,FilePathName);
		SearchHandle.Send(&FileInfoSearchSend,sizeof(FileInfoSearchSend),0);
		nCount++;
		m_pRecordSet1->MoveNext();
	}
	m_pRecordSet1->Close();
	//adoconn.ExitConnect();
	SearchHandle.Detach();
	SearchHandle.Close();//�ر��׽���
	return 0;
}

//ע�ᴦ���߳�
UINT RegisterHandleThread(LPVOID clientSocket)
{
	AfxSocketInit(NULL);
	SOCKET client = (SOCKET)clientSocket;
	CSocket RegisterSocket;
	RegisterSocket.Attach(client);//ת��ΪCsocket

	USERINFO userinfo;
	memset(&userinfo,0,sizeof(userinfo));
	RegisterSocket.Receive(&userinfo,sizeof(userinfo),0);
	try
	{
		ADOConn adoconn;//���Ӷ���
		adoconn.OnInitConnect();
		CString sqlstr;
		sqlstr.Format(_T("select * from userinfo where username='%s'"),userinfo.username);//schooljoy
		_bstr_t vSQL;
		vSQL=(_bstr_t)sqlstr;	
		_RecordsetPtr m_recordset;//��¼������
		m_recordset=adoconn.GetRecordSet(vSQL);//ִ�в�ѯ
		char flags[2]={0};
		if(m_recordset->adoEOF)
		{
			m_recordset->AddNew();
			m_recordset->PutCollect("username",_variant_t(userinfo.username));
			m_recordset->PutCollect("password",_variant_t(userinfo.password));
			m_recordset->Update();
			//MessageBox(_T("�û���ӳɹ������ס�û���������"),_T("��ϲ"),MB_OK);
			adoconn.ExitConnect();
			flags[0]='#';
			flags[1]='1';
			RegisterSocket.Send(flags,sizeof(flags),0);
			RegisterSocket.Close();
		}
		else
		{
			//MessageBox(_T("�û����Ѵ��ڣ�������ע������һ��"),_T("����"),MB_ICONWARNING|MB_OK);
			flags[0]='#';
			flags[1]='0';
			RegisterSocket.Send(flags,sizeof(flags),0);
			RegisterSocket.Close();
		}
	}
	catch(...)
	{
		AfxMessageBox(_T("ע��ʧ��"));
		return -1 ;
	}
	return 0;
}
//�ϴ��߳�
UINT UploadHandleThread(LPVOID clientSocket)
{
	AfxSocketInit(NULL);
	SOCKET client = (SOCKET)clientSocket;
	CSocket UploadSocket;
	UploadSocket.Attach(client);//ת��ΪCsocket

	FILEINFO fileinfo;
	memset(&fileinfo,0,sizeof(fileinfo));
	UploadSocket.Receive(&fileinfo,sizeof(fileinfo),0);
	try
	{
		char flags[2]={0};
		ADOConn adoconn;//���Ӷ���
		adoconn.OnInitConnect();
		CString sqlstr;
		//filesize.Format("%f",fileinfo.fileSize);
		sqlstr.Format(_T("select * from fileinfo where filename='%s' and filesize='%f' and userlist='%s'"),fileinfo.fileName,fileinfo.fileSize,fileinfo.username);//schooljoy,filesize
		_bstr_t vSQL;
		vSQL=(_bstr_t)sqlstr;	
		_RecordsetPtr m_recordset;//��¼������
		m_recordset=adoconn.GetRecordSet(vSQL);//ִ�в�ѯ
		if(m_recordset->adoEOF)
		{
			m_recordset->AddNew();
			m_recordset->PutCollect("filename",(const _variant_t)(fileinfo.fileName));//fileinfo.fileName
			m_recordset->PutCollect("userlist",(const _variant_t)(fileinfo.username));//fileinfo.username
			m_recordset->PutCollect("filepathname",(const _variant_t)(fileinfo.filepath));//fileinfo.filepath
			m_recordset->PutCollect("filetype",(const _variant_t)(fileinfo.fileType));//fileinfo.fileType
			m_recordset->PutCollect("userIP",(const _variant_t)(fileinfo.fileownerIP));//fileinfo.fileownerIP
			m_recordset->PutCollect("filesize",(const _variant_t)(fileinfo.fileSize));//fileinfo.fileSize
			//m_recordset->PutCollect("totalsize",(const _variant_t)(filesize));
			m_recordset->Update();			
			//adoconn.ExitConnect();
			flags[0]='#';
			flags[1]='1';
			UploadSocket.Send(flags,sizeof(flags),0);
			UploadSocket.Close();

		}
		else
		{
			flags[0]='#';
			flags[1]='0';
			UploadSocket.Send(flags,sizeof(flags),0);
			UploadSocket.Close();

		}
		
	}
	catch(...)
	{
		AfxMessageBox(_T("�ϴ��ļ���Ϣʧ��"));
		return -1 ;
	}

	return 0;

}

//�û��˳���¼�߳�
UINT QuitHandleThread(LPVOID clientSocket)
{
	AfxSocketInit(NULL);
	SOCKET client = (SOCKET)clientSocket;
	CSocket QuitSocket;
	QuitSocket.Attach(client);//ת��ΪCsocket
	USERINFO userinfo;
	memset(&userinfo,0,sizeof(userinfo));
	QuitSocket.Receive(&userinfo,sizeof(userinfo),0);

	CString sqlstr;
	try
	{
		ADOConn adoconn;//���Ӷ���
		adoconn.OnInitConnect();
		sqlstr.Format(_T("select * from userinfo where username='%s'and password='%s'"),userinfo.username,userinfo.password);//StudentTable
		_bstr_t vSQL;
		vSQL=(_bstr_t)sqlstr;	
		_RecordsetPtr m_recordset;//��¼������
		m_recordset=adoconn.GetRecordSet(vSQL);//ִ�в�ѯ
		char flags[2]={0};
		if(!m_recordset->adoEOF)
		{
			m_recordset->Close();
			CString _str1;
			_str1.Format(_T("select * from userinfo where username='%s'and password='%s'and onlineflag='%s'"),userinfo.username,userinfo.password,_T("1"));
			_bstr_t vSQL1;
			vSQL1=(_bstr_t)_str1;	
			_RecordsetPtr m_recordset1;//��¼������
			m_recordset1=adoconn.GetRecordSet(vSQL1);//ִ�в�ѯ
			if(!m_recordset1->adoEOF)
			{
				m_recordset1->Close();
				flags[0]='#';
				flags[1]='1';
				QuitSocket.Send(flags,sizeof(flags),0);
				CString sql2;
				sql2.Format(_T("update userinfo set username='%s',password='%s',IP='%s',onlineflag='%s' where username='%s'"),userinfo.username,userinfo.password,_T("0"),_T("0"),userinfo.username);
				//m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
				_bstr_t vSQL2;
				vSQL2=(_bstr_t)sql2;	
				adoconn.ExecuteSQL(vSQL2);
				CString _str;
				_str.Format("�û�'%s'�˳��ɹ���",userinfo.username);
				AfxMessageBox(_str);
				//adoconn.ExitConnect();
				QuitSocket.Close();
				return 0;
			}
			else
			{
				m_recordset1->Close();
				flags[0]='#';
				flags[1]='0';
				QuitSocket.Send(flags,sizeof(flags),0);
				CString _str;
				_str.Format("�û�'%s'û�е�¼���˳�ʧ�ܣ�",userinfo.username);
				AfxMessageBox(_str);
				//adoconn.ExitConnect();
				QuitSocket.Close();
				return 0;
			}
		}
	}
	catch(...)
	{
		AfxMessageBox(_T("�˳�ʧ��"));
		return 0 ;
	}
	QuitSocket.Close();

	return 0;

}

//�û���¼�Ĵ����߳�
UINT LoginHandleThread(LPVOID clientSocket)
{
	AfxSocketInit(NULL);
	SOCKET client = (SOCKET)clientSocket;
	CSocket LoginHandle;
	LoginHandle.Attach(client);//ת��ΪCsocket

	USERINFO userinfo;
	memset(&userinfo,0,sizeof(userinfo));
	LoginHandle.Receive(&userinfo,sizeof(userinfo),0);
	CString sqlstr;
	try
	{
		ADOConn adoconn;//���Ӷ���
		adoconn.OnInitConnect();
		sqlstr.Format(_T("select * from userinfo where username='%s'and password='%s'"),userinfo.username,userinfo.password);//StudentTable
		_bstr_t vSQL;
		vSQL=(_bstr_t)sqlstr;	
		_RecordsetPtr m_recordset;//��¼������
		m_recordset=adoconn.GetRecordSet(vSQL);//ִ�в�ѯ
		char flags[2]={0};
		if(!m_recordset->adoEOF)
		{
			m_recordset->Close();
			CString _str1;
			_str1.Format(_T("select * from userinfo where username='%s'and password='%s'and onlineflag='%s'"),userinfo.username,userinfo.password,_T("1"));
			_bstr_t vSQL1;
			vSQL1=(_bstr_t)_str1;	
			_RecordsetPtr m_recordset1;//��¼������
			m_recordset1=adoconn.GetRecordSet(vSQL1);//ִ�в�ѯ
			if(!m_recordset1->adoEOF)
			{
				flags[0]='#';
				flags[1]='2';
				LoginHandle.Send(flags,sizeof(flags),0);
				CString _str;
				_str.Format("'%s'�ѵ�¼,�����ٴε�¼��",userinfo.username);
				AfxMessageBox(_str);
				adoconn.ExitConnect();
				LoginHandle.Close();
				return 0;
			}
			else
			{
				flags[0]='#';
				flags[1]='1';
				LoginHandle.Send(flags,sizeof(flags),0);
				CString sql2;
				//AfxMessageBox(userinfo.userIP);
				sql2.Format(_T("update userinfo set username='%s',password='%s',IP='%s',onlineflag='%s' where username='%s'"),userinfo.username,userinfo.password,userinfo.userIP,_T("1"),userinfo.username);
				//m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
				_bstr_t vSQL2;
				vSQL2=(_bstr_t)sql2;	
				adoconn.ExecuteSQL(vSQL2);
				CString _str;
				_str.Format("'%s'��¼�ɹ���",userinfo.username);
				AfxMessageBox(_str);
				adoconn.ExitConnect();
				LoginHandle.Close();
				return 0;
			}
			m_recordset1->Close();
		}
		else
		{
			CString _str3;
			_str3.Format(_T("select * from userinfo where username='%s'"),userinfo.username);
			_bstr_t vSQL3;
			vSQL3=(_bstr_t)_str3;	
			_RecordsetPtr m_recordset3;//��¼������
			m_recordset3=adoconn.GetRecordSet(vSQL3);//ִ�в�ѯ
			if (m_recordset3->adoEOF)
			{
				flags[0]='#';
				flags[1]='0';
				LoginHandle.Send(flags,sizeof(flags),0);
				CString _str;
				_str.Format("'%s'���Ե�¼ʧ�ܣ��û��������ڣ�",userinfo.username);
				AfxMessageBox(_str);
				adoconn.ExitConnect();
				LoginHandle.Close();
				return 0;
			}
			else
			{
				flags[0]='#';
				flags[1]='3';
				LoginHandle.Send(flags,sizeof(flags),0);
				CString _str;
				_str.Format("'%s'���Ե�¼ʧ�ܣ��û����벻��ȷ��",userinfo.username);
				AfxMessageBox(_str);
				adoconn.ExitConnect();
				LoginHandle.Close();
				return 0;
			}
			
		}
		

	}
	catch(...)
	{
		AfxMessageBox(_T("��½ʧ��"));
		return 0 ;
	}
	LoginHandle.Close();
	return 0;
}



//�����ļ���Ϣ�Ĵ����߳�
UINT RequireHandleThread(LPVOID clientSocket)
{
	AfxSocketInit(NULL);
	SOCKET client = (SOCKET)clientSocket;
	CSocket RequireHandle;
	RequireHandle.Attach(client);//ת��ΪCsocket

	FILEINFO FileInfo1;
	memset(&FileInfo1,0,sizeof(FileInfo1));
	RequireHandle.Receive(&FileInfo1,sizeof(FileInfo1));
	CString FileName=FileInfo1.fileName;
	ADOConn adoconn;//�����ݿ��в�����Ϣ
	adoconn.OnInitConnect();
	CString sql;
	sql.Format(_T("select * from userinfo,fileinfo where userinfo.username=fileinfo.userlist and fileinfo.filename='%s' and userinfo.onlineflag='%s'"),FileName,_T("1"));//���ݿ�����ļ��Ƿ�ƥ��
	_bstr_t vSQL;
	vSQL=(_bstr_t)sql;
	_RecordsetPtr m_pRecordSet;
	m_pRecordSet=adoconn.GetRecordSet(vSQL);
	CString FileOwnerIP;//�ļ�ӵ����IP
	if(!m_pRecordSet->adoEOF)
	{    
		FileOwnerIP = m_pRecordSet->GetCollect("IP");//�õ���Դӵ�з���IP
	}	
	else
	{
		AfxMessageBox(_T("���ҳ���"));

	}
	m_pRecordSet->Close();//�رռ�¼��
	FILEINFO FileInfo2;
	memset(&FileInfo2,0,sizeof(FileInfo2));
	strcpy_s(FileInfo2.fileownerIP,FileOwnerIP);//��IPд���ṹ��
	RequireHandle.Send(&FileInfo2,sizeof(FileInfo2));	
	RequireHandle.Detach();
	RequireHandle.Close();//�ر��׽���
	return 0;
}

////////////////////////////////////////////////////
UINT StartshowResourcesThread(LPVOID pParam)
{
	CThreadServerDlg *dialog = (CThreadServerDlg *)pParam;
	dialog->m_Resourceslist.DeleteAllItems();//ɾ��ListView�е���������
	CString _str="���Եȣ�����Ŭ��������Դ��Ϣ�С�����";
	dialog->Update(_str);
	try
	{
		ADOConn  adoconn;
		adoconn.OnInitConnect();
		CString sqlstr;
		_RecordsetPtr m_recordset;//��¼������
		_ConnectionPtr m_pConnection;
		sqlstr.Format(_T("select * from fileinfo "));
		_bstr_t vSQL;
		vSQL=(_bstr_t)sqlstr;		
		m_recordset=adoconn.GetRecordSet(vSQL);//ִ�в�ѯ
		int nCount =0; //����һ�в���
		while(!m_recordset->adoEOF)
		{
			dialog->m_Resourceslist.InsertItem(nCount,_T(""));//�����µ�һ��
			dialog->m_Resourceslist.SetItemText(nCount,0,(LPCTSTR)(_bstr_t)m_recordset->GetCollect("filename"));
			dialog->m_Resourceslist.SetItemText(nCount,1,(LPCTSTR)(_bstr_t)m_recordset->GetCollect("userlist"));
			dialog->m_Resourceslist.SetItemText(nCount,2,(LPCTSTR)(_bstr_t)m_recordset->GetCollect("filetype"));
			double FileSize=m_recordset->GetCollect("filesize");
			dialog->m_Resourceslist.SetItemText(nCount,3,(LPCTSTR)(_bstr_t)dialog->FileSizeTransfer(FileSize));
			nCount++;
			m_recordset->MoveNext();
		}
		CString _str="��Դ��Ϣ���³ɹ�";
		dialog->Update(_str);
		adoconn.ExitConnect();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	return 0;
}

//��ʾ�û��б���߳�
UINT StartshowUserThread(LPVOID pParam)
{
	CThreadServerDlg *dialog = (CThreadServerDlg *)pParam;
	dialog->m_Userlist.DeleteAllItems();//ɾ��ListView�е���������
	CString _str="���Եȣ�����Ŭ�������û���Ϣ�С�����";
	dialog->Update(_str);
	try
	{
		ADOConn  adoconn;
		adoconn.OnInitConnect();
		CString sqlstr;
		_RecordsetPtr m_recordset;//��¼������
		//_ConnectionPtr m_pConnection;
		sqlstr.Format(_T("select * from userinfo where onlineflag='%s'"),"1");
		_bstr_t vSQL;
		vSQL=(_bstr_t)sqlstr;		
		m_recordset=adoconn.GetRecordSet(vSQL);//ִ�в�ѯ
		int nCount =0; //����һ�в���
		while(!m_recordset->adoEOF)
		{
			dialog->m_Userlist.InsertItem(nCount,_T(""));//�����µ�һ��
			dialog->m_Userlist.SetItemText(nCount,0,(LPCTSTR)(_bstr_t)m_recordset->GetCollect("username"));
			dialog->m_Userlist.SetItemText(nCount,1,(LPCTSTR)(_bstr_t)m_recordset->GetCollect("IP"));
			nCount++;
			m_recordset->MoveNext();
		}
		CString _str="�û���Ϣ���³ɹ�";
		dialog->Update(_str);
		adoconn.ExitConnect();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	return 0;

}

//��ʼ���߳�
UINT StartServerThread(LPVOID pParam)
{
	CThreadServerDlg *dialog = (CThreadServerDlg *)pParam;
	AfxSocketInit(NULL);
    CSocket ServerListenSocket;//�����������׽���
	if(!ServerListenSocket.Create(dialog->m_serverPORT))
	{
	  CString _str=_T("�����׽����쳣�����鱾�ض˿��Ƿ�ռ��\\r\n");
	  dialog->Update(_str);
	  return 0;
	}
	if(!ServerListenSocket.Listen(500))
	{
		CString _str=_T("������������ʧ��,\r\n");
		dialog->Update(_str);
		return 0;
	}
	CString _str=_T("�������������������ڵȴ����ӡ�����\r\n");
	dialog->Update(_str);

    CSocket ClientSocketIn;
	int stateCode=0;
	char buffer[sizeof(stateCode)]="0";
	while(true)
	{
		ServerListenSocket.Accept(ClientSocketIn);
		int bytesRec = ClientSocketIn.Receive(buffer,sizeof(stateCode),0);//����������
		stateCode = atoi(buffer);//ת��Ϊ����
		switch(stateCode)
		{
		case 1://1��������û���¼
			{
				sockaddr_in clientAddress;
				CString ipAddress;
				CString nowPort;
				int addressLen = sizeof(clientAddress);
				::getpeername(ClientSocketIn,(sockaddr*)&clientAddress,&addressLen);
				ipAddress = inet_ntoa(clientAddress.sin_addr);
				int port = ntohs(clientAddress.sin_port);
				nowPort.Format("%d",port);
				CString _str;
				_str.Format("���ڴ�������'%s'�ĵ�¼����ͨ�Ŷ˿ں�Ϊ'%s'",ipAddress,nowPort);
				dialog->Update(_str);
				SOCKET LoginHandleSocket;
				LoginHandleSocket = ClientSocketIn.Detach();//���׽��ַ���ת��ʹ������һ���׽���
				AfxBeginThread(LoginHandleThread,(LPVOID)LoginHandleSocket);//������������
				break;
			}

		case 2://2�����������һ�����߳�,����ͻ�����Ҫ�ļ�����
			{
				sockaddr_in clientAddress;
				int addressLen = sizeof(clientAddress);
				::getpeername(ClientSocketIn,(sockaddr*)&clientAddress,&addressLen);
				IP_Address_Require= inet_ntoa(clientAddress.sin_addr);
				CString _str;
				_str.Format("���ڴ�������'%s'��Զ���ļ�����",IP_Address_Require);
				dialog->Update(_str);
				SOCKET RequireHandleSocket;
				RequireHandleSocket = ClientSocketIn.Detach();//���׽��ַ���ת��ʹ������һ���׽���
				AfxBeginThread(RequireHandleThread,(LPVOID)RequireHandleSocket);//�����������̲߳���handeConnectThread
				break;
			}
		case 3://3�����������һ�����߳�,����ͻ��������ļ�����
			{
				sockaddr_in clientAddress;
				int addressLen = sizeof(clientAddress);
				::getpeername(ClientSocketIn,(sockaddr*)&clientAddress,&addressLen);
				IP_Address_Require= inet_ntoa(clientAddress.sin_addr);
				CString _str;
				_str.Format("���ڴ�������'%s'�������ļ�����",IP_Address_Require);
				dialog->Update(_str);
				SOCKET SearchHandleSocket;
				SearchHandleSocket = ClientSocketIn.Detach();//���׽��ַ���ת��ʹ������һ���׽���
				AfxBeginThread(SearchHandleThread,(LPVOID)SearchHandleSocket);//�����������̲߳���handeConnectThread
				break;
			}
		case 4://4��������û�������һ��ע�����룬�������̣߳�����ͻ�������
			{
				sockaddr_in clientAddress;
				int addressLen = sizeof(clientAddress);
				::getpeername(ClientSocketIn,(sockaddr*)&clientAddress,&addressLen);
				IP_Address_Require= inet_ntoa(clientAddress.sin_addr);
				CString _str;
				_str.Format("���ڴ�������'%s'���û�ע������",IP_Address_Require);
				dialog->Update(_str);
				SOCKET RegisterHandleSocket;
				RegisterHandleSocket = ClientSocketIn.Detach();//���׽��ַ���ת��ʹ������һ���׽���
				AfxBeginThread(RegisterHandleThread,(LPVOID)RegisterHandleSocket);//�����������̲߳���handeConnectThread
				break;

			}
			case 5://5��������û�������һ���ϴ��ļ����룬�������̣߳�����ͻ����ϴ�����
			{
				sockaddr_in clientAddress;
				int addressLen = sizeof(clientAddress);
				::getpeername(ClientSocketIn,(sockaddr*)&clientAddress,&addressLen);
				IP_Address_Require= inet_ntoa(clientAddress.sin_addr);
				CString _str;
				_str.Format("���ڴ�������'%s'���û��ϴ��ļ�����",IP_Address_Require);
				dialog->Update(_str);
				SOCKET UploadHandleSocket;
				UploadHandleSocket = ClientSocketIn.Detach();//���׽��ַ���ת��ʹ������һ���׽���
				AfxBeginThread(UploadHandleThread,(LPVOID)UploadHandleSocket);//�����������̲߳���handeConnectThread
				break;
			}
			case 6://6��������û��˳���¼����
			{
				sockaddr_in clientAddress;
				int addressLen = sizeof(clientAddress);
				::getpeername(ClientSocketIn,(sockaddr*)&clientAddress,&addressLen);
				IP_Address_Require= inet_ntoa(clientAddress.sin_addr);
				CString _str;
				_str.Format("���ڴ�������'%s'���û��˳���¼����",IP_Address_Require);
				dialog->Update(_str);
				SOCKET QuitHandleSocket;
				QuitHandleSocket = ClientSocketIn.Detach();//���׽��ַ���ת��ʹ������һ���׽���
				AfxBeginThread(QuitHandleThread,(LPVOID)QuitHandleSocket); //�����������̲߳���
				break;
			}
		}
		ClientSocketIn.Close();
	}
	return 0;
}



void ThreadOperate::startMainThread(void* cw)
{
	this->dialog =(CDialog*)cw;
	AfxBeginThread(StartServerThread,dialog);
}
void ThreadOperate::startshowUserThread( void* cw)
{
	this->dialog =(CDialog*)cw;
	AfxBeginThread(StartshowUserThread,dialog);
}

void ThreadOperate::startshowResourcesThread( void* cw)
{
	this->dialog =(CDialog*)cw;
	AfxBeginThread(StartshowResourcesThread,dialog);
}