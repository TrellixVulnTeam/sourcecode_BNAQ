

//���ڶ���ͨ��Э��

#pragma  once 


const int    g_iServerPort	= 6686;            //ͨ�Ŷ˿�
const int    g_iBufSize   	= (1024 * 60);		//�������Ĵ�С

//����ϵͳ�ķ��ͺͽ������ݻ�����ΪĬ�ϵ�10������xp32��Ϊ 8k*10
const int    g_iBufTimes = 10;

enum REQTYPE
{
	REQ_NONE = 0,           //��ǰ��������
	REQ_MESSAGE = 1,	    //��ͨ��Ϣ
	REQ_SEND_TEXT_MESSAGE_TO_CLINET,    //������Ϣ���ͻ���
};


typedef struct _hdr    //ͨ�Ű�ͷ
{
	int	      iReqType;	     //��������		
	u_short	  usTotalLen;	//���ݰ�����(ͷ+����)

}hdr, *phdr;

const int   g_iHeadLen = (sizeof(hdr));    //��ͷ�ĳ���


typedef struct _SysLogInfo
{
	char showInfo[1024];
	void* p_voidTemp;
}SysLogInfo,*p_SysLogInfo;



//���ݰ�����
////////******����Ϊ���յ������ݰ���������******////////////
enum  enumPacketType
{
    ENUM_RECV_PACKET_TEXT_MESSAGE = 1,      //�����ı�������Ϣ  
    ENUM_REPLY_PACKET_TEXT_MESSAGE = 2,     //��ִ���ı���Ϣ
	ENUM_SEND_MESSAGE_TO_CLIENT = 3,       //���ͻ��˷���Ϣ
	ENUM_RECV_REPLY_FROM_CLIENT = 4,       //���յ��ͻ��˷���
};
  

typedef struct _Package
{
	char   buff[1024];   //�������պͷ������ݵĻ�����
}Package;





