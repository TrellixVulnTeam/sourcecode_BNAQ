// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����


#include <WINSOCK2.H>
#include <afxsock.h>
//#include <list>
#include <string>

#include <afxcmn.h>


#pragma comment(lib, "ws2_32.lib")
using namespace std;

#include "ExListCtrl.h"         //�ɱ༭list
#include "ADOExcel.h"




#define		BACKGROUNDCOLOR          RGB(185,211,255)     //�Ի��򱳾�ɫ
#define     CONCTRLBKCOLOR   RGB(223, 223, 223)   //�ؼ�����ɫ
///////**********�Զ�����Ϣ*********/////////////
#define		WM_LOGINSUCCESS						(WM_USER+100)    //��¼�ɹ�����Ϣ
#define     WM_CURSORTONORMAL					(WM_USER+101)    //�ı����Ϊ����״̬
#define     WM_LOGINFAIL						(WM_USER+102)    //��¼ʧ�ܵ���Ϣ
#define     WM_PAITMTTREE						(WM_USER+103)   //���Ʋ������ؼ�����Ϣ
#define     WM_UPDATESTATUS_MtSetProp			(WM_USER+104)
#define     WM_UPDATEOPERATIONSTATUS			(WM_USER+105)  //����״̬���Ĳ�����Ϣ
#define     WM_REQNOTENEW_MtSetProp				(WM_USER+106)   //�����½��������ڵ��������Ϣ
#define     WM_STRATREQMT_MtSetProp				(WM_USER+107)
#define     WM_ENDREQMT_MtSetProp				(WM_USER+108)
#define     WM_CLEARMTTREE_MtSetProp			(WM_USER+109)
#define     WM_REQNODEEDIT_MtSetProp			(WM_USER+110)
#define     WM_SHOWNOTEINEDIT_MainView			(WM_USER+111)    //������ʽ ��ʾ���¹�����Ϣ ��������ʾ�ض�������Ϣ
#define     WM_REQNOTEPUBLIC_NotePublic			(WM_USER+112)
#define     WM_ENDNOTEPUBLIC_NotePublic			(WM_USER+113)
#define     WM_NOTEPUBLICSUCCESS_NotePublic		(WM_USER+114)
#define     WM_REQSTARTINITNOTE_MainView		(WM_USER+115)
#define	    WM_REQINITNOTEEND_MainView			(WM_USER+116)
#define		WM_DELSELNOTE_MainView				(WM_USER+117)
#define		WM_REQEMPNEWSTART_EmpNew			(WM_USER+118)
#define		WM_REQEMPNEWEND_EmpNew				(WM_USER+119)
#define     WM_STARTTASK_EmpInfoView			(WM_USER+120)
#define     WM_ENDTASK_EmpInfoView				(WM_USER+121)
#define     WM_STARTTASK_EmpEdit				(WM_USER+122)
#define     WM_ENDTASK_EmpEdit					(WM_USER+123)
#define     WM_DELSELEMPINFO					(WM_USER+124)
#define     WM_STARTTASK_FctEdit				(WM_USER+125)
#define     WM_ENDTASK_FctEdit					(WM_USER+126)
#define     WM_STARTTASK_FctNew					(WM_USER+127)
#define     WM_ENDTASK_FctNew					(WM_USER+128)
#define		WM_STARTTASK_FctSet					(WM_USER+129)
#define		WM_ENDTASK_FctSet					(WM_USER+130)
#define     WM_STARTTASK_CtmInfo				(WM_USER+131)
#define		WM_ENDTASK_CtmInfo					(WM_USER+132)
#define     WM_STARTTASK_CtmNew					(WM_USER+133)
#define		WM_ENDTASK_CtmNew					(WM_USER+134)
#define     WM_STARTTASK_CtmEdit				(WM_USER+135)
#define     WM_ENDTASK_CtmEdit					(WM_USER+136)
#define     WM_DELCTM_CtmInfo					(WM_USER+137)
#define     WM_STARTTASK_StoreInfo				(WM_USER+138)
#define     WM_ENDTASK_StoreInfo				(WM_USER+139)
#define     WM_STARTTASK_StoreAdd				(WM_USER+140)
#define     WM_ENDTASK_StoreAdd				    (WM_USER+141)
#define     WM_STARTTASK_StoreOut				(WM_USER+142)
#define     WM_ENDTASK_StoreOut					(WM_USER+143)
#define     WM_STARTTASK_StoreAlertSet			(WM_USER+144)
#define     WM_ENDTASK_StoreAlertSet			(WM_USER+145)
#define     WM_STARTTASK_StoreHistory			(WM_USER+146)
#define     WM_ENDTASK_StoreHistory			    (WM_USER+147)
#define     WM_DELHISTORY_StoreHistory          (WM_USER+148)
#define     WM_STARTTASK_ServReg				(WM_USER+149)
#define     WM_ENDTASK_ServReg					(WM_USER+150)
#define     WM_STARTTASK_ServModify				(WM_USER+151)
#define     WM_ENDTASK_ServModify				(WM_USER+152)
#define     WM_STARTTASK_ServiceSearch			(WM_USER+153)
#define     WM_ENDTASK_ServiceSearch			(WM_USER+154)
#define     WM_DELSERV_ServiceSearch			(WM_USER+155)
#define     WM_STARTTASK_OrderContent			(WM_USER+156)
#define     WM_ENDTASK_OrderContent				(WM_USER+157)
#define     WM_STARTUPLOADFILE_OrderContent		(WM_USER+158)
#define     WM_CONFIRMUPLOADFILE_OrderContent   (WM_USER+159)
#define     WM_RESETUPLOAD_OrderContent			(WM_USER+160)
#define     WM_STARTTASK_DealListView			(WM_USER+161)
#define     WM_ENDTASK_DealListView			    (WM_USER+162)
#define     WM_RESETDLSTATUS_DealListView       (WM_USER+163)
#define     WM_VALID_FILEDL_DealListView        (WM_USER+164)						
#define     WM_STARTTASK_OrderEdit				(WM_USER+165)
#define     WM_ENDTASK_OrderEdit				(WM_USER+166)
#define     WM_STARTTASK_DeductSet				(WM_USER+167)
#define     WM_ENDTASK_DeductSet				(WM_USER+168)
#define     WM_LOADSETOVER_DeductSet			(WM_USER+169)
#define     WM_STRATDLOAD_DealListView			(WM_USER+170)
#define     WM_ENDDLOAD_DealListView			(WM_USER+171)
#define     WM_DEL_DEAL_DealListView			(WM_USER+172)
#define     WM_STARTTASK_DBNew					(WM_USER+173)
#define     WM_ENDTASK_DBNew					(WM_USER+174)
#define     WM_STARTTASK_PwdEdit				(WM_USER+175)
#define     WM_ENDTASK_PwdEdit					(WM_USER+176)
#define     WM_STARTTASK_EmpInfoExProp			(WM_USER+177)
#define     WM_ENDTASK_EmpInfoExProp			(WM_USER+178)
#define     WM_STARTTASK_EmpInfoProp            (WM_USER+179)
#define     WM_ENDTASK_EmpInfoProp              (WM_USER+180)
#define     WM_STARTTASK_ProdInfoExProp			(WM_USER+181)
#define     WM_ENDTASK_ProdInfoExProp           (WM_USER+182) 
#define     WM_STARTTASK_CustomExProp			(WM_USER+183)
#define     WM_ENDTASK_CustomExProp			    (WM_USER+184)
#define     WM_HANDLE_BATCH_CTM_CtmEx			(WM_USER+185)
#define     WM_STARTTASK_ProdIm					(WM_USER+186)
#define     WM_ENDTASK_ProdIm					(WM_USER+187)
#define     WM_STARTTASK_CtmIm					(WM_USER+188)
#define     WM_ENDTASK_CtmIM					(WM_USER+189)
#define     WM_STARTTASK_OrderIncomplete		(WM_USER+190)
#define     WM_ENDTASK_OrderIncomplete			(WM_USER+191)
#define     WM_FILLLIST_OrderIncomplete			(WM_USER+192)
#define     WM_HANDLE_BATCH_ProdEx				(WM_USER+193)
#define     WM_STARTTASK_EmpPerformance			(WM_USER+194)
#define     WM_ENDTASK_EmpPerformance			(WM_USER+195)
#define		WM_FILLDATATOLIST_EmpPerformance	(WM_USER+196)
#define     WM_ENDTASK_SysPostion				(WM_USER+197)
#define     WM_STARTTASK_SysPostion				(WM_USER+198)
#define     WM_STARTTASK_PosAdd					(WM_USER+199)
#define     WM_ENDTASK_PosAdd					(WM_USER+200)
#define     WM_FILLLIST_SysPostion				(WM_USER+201)
#define     WM_DEL_USERS_SysPostion				(WM_USER+202)
#define		WM_STARTTASK_PosEdit				(WM_USER+203)
#define		WM_ENDTASK_PosEdit				    (WM_USER+204)
#define		WM_INITUSER_AUTHORITY_PosEdit		(WM_USER+205)
#define		WM_DEL_FCT_FctSet					(WM_USER+206)
///////*********�Զ�����Ϣ*********/////////////
#define		RECV_BUFF               (1024*20)          //�����ļ���������С
#define		SEND_BUFF				(1024*20)         //�ϴ��ļ��������ļ��Ļ�������С
#define		HEADLEN					sizeof(hdr)     //���ݰ��ṹ��Ĵ�С
#define		SERVPORT				6686            //����Ĭ�ϵ�ͨѶ�˿�
#define		TIMEHEARTPACKAGE		(60*1000)     //���������
#define		MAX_RECVFILE_THREAD		2           //�����ļ�������߳���      

