// VariableConstant.h: interface for the VariableConstant class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VARIABLECONSTANT_H__1E7A0731_F1D5_4524_9BF2_8A0750D9147F__INCLUDED_)
#define AFX_VARIABLECONSTANT_H__1E7A0731_F1D5_4524_9BF2_8A0750D9147F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class VariableConstant  
{
public:
	VariableConstant();
	virtual ~VariableConstant();
	 int static heart_request;//��������
	 int static hole_request;//������
	 int static update_fragment;//���·�Ƭ��Ϣ
	 int static fragment_transmit;//��Ƭ��������
	 int static search_fragment;//��ѯ��Ƭ��Ϣ
	 int static SERVER_LISTEN_PORT; //�������˼����˿�
	 int static MAX_ACCAPT;//�����յĿͻ��˿ڵ���Ŀ
     int static BUFFER_SIZE;
	 int static SUCCESS_CODE;//ִ�гɹ����ز���
	 int static ERROR_CODE;//ִ��ʧ�ܷ��ز���
	 int static search_detail_fragment;//��ѯĳ����Ƭ��λ��
	 long static fragment_longbytes; //ÿ���ֶεĳ���
	 CString static server_address;
	 CString static xml_file_path;
};

#endif // !defined(AFX_VARIABLECONSTANT_H__1E7A0731_F1D5_4524_9BF2_8A0750D9147F__INCLUDED_)
