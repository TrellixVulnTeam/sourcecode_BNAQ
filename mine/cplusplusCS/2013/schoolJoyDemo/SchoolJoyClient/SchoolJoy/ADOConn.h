// ADOConn.h: interface for the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOCONN_H__CF72097A_C007_4C0B_8B55_324170C47F2F__INCLUDED_)
#define AFX_ADOCONN_H__CF72097A_C007_4C0B_8B55_324170C47F2F__INCLUDED_
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" no_namespace rename("EOF", "adoEOF") 
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ADOConn  
{
public:
	ADOConn();
	virtual ~ADOConn();
	_ConnectionPtr m_pConnection;//ָ��Connection�����ָ��
	_RecordsetPtr m_pRecordset;//ָ��Recordset�����ָ��
	void OnInitDBConnect();//��ʼ�����������ݿ�
	_RecordsetPtr &GetRecordSet(_bstr_t bstrSQL);//ִ�в�ѯ
	BOOL ExecuteSQL(_bstr_t bstrSQL);//ִ��SQL���
	void ExitConnect();//�Ͽ�����

};

#endif // !defined(AFX_ADOCONN_H__CF72097A_C007_4C0B_8B55_324170C47F2F__INCLUDED_)