#define NORMAL		0			//������������
#define EXCEPT		1			//���������쳣
#define FINISH		2			//���ݽ������

#define DATA_START		-1    //���ݿ�ʼ����
#define DATA_MID		0      //�����м䲿��
#define DATA_END		1      //���ݽ�β����


#define WT					USES_CONVERSION
#define BUF_TIMES			10			//����ϵͳ�ķ��ͺͽ������ݻ�����ΪĬ�ϵ�10������xp32��Ϊ 8k*10
#define BUF_SIZE			(1024 * 60)	//�������Ĵ�С
#define THREAD_SLEEP		500         //�߳�����ʱ��


///////����Ϊ��ͷ����������///////////////
#define		LOGIN									1      
#define     SEARCH_ALL_EMP_INFO						3
#define     HEART_PACKAGE							5
#define     INIT_MATERIAL_TREE						7
#define     EXPAND_MATERIAL_TREE					9
#define     MT_NODE_NEW								11
#define     MT_NODE_RENAME							13
#define     MT_NODE_DELETE							15
#define     NOTE_PUBLIC_MainView					17
#define		INIT_NOTE_MainView						19
#define     DEL_NOTE_MainVIew						21
#define     EMP_NEW_EmpNew							23
#define     EMP_EDIT_EmpEdit						25
#define     EMP_DEL_EmpInfoView						27
#define     EMP_SEARCHBYKEYWORD_EmpInfoView			29
#define     FCT_NEW_FctNew							31
#define		FCT_FIND_ALL							33
#define     FCT_EDIT_FactoryEdit					35
#define		FCT_DEL_FctSet							37
#define     CTM_NEW_CtmNew							39
#define     CTM_EDIT_CtmEdit						41
#define		CTM_FINDALL_CtmInfo						43
#define     CTM_DEL_CtmInfo							45
#define     STORE_FINDALL_StoreInfo					47
#define     STORE_ADD_StoreAdd						49
#define     STORE_OUT_StoreOut						51
#define     STORE_GOODS_ALERT_SET	                53	
#define     STOREHISTORY_FINDALL					55
#define     STORYHISTORY_DEL						57
#define     SERV_REG_ServReg						59	
#define     SERV_MODIFY_ServModify					61
#define		SERV_FINDALL							63
#define     SERV_DEL								65
#define     SERV_FIND_BY_KEYWORD					67
#define     CHECK_FILE_EXIST                        69
#define     FILE_UPLOAD								71
#define     SEND_FILEINFO                           73
#define     FILE_SIZE							    75
#define     ORDER_NEW_OrderContent                  77
#define     ORDER_FIND_DealListView                 79
#define     ORDER_EDIT_OrderEdit					81
#define     DEDUCT_INIT                             83
#define     DEDUCT_SET                              85
#define     REQ_FILE_DOWNLOAD                       87
#define     DEL_DEAL                                89
#define     DATABASE_NEW                            91
#define     PWD_EDIT								93
#define     NOTE_DETAIL                             95
#define     EMP_INFO_FOR_EX                         97
#define     EMP_INFO_IMPORT                         99
#define     CTM_EX                                  101
#define     CTM_IM								    103
#define		FIND_ORDER_INCOMPLETE					105
#define     UPDATE_ORDER_BATCH                      107
#define     PROD_IM								    109
#define     PROD_EX									111
#define     FIND_EMP_PERPFORMANCE					113
#define     POS_ADD									115
#define     POS_FIND_ALL							117
#define     POS_DEL									119
#define     USER_INIT								121
#define		POS_EDIT								123
///////����Ϊ��ͷ����������///////////////


