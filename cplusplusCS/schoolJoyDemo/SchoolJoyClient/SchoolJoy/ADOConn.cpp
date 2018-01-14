// ADOConn.cpp: implementation of the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADOConn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ADOConn::ADOConn()
{

}

ADOConn::~ADOConn()
{

}

void ADOConn::OnInitDBConnect()
{
	//��ʼ��OLE/COM�⻷��
	::CoInitialize(NULL);
	try
	{
		//����connection����
		m_pConnection.CreateInstance("ADODB.Connection");
		//���������ַ���,������BSTR�ͻ���_bstr_t����
		m_pConnection->Open("Driver=SQL Server;Database=StudentManagement;Server=WQDNAN-PC;","","",adModeUnknown);
	}
	//��׽�쳣
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());//��ʾ������Ϣ
	}
}

_RecordsetPtr& ADOConn::GetRecordSet(_bstr_t bstrSQL)//ִ�в�ѯ
{
	try
	{	
		if(m_pConnection==NULL)//���Ӷ��󲻴���
			OnInitDBConnect();//��������
		m_pRecordset.CreateInstance(__uuidof(Recordset));//������¼������
		//ִ�в�ѯ���õ���¼��
		m_pRecordset->Open(bstrSQL,m_pConnection.GetInterfacePtr(),
						adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)//��׽�쳣
	{
		AfxMessageBox(e.Description());//��ʾ������Ϣ
	}
	return m_pRecordset;//���ؼ�¼��
}

BOOL ADOConn::ExecuteSQL(_bstr_t bstrSQL)//ִ��SQL�������
{
	try
	{
		if(m_pConnection==NULL)//���Ӷ��󲻴���
			OnInitDBConnect();//��������
		m_pConnection->Execute(bstrSQL,NULL,adCmdText);//ִ��
		return true;
	}	
	catch(_com_error e)//��׽�쳣
	{
		AfxMessageBox(e.Description());//��ʾ������Ϣ
		return false;
	}
}

void ADOConn::ExitConnect()//�Ͽ�����
{
	if(m_pRecordset!=NULL)
	{
		m_pRecordset->Close();//�رռ�¼��
		m_pConnection->Close();//�ر�����
	}	
	::CoUninitialize();//�ͷŻ���
}
