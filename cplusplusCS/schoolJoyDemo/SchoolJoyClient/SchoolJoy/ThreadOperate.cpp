// ThreadOperate.cpp: implementation of the ThreadOperate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ThreadOperate.h"
#include "SchoolJoy.h"
#include "SchoolJoyDlg.h"
#include "Search.h"
#include "Register.h"
#include "ConnectSet.h"
#include "Download_Downloading.h"
#include "Upload.h"
#include "LogIn.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define		SIZEFILE			1024//�����ļ����С���ɸı�
#define		ELAPSE_DEFAULT		1000
#define		ELAPSE_SPEED		1000
#define		MAX_BUF_LEN			1024
#define		Kb					1024
#define		Mb					Kb*Kb

#define		P2PPort				12345
//////////////////////////////////////////////////////////////////////
CWinThread *pRequireFileThread;	
CString FileOwenerPath;
CString FileOwnerIP;
CString FILENAME;
CString FILETYPE;
float FILESIZE;
CString FILEPATH;
long OFFSET;
//////////////////////////////////////////////////////////////////////





ThreadOperate::ThreadOperate()
{

}

ThreadOperate::~ThreadOperate()
{

}




//////////////////////////////////////////////////////////////////
//////////////**********ע���߳�*****************////////////////
//////////////////////////////////////////////////////////////////
UINT RegisterThread(LPVOID pParam)
{
	CRegister *Mydlg =(CRegister *)pParam;

	AfxSocketInit(NULL);
	CSocket RegisterSocket;
	if(!RegisterSocket.Create())
	{
		//dialog->GetDlgItem(IDC_EDIT_Log)->SetWindowText(_T("�ͻ���**�����ļ���Ϣ**�׽��� ����ʧ��\r\n"));
		AfxMessageBox(_T("�ͻ���**ע��**�׽��� ����ʧ��\r\n"));
		return 0;
	}
	//CConnectSet connectset;
	if(!RegisterSocket.Connect((LPCTSTR)CConnectSet::ServerIP,(UINT)CConnectSet::ServerPort))
	{
		AfxMessageBox(_T("�ͻ���**ע��**�׽���**����ʧ��\r\n"));
		return 0;
	}
	int stateCode=4;
	char buffer[sizeof(stateCode)]={0};
	sprintf_s(buffer,"%d",stateCode);

	int sendbytes= RegisterSocket.Send(buffer,sizeof(stateCode),0);

	if(sendbytes == SOCKET_ERROR)
	{
		AfxMessageBox("���տͻ��˷��͵ĵ�ַ��Ϣʧ��");
		return 0;
	}
	USERINFO userinfo;
	memset(&userinfo,0,sizeof(userinfo));
	strcpy_s(userinfo.password,CRegister::password);
	strcpy_s(userinfo.username,CRegister::username);
	//AfxMessageBox(userinfo.username);
	//AfxMessageBox(userinfo.password);


	int sendnum=RegisterSocket.Send(&userinfo,sizeof(userinfo),0);
	if(sendnum== SOCKET_ERROR)
	{
		AfxMessageBox("�ͻ��˷��͵ĵ�ַ��Ϣʧ��");
		return 0;
	}
	char flags[2]={0};
	int recvnum=RegisterSocket.Receive(flags,sizeof(flags),0);
	if(recvnum== SOCKET_ERROR)
	{
		AfxMessageBox("���շ���������ע��״̬ʧ��");
		return 0;
	}
	if(flags[0]=='#'&&flags[1]=='1')
	{
		AfxMessageBox(_T("��ϲ��ע��ɹ������μ�����"));
		RegisterSocket.Close();
		return 0;
	}
	if(flags[0]=='#'&&flags[1]=='0')
	{
		AfxMessageBox(_T("�û����Ѵ��ڣ�������ע��"));
		RegisterSocket.Close();
		return 0;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////
//////////////**********�����߳�*****************////////////////
//////////////////////////////////////////////////////////////////

UINT SearchThread(LPVOID pParam)
{
	CSearch *dialog = (CSearch *)pParam;
	AfxSocketInit(NULL);
	CSocket SearchSocket;
	//AfxMessageBox(dialog->m_SearchFile);
	if (!SearchSocket.Create())
	{
		AfxMessageBox(_T("�ͻ���**����**�׽��ִ���ʧ��\r\n"));
		return 0;
	}
	//CConnectSet *_pconnectset=new CConnectSet;
	if(!SearchSocket.Connect((LPCTSTR)CConnectSet::ServerIP,(UINT)CConnectSet::ServerPort))//���ӷ�����IP��Port
	{
		AfxMessageBox(_T("�ͻ���**����**�׽������ӷ�����ʧ��\r\n"));
		return 0;
	}
	//delete [] _pconnectset;
	//����״̬��3
	int stateCode = 3;
	char buffer[sizeof(stateCode)]="0";
	sprintf_s(buffer,"%d",stateCode);
	int sendbytes= SearchSocket.Send(buffer,sizeof(stateCode),0);
	if(sendbytes == SOCKET_ERROR)
	{
		AfxMessageBox("���տͻ��˷��͵ĵ�ַ��Ϣʧ��");
		return 0;	
	}
	char SearchFileName[150]={0};
	strcpy_s(SearchFileName,dialog->m_SearchFile);//��������ת��
	//AfxMessageBox(dialog->m_SearchFile);
	SearchSocket.Send(&SearchFileName,sizeof(SearchFileName),0);//�����������ļ���

	//char FileNum[10]={0};
	//SearchSocket.Receive(FileNum,sizeof(FileNum),0);//�������ݿ��������ļ��ĸ���c

	//int FileNum;
	//FileNum=atoi(SqlFileNumRecive);//���鵽���͵�ת��
	int FileNum=0;  //��������������
	int recvnum=SearchSocket.Receive(&FileNum,sizeof(FileNum),0);
	if(recvnum==SOCKET_ERROR)
	{
		AfxMessageBox("���������������");
		SearchSocket.Close();
		return 0;
	}
	if(FileNum==0)
	{
		AfxMessageBox("���ź���û�п���ƥ����������ѡ����������ؼ����ٴ��������ԡ�");
		SearchSocket.Close();
		return 0;
	}

	FILEINFO FileInfoSearchRecive;//�ṹ�崫�����ݿ��ļ���Ϣ
	int nCount=0;
	memset(&FileInfoSearchRecive,0,sizeof(FileInfoSearchRecive));
	//CString strFileSize;
	while(FileNum!=0)
	{
		SearchSocket.Receive(&FileInfoSearchRecive,sizeof(FileInfoSearchRecive),0);//�������ݿ��ļ���Ϣ
		dialog->m_List_Search.InsertItem(nCount,NULL);
		dialog->m_List_Search.SetItemText(nCount,0,(LPCTSTR)FileInfoSearchRecive.fileName);//��ListSearch��д���ļ���
		//��ListSearch��д���ļ�����
		//AfxMessageBox(FileInfoSearchRecive.fileName);
		dialog->m_List_Search.SetItemText(nCount,1,(LPCTSTR)FileInfoSearchRecive.fileType);
		//AfxMessageBox(FileInfoSearchRecive.fileType);
		double SearchFileSize=(double)(FileInfoSearchRecive.fileSize);//intת��Ϊdouble
		CString _str=dialog->FileSizeTransfer(SearchFileSize);
		//��ListSearch��д���ļ���С
		dialog->m_List_Search.SetItemText(nCount,2,(LPCTSTR)_str);
		//AfxMessageBox(_str);
		dialog->m_List_Search.SetItemText(nCount,3,(LPCTSTR)FileInfoSearchRecive.filepath);

		nCount++;
		FileNum--;
	}
	SearchSocket.Close();
	return 0;
}


////****�ͻ�����P2P�����ļ�����

UINT RequireFileThread(LPVOID pParam)
{
	CDownload_Downloading *MyDlg = (CDownload_Downloading *)pParam;
	AfxSocketInit(NULL);
	CSocket RequireFileSocket;
	if (!RequireFileSocket.Create())
	{
		AfxMessageBox("�ͻ��������ļ���Դ�׽��� ����ʧ��\r\n");
		return 0;
	}
	CString P2PIP=FileOwnerIP;//������Դӵ�з�IP�����������������ɸġ���������������
	if(!RequireFileSocket.Connect(P2PIP,P2PPort))//������Դӵ�з�IP��Port
	{
		AfxMessageBox("�ͻ��������ļ���Դ�׽��� ����ʧ��\r\n");
		return 0;
	}

	//����״̬��1
	int stateCode = 1;
	char buffer[sizeof(stateCode)]="0";
	sprintf_s(buffer,"%d",stateCode);
	int sendbytes= RequireFileSocket.Send(buffer,sizeof(stateCode),0);
	if(sendbytes == SOCKET_ERROR)
	{
		AfxMessageBox("���տͻ��˷��͵ĵ�ַ��Ϣʧ��");
		return 0;
	}
	char sendFilePath[150]={0};//////////////////������char������char*��CString��Ҫ��
	strcpy_s(sendFilePath,FileOwenerPath);
	RequireFileSocket.Send(sendFilePath,sizeof(sendFilePath),0);	//�����ļ�·��

	WIN32_FIND_DATA ReciveFileInfo;
	RequireFileSocket.Receive(&ReciveFileInfo, sizeof(ReciveFileInfo),0);
	int nFileSize = ReciveFileInfo.nFileSizeLow;
	CFileDialog dlg(false);	//����ļ�
	dlg.m_ofn.lpstrFile=ReciveFileInfo.cFileName;	//�ļ�����
	dlg.m_ofn.lpstrFilter=_T("All Files(*.*)\0*.*\0\0");
	CString fpathname;
	if(dlg.DoModal()==IDOK)
	{   
		fpathname=dlg.GetPathName();	//�õ��ļ������ơ�·��
	}
	CFile file(fpathname,CFile::modeCreate | CFile::modeWrite| CFile::typeBinary);
	unsigned long RecvOnce = 0;
	unsigned long RecvPerTime = 0;
	//char *szBuff=NULL;
	wchar_t szBuff[SIZEFILE]={0};
	int i=MyDlg->m_NUMDownloading;


	double Speed=0;
	CString SpeedUpdate;
	int Count=0;

	// LARGE_INTEGER litmp; 
   //  LONGLONG QPart1,QPart2;
   //  double dfMinus, dfFreq, dfTim; 

	while(RecvOnce<(unsigned long)nFileSize)
	{ 
			//QueryPerformanceFrequency(&litmp);
			//dfFreq = (double)litmp.QuadPart;// ��ü�������ʱ��Ƶ��6.  
			//QueryPerformanceCounter(&litmp);
			//QPart1 = litmp.QuadPart;// ��ó�ʼֵ
		
		DWORD starttime=::GetTickCount(); 
		RecvPerTime=RequireFileSocket.Receive(szBuff,SIZEFILE);
		file.Write(szBuff,RecvPerTime);
		RecvOnce+=RecvPerTime;
		double per=(double)RecvOnce/(double)nFileSize;
		MyDlg->m_Download_Downloading.SetItemData(i,per*100);

		DWORD endtime=::GetTickCount(); //��ȡ���뼶��Ŀ
		if(endtime-starttime!=0)							//���������ٶ�
		{
			Speed=double(RecvPerTime)/double(endtime-starttime);
			Speed=10000*Speed;
		}
		
			//QueryPerformanceCounter(&litmp);
			//QPart2 = litmp.QuadPart;//�����ֵֹ12.         
			//dfMinus = (double)(QPart2-QPart1);
			//if(dfMinus==0) Speed=0;
			//else
			//{
			//	dfTim = dfMinus / dfFreq;// ��ö�Ӧ��ʱ��ֵ����λΪ��
			//	Speed=RecvPerTime/dfTim;
				
			//}
			if(Speed/1024/1024/1024>=1)
			{
				SpeedUpdate.Format("%.2f GB/S",Speed*1000/1024/1024);
			}
			if(Speed/1024/1024>=1)
			{
				SpeedUpdate.Format("%.2f MB/S",Speed*1000/1024/1024);
			}
			else
			{
				SpeedUpdate.Format("%.2f KB/S",Speed/1024);
			}
			if(Count%100==0)
			{
				MyDlg->m_Download_Downloading.SetItemText(i,5,SpeedUpdate);
			}
		Count++;
		//delete szBuff;	
		//delete szBuff;	
	}
	AfxMessageBox(_T("�������"));
	MyDlg->m_Download_Downloading.SetItemText(i,5,_T(""));
	MyDlg->m_Download_Downloading.SetItemText(i,6,_T("�������"));
	file.Close();
	RequireFileSocket.Close();
	return 0;
}


///**�ļ������߳�

//UINT MyThreadFunction(LPVOID pParam��
UINT SendFileThread(LPVOID sendfileSocket)
{
	AfxSocketInit(NULL) ;
	SOCKET sendfile = (SOCKET)sendfileSocket;
	CSocket SendFileSocket;
	SendFileSocket.Attach(sendfile);

	char ReciveFilePath[150]={0};//////////////////������char������char*��CString��Ҫ��
	//Sleep(400);
	SendFileSocket.Receive(ReciveFilePath,sizeof(ReciveFilePath),0);
	//CString s;
	//s.Format(_T("%s"), ReciveFilePath);
	//AfxMessageBox(s);


	WIN32_FIND_DATA SendFileInfo;
	//�����ļ��������ļ�  Long����ִ�гɹ�������һ�����������
	//�����������һ��INVALID_HANDLE_VALUE������һ��������Ҫ��Ӧ����FindClose�����ر�������
	FindClose(FindFirstFile(ReciveFilePath, &SendFileInfo));
	SendFileSocket.Send(&SendFileInfo,sizeof(SendFileInfo),0);//�����ļ���С���ļ���

	CFile file;
	if(!file.Open(ReciveFilePath,CFile::modeRead|CFile::typeBinary))
	{
		AfxMessageBox(_T("�ļ�������"));
		return 1;
	}
	////////////////////////////////////////////////////////////
	unsigned long SendOnce = 0;
	unsigned long nSendPerTime = 0;
	file.Seek(0,CFile::begin);
	wchar_t szBuff[SIZEFILE]={0};
	//����
	unsigned long nFileSize = SendFileInfo.nFileSizeLow;
	while(SendOnce<nFileSize)
	{
		nSendPerTime = file.Read(szBuff,SIZEFILE);
		SendFileSocket.Send(szBuff,nSendPerTime);//��������
		SendOnce+=nSendPerTime;			 
	}
	file.Close();
	SendFileSocket.Close();
	return 0;
}


////**���ӷ������߳�
UINT ConnectServerThread(LPVOID pParam)
{
	CSearch *dialog = (CSearch *)pParam;
	AfxSocketInit(NULL);
	CSocket ConnectServerSocket;
	if (!ConnectServerSocket.Create())
	{
		AfxMessageBox(_T("�ͻ��������󶨶˿�ʧ�ܣ�����\r\n"));
		return 0;
	}
	if(!ConnectServerSocket.Connect((LPCTSTR)CConnectSet::ServerIP,(UINT)CConnectSet::ServerPort))//���ӷ�����IP��Port
	{
		AfxMessageBox(_T("���ӷ�����ʧ��\r\n"));
		return 0;
	}
	int stateCode = 1;
	char buffer[sizeof(stateCode)]="0";
	sprintf_s(buffer,"%d",stateCode);
	int sendbytes= ConnectServerSocket.Send(buffer,sizeof(stateCode),0);
	if(sendbytes == SOCKET_ERROR)
	{
		AfxMessageBox("���տͻ��˷��͵ĵ�ַ��Ϣʧ��");
		return 0;
	}
	ConnectServerSocket.Close();
	return 0;

}
//�ͻ��˵�¼�߳�
UINT LoginThread(LPVOID pParam)
{
	CLogIn *MyDlg = (CLogIn *)pParam;
	AfxSocketInit(NULL);
	CSocket LoginSocket;
	if(!LoginSocket.Create())
	{
		AfxMessageBox("�ͻ���**��¼**�׽��� ����ʧ��\r\n");
		return 0;
	}
	//CConnectSet connectset;
	if(!LoginSocket.Connect((LPCTSTR)CConnectSet::ServerIP,(UINT)CConnectSet::ServerPort))//���ӷ�����IP��Port
	{
		AfxMessageBox("�ͻ���**��¼**�׽���**����ʧ��\r\n");
		return 0;
	}
	
	int stateCode = 1;
	char buffer[sizeof(stateCode)]="0";
	sprintf_s(buffer,"%d",stateCode);
	int sendbytes= LoginSocket.Send(buffer,sizeof(stateCode),0);
	if(sendbytes == SOCKET_ERROR)
	{
		AfxMessageBox("���տͻ��˷��͵ĵ�ַ��Ϣʧ��");
		return 0;
	}
	USERINFO userinfo;
	memset(&userinfo,0,sizeof(userinfo));
	char   name[128];   
	::gethostname(name,128);//���������  
	hostent* pHost=gethostbyname(name);//��������ṹ  
	strcpy_s(userinfo.userIP,inet_ntoa(*((in_addr*)pHost->h_addr_list[0])));
	strcpy_s(userinfo.username,CLogIn::username);
	strcpy_s(userinfo.password,CLogIn::password);
	//AfxMessageBox(userinfo.password);
	int err=LoginSocket.Send(&userinfo,sizeof(userinfo),0);
	if (err==SOCKET_ERROR)
	{
		AfxMessageBox(_T("�ͻ��˷��͵�¼��Ϣʧ��"));
		return 0;
	}
	char flags[2]={0};
	LoginSocket.Receive(flags,sizeof(flags),0);
	if (flags[0]=='#'&&flags[1]=='0')
	{
		LoginSocket.Close();
		AfxMessageBox(_T("�ף�û�е�¼�ɹ�Ӵ���û��������ڣ�����ע���¡�����"));
		return 0;
	}
	if (flags[0]=='#'&&flags[1]=='1')
	{
		LoginSocket.Close();
		AfxMessageBox(_T("�ף���ӭ��ʹ��У԰�������������Կ�ʼ���������ˡ�����"));
		return 0;
	}
	if (flags[0]=='#'&&flags[1]=='2')
	{
		LoginSocket.Close();
		AfxMessageBox(_T("�ף����Ѿ���¼��У԰���������ٴε�¼��Ӵ������"));
		return 0;
	}
	if (flags[0]=='#'&&flags[1]=='3')
	{
		LoginSocket.Close();
		AfxMessageBox(_T("�ף�û�е�¼�ɹ�Ӵ���û����벻��ȷ������ע���¡�����"));
		return 0;
	}

	LoginSocket.Close();
	return 0;
}


//////////�˳���¼
UINT QuitThread(LPVOID pParam)
{
	CLogIn *MyDlg = (CLogIn *)pParam;
	AfxSocketInit(NULL);
	CSocket QuitSocket;
	if(!QuitSocket.Create())
	{
		AfxMessageBox("�ͻ���**��¼**�׽��� ����ʧ��\r\n");
		return 0;
	}
	//CConnectSet connectset;
	if(!QuitSocket.Connect((LPCTSTR)CConnectSet::ServerIP,(UINT)CConnectSet::ServerPort))//���ӷ�����IP��Port
	{
		AfxMessageBox("�ͻ���**��¼**�׽���**����ʧ��\r\n");
		return 0;
	}
	int stateCode = 6;
	char buffer[sizeof(stateCode)]="0";
	sprintf_s(buffer,"%d",stateCode);
	int sendbytes= QuitSocket.Send(buffer,sizeof(stateCode),0);
	if(sendbytes == SOCKET_ERROR)
	{
		AfxMessageBox("���տͻ��˷��͵ĵ�ַ��Ϣʧ��");
		return 0;
	}
	USERINFO userinfo;
	memset(&userinfo,0,sizeof(userinfo));
	strcpy_s(userinfo.username,CLogIn::username);
	strcpy_s(userinfo.password,CLogIn::password);
	//AfxMessageBox(userinfo.password);
	int err=QuitSocket.Send(&userinfo,sizeof(userinfo),0);
	if (err==SOCKET_ERROR)
	{
		AfxMessageBox(_T("�ͻ��˷��͵�¼��Ϣʧ��"));
		return 0;
	}
	char flags[2]={0};
	QuitSocket.Receive(flags,sizeof(flags),0);
	if (flags[0]=='#'&&flags[1]=='1')
	{
		QuitSocket.Close();
		AfxMessageBox(_T("�ף����Ѿ��ɹ��˳�У԰����"));
		return 0;
	}
	if (flags[0]=='#'&&flags[1]=='0')
	{
		QuitSocket.Close();
		AfxMessageBox(_T("�ף�����û�е�¼���޷��˳�"));
		return 0;
	}


	return 0;
}
//////////////////////////////////////////////////////////////////
//////////////**********�����ļ���Ϣ�߳�*************/////////////
//////////////////////////////////////////////////////////////////

UINT RequireInfoThread(LPVOID pParam)
{
	CDownload_Downloading *MyDlg = (CDownload_Downloading *)pParam;
	AfxSocketInit(NULL);
	CSocket RequireSocket;
	if(!RequireSocket.Create())
	{
		AfxMessageBox("�ͻ���**�����ļ���Ϣ**�׽��� ����ʧ��\r\n");
		return 0;
	}
	//CConnectSet connectset;
	if(!RequireSocket.Connect((LPCTSTR)CConnectSet::ServerIP,(UINT)CConnectSet::ServerPort))//���ӷ�����IP��Port
	{
		AfxMessageBox("�ͻ���**�����ļ���Ϣ**�׽���**����ʧ��\r\n");
		return 0;
	}

	//����״̬��2
	int stateCode = 2;
	char buffer[sizeof(stateCode)]="0";
	sprintf_s(buffer,"%d",stateCode);
	int sendbytes= RequireSocket.Send(buffer,sizeof(stateCode),0);
	if(sendbytes == SOCKET_ERROR)
	{
		AfxMessageBox("���տͻ��˷��͵ĵ�ַ��Ϣʧ��");
		return 0;
	}
	if(MyDlg==NULL)
	{
		AfxMessageBox("ָ��Ϊ��");
		return 0;
	}
	FileOwenerPath=MyDlg->m_filepath;//��ȡ�ļ���·����������
	FILENAME=MyDlg->m_filename;
	//////////////////////////////////////////�����ļ���Ϣ
	FILEINFO FileInfo1;
	memset(&FileInfo1,0,sizeof(FileInfo1));
	strcpy_s(FileInfo1.fileName,FILENAME);//�õ��ļ�����
	RequireSocket.Send(&FileInfo1,sizeof(FileInfo1));	//����������ļ���Ϣ
	FILEINFO FileInfo2;
	memset(&FileInfo2,0,sizeof(FileInfo2));
	RequireSocket.Receive(&FileInfo2,sizeof(FileInfo2));
	//FileOwenerPath=FileInfo2.filepath;//��ȡ�ļ���·����������
	FileOwnerIP=FileInfo2.fileownerIP;//��ȡ�ļ�ӵ���ߵ�IP������FileOwnerIP��
	RequireSocket.Close();
	pRequireFileThread=AfxBeginThread(RequireFileThread,MyDlg);  //���������ļ��߳�
	return 0;
}

//////////////////////////////////////////////////////////////////
//////////////**********�ͻ��������ϴ��ļ���Ϣ�߳�*************///
//////////////////////////////////////////////////////////////////

UINT UploadThread(LPVOID pParam)
{
	CUpload *MyDlg = (CUpload *)pParam;
	AfxSocketInit(NULL);
	CSocket UploadSocket;
	if(!UploadSocket.Create())
	{
		AfxMessageBox("�ͻ���**�����ļ���Ϣ**�׽��� ����ʧ��\r\n");
		return 0;
	}
	if(!UploadSocket.Connect((LPCTSTR)CConnectSet::ServerIP,(UINT)CConnectSet::ServerPort))//���ӷ�����IP��Port
	{
		AfxMessageBox("�ͻ���**�����ļ���Ϣ**�׽���**����ʧ��\r\n");
		return 0;
	}

	//����״̬��5
	int stateCode = 5;
	char buffer[sizeof(stateCode)]="0";
	sprintf_s(buffer,"%d",stateCode);
	int sendbytes= UploadSocket.Send(buffer,sizeof(stateCode),0);
	if(sendbytes == SOCKET_ERROR)
	{
		AfxMessageBox("�ϴ��ͻ��˷��͵�״̬��Ϣʧ��");
		return 0;
	}
	if(MyDlg==NULL)
	{
		AfxMessageBox("ָ��Ϊ��");
		return 0;
	}

//////////////////////////////////////////�����ļ���Ϣ
	FILEINFO FileUpload1;
	memset(&FileUpload1,0,sizeof(FileUpload1));
	char   name[128];  
	hostent*   pHost;  
	gethostname(name,128);//���������  
	pHost=gethostbyname(name);//��������ṹ  
	strcpy_s(FileUpload1.fileownerIP,inet_ntoa(*((in_addr*)pHost->h_addr_list[0])));
	//AfxMessageBox(FileUpload1.fileownerIP);
	strcpy_s(FileUpload1.fileName,MyDlg->strFileName);//�õ��ļ�����
	strcpy_s(FileUpload1.filepath,MyDlg->strFilePath);//�õ��ļ�·��
	FileUpload1.fileSize = MyDlg->fFileTotalSize;//�õ��ļ���С
	strcpy_s(FileUpload1.fileType,MyDlg->strFileType);//�õ��ļ�����
	strcpy_s(FileUpload1.username,MyDlg->strFileUserList);

	UploadSocket.Send(&FileUpload1,sizeof(FileUpload1),0);	//����������ļ���Ϣ

	char flags[2]={0};
	int recvnum=UploadSocket.Receive(flags,sizeof(flags),0);
	if(recvnum== SOCKET_ERROR)
	{
		AfxMessageBox("���շ����������ϴ�״̬ʧ��");
		UploadSocket.Close();
		return 0;
	}
	if(flags[0]=='#'&&flags[1]=='1')
	{
		AfxMessageBox("��ϲ�����ļ��ϴ��ɹ���");
		CString strNum = "";
		strNum.Format("%d", MyDlg->m_uploadNum); //��int���CString����
		CString filesize;
		//filesize.Format("%f",MyDlg->strFileTotalSize);
		MyDlg->m_List_Upload.InsertItem(MyDlg->m_uploadNum, strNum);    
		MyDlg->m_List_Upload.SetItemText(MyDlg->m_uploadNum, 1, MyDlg->strFileName);    
		MyDlg->m_List_Upload.SetItemText(MyDlg->m_uploadNum, 2, MyDlg->strFileUserList); 
		MyDlg->m_List_Upload.SetItemText(MyDlg->m_uploadNum, 3, MyDlg->strFileTotalSize); 
		MyDlg->m_uploadNum ++;

	}
	else if(flags[0]=='#'&&flags[1]=='0')
	{
		AfxMessageBox("���ļ��Ѿ��ϴ�����");
	}
	UploadSocket.Close();
	return 0;
}
//////////////////////////////////////////////////////////////////
//////////////**********��ʼ���߳�*****************////////////////
//////////////////////////////////////////////////////////////////

UINT StartClientThread(LPVOID pParam)
{
	CDialog *dialog = (CDialog *)pParam;
	AfxSocketInit(NULL);
    CSocket ClientListenSocket;
	if (!ClientListenSocket.Socket())
	{
		AfxMessageBox(_T("��ʼ��socketʧ��"));
		return 0;
	}
	UINT optValue = 1 ;
	if (!ClientListenSocket.SetSockOpt(SO_REUSEADDR , &optValue,sizeof(UINT)))
	{
		AfxMessageBox(_T("����socket��������ʧ��")) ;
		return 0 ;
	}
	if (!ClientListenSocket.Bind(P2PPort))
	{
		AfxMessageBox(_T("�ͻ��˰󶨶˿�ʧ��\r\n"));
		return 0 ;
	}
	if(!ClientListenSocket.Listen(10))
	{
		//dialog->GetDlgItem(IDC_EDIT_Log)->SetWindowText(_T("������������ʧ��,\r\n"));
		AfxMessageBox(_T("������������ʧ��,\r\n"));
		return 0;
	}
	//AfxMessageBox(_T("�������������������ڵȴ�����\r\n"));
	CSocket P2PClientSocketIn;
	int stateCode=0;
	char buffer[sizeof(stateCode)]="0";
	while(true)
	{
		ClientListenSocket.Accept(P2PClientSocketIn);
		int bytesRec =P2PClientSocketIn.Receive(buffer,sizeof(stateCode),0);
		stateCode = atoi(buffer);//ת��Ϊ����
		switch(stateCode)
		{
		case 1:
			{
				SOCKET SendFilehandleSocket;
				SendFilehandleSocket = P2PClientSocketIn.Detach();
				//::AfxBeginThread(SendFileHandleThread,(LPVOID)SendFilehandleSocket);
				AfxBeginThread(SendFileThread,(LPVOID)SendFilehandleSocket);
				//AfxBeginThread(
				break;
			}
		case 2:
			{
				SOCKET handleSocket2;
				handleSocket2 =P2PClientSocketIn.Detach();
				::AfxBeginThread(RequireFileThread,(LPVOID)handleSocket2);
				break;
			}
		//case 3:
			//{
				//SOCKET handleSocket3;
				//handleSocket3 = P2PClientSocketIn.Detach();
				//AfxBeginThread(RequireFileThread,(LPVOID)handleSocket3);
				//break;
			//}
		}
		P2PClientSocketIn.Close();
	}
	return 0;
}



void ThreadOperate::startMainThread(void* cw)
{
	this->dialog =(CDialog*)cw;
	AfxBeginThread(StartClientThread,dialog);
}

void ThreadOperate::startConnectServerThread(void* cw)
{
	this->dialog =(CDialog*)cw;
	AfxBeginThread(ConnectServerThread,dialog);
}

void ThreadOperate::startRequireInfoThread(void* cw)
{
	this->dialog =(CDialog*)cw;
	AfxBeginThread(RequireInfoThread,dialog);
}

void ThreadOperate::startSearchThread(void* cw)
{
	this->dialog =(CDialog*)cw;
	AfxBeginThread(SearchThread,dialog);
}

void ThreadOperate::startRegisterThread(void* cw)
{
	//this->dialog =(CDialog*)cw;
	CRegister *Mydlg=(CRegister *)cw;
	AfxBeginThread(RegisterThread,Mydlg);
}
void ThreadOperate::StartLoginThread(void* cw)
{
	CLogIn *MyDlg=(CLogIn*)cw;
	AfxBeginThread(LoginThread,MyDlg);
}
void ThreadOperate::StartQuitThread(void* cw)
{
	CLogIn *MyDlg=(CLogIn*)cw;
	AfxBeginThread(QuitThread,MyDlg);
}
void ThreadOperate::startUploadThread(void * cw)
{
	this->dialog =(CDialog*)cw;
	AfxBeginThread(UploadThread,dialog);
}
void ThreadOperate::UpdateSpeed(void *Mydlg)
{
	CDownload_Downloading *dlg=(CDownload_Downloading *)Mydlg;
	this->SetOffset(OFFSET);
	_endOffset = this->GetOffset();
	CString _strSpeed = GetSpeed();
	if (_strSpeed != _T(""))
	{
		//dlg->GetDlgItem(_speedID)->SetWindowText(_strSpeed);		//����
		dlg->m_Download_Downloading.SetItemText(dlg->m_NUMDownloading,5,_strSpeed);
	}
	_startOffset = _endOffset;		//������ʼ��־
}
long ThreadOperate::GetOffset(void)
{
	return this->Offset;
}
CString ThreadOperate::GetSpeed()
{
	long _speed = _endOffset - _startOffset;
	long _ratio = ELAPSE_DEFAULT / ELAPSE_SPEED;

	char szSpeed[MAX_BUF_LEN];
	CString _strSpeed;
	CString _strEx;

	if (_speed <= 0)
	{
		return _T("");
	}
	else if (_speed < Kb)		//�ֽ�
	{
		_speed = _speed * _ratio;
		_ltoa_s(_speed, szSpeed, 10);
		_strEx = _T(" B / s");
	}
	else if ( (_speed >= Kb) && (_speed < Mb) )		//KB
	{
		_speed = _speed / Kb;
		_speed = _speed * _ratio;
		_ltoa_s(_speed, szSpeed, 10);
		_strEx = _T(" KB / s");
	}
	else
	{
		_speed = _speed / Mb;
		_speed = _speed * _ratio;
		_ltoa_s(_speed, szSpeed, 10);
		_strEx = _T(" MB / s");
	}
	_strSpeed = szSpeed;
	_strSpeed = _strSpeed + _strEx;
	return _strSpeed;
}
long ThreadOperate::SetOffset(long offset)
{
	return this->Offset=offset;
}