///////����Ϊ��ͷ�Ļظ�����///////////////
#define		REPLY_LOGIN										2
#define     REPLY_SEARCH_ALL_EMP_INFO						4
#define     REPLY_HEART_PACKAGE								6
#define     REPLY_INIT_MATERIAL_TREE						8 
#define     REPLY_EXPAND_MATERIAL_TREE						10
#define     REPLY_MT_NODE_NEW								12
#define     REPLY_MT_NODE_RENAME							14
#define     REPLY_MT_NODE_DELETE							16
#define     REPLY_NOTE_PUBLIC_MainView						18
#define		REPLY_INIT_NOTE_MainView						20
#define     REPLY_DEL_NOTE_MainVIew							22
#define     REPLY_EMP_NEW_EmpNew							24
#define     REPLY_EMP_EDIT_EmpEdit						    26
#define     REPLY_EMP_DEL_EmpInfoView						28
#define     REPLY_EMP_SEARCHBYKEYWORD_EmpInfoView			30
#define     REPLY_FCT_NEW_FctNew							32
#define		REPLY_FCT_FIND_ALL								34
#define     REPLY_FCT_EDIT_FactoryEdit						36
#define		REPLY_FCT_DEL_FctSet							38
#define     REPLY_CTM_NEW_CtmNew							40
#define     REPLY_CTM_EDIT_CtmEdit							42
#define		REPLY_CTM_FINDALL_CtmInfo						44
#define     REPLY_CTM_DEL_CtmInfo							46
#define     REPLY_STORE_FINDALL_StoreInfo					48
#define     REPLY_STORE_ADD_StoreAdd						50
#define     REPLY_STORE_OUT_StoreOut						52
#define     REPLY_STORE_GOODS_ALERT_SET						54
#define     REPLY_STOREHISTORY_FINDALL						56
#define     REPLY_STORYHISTORY_DEL						    58
#define     REPLY_SERV_REG_ServReg							60	
#define     REPLY_SERV_MODIFY_ServModify					62
#define		REPLY_SERV_FINDALL								64
#define     REPLY_SERV_DEL								    66
#define     REPLY_SERV_FIND_BY_KEYWORD					    68
#define     REPLY_CHECK_FILE_EXIST                          70
#define     REPLY_FILE_UPLOAD                               72
#define     REPLY_FILE_DLINFO                               74    //���������ļ�����Ϣ
#define     REPLY_FILE_SIZE							        76
#define     REPLY_ORDER_NEW_OrderContent                    78
#define     REPLY_ORDER_FIND_DealListView                   80
#define     REPLY_ORDER_EDIT_OrderEdit					    82
#define     REPLY_DEDUCT_INIT                               84
#define     REPLY_DEDUCT_SET                                86
#define     REPLY_REQ_FILE_DOWNLOAD                         88
#define     REPLY_REQ_DEL_DEAL                              90
#define     REPLY_DATABASE_NEW                              92
#define     REPLY_PWD_EDIT								    94
#define     REPLY_NOTE_DETAIL                               96
#define     REPLY_EMP_INFO_FOR_EX                           98
#define     REPLY_EMP_INFO_IMPORT                           100
#define     REPLY_CTM_EX                                    102
#define     REPLY_CTM_IM								    104
#define		REPLY_FIND_ORDER_INCOMPLETE					    106
#define     REPLY_UPDATE_ORDER_BATCH                        108
#define     REPLY_PROD_IM								    110
#define     REPLY_PROD_EX									112
#define     REPLY_FIND_EMP_PERPFORMANCE						114
#define     REPLY_POS_ADD									116
#define     REPLY_POS_FIND_ALL							    118
#define     REPLY_POS_DEL									120
#define     REPLY_USER_INIT								    122
#define		REPLY_POS_EDIT								    124
#define     REPLY_POS_AUTHORITY								126
///////����Ϊ��ͷ�Ļظ�����///////////////


