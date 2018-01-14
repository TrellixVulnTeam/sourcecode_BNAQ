// DBConnection.cpp: implementation of the DBConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ThreadServer.h"
#include "DBConnection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DBConnection::DBConnection()
{
	::CoInitialize(NULL);
}

DBConnection::~DBConnection()
{
	::CoUninitialize(); 
}

_ConnectionPtr DBConnection::getConnection(){
	HRESULT hr;
	hr=m_pConnection.CreateInstance(_uuidof(Connection));//ʵ����Ӧ�ó����Connection����
	if(FAILED(hr)){
		AfxMessageBox("Connection�������ʧ��");
	}
	try{
		_bstr_t strConnect ="Provider=SQLOLEDB;Data Source=10.6.11.243;Initial Catalog=P2PDBMS;uid=sa; pwd=sa";//���������ݿ����ӵ��ַ���
		hr=m_pConnection->Open(strConnect,"","",adModeUnknown);//����ָ�����ݿ�
	}
	catch(_com_error e){
		AfxMessageBox(e.ErrorMessage());
	}
	return m_pConnection;
}
