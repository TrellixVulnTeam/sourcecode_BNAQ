// VariableConstant.cpp: implementation of the VariableConstant class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ThreadServer.h"
#include "VariableConstant.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VariableConstant::VariableConstant()
{

}

VariableConstant::~VariableConstant()
{

}
int VariableConstant::heart_request = 1;//����������Ϣ
int VariableConstant::hole_request = 2;//������
int VariableConstant::search_fragment = 3;//��ѯ��Ƭ��Ϣ
int VariableConstant::update_fragment = 4; //���·�Ƭ��Ϣ
int VariableConstant::fragment_transmit =5;//��Ƭ��������
int VariableConstant::SERVER_LISTEN_PORT = 8091;//�����������Ķ˿�
int VariableConstant::MAX_ACCAPT = 500;//�������������յ���������
int VariableConstant::BUFFER_SIZE =4096;
int VariableConstant::SUCCESS_CODE = 0;//ִ�гɹ����ش���
int VariableConstant::ERROR_CODE = 1;//ִ��ʧ�ܷ��ش���
int VariableConstant::search_detail_fragment =6;//��ѯĳ����Ƭ������λ��
long VariableConstant::fragment_longbytes =1048576*60;
CString VariableConstant::xml_file_path="d:\\serverCollege\\";