//////////����Ϊ�û�Ȩ��////////////////////////
#define		 NUM_AUTHORITY                          44

#define      AUTHORITY_DEAL_NEW						0
#define      AUTHORITY_DEAL_EDIT					1
#define		 AUTHORITY_DEAL_FIND					2
#define		 AUTHORITY_DEAL_DEL						3
#define		 AUTHORITY_FILE_UPLOAD					4
#define		 AUTHORITY_FILE_DOWNLOAD				5	
#define		 AUTHORITY_FILE_DEL						6
#define		 AUTHORITY_DEAL_INCOMPLETE_FIND			7
#define		 AUTHORITY_DEAL_INCOMPLETE_EDIT			8
#define		 AUTHORITY_STORE_FIND					9
#define		 AUTHORITY_ALERT_SET					10
#define		 AUTHORITY_STORE_ADD					11	
#define		 AUTHORITY_STORE_OUT					12	
#define		 AUTHORITY_HISTORY_FIND					13	
#define		 AUTHORITY_HISTORY_DEL					14	
#define		 AUTHORITY_EMP_FIND					    15	
#define		 AUTHORITY_EMP_EDIT					    16	
#define		 AUTHORITY_EMP_NEW						17	
#define		 AUTHORITY_EMP_DEL					    18	
#define		 AUTHORITY_EMP_PERFERENCE_FIND			19	
#define		 AUTHORITY_CTM_FIND						20	
#define		 AUTHORITY_CTM_NEW						21	
#define		 AUTHORITY_CTM_EDIT						22	
#define		 AUTHORITY_CTM_DEL						23	
#define		 AUTHORITY_POS_ADD						24	
#define		 AUTHORITY_POS_FIND						25	
#define		 AUTHORITY_POS_DEL					    26	
#define		 AUTHORITY_POS_EDIT						27	
#define		 AUTHORITY_PROD_IM						28	
#define		 AUTHORITY_PROD_EX						29	
#define		 AUTHORITY_CTM_IM						30	
#define		 AUTHORITY_CTM_EX						31	
#define		 AUTHORITY_EMP_IM						32	
#define		 AUTHORITY_EMP_EX						33	
#define		 AUTHORITY_MT_FIND						34	
#define		 AUTHORITY_NODE_NEW						35	
#define		 AUTHORITY_NODE_EDIT					36	
#define		 AUTHORITY_NODE_DEL						37	
#define		 AUTHORITY_FCT_FIND					    38
#define      AUTHORITY_FCT_NEW						39
#define		 AUTHORITY_FCT_EDIT					    40
#define		 AUTHORITY_FCT_DEL						41
#define		 AUTHORITY_NOTE_PUBLIC					42
#define		 AUTHORITY_NOTE_DEL						43
//////////����Ϊ�û�Ȩ��////////////////////////
enum REQTYPE{									//��������
		REQLOGIN,								//�����¼
		REQSEARCHALLEMPINFO,					//������������Ա����Ϣ
		REQKEEPHEART,							//������
		REQ_INIT_MATERIAL_TREE,					//�����ʼ��������
		REQ_Expant_MATERIAL_TREE,				//�������������Ŀ¼
		REQ_MT_NODE_NEW,						//�����½��������ڵ�
		REQ_MT_NODE_RENAME,						//����༭���Ͻڵ�
		REQ_MT_NODE_DELETE,						//����ɾ��ĳ���ڵ�
		REQ_MAINVIEW_NOTE_PUBLIC,				//���󷢲�����
		REQ_INIT_NOTE_MAINVIEW,					//�����ʼ��֪ͨ��
		REQ_DEL_NOTE_MAINVIEW,					//����ɾ��֪ͨ����һЩ��
		REQ_EMP_NEW_EmpNew,						//�����½�Ա��
		REQ_EMP_EDIT_EmpNew,					//����༭Ա��
		REQ_EMP_DEL_EmpInfoView,				//����ɾ��Ա������
		REQ_EMP_SEARCHBYKEYWORD_EmpInfoView,   //���󰴹ؼ�������Ա������
		REQ_FCT_NEW_FctNew,						//�����½���������
		REQ_FCT_FINDALL_FctSet,					//�����������г�������
		REQ_FCT_EDIT_FctEdit,					//�����޸ĳ�������
		REQ_FCT_DEL_FctSet,						//����ɾ����������
		REQ_CTM_NEW_CtmNew,						//�����½��ͻ�����
		REQ_CTM_EDIT_CtmEdit,					//����༭�ͻ�����
		REQ_CTM_FINDALL_CtmInfo,				//����������пͻ�����
		REQ_CTM_DEL_CtmInfo,					//����ɾ���ͻ�����
		REQ_STORE_FINDALL_StoreInfo,			//�����ѯ���еĿ������
		REQ_STORE_ADD_StoreAdd,					//������ӿ����Ʒ
		REQ_STORE_OUT_StoreOut,					//�������
		REQ_GOODS_ALERT_NUM_StoreAlertSet,		//������Ԥ����Ϣ
		REQ_FIND_ALL_STOREHISTORY_StoryHistory,			//�����������п����Ϣ
		REQ_DEL_STOREHISTORY,					//����ɾ�������ʷ��¼
		REQ_SERV_REG_ServReg,					//����ע�����
		REQ_SERV_MODIFY_ServModify,				//�����޸ķ���
		REQ_SERV_FINDALL,						//�����ѯ���з���
		REQ_SERV_DEL,							//����ɾ������
		REQ_SERV_FIND_BY_KEYWORD,				//���ݹؼ��ֲ��ҷ���
		REQ_CHECK_FILEEXIST,                    //����ϴ��ĸ����Ƿ����
		REQ_UPLOADFILE,							//�����ϴ��ļ�
		REQ_FILE_SIZE,                            //���������ļ�
		REQ_ORDER_NEW,                          //�����½�����
		REQ_FIND_DEAL,                          //������Ҷ���
		REQ_ORDER_EDIT,                        //����༭����
		REQ_INIT_DEDUCT,                       //�����ʼ���������
		REQ_SET_DEDUCT,                       //�����������
		REQ_DEL_DEAL,                         //����ɾ������
		REQ_PSW_EDIT,                          //�޸�����
		REQ_NOTE_DETAIL,                       //������ع�����ϸ��Ϣ
		REQ_EMP_EX,                            //������������Ա������
		REQ_EMP_IM,                            //�����ύԱ�����ݵ����ݿ�
		REQ_CTM_EX,                            //����ͻ������Թ�����
		REQ_CTM_IM,                             //���������ύ�ͻ����ϵ����ݿ�
		REQ_FIND_ORDER_INCOMPLETE,               //�����ѯδ��ɶ���
		REQ_UPDATE_ORDER_BATCH,              //��������δ��ɶ�������
		REQ_UPDATE_PROD_BATCH,               //�����ύ��Ʒ����
		REQ_PROD_EX,                          //����������Ʒ����
		REQ_EMP_PERFORMANCE,                  //����Ա��ҵ����
		REQ_POS_ADD,                           //�������û�
		REQ_FINDALL_USERS,                     //���������û�
		REQ_DELE_USERS,                       //ɾ���û�
		REQ_LOAD_USER_AUTHORITY,				//�����û�Ȩ��
		REQ_EDIT_USER,                           //���±༭�û�
		REQNON        //��ǰ������		
};



