#ifndef SOCK_H_H_H_H
#define SOCK_H_H_H_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSock          //������������� ����ͨ�źͶ��̵߳ĵ��Ⱥ�ʵ��
{
public:
	CSock(void);
	~CSock(void);
public:
	static      BOOL      StartLookNoteDetail(void* ptr);          //�鿴֪ͨ��
	static      BOOL	  StartReqLoadUserAuthority(void* ptr);
	static      BOOL      StartDelUsers(void* ptr);      //ɾ���û�
	static      BOOL	  StartFindAllUser(void* ptr);      //���������û�
	static      BOOL	  StartReqPosEdit(void* ptr);       //����༭�û���ɫ
	static      BOOL	  StartReqPosAdd(void* ptr);
	static      BOOL      StartFindEmpPerformance(void* ptr);    //��ѯԱ������
	static      BOOL      FindDealIncomplete(void* ptr);      //��ѯ����δ��ɶ���
	static      BOOL      StartFindCtmForEx(void* ptr);      //���������ͻ�����
	static      BOOL      StartReqFindProd(void* ptr);        //����������Ʒ����
	static      BOOL      StartUpdateOrderIncomplete(void* ptr);    //��������δ��ɶ���
	static      BOOL      StartSubmitProd(void* ptr);         //�����ύ��Ʒ����
	static      BOOL      StartSubmitCtmInfo(void* ptr);      //�����ύ�ͻ����ݵ����ݿ�
	static      BOOL      StartImportEmpInfo(void* ptr);     //�����ύԱ����Ϣ�����ݿ�
	static      BOOL      StartReqFindEmpForEx(void* ptr);          //Ϊ�˵������ݶ���ѯԱ������
	static      void      UpdateOperationStatus(CString _status);  //����״̬������ʾ��Ϣ
	static      BOOL      StartReqPswEdit(void* ptr);       //�޸�����
	static      BOOL      StartReqSetDeduct(void* ptr);     //�������
	static      BOOL      StartReqInitDeduct(void* ptr);         //��ʼ���������
	static      BOOL      StartReqOrderEdit(void* ptr);          //��ʼ����༭����
	static      BOOL      StartReqFindDeal(void* ptr);           //��ʼ��������
	static      BOOL      StartReqOrderNew(void* ptr);           //�½�����
	static      BOOL      StartDLFile(void* ptr);               //��ʼ���������ļ�
	static      BOOL      StartUpLoadFile(void* ptr);           //��ʼ�ϴ��ļ�
	static      BOOL      StartCheckFileExist(void* ptr);        //���Ҫ�ϴ��ĸ����Ƿ����
	static      BOOL      StartFindServByKeyWord(void* ptr);      //������ҹؼ��� ���ùؼ���
	static      BOOL      StartDelDeal(void* ptr);             //����ɾ������
	static      BOOL      StartDelServ(void* ptr);            //����ɾ������
	static      BOOL      StartFindAllServ(void* ptr);        //�����ѯ���з�����Ϣ
	static      BOOL      StartReqServModify(void* ptr);      //�����޸ķ���
	static      BOOL      StartReqServReg(void* ptr);        //�������ע��
	static      BOOL      StartDelHistory(void* ptr);       //����ɾ�������ʷ��¼
	static      BOOL      StartFindAllStoreHistory(void* ptr);   //�����������п���¼
	static      BOOL      StartReqGoodsAlertNumSet(void* ptr);   //�������ÿ����ƷԤ��
	static      BOOL      StartReqStoreOut(void* ptr);       //�������
	static      BOOL      StartReqStoreAdd(void* ptr);       //������ӿ����Ʒ
	static      BOOL      StartFindAllStore(void* ptr);      //��������ȫ�������Ϣ
	static      BOOL      StartDelCtm(void* ptr);            //����ɾ���ͻ�����
	static      BOOL      StartFindAllCtm(void* ptr);       //����������пͻ�����
	static      BOOL      StartReqCtmEdit(void* ptr);       //����༭�ͻ�����
	static      BOOL      StartReqCtmNew(void* ptr);        //�����½��ͻ�����
	static      BOOL      StartReqFctNew(void* ptr);        //�����½���������
	static      BOOL	  StartReqEmpEdit(void* ptr);		//����༭Ա������
	static		BOOL      StartReqFctEdit(void* ptr);    //���������޸ĳ�������
	static		BOOL	  StartReqEmpNew(void* ptr);
	static      BOOL	  StartDelNoteMainView(void* ptr);    //����ɾ��֪ͨ
	static		BOOL	  StartDelEmpInfo(void* ptr);        //����ɾ��Ա������
	static		BOOL      StartDelFct(void* ptr);            //����ɾ����������
	static      BOOL      StartReqLoadNote(void* ptr);        //���������ҳ�Ĺ���
	static		BOOL	  StartReqNotePublic(void* ptr);    //���󷢲�����
	static      BOOL      StartReqDeleteNode(void* ptr);       //����ɾ���������Ľڵ�         
	static      BOOL      StartRefreshMtTree(void* ptr);      //���²�����
	static      BOOL      StartExpandMtTree(void* ptr);
	static      BOOL      StartSendHeartPackage();   //��ʱ����������
	static		BOOL      StartLogin(void* ptr);	//��¼ʱ����� ����CLoginָ�� ����ʼ���ӷ�����   ����������������ݽ�������	
	static      BOOL      StartReqMtNodeNew(void* ptr);   //�����½��������ڵ�
	static      BOOL      StartReqMtNodeEdit(void* ptr);     //����༭�������Ľڵ�
	static		BOOL      StartFindALLFct(void* ptr);        //�����������г��ҵ�����
	static		BOOL	  StartSearchAllEmpInfo(void* ptr);		//����ȫ��ְԱ��Ϣ����ʾ
	static		BOOL	  StartSearchEmpByKeyWord(void* ptr);   //���ݹؼ�������Ա����Ϣ
	static		BOOL	  ConnectServer();			//������ӷ����������� �ڵ�¼��ʱ�����
	static		UINT	  SendAndRecvClientThread(LPVOID pParam);		//������պͷ������ݵ��߳�
	static		BOOL	  SendReq();			//���������������  
	static		BOOL	  RecvData();			//���մӷ��������ص�����
	static      void      InitSocket();
	static		BOOL	  ReqLogin();			//������������û���������֤��¼
	static      BOOL      FindServByKeyWord();    //���ݹؼ��ֲ��ҷ���
	static      BOOL      SearchEmpByKeyWord();    //���ݹؼ�������Ա����Ϣ
	static		BOOL      ReqFindAllCtmInfo();     //����������Ͳ�ѯ���пͻ����ϵ�����
	static      BOOL      ReqProdForEx();   //�������в�Ʒ����
	static      BOOL	  ReqCtmForEx();    //�������пͻ�����
	static      BOOL      ReqFindOrderIncomplete();    //��ѯδ��ɶ���
	static      BOOL      ReqFindEmpPerformance();   //��ѯԱ��ҵ����
	static		BOOL      ReqFindAllUsers();    //���������û�
	static      BOOL      ReqLoadUserAuthority();      //�����û�Ȩ��
	static      BOOL      ReqDelUsers();   //ɾ���û�
	static      BOOL      ReqFindAllStoreInfo();     //�����������п������
	static      BOOL      ReqAddStore();        //���������Ʒ���
	static		BOOL      ReqRegServ();   //����ע�����
	static      BOOL      ReqModifyServ();    //�����޸ķ���
	static      BOOL      ReqOutStore();        //�������
	static      BOOL      ReqStoreAlertNumSet();    //������Ԥ����Ϣ����
	static      BOOL      ReqFindAllStoreHistory();   //�������п���¼��Ϣ
	static      BOOL      ReqFindAllServ();			//�����ѯ���з���
	static      BOOL      ReqDelStoreHistory();    //����ɾ�������ʷ��¼��Ϣ
	static      BOOL      ReqDelServ();        //����ɾ��������Ϣ
	static      BOOL      ReqDelDeal();         //����ɾ������
	static      BOOL      ReqCheckFileExist();   //�����ѯ�ļ��Ƿ����
	static      BOOL      ReqUpLoadFile();    //��������ϴ��ļ�
	static      BOOL	  ReqDLFile();     //���������ļ�
	static      BOOL      ReqOrderNew();    //�����½�����
	static      BOOL      ReqFindDeal();     //������Ҷ���
	static      BOOL      ReqOrderEdit();    //����༭����
	static      BOOL      ReqInitDeduct();     //�����������
	static      BOOL      ReqSetDeduct();     //�����������
	static      BOOL      ReqPswEdit();       //�����޸�����
	static      BOOL      ReqPosAdd();    //��������û�
	static      BOOL      ReqPosEdit();    //����༭�ͻ�
	static      BOOL      ReqDetailNote();    //������ҹ������ϸ��Ϣ
	static		DWORD WINAPI     UploadFileThread(void *pParam);	//�ϴ��ļ��̺߳���
	static		BOOL	  ReqSearchAllFctInfo();   //��������������������г�����Ϣ
	static		BOOL	  ReqSearchAllEmpInfo();		//�������������������Ա����Ϣ������
	static      BOOL      ReqSearchAllEmpInfoForEx();   //���������������Ա������ Ϊ����������
	static      BOOL      ReqSubmitEmpInfo();    //�����ύԱ�����ݵ����ݿ�
	static      BOOL      ReqSubmitProdInfo();   //���������Ʒ����
	static      BOOL	  ReqSubmitCtmInfo();   //�����ύ�ͻ����ݵ����ݿ�
	static      BOOL      ReqUpdateOrderIncomplete();    //�ύ�������ݵ����ݿ�
	static      BOOL      ReqKeepHeart();
	static      BOOL      ReqInitMtTree();            //�����ʼ�����ؼ�
	static      BOOL      ReqMtNodeNew();
	static      BOOL      ReqMtNodeRename();          //�������������Ͻڵ�
	static      BOOL      ReqMtNodeDelete();            //����ɾ������ĳ���ڵ�
	static      BOOL	  ReqMainViewNotePublic();      //���󷢲�֪ͨ
	static		BOOL	  ReqMainViewInitNote();		//�������֪ͨ
	static      BOOL      ReqMainViewDeleteSelNote();    //����ɾ��һЩ֪ͨ
	static		BOOL	  ReqDeleteSelEmpInfo_EmpInfoView();   //����ɾ��һЩԱ������
	static      BOOL      ReqDeleteSelCtm();      //��������ɾ���ͻ�����
	static		BOOL	  ReqDeleteSelFct_FctSet();     //��������ɾ����������
	static		BOOL	  ReqEmpNew();				//�����½�Ա��
	static      BOOL      ReqFctNew();      //�����½���������
	static      BOOL      ReqCtmNew();   //�����½��û�����
	static      BOOL      ReqFctEdit();   //����༭��������
	static      BOOL      ReqEmpEdit();             //����༭��Ա��
	static      BOOL      ReqCtmEdit();    //����༭�ͻ�����
	static      BOOL      ReqExpandMtTree();          //����������ӽڵ�
	static		BOOL	  RecvReplyOfLoginIn(int len);			//���ջظ���Ϣ ���ڵ�¼�Ƿ�ɹ���
	static      BOOL      RecvReplyOfDeletNote(int len);
	static      BOOL      RecvReplyOfDetailNote(int len);    //�ظ��û��鿴֪ͨ
	static      BOOL      RecvReplyOfEmpEdit(int len);        //���շ����������޸�Ա�����ϵĻظ�
	static      BOOL      RecvReplyOfFctEdit(int len);      //���շ����������޸ĳ������ϵĻظ�
	static      BOOL      RecvReplyOfCtmEdit(int len);   //�����޸Ŀͻ����ϵĽ��
	static      BOOL      RecvReplyOfServModify(int len);   //�޸ķ���
	static      BOOL      RecvReplyOfCtmDel(int len);      //���շ�������Ӧɾ���ͻ�����
	static      BOOL      RecvReplyOfStoreHistoryDel(int len);   //����ɾ�����ֿ����ʷ��¼��Ϣ
	static      BOOL      RecvReplyOfServDel(int len);   //�ظ�ɾ�����������
	static      BOOL      RecvReplyOfDealDel(int len);      //�ظ�ɾ������������
	static      BOOL      RecvReplyOfUsersDel(int len);    //�ظ�ɾ���û�
	static		BOOL      RecvReplyOfUsersInit(int len);      //���շ������������û�Ȩ��
	static      BOOL      RecvReplyOfPosAdd(int len);    //�������û��Ļظ�
	static		BOOL      RecvReplyOfPosEdit(int len);     //�����޸��û��Ļظ�
	static      BOOL      RecvReplyOfPosAuthority(int len);     //�����û�Ȩ��
	static      BOOL      RecvReplyOfEmpInfoIm(int len);    //��������Ա�����ݵĻظ�
	static      BOOL      RecvReplyOfProdInfoIm(int len);   //���������Ʒ���ݵĽ��
	static      BOOL      RecvReplyOfCtmInfoIm(int len);    //�����ύ�ͻ����ݵ����ݿ�
	static      BOOL      RecvReplyOfUpdateOrderBatch(int len);     //�������¶������ݵĻظ�
	static      BOOL      RecvReplyOfPswEdit(int len);    //�޸�����Ľ��
	static      BOOL      RecvReplyOfCheckFile(int len);   //�ظ����ļ��Ƿ���ڵĽ��
	static      BOOL      RecvReplyOfFileDLInfo(int len);   //���������ļ�����Ϣ
	static      BOOL      RecvReplyOfUploadFile(int len);    //�ϴ��ļ��Ľ��
	static      BOOL      RecvReplyOfDLFile(int len,char *strFilePath);        //���������ļ��Ļظ�
	static      void      PrepareFileDownload(void);        //׼�������ļ������߳�
	static      DWORD WINAPI   DownloadFileThread(void* pParam);	//�ļ������߳�
	static      DWORD WINAPI   CreateDownloadFileThread(void* pParam);	//�����ļ������߳�
	static      BOOL	  RecvReplyOfEmpDel(int len);
	static      BOOL      RecvReplyOfFctDel(int len);      //����ɾ���������ϵĻ�Ӧ
	static      BOOL	  RecvReplyOfFctNew(int len);         //���չ����½��������ϵĻ�Ӧ
	static      BOOL      RecvReplyOfCtmNew(int len);   //���շ����½��ͻ����ϵĽ��
	static      BOOL      RecvReplyOfAddStore(int len);    //���������Ʒ�����Ϣ
	static      BOOL      RecvReplyOfRegServ(int len);   //�ظ�����ע�����
	static      BOOL      RecvReplyOfOrderNew(int len);    //�½�����
	static      BOOL      RecvReplyOfOrderEdit(int len);    //�༭�����Ļظ�
	static      BOOL      RecvReplyOfDeductSet(int len);     //����������ɵĻظ�
	static      BOOL      RecvReplyOfOrderFind(int len);   //�ظ���������
	static      BOOL      RecvReplyOfInitDeduct(int len);   //�ظ���ʼ�����
	static      BOOL      RecvReplyOfStoreAlertSet(int len);    //���չ����û�����Ԥ����Ϣ�Ļظ�
	static      BOOL      RecvReplyOfStoreFindAll(int len);    //�ظ��û�����ȫ�������ʷ��¼
	static      BOOL      RecvReplyOfServFindAll(int len);		//��������������Ϣ
	static      BOOL      RecvReplyOfOutStore(int len);    //�������
	static		BOOL	  RecvReplyOfEmpNew(int len);        //�����½�Ա��
	static      BOOL      RecvReplyOfKeepHeart(int len);
	static      BOOL      RecvReplyOfInitMtTree(int len);
	static      BOOL	  RecvReplyOfMtNodeNew(int len);      //�����½��������Ľڵ���Ϣ
	static      BOOL      RecvReplyOfMtNodeDelete(int len);     //����ɾ���������ڵ�Ļ�Ӧ
	static      BOOL      RecvReplyOfNotePublicMainView(int len);   //���շ��������ڷ����¹���Ļظ�
	static      BOOL	  RecvReplyOfInitNote(int len);
	static      BOOL	  RecvReplyOfMtNodeRename(int len);    //�����޸Ĳ������ڵ�Ļ�Ӧ
	static      BOOL      RecvReplyOfSearchAllEmpInfo(int len);    //���ջظ���Ϣ ��������ȫ��Ա����Ϣ��
	static		BOOL      RecvReplyOfSearchAllFctInfo(int len);    //���յ��ظ���Ϣ  ��������ȫ����������
	static      BOOL	  RecvReplyOfFindAllCtm(int len);      //���������ͻ����ϵĻظ�
	static      BOOL      RecvReplyOfCtmEx(int len);     //���ڿͻ�������������
	static      BOOL	  RecvReplyOfProdEx(int len);     //��������������Ʒ����
	static      BOOL      RecvReplyOfFindEmpPerformance(int len);   //Ѱ��Ա��ҵ���Ļظ�
	static      BOOL      RecvReplyOfFindAllUsers(int len);      //Ѱ�������û�
	static		BOOL      RecvReplyFindOrderIncomplete(int len);    //����δ��ɶ����Ļظ�
	static      BOOL      RecvReplyOfFindAllStore(int len);     //���������������
	static      BOOL      RecvReplyOfSearchAllEmpInfoForEx(int len);    //��������Ա�������Թ�����
	//static      void      DeletePtr();				//ɾ����ʱָ��
//////***********����ΪһЩȫ�ֵļ����Ժ���*****************////////////////
public:
	static      BOOL     IsUserHasAuthority(int n_authority);
	static      CString	 GetItemFromString(CString source,int index);     //���ַ�����ȡ����������
	static      void	 InitUserAuthority(char *p);   //���û�Ȩ��д���ṹ����
	static      BOOL     RecvDataFromServer(SOCKET s,char* p_recv,int data_len,CString message);
	static      BOOL     SendDataToServer(SOCKET s,char* p_send,CString message,int data_len = HEADLEN);
	static      BOOL     IsNum(CString _source,BOOL bCheckDot);
	static      BOOL	 IsNum(CString str);    //����һ���ַ��� ������Ƿ�Ϊ����
	static      BOOL	 ContainsCharsRemain(CString str);     //����ַ����Ƿ�������ַ���
	static      BOOL	 IsItemValidity(CString _source,CString _item_name,BOOL bCheckEmpty,BOOL bCheckNum,BOOL bCheckDateFormat,int str_len_max);    //true  ��Ч ������Ч 
//////***********����ΪһЩȫ�ֵļ����Ժ���*****************////////////////

//////***********����ΪһЩȫ�ֵ������ļ�����*****************////////////////
public:
	static      u_long		AssembleLine(FILE* destFile, int startPos, FILE* resoFile);
	static		void		AssemblyFile(void* ptr);
	static      int			RecvFileData(SOCKET s, unsigned short ID,void* ptr);  //�����ļ����ݺ���
	static      void		SaveFile(u_short nIndexThread, const char* pBuf, u_long ulLen, u_long ulPos,void* ptr);
//////***********����ΪһЩȫ�ֵ������ļ�����*****************////////////////


public:
	static      BOOL      m_bUpLoading;      //�ϴ��ļ���־
	static		SOCKET    m_sockWhole;         //ȫ��socket һֱ�ͷ�������������
	static	    u_short   m_port;             //�������˿�
	static      CString   m_IP;               //��������ַ
	static		BOOL      m_bIsConnecting;		//�ж��Ƿ������������
	static		REQTYPE   m_nCurReq;            //��������  
	static      CString   m_DB;                  //���ݿ�����
	static      BOOL	  m_bOnline;             //�ж��û��Ƿ�����
	static      CString   m_nameOnline;           //�Ѿ���¼���û�
	static      CString   m_user_pos;            //�û���ɫ
	static      p_Pos_Authority	m_pPosAuthority;     //�û�Ȩ�޽ṹ��
	static      HANDLE	  m_hThreadFileDL;		//�����ļ������߳�
	//static		BOOL	  m_bReqAvailable;        //�ж������Ƿ����
////////////***����Ϊ�Ի���ָ����*****//////////////
public:
	static      void*		m_pLogin;            //ָ���¼�Ի����ָ��
	static      void*		m_pNotePublic;       //ָ�򷢲�֪ͨ�Ի����ָ��	
	static		void*		m_pMtSetProp;
	static      void*		m_pEmpInfoView; 
	static      void*       m_pProdBatch;          //������Ʒ����
	static      void*       m_pCtmSubmit;          //�����ύ�ͻ����ϵ����ݿ�
	static      void*       m_pEmpInfoIm;         //Ա�����������ύ�����ݿ�
	static      void*       m_pEmpInfoEx;        //Ա������������������ҳ
	static      void*       m_pMainFormView;         //ָ����ҳ�ı�����
	static      void*		m_pEmpNew;               //ָ���½�Ա���Ի���
	static      void*       m_pEmpEdit;              //ָ��༭Ա���ĶԻ���
	static      void*       m_pFctNew;				//ָ���½�������
	static      void*       m_pFactoryEdit;			//ָ�򳧼ұ༭��
	static		void*		m_pFctSet;				//ָ������ҳ ����
	static      void*		m_pCtmInfo;             //ָ��ͻ�������
	static      void*       m_pCtmNew;				//ָ���½��ͻ�������
	static      void*       m_pCtmEdit;            //ָ��༭�ͻ����ϴ�����
	static      void*       m_pStoreAdd;			//ָ�������Ʒ��
	static      void*       m_pStoreInfo;			//ָ����Ʒ�Ŀ����
	static      void*       m_pStoreOut;            //ָ����Ʒ�ĳ�����
	static      void*       m_pStoreHistory;        //ָ������ʷ��¼��
	static      void*       m_pStoreAlertSet;		//ָ����Ʒ��Ԥ��������
	static      void*       m_pServReg;             //ָ��ע����񴰿���
	static      void*       m_pServModify;          //ָ��༭���񴰿���
	static      void*       m_pServiceSearch;		//ָ������ѯ��
	static      void*       m_pOrderContent;        //ָ���½���������
	static      void*       m_pDealListView;         //ָ�򶩵���ͼ��
	static      void*       m_pOrderEdit;           //�༭��������
	static      void*       m_pDeductSet;           //ָ��������ô���
	static      void*       m_pPwdEdit;             //ָ������༭����
	static      void*       m_pCtmEx;               //ָ�����������ͻ����ϴ���
	static      void*       m_pProdEx;               //��Ʒ���ϵ���
	static      void*       m_pOrderIncompleteView;      //δ��ɶ�����ͼ����
	static      void*       m_pEmpPerformance;           //Ա��ҵ����ͼ
	static      void*		m_pPosAdd;                  //�������û�
	static      void*		m_pSysPostion;				//�û�����Ի���
	static      void*       m_pPosEdit;                  //�༭�û��Ի���
	///////////****����Ϊ�Ի���ָ����******/////////////////
};

#endif