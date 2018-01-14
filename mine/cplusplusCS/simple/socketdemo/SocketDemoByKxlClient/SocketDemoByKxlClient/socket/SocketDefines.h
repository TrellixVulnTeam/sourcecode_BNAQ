

#pragma  once

const int g_iBufTimes = 10;    //�趨socket������ΪĬ�ϵ�10��
const int g_iPort     = 6686;      //����Ĭ�϶˿ں�

typedef struct _hdr    //ͨ�Ű�ͷ
{
	int	      iReqType;	     //��������		
	u_short	  usTotalLen;	//���ݰ�����(ͷ+����)

}hdr, *phdr;

#define		HEADLEN					sizeof(hdr)     //���ݰ��ṹ��Ĵ�С


/******************��ͷ������ͻ�ִ���Ϳ�ʼ*******************/
//ͨ��Э��
enum   enumPacketType
{
	ENUM_PACKET_SEND_TEXT_MESSAGE = 1,      //�ı���Ϣ
    ENUM_PACKET_RECV_TEXT_MESSAGE = 2,     //���յ��Ļ�ִ�ı���Ϣ
	ENUM_PACKET_RECV_MESSAGE_FROM_SERVER,    //���մӷ���������������Ϣ
	ENUM_PACKER_SEND_RELPY_MESSAGE_TO_SERVER,   //�յ�����������������Ϣ�����������Ӧ
};

/******************��ͷ������ͻ�ִ���ͽ���*******************/



/******************�������Ϳ�ʼ*******************/
enum   enumREQTYPE
{			
	REQ_NONE = 0,                   //��ǰ������
	REQ_TEXT_MESSAGE,				//�����¼
	REQ_REPLY_MESSAGE_FROM_SERVER,    //�ظ��������յ���Ϣ��
};


/****************�������ͽ���*****************/

typedef struct _Package
{
	char   buff[1024];   //�������պͷ������ݵĻ�����
}Package;