typedef struct _hdr
{
	int	type;	//����		
	u_short	len;	//���ݰ�����(ͷ+����)
	u_long 	fpos;	//�ļ�λ��
	u_long 	flen;	//�ļ�����
	char    fname[MAX_PATH];   //�ļ�������
	char    NO_Order[20];    //�������
	//u_long  nIndex;  //��ѯ���ݿ�õ���ƥ�����ĵڼ���
}hdr, *phdr;

typedef struct _Pos_Authority
{
	BOOL bLoadSuccess;
	BOOL autority[NUM_AUTHORITY];      //Ȩ���б�
}Pos_Authority,*p_Pos_Authority;

typedef	struct _FileDownloadParam  
{
	unsigned short	ID;			//��ʶ
	hdr				header;		//��ͷ
	SOCKET			s;			//�׽���
	void*		    ptr;		//���߳�
	char			strFilePath[MAX_PATH];//�����ļ�·��
}FileDownloadParam, *pFileDownloadParam;


typedef struct _DeductInfo     ////�����Ϣ��
{
	char decorate_company[50];
	char discuss_deal_person[50];
	char emp[50];
	char exact_test_person[50];
	char has_inner_modify[50];
	char measure[50];
	char no_inner_modify[50];
}DeductInfo;


typedef struct _FileInfo   //�ϴ������ص��ļ���Ϣ
{
	char order_NO[20];   //�������
	char filename[MAX_PATH];
	char filepath[MAX_PATH];
	u_long filesize;
}FileInfo;
typedef struct _OrderInfo   //������Ϣ��
{
	char  NO_Order[20];  //�������
	char  date_accept_order[20];  //�ӵ�����
	char  date_finished_order[20];  //���ʱ��
	char  name_person_charge_order[20];   //����������
	char  base_ps_order[200];      //������Ϣ�Ļ�����ע
	char  ctm_from[20];    //�ͻ���Դ
	char  name_intr[20];   //����������
	char  phone_intr[20];   //�����˵绰
	char  name_serv_persion[20];    //�Ӵ���Ա����
	char  name_emp[20];      //ҵ��Ա����
	char  call_ctm[20];      //�ͻ�����
	char  name_ctm[20];      //�˿�����
	char  phone_ctm[20];     //�˿͵绰
	char  addr_ctm[50];      //�˿͵�ַ
	char  ps_ctm[100];       //�˿ͱ�ע
	char  NO_contract[20];   //��ͬ����
	char  prog_business[20];   //ҵ�����
	char  price_total_contract[20];  //�����ܼ�
	char  money_already_take[20];   //���ս��
	char  date_first_test_book[20];  //����ԤԼʱ��
	char  persion_first_test[20];   //������Ա
	char  persion_first_design[20];  //���������Ա
	char  type_early_modify[20];    //ǰ���޸�����
	char  persion_early_modify[20];    //ǰ���޸���Ա
	char  persion_budget[20];       //Ԥ����Ա
	char  type_discuss_order[20];    //̸������
	char  persion1_discuss_order[20];   //̸����Ա1
	char  persion2_discuss_order[20];   //̸����Ա2
	char  date_final_scheme[20];        //������������
	char  date_book[20];				//����ԤԼʱ��
	char  person_exact_measure[20];		//����������Ա
	char  date_out_order_book[20];      //����ԤԼʱ��
	char  person_out_order[20];       //������Ա
	char  factory_choose[50];       //��λѡ��
	char  pay_deal_choice[20];      //����ѡ��
	char  date_install_book[20];    //��װԤԼʱ��
	char  persion_install[20];      //��װ��Ա
	char  problems_install[100];      //��װ����
	char  filepath_accessory[MAX_PATH];   //�ļ�·��
	char  filesize[50];               //�ļ���С
}OrderInfo,*pOrderInfo;


typedef struct _NotePublic_MainView      //��ҳ������������Ľṹ��
	{
		char content[600];   //��������
		char title[100];      //������Ŀ
		char persion_public[50];   //���淢���Ķ���
		char time_public[50];   //���淢����ʱ��
	}NotePublic_MainView,*p_NotePublic_MainView;

typedef struct _ServInfo    //������Ϣ
{
	char serv_NO[20];        //���񵥺�
	char client_type[20];   //�ͻ�����
	char ctm_name[20];		//�ͻ�����
	char client_name[20];  //�˿�����
	char ctm_sex[10];		//�˿��Ա�
	char client_phone[20];  //�˿͵绰
	char addr[50];			//��ַ
	char ps[200];			//��ע
	char serv_content[60];  //��������
	char req_serv_date[20];  //Ҫ���������
	char serv_name[20];		//������Ա����
	char serv_phone[20];	//������Ա�绰
	char prog[20];			//����
	char delay_date[20];   //��������
	char charge[20];	   //�շѽ��
	char serv_type[30];   //��������
}ServInfo,pServInfo;

typedef struct _StoreInfo{    //���ڼ�¼���Ľṹ��
	//char store_NO[20];    //�����
	char Store_Name[50];    //����
	char Store_Num[20];      //�������
	char Store_Alert_NUM[20];   //Ԥ������
}StoreInfo,*pStoreInfo;

typedef struct _StoreHistory    //�����ʷ��¼
{
	char Store_Name[50];    //����
	char num_change[20];    //�䶯����
	char status[20];        //״̬
	char time[30];           //�䶯ʱ��
}StoreHistory,*pStoreHistory;

typedef struct _LoginInfo{    //�����û���¼�Ľṹ��
	char username[50];    //�û���
	char password[50];    //����
	char DBName[50];      //���ݿ������
	char loginAddr[50];   //�û���¼�ص�
	char loginPos[30];    //�û���¼��ɫ

}loginInfo,*pLogInfo;

typedef struct _CtmInfo
{
	char NO[50];
	char name[50];    //�˿�����
	char call_ctm[50];    //�ͻ�����
	char sex[10];   
	char phone[20];
	char pay_times[20];   //���Ѵ���
	char pay_total[20];   //���ѽ��
    char first_pay_time[30];  //�״�����ʱ��
	char late_pay_time[30];   //�������ʱ��
	char ps[300];        //��ע

}CtmInfo,*p_CtmInfo;

typedef struct _fileuploadparam
{
	u_long	ulFileSize;		//�ļ�����
	u_long	ulFilePos;		//�ļ�λ��
	void* ptr;			   //ָ��
	char filepath[MAX_PATH];       //�ļ�·��
	CRITICAL_SECTION cs;
}FileUploadParam, *pFileUploadParam;


typedef struct _FctInfo
{
	char	name_fct[100];   //��������
	char	addr_fct[200];   //���ҵ�ַ
	char	contacts_fct[50];  //������ϵ��
	char    phone_fct[20];		//���ҵ绰
	char    main_product_fct[200];  //������Ҫ��Ʒ
	char    ps_fct[400];      //���ұ�ע
}FctInfo,p_FctInfo;



typedef struct _EmpInfo
{
	char empNum[50];
	char empName[50];
	char empAddr[50];
	char empPos[50];
	char empPhone[20];
	char empPS[900];
}EmpInfo,*pEmpInfo;

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��
#include <afxdlgs.h>



////////*******����Ϊ�Լ���ӵ��ڴ�й¶��⹦��************////////////
#define _CRTDBG_MAP_ALLOC
#include "stdlib.h"
#include "crtdbg.h"

#include "vld.h"
////////*******����Ϊ�Լ���ӵ��ڴ�й¶��⹦��************////////////





#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


