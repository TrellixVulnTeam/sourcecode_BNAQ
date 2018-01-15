#include "stdafx.h"
#include "Sock.h"
#include "BM.h"
#include "Login.h"
#include "EmpInfoView.h"
#include "MtSetProp.h"
#include  "MainFrm.h"
#include  "NotePublic.h"
#include  "MainFormView.h"
#include  "EmpNew.h"
#include  "EmpEdit.h"
#include  "FactoryNew.h"
#include  "FctSet.h"
#include  "FactoryEdit.h"
#include  "CtmNew.h"
#include  "CtmEdit.h"
#include  "CtmInfo.h"
#include  "StoreInfo.h"
#include  "StoreAdd.h"
#include  "StoreOut.h"
#include  "StoreAlertSet.h"
#include  "StoreHistory.h"
#include  "ServReg.h"
#include  "ServModify.h"
#include  "ServiceSearch.h"
#include  "OrderContent.h"
#include  "DealListView.h"
#include  "OrderEdit.h"
#include  "DeductSet.h"
#include  "PwdEdit.h"
#include  "EmpInfoExProp.h"
#include  "EmpInfoProp.h"
#include  "CustomInfoExProp.h"
#include  "CustomInfoProp.h"
#include  "OrderIncompletedProgView.h"
#include  "ProdInfoProp.h"
#include  "ProdInfoExProp.h"
#include  "PerformanceMgView.h"
#include  "PosAdd.h"
#include  "SysPostion.h"
#include  "PosEdit.h"

///////////////��ʼ������ֵ//////////////////////
BOOL      CSock::m_bUpLoading = FALSE;
SOCKET    CSock::m_sockWhole = INVALID_SOCKET;
u_short   CSock::m_port = SERVPORT;
CString   CSock::m_IP = NULL;
BOOL	  CSock::m_bIsConnecting = FALSE;
//VOID*     CSock::m_pVoid = NULL;
REQTYPE   CSock::m_nCurReq = REQNON;        //�Ƿ���ø���m_bReqAvailable����
BOOL      CSock::m_bOnline = FALSE;
CString   CSock::m_DB = NULL;
CString   CSock::m_nameOnline = NULL;
CString   CSock::m_user_pos = NULL;
HANDLE    CSock::m_hThreadFileDL = NULL;
p_Pos_Authority CSock::m_pPosAuthority = NULL;
//BOOL	  CSock::m_bReqAvailable = TRUE;      // ��ʼ������ʱ�����õ�


///////////************/////////////////////
VOID*		CSock::m_pLogin = NULL;
VOID*		CSock::m_pNotePublic = NULL;
VOID*		CSock::m_pMtSetProp = NULL;
VOID*		CSock::m_pEmpInfoView = NULL;
VOID*       CSock::m_pEmpInfoEx = NULL;
VOID*       CSock::m_pEmpInfoIm = NULL;
VOID*       CSock::m_pCtmSubmit = NULL;
VOID*       CSock::m_pProdBatch = NULL;
VOID*	    CSock::m_pMainFormView = NULL;
VOID*		CSock::m_pEmpNew = NULL;
VOID*       CSock::m_pEmpEdit = NULL;
VOID*       CSock::m_pFctNew = NULL;
VOID*		CSock::m_pFctSet = NULL;
VOID*       CSock::m_pFactoryEdit = NULL;
VOID*       CSock::m_pCtmInfo = NULL;
VOID*       CSock::m_pCtmNew = NULL;
VOID*       CSock::m_pCtmEdit = NULL;
VOID*       CSock::m_pStoreInfo = NULL;
VOID*       CSock::m_pStoreAdd = NULL;
VOID*       CSock::m_pStoreOut = NULL;
VOID*       CSock::m_pStoreAlertSet = NULL;
VOID*       CSock::m_pStoreHistory = NULL;
VOID*       CSock::m_pServReg = NULL;
VOID*		CSock::m_pServModify = NULL;
VOID*		CSock::m_pServiceSearch = NULL;
VOID*       CSock::m_pOrderContent = NULL;
VOID*       CSock::m_pDealListView = NULL;
VOID*       CSock::m_pOrderEdit = NULL;
VOID*       CSock::m_pDeductSet = NULL;
VOID*       CSock::m_pPwdEdit = NULL;
VOID*       CSock::m_pCtmEx = NULL;
VOID*       CSock::m_pOrderIncompleteView = NULL;
VOID*       CSock::m_pProdEx = NULL;
VOID*		CSock::m_pEmpPerformance = NULL;
VOID*		CSock::m_pPosAdd = NULL;
VOID*		CSock::m_pSysPostion = NULL;
VOID*		CSock::m_pPosEdit = NULL;
///////////************/////////////////////
CSock::CSock(void)
{
}


CSock::~CSock(void)
{
}

BOOL CSock::StartSendHeartPackage()
{
	/*
	if(!CSock::m_bReqAvailable){
		return FALSE;
	}*/
	if(!m_bIsConnecting)      //����Ѿ��Ͽ�������
	{
		//AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	m_nCurReq = REQKEEPHEART;
	//m_bReqAvailable = FALSE;   //ʹ��ǰ�����ٿ���  ֻ�е������������֮������������
	return TRUE;
}

BOOL CSock::StartRefreshMtTree(VOID* ptr)
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		CMtSetProp* p_dlg = (CMtSetProp*)ptr;
		p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)_T("��������Ͽ����ӣ������µ�¼��"));
		
		return FALSE;
	}
	/*
	if(!CSock::m_bReqAvailable){
		AfxMessageBox(_T("���²�����ʧ��,�����ĵȴ���ǰ������ɣ����ֶ����²������ṹ��"));
		CMtSetProp* p_dlg = (CMtSetProp*)ptr;
		p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}*/
	
	m_pMtSetProp = ptr;
	CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
	p_dlg->SendMessage(WM_STRATREQMT_MtSetProp,0,0);   
	p_dlg->m_nodeName.Empty();
	m_nCurReq = REQ_INIT_MATERIAL_TREE;
	return TRUE;
}


BOOL CSock::StartExpandMtTree(void* ptr)
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		CMtSetProp* p_dlg = (CMtSetProp*)ptr;
		p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	m_pMtSetProp = ptr;
	CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
	p_dlg->SendMessage(WM_STRATREQMT_MtSetProp,0,0);
	m_nCurReq = REQ_Expant_MATERIAL_TREE;
	//m_bReqAvailable = FALSE;   //ʹ��ǰ�����ٿ���  ֻ�е������������֮������������
	return TRUE;
}

BOOL CSock::StartReqMtNodeEdit(VOID * ptr)
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		CString _str = _T("��������Ͽ����ӣ������µ�¼��");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_NODE_EDIT))
	{
		return FALSE;
	}
	
	m_pMtSetProp = ptr;
	CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
	p_dlg->SendMessage(WM_STRATREQMT_MtSetProp,0,0);
	m_nCurReq = REQ_MT_NODE_RENAME;
	//m_bReqAvailable = FALSE;   //ʹ��ǰ�����ٿ���  ֻ�е������������֮������������
	return TRUE;
}

BOOL CSock::StartReqFctEdit(void* ptr)    //���������޸ĳ�������
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		CString _str = _T("��������Ͽ����ӣ������µ�¼��");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_FCT_EDIT))
	{
		return FALSE;
	}
	m_pFactoryEdit = ptr;
	//CFactoryEdit* p_dlg = (CFactoryEdit*)m_pFactoryEdit;
	//p_dlg->SendMessage(WM_STARTTASK_FctEdit,0,0);
	m_nCurReq = REQ_FCT_EDIT_FctEdit;
	return TRUE;
}

BOOL  CSock::StartReqCtmEdit(void* ptr)       //����༭�ͻ�����
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		CString _str = _T("��������Ͽ����ӣ������µ�¼��");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	m_pCtmEdit = ptr;
	//CCtmEdit* p_dlg = (CCtmEdit*)m_pCtmEdit;
	//p_dlg->SendMessage(WM_STARTTASK_CtmEdit,0,0);
	m_nCurReq = REQ_CTM_EDIT_CtmEdit;
	return TRUE;
}

BOOL CSock::StartReqEmpEdit(void* ptr)
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		CString _str = _T("��������Ͽ����ӣ������µ�¼��");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_EMP_EDIT))
	{
		return FALSE;
	}
	m_pEmpEdit = ptr;
	//CEmpEdit* p_dlg = (CEmpEdit*)m_pEmpEdit;
	//p_dlg->SendMessage(WM_STARTTASK_EmpEdit,0,0);
	//p_dlg->DeleteSelNote();
	m_nCurReq = REQ_EMP_EDIT_EmpNew;
	//m_bReqAvailable = FALSE;   //ʹ��ǰ�����ٿ���  ֻ�е������������֮������������
	return TRUE;
}

BOOL CSock::StartReqCtmNew(void* ptr)   //�����½���������
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		CString _str = _T("��������Ͽ����ӣ������µ�¼��");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_CTM_NEW))
	{
		return FALSE;
	}
	m_pCtmNew = ptr;
	//CCtmNew* p_dlg = (CCtmNew*)m_pCtmNew;
	//p_dlg->SendMessage(WM_STARTTASK_CtmNew,0,0);
	m_nCurReq = REQ_CTM_NEW_CtmNew;
	return TRUE;
}

BOOL CSock::StartReqFctNew(void* ptr)   //�����½���������
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		CString _str = _T("��������Ͽ����ӣ������µ�¼��");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_FCT_NEW))
	{
		return FALSE;
	}
	m_pFctNew = ptr;
	//CFactoryNew* p_dlg = (CFactoryNew*)m_pFctNew;
	//p_dlg->SendMessage(WM_STARTTASK_FctNew,0,0);
	m_nCurReq = REQ_FCT_NEW_FctNew;
	return TRUE;
}

BOOL CSock::StartReqEmpNew(void* ptr)
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		CString _str = _T("��������Ͽ����ӣ������µ�¼��");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_EMP_NEW))
	{
		return FALSE;
	}
	m_pEmpNew = ptr;
	//CEmpNew* p_dlg = (CEmpNew*)m_pEmpNew;
	//p_dlg->SendMessage(WM_REQEMPNEWSTART_EmpNew,0,0);
	//p_dlg->DeleteSelNote();
	m_nCurReq = REQ_EMP_NEW_EmpNew;
	return TRUE;
}

BOOL CSock::StartDelFct(void* ptr)    //����ɾ����������
{
	if( !(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		CString _str = _T("��������Ͽ����ӣ������µ�¼��");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_FCT_DEL))
	{
		return FALSE;
	}
	m_pFctSet = ptr;
	CFctSet* p_dlg = (CFctSet*)m_pFctSet;
	p_dlg->SendMessage(WM_STARTTASK_FctEdit,0,0);
	m_nCurReq = REQ_FCT_DEL_FctSet;
	return TRUE;
}

BOOL CSock::StartDelCtm(void* ptr)        //����ɾ���ͻ�����
{
	if( !(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		CString _str = _T("��������Ͽ����ӣ������µ�¼��");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_CTM_DEL))
	{
		return FALSE;
	}
	m_pCtmInfo = ptr;
	//CCtmInfo* p_dlg = (CCtmInfo*)m_pCtmInfo;
	//p_dlg->SendMessage(WM_STARTTASK_CtmInfo,0,0);
	m_nCurReq = REQ_CTM_DEL_CtmInfo;
	return TRUE;
}


BOOL CSock::StartDelEmpInfo(void* ptr)    //����ɾ��Ա������
{
	if( !(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		CString _str = _T("��������Ͽ����ӣ������µ�¼��");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_EMP_DEL))
	{
		return FALSE;
	}
	m_pEmpInfoView = ptr;
	//CEmpInfoView* p_dlg = (CEmpInfoView*)m_pEmpInfoView;
	//p_dlg->SendMessage(WM_STARTTASK_EmpInfoView,0,0);
	m_nCurReq = REQ_EMP_DEL_EmpInfoView;
	return TRUE;
}

BOOL CSock::StartDelNoteMainView(void* ptr)
{
	if( !(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		CString _str = _T("��������Ͽ����ӣ������µ�¼��");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_NOTE_DEL))
	{
		return FALSE;
	}
	m_pMainFormView = ptr;
	CMainFormView* p_dlg = (CMainFormView*)m_pMainFormView;
	//p_dlg->SendMessage(WM_REQSTARTINITNOTE_MainView,0,0);
	//p_dlg->DeleteSelNote();
	m_nCurReq = REQ_DEL_NOTE_MAINVIEW;
	//m_bReqAvailable = FALSE;   //ʹ��ǰ�����ٿ���  ֻ�е������������֮������������
	return TRUE;
}

BOOL CSock::StartReqLoadNote(void* ptr)
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		CString _str = _T("��������Ͽ����ӣ������µ�¼��");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	m_pMainFormView = ptr;
	CMainFormView* p_dlg = (CMainFormView*)m_pMainFormView;
	//p_dlg->SendMessage(WM_REQSTARTINITNOTE_MainView,0,0);
	p_dlg->m_list.DeleteAllItems();
	m_nCurReq = REQ_INIT_NOTE_MAINVIEW;
	//m_bReqAvailable = FALSE;   //ʹ��ǰ�����ٿ���  ֻ�е������������֮������������
	return TRUE;
}

BOOL CSock::StartReqNotePublic(VOID* ptr)
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		CString _str = _T("��������Ͽ����ӣ������µ�¼��");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_NOTE_PUBLIC))
	{
		return FALSE;
	}
	
	m_pNotePublic = ptr;
	CNotePublic* p_dlg = (CNotePublic*)m_pNotePublic;
	//p_dlg->SendMessage(WM_REQNOTEPUBLIC_NotePublic,0,0);
	m_nCurReq = REQ_MAINVIEW_NOTE_PUBLIC;
	//m_bReqAvailable = FALSE;   //ʹ��ǰ�����ٿ���  ֻ�е������������֮������������
	return TRUE;
}

BOOL CSock::StartReqDeleteNode(VOID* ptr)
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		CString _str = _T("��������Ͽ����ӣ������µ�¼��");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_NODE_DEL))
	{
		return FALSE;
	}
	
	m_pMtSetProp = ptr;
	CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
	p_dlg->SendMessage(WM_STRATREQMT_MtSetProp,0,0);
	m_nCurReq = REQ_MT_NODE_DELETE;
	//m_bReqAvailable = FALSE;   //ʹ��ǰ�����ٿ���  ֻ�е������������֮������������
	return TRUE;
}

BOOL CSock::StartReqMtNodeNew(VOID * ptr)
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		CString _str = _T("��������Ͽ����ӣ������µ�¼��");
		AfxMessageBox(_str);
		CMtSetProp* p_dlg = (CMtSetProp*)ptr;
		p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_NODE_NEW))
	{
		return FALSE;
	}
	
	m_pMtSetProp = ptr;
	CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
	p_dlg->SendMessage(WM_STRATREQMT_MtSetProp,0,0);
	m_nCurReq = REQ_MT_NODE_NEW;
	//m_bReqAvailable = FALSE;   //ʹ��ǰ�����ٿ���  ֻ�е������������֮������������
	return TRUE;
}

BOOL CSock::StartLogin(VOID * ptr)
{
	m_pLogin = ptr;
	if(m_sockWhole == INVALID_SOCKET)
	{
		BOOL flag = ConnectServer();		//���ӷ�����
		if(FALSE == flag)
		{
			m_bOnline = FALSE;
			return FALSE;
		}
		AfxBeginThread(SendAndRecvClientThread,NULL);    //�������պͷ��������߳�
		
	}
	m_nCurReq = REQLOGIN;
	return TRUE;
}

BOOL CSock::StartFindServByKeyWord(void* ptr)   //��ȷ����
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	m_pServiceSearch = ptr;
	CServiceSearch* p_dlg = (CServiceSearch*)m_pServiceSearch;
	//p_dlg->SendMessage(WM_STARTTASK_ServiceSearch,0,0);
	p_dlg->m_list.DeleteAllItems();
	m_nCurReq = REQ_SERV_FIND_BY_KEYWORD; 
	return TRUE;
}

BOOL CSock::StartSearchEmpByKeyWord(void* ptr)   //��ȷ����
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_EMP_FIND))
	{
		return FALSE;
	}
	m_pEmpInfoView = ptr;
	CEmpInfoView* p_dlg = (CEmpInfoView*)m_pEmpInfoView;
	p_dlg->SendMessage(WM_STARTTASK_EmpInfoView,0,0);
	p_dlg->m_list.DeleteAllItems();
	m_nCurReq = REQ_EMP_SEARCHBYKEYWORD_EmpInfoView; 
	return TRUE;
}

BOOL CSock::StartLookNoteDetail(void* ptr)    //�鿴֪ͨ��
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	m_pMainFormView = ptr;
	CMainFormView* p_dlg = (CMainFormView*)m_pMainFormView;
	//p_dlg->SendMessage(WM_REQSTARTINITNOTE_MainView,0,0);
	//p_dlg->m_list.DeleteAllItems();
	p_dlg->m_status.SetWindowText(_T("���Եȣ�����������ع�����ϸ��Ϣ"));
	m_nCurReq = REQ_NOTE_DETAIL;
	return TRUE;
}

BOOL CSock::StartReqPosEdit(void* ptr)   //����༭�û�
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_POS_EDIT))
	{
		return FALSE;
	}
	m_pPosEdit = ptr;
	CPosEdit* p_dlg = (CPosEdit*)m_pPosEdit;
	//p_dlg->SendMessage(WM_STARTTASK_PosEdit,0,0);
	p_dlg->m_tip.SetWindowText(_T("���Եȣ�������������û�"));
	m_nCurReq = REQ_EDIT_USER;
	return TRUE;
}

BOOL CSock::StartReqPosAdd(void* ptr)    //�����û�
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_POS_ADD))
	{
		return FALSE;
	}
	m_pPosAdd = ptr;
	CPosAdd* p_dlg = (CPosAdd*)m_pPosAdd;
	//p_dlg->SendMessage(WM_STARTTASK_PosAdd,0,0);
	p_dlg->m_tip.SetWindowText(_T("���Եȣ�������������û�"));
	m_nCurReq = REQ_POS_ADD;
	return TRUE;
}

BOOL CSock::StartReqPswEdit(void* ptr)       //�޸�����
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	m_pPwdEdit = ptr;
	CPwdEdit* p_dlg = (CPwdEdit*)m_pPwdEdit;
	p_dlg->SendMessage(WM_STARTTASK_PwdEdit,0,0);
	//p_dlg->m_list.DeleteAllItems();
	p_dlg->m_tip.SetWindowText(_T("���Եȣ����������޸�����"));
	m_nCurReq = REQ_PSW_EDIT;
	return TRUE;
}

BOOL CSock::StartReqSetDeduct(void* ptr)     //�������
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	m_pDeductSet = ptr;
	CDeductSet* p_dlg = (CDeductSet*)m_pDeductSet;
	p_dlg->SendMessage(WM_STARTTASK_DeductSet,0,0);
	//p_dlg->m_list.DeleteAllItems();
	p_dlg->m_tip.SetWindowText(_T("���Եȣ����ڱ�������"));
	m_nCurReq = REQ_SET_DEDUCT;
	return TRUE;
}

BOOL CSock::StartReqInitDeduct(void* ptr)    //��ʼ���������
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	m_pDeductSet = ptr;
	CDeductSet* p_dlg = (CDeductSet*)m_pDeductSet;
	p_dlg->SendMessage(WM_STARTTASK_DeductSet,0,0);
	//p_dlg->m_list.DeleteAllItems();
	p_dlg->m_tip.SetWindowText(_T("���Եȣ����ڼ��ء�����"));
	m_nCurReq = REQ_INIT_DEDUCT;
	return TRUE;
}

BOOL CSock::StartReqOrderEdit(void* ptr)  //����༭����
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!CSock::IsUserHasAuthority(AUTHORITY_DEAL_EDIT))
	{
		return FALSE;
	}
	m_pOrderEdit = ptr;
	COrderEdit* p_dlg = (COrderEdit*)m_pOrderEdit;
	//p_dlg->SendMessage(WM_STARTTASK_OrderEdit,0,0);
	m_nCurReq = REQ_ORDER_EDIT;
	return TRUE;
}

BOOL CSock::StartReqFindDeal(void* ptr)     //��ʼ��������
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}

	if(!CSock::IsUserHasAuthority(AUTHORITY_DEAL_FIND))
	{
		return FALSE;
	}
	m_pDealListView = ptr;
	CDealListView* p_dlg = (CDealListView*)m_pDealListView;
	//p_dlg->SendMessage(WM_STARTTASK_DealListView,0,0);
	p_dlg->m_list.DeleteAllItems();
	m_nCurReq = REQ_FIND_DEAL;
	return TRUE;
}

BOOL CSock::StartReqOrderNew(void* ptr)    //�½�����
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}

	if(!CSock::IsUserHasAuthority(AUTHORITY_DEAL_NEW))
	{
		return FALSE;
	}
	m_pOrderContent = ptr;
	COrderContent* p_dlg = (COrderContent*)m_pOrderContent;
	//p_dlg->SendMessage(WM_STARTTASK_OrderContent,0,0);
	m_nCurReq = REQ_ORDER_NEW;
	return TRUE;
}

BOOL CSock::StartDLFile(void* ptr)                //��ʼ���������ļ�
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!CSock::IsUserHasAuthority(AUTHORITY_FILE_DOWNLOAD))
	{
		return FALSE;
	}
	m_pDealListView = ptr;
	CDealListView* p_dlg = (CDealListView*)m_pDealListView;
	p_dlg->SendMessage(WM_STRATDLOAD_DealListView,0,0);
	p_dlg->m_tip.SetWindowText(_T("��������"));
	m_nCurReq = REQ_FILE_SIZE;
	return TRUE;
}

BOOL CSock::StartUpLoadFile(void* ptr)           //��ʼ�ϴ��ļ�
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!CSock::IsUserHasAuthority(AUTHORITY_FILE_UPLOAD))
	{
		return FALSE;
	}
	m_pOrderContent = ptr;
	COrderContent* p_dlg = (COrderContent*)m_pOrderContent;
	p_dlg->SendMessage(WM_STARTTASK_OrderContent,0,0);
	p_dlg->m_static_upload_status.SetWindowText(_T("��ʼ�ϴ�"));
	m_nCurReq = REQ_UPLOADFILE;
	return TRUE;
}

BOOL CSock::StartCheckFileExist(void* ptr)    //��������ϴ��ļ��Ƿ����
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	m_pOrderContent = ptr;
	COrderContent* p_dlg = (COrderContent*)m_pOrderContent;
	p_dlg->SendMessage(WM_STARTTASK_OrderContent,0,0);
	p_dlg->m_static_upload_status.SetWindowText(_T("���ڼ�鸽���Ƿ����"));
	m_nCurReq = REQ_CHECK_FILEEXIST;
	return TRUE;
}

BOOL CSock::StartDelDeal(void* ptr)         //����ɾ������
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	m_pDealListView = ptr;
	CDealListView* p_dlg = (CDealListView*)m_pDealListView;
	int index = p_dlg->m_strToDelDeal.Find(',');
	if(_T("ɾ������") == p_dlg->m_strToDelDeal.Mid(0,index))
	{
		if(!CSock::IsUserHasAuthority(AUTHORITY_FILE_DEL))
		{
			return FALSE;
		}
	}else{
		if(!CSock::IsUserHasAuthority(AUTHORITY_DEAL_DEL))
		{
			return FALSE;
		}
	}
	//p_dlg->SendMessage(WM_STARTTASK_DealListView,0,0);
	m_nCurReq = REQ_DEL_DEAL;
	return TRUE;
}

BOOL CSock::StartDelServ(void* ptr)           //����ɾ������
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	m_pServiceSearch = ptr;
	//CServiceSearch* p_dlg = (CServiceSearch*)m_pServiceSearch;
	//p_dlg->SendMessage(WM_STARTTASK_ServiceSearch,0,0);
	m_nCurReq = REQ_SERV_DEL;
	return TRUE;
}

BOOL CSock::StartDelHistory(void* ptr)    //����ɾ����ʷ��¼
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_HISTORY_FIND))
	{
		return FALSE;
	}
	m_pStoreHistory = ptr;
	//CStoreHistory* p_dlg = (CStoreHistory*)m_pStoreHistory;
	//p_dlg->SendMessage(WM_STARTTASK_StoreHistory,0,0);
	m_nCurReq = REQ_DEL_STOREHISTORY;
	return TRUE;
}

BOOL CSock::StartFindAllServ(void* ptr)       //�����ѯ���з�����Ϣ
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	m_pServiceSearch = ptr;
	CServiceSearch* p_dlg = (CServiceSearch*)m_pServiceSearch;
	//p_dlg->SendMessage(WM_STARTTASK_ServiceSearch,0,0);
	p_dlg->m_list.DeleteAllItems();
	m_nCurReq = REQ_SERV_FINDALL;
	return TRUE;
}

BOOL CSock::StartFindAllStoreHistory(void* ptr)   //�����������п���¼
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_HISTORY_FIND))
	{
		return FALSE;
	}
	m_pStoreHistory = ptr;
	CStoreHistory* p_dlg = (CStoreHistory*)m_pStoreHistory;
	//p_dlg->SendMessage(WM_STARTTASK_StoreHistory,0,0);
	p_dlg->m_list.DeleteAllItems();
	m_nCurReq = REQ_FIND_ALL_STOREHISTORY_StoryHistory;
	return TRUE;
}

BOOL CSock::StartReqGoodsAlertNumSet(void* ptr)    //�������ÿ��Ԥ����Ϣ
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!CSock::IsUserHasAuthority(AUTHORITY_ALERT_SET))
	{
		return FALSE;
	}

	m_pStoreAlertSet = ptr;
	//CStoreAlertSet* p_dlg = (CStoreAlertSet*)m_pStoreAlertSet;
	//p_dlg->SendMessage(WM_STARTTASK_StoreAlertSet,0,0);
	m_nCurReq = REQ_GOODS_ALERT_NUM_StoreAlertSet;
	return TRUE;
}

BOOL CSock::StartReqStoreOut(void* ptr)    //�������
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_STORE_OUT))
	{
		return FALSE;
	}
	m_pStoreOut = ptr;
	//CStoreOut* p_dlg = (CStoreOut*)m_pStoreOut;
	//p_dlg->SendMessage(WM_STARTTASK_StoreOut,0,0);
	m_nCurReq = REQ_STORE_OUT_StoreOut;
	return TRUE;
}

BOOL CSock::StartReqServModify(void* ptr)   //�����޸ķ���
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	m_pServModify = ptr;
	//CServModify* p_dlg = (CServModify*)m_pServModify;
	//p_dlg->SendMessage(WM_STARTTASK_ServModify,0,0);
	m_nCurReq = REQ_SERV_MODIFY_ServModify;
	return TRUE;
}

BOOL CSock::StartReqServReg(void* ptr)    //������ӷ���
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	m_pServReg = ptr;
	//CServReg* p_dlg = (CServReg*)m_pServReg;
	//p_dlg->SendMessage(WM_STARTTASK_ServReg,0,0);
	m_nCurReq = REQ_SERV_REG_ServReg;
	return TRUE;
}

BOOL CSock::StartReqStoreAdd(void* ptr)    //������ӿ����Ʒ
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_STORE_ADD))
	{
		return FALSE;
	}
	m_pStoreAdd = ptr;
	CStoreAdd* p_dlg = (CStoreAdd*)m_pStoreAdd;
	//p_dlg->SendMessage(WM_STARTTASK_StoreAdd,0,0);
	m_nCurReq = REQ_STORE_ADD_StoreAdd;
	return TRUE;
}

BOOL CSock::StartFindAllStore(void* ptr)   //��������ȫ�������Ϣ
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_STORE_FIND))
	{
		return FALSE;
	}
	m_pStoreInfo = ptr;
	CStoreInfo* p_dlg = (CStoreInfo*)m_pStoreInfo;
	//p_dlg->SendMessage(WM_STARTTASK_StoreInfo,0,0);
	p_dlg->m_list.DeleteAllItems();
	m_nCurReq = REQ_STORE_FINDALL_StoreInfo;
	return TRUE;
}

BOOL CSock::StartFindAllCtm(void* ptr)
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_CTM_FIND))
	{
		return FALSE;
	}
	m_pCtmInfo = ptr;
	CCtmInfo* p_dlg = (CCtmInfo*)m_pCtmInfo;
	//p_dlg->SendMessage(WM_STARTTASK_CtmInfo,0,0);
	p_dlg->m_list.DeleteAllItems();
	m_nCurReq = REQ_CTM_FINDALL_CtmInfo;
	return TRUE;
}

BOOL CSock::StartFindALLFct(void* ptr)    //����ȫ��������Ϣ����ʾ
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_FCT_FIND))
	{
		return FALSE;
	}
	m_pFctSet = ptr;
	CFctSet* p_dlg = (CFctSet*)m_pFctSet;
	//p_dlg->SendMessage(WM_STARTTASK_FctSet,0,0);
	p_dlg->m_list.DeleteAllItems();
	m_nCurReq = REQ_FCT_FINDALL_FctSet;
	return TRUE;
}

BOOL CSock::StartReqLoadUserAuthority(void* ptr)   //�����û�Ȩ��
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	m_pPosEdit = ptr;
	CPosEdit* p_dlg = (CPosEdit*)m_pPosEdit;
	p_dlg->SendMessage(WM_STARTTASK_PosEdit,0,0);
	m_nCurReq = REQ_LOAD_USER_AUTHORITY;
	return TRUE;
}

BOOL CSock::StartDelUsers(void* ptr)     //��Ҫ��ɾ�����û�
{
	
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_POS_DEL))
	{
		return FALSE;
	}
	m_pSysPostion = ptr;
	//CSysPostion* p_dlg = (CSysPostion*)m_pSysPostion;
	//p_dlg->SendMessage(WM_STARTTASK_SysPostion,0,0);
	m_nCurReq = REQ_DELE_USERS;
	return TRUE;
}

BOOL CSock::StartFindAllUser(void* ptr)
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_POS_FIND))
	{
		return FALSE;
	}
	m_pSysPostion = ptr;
	//CSysPostion* p_dlg = (CSysPostion*)m_pSysPostion;
	//p_dlg->SendMessage(WM_STARTTASK_SysPostion,0,0);
	m_nCurReq = REQ_FINDALL_USERS;
	return TRUE;
}

BOOL CSock::StartFindEmpPerformance(void* ptr)    //��ѯԱ������
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_EMP_PERFERENCE_FIND))
	{
		return FALSE;
	}
	m_pEmpPerformance = ptr;
	//CPerformanceMgView* p_view = (CPerformanceMgView*)m_pEmpPerformance;
	//p_view->SendMessage(WM_STARTTASK_EmpPerformance,0,0);
	m_nCurReq = REQ_EMP_PERFORMANCE;
	return TRUE;
}
BOOL CSock::FindDealIncomplete(void* ptr)      //��ѯ����δ��ɶ���
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!CSock::IsUserHasAuthority(AUTHORITY_DEAL_INCOMPLETE_FIND))
	{
		return FALSE;
	}
	m_pOrderIncompleteView = ptr;
	//COrderIncompletedProgView* p_view = (COrderIncompletedProgView*)m_pOrderIncompleteView;
	//p_view->SendMessage(WM_STARTTASK_OrderIncomplete,0,0);
	m_nCurReq = REQ_FIND_ORDER_INCOMPLETE;
	return TRUE;
}

BOOL CSock::StartReqFindProd(void* ptr)    //����������Ʒ����
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_PROD_EX))
	{
		return FALSE;
	}
	m_pProdEx = ptr;
	CProdInfoExProp* p_dlg = (CProdInfoExProp*)m_pProdEx;
	p_dlg->SendMessage(WM_STARTTASK_ProdInfoExProp,0,0);
	p_dlg->m_prod_batch.Empty();
	//p_dlg->m_listEmp.DeleteAllItems();
	m_nCurReq = REQ_PROD_EX;
	//m_bReqAvailable = FALSE;   //ʹ��ǰ�����ٿ���  ֻ�е������������֮������������
	return TRUE;
}

BOOL CSock::StartFindCtmForEx(void* ptr)     //���������ͻ�����
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_CTM_EX))
	{
		return FALSE;
	}
	m_pCtmEx = ptr;
	CCustomInfoExProp* p_dlg = (CCustomInfoExProp*)m_pCtmEx;
	p_dlg->SendMessage(WM_STARTTASK_CustomExProp,0,0);
	p_dlg->m_ctm_batch_from_db.Empty();
	//p_dlg->m_listEmp.DeleteAllItems();
	m_nCurReq = REQ_CTM_EX;
	//m_bReqAvailable = FALSE;   //ʹ��ǰ�����ٿ���  ֻ�е������������֮������������
	return TRUE;
}

BOOL CSock::StartUpdateOrderIncomplete(void* ptr)   //��������δ��ɶ���
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}

	if(!CSock::IsUserHasAuthority(AUTHORITY_DEAL_INCOMPLETE_EDIT))
	{
		return FALSE;
	}
	m_pOrderIncompleteView = ptr;
	//COrderIncompletedProgView* p_dlg = (COrderIncompletedProgView*)m_pOrderIncompleteView;
	//p_dlg->SendMessage(WM_STARTTASK_OrderIncomplete,0,0);
	m_nCurReq = REQ_UPDATE_ORDER_BATCH;
	return TRUE;
}

BOOL CSock::StartSubmitProd(void* ptr)    //�����ύ��Ʒ����
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_PROD_IM))
	{
		return FALSE;
	}
	m_pProdBatch = ptr;
	CProdInfoProp* p_dlg = (CProdInfoProp*)m_pProdBatch;
	p_dlg->SendMessage(WM_STARTTASK_ProdIm,0,0);
	m_nCurReq = REQ_UPDATE_PROD_BATCH;
	return TRUE;
}

BOOL CSock::StartSubmitCtmInfo(void* ptr)     //�����ύ�ͻ����ݵ����ݿ�
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_CTM_IM))
	{
		return FALSE;
	}
	m_pCtmSubmit = ptr;
	CCustomInfoProp* p_dlg = (CCustomInfoProp*)m_pCtmSubmit;
	p_dlg->SendMessage(WM_STARTTASK_CtmIm,0,0);
	m_nCurReq = REQ_CTM_IM;
	return TRUE;
}

BOOL CSock::StartImportEmpInfo(void* ptr)     //�����ύԱ����Ϣ�����ݿ�
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_EMP_IM))
	{
		return FALSE;
	}
	m_pEmpInfoIm = ptr;
	CEmpInfoProp* p_dlg = (CEmpInfoProp*)m_pEmpInfoIm;
	p_dlg->SendMessage(WM_STARTTASK_EmpInfoProp,0,0);
	//p_dlg->m_listEmp.DeleteAllItems();
	m_nCurReq = REQ_EMP_IM;
	//m_bReqAvailable = FALSE;   //ʹ��ǰ�����ٿ���  ֻ�е������������֮������������
	return TRUE;
}

BOOL  CSock::StartReqFindEmpForEx(void* ptr)          //Ϊ�˵������ݶ���ѯԱ������
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	if(!IsUserHasAuthority(AUTHORITY_EMP_EX))
	{
		return FALSE;
	}
	m_pEmpInfoEx = ptr;
	CEmpInfoExProp* p_dlg = (CEmpInfoExProp*)m_pEmpInfoEx;
	p_dlg->SendMessage(WM_STARTTASK_EmpInfoExProp,0,0);
	p_dlg->m_list.DeleteAllItems();
	m_nCurReq = REQ_EMP_EX;
	//m_bReqAvailable = FALSE;   //ʹ��ǰ�����ٿ���  ֻ�е������������֮������������
	return TRUE;
}

BOOL CSock::StartSearchAllEmpInfo(VOID* ptr)		//����ȫ��ְԱ��Ϣ����ʾ
{
	if(!(m_bIsConnecting && !m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("��������Ͽ����ӣ������µ�¼��"));
		return FALSE;
	}
	m_pEmpInfoView = ptr;
	CEmpInfoView* p_dlg = (CEmpInfoView*)m_pEmpInfoView;
	//p_dlg->SendMessage(WM_STARTTASK_EmpInfoView,0,0);
	p_dlg->m_list.DeleteAllItems();
	m_nCurReq = REQSEARCHALLEMPINFO;
	//m_bReqAvailable = FALSE;   //ʹ��ǰ�����ٿ���  ֻ�е������������֮������������
	return TRUE;
}

void CSock::InitSocket()
{
	WORD	wVersionRequested;			//����socket�汾
	WSADATA	wsaData;					//wsaData�ṹ
	int		nErrCode;					//����ֵ
	
	wVersionRequested = MAKEWORD( 2, 2 );//����windows Sockets 2.2�汾	
	nErrCode = WSAStartup( wVersionRequested, &wsaData );
	if ( 0 != nErrCode )
	{
		return;
	}
	
	//�����׽���
	m_sockWhole = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_sockWhole)
	{
		AfxMessageBox(_T("�����׽���ʧ��"));
		return;
	}
	
	//����ϵͳ��������ΪĬ�ϵ�BUF_TIMES��
	unsigned int uiRcvBuf;
	int uiRcvBufLen = sizeof(uiRcvBuf);
	nErrCode= getsockopt(m_sockWhole, SOL_SOCKET, SO_RCVBUF,(char*)&uiRcvBuf, &uiRcvBufLen);
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("��ȡϵͳĬ�Ϸ������ݻ�����ʧ�ܣ�"));
		return;
	}
	uiRcvBuf *= BUF_TIMES;
	nErrCode = setsockopt(m_sockWhole, SOL_SOCKET, SO_RCVBUF,(char*)&uiRcvBuf, uiRcvBufLen);
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("�޸�ϵͳ�������ݻ�����ʧ�ܣ�"));
		return;
	}

	//�������ϵͳ�������ݻ������Ƿ�ɹ�
	unsigned int uiNewRcvBuf;
	getsockopt(m_sockWhole, SOL_SOCKET, SO_RCVBUF,(char*)&uiNewRcvBuf, &uiRcvBufLen);
	if (SOCKET_ERROR == nErrCode || uiNewRcvBuf != uiRcvBuf)
	{
		AfxMessageBox(_T("�޸�ϵͳ�������ݻ�����ʧ�ܣ�"));;
		return ;
	}

	return;
}

BOOL CSock::ConnectServer()			//������ӷ����������� �ڵ�¼��ʱ�����
{
	if(m_pLogin != NULL){
		((CLogin *)m_pLogin)->m_status.SetWindowText(_T("��ʼ���ӷ�����"));
	}
	//��÷�������IP��ַ
	USES_CONVERSION;
	char *pIPTemp = T2A(m_IP);		//��CString���͵�IP��ַת��Ϊcharָ����ָ������	
	long IP = ntohl((u_long)inet_addr(pIPTemp));
	//ntohl()�ǽ�һ���޷��ų��������������ֽ�˳��ת��Ϊ�����ֽ�˳��
	if(IP==INADDR_NONE)
	{
		AfxMessageBox(_T("IP��ַ���Ϸ�������������"));
		if(m_pLogin != NULL){
			((CLogin *)m_pLogin)->SendMessage(WM_CURSORTONORMAL,0,0);
		}
		return FALSE;
	}

	//�������׽��ֵ�ַ
	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;

	servAddr.sin_addr.S_un.S_addr = htonl(IP);
	servAddr.sin_port = htons(m_port);

	//���ӷ�����
	CBMApp* p_App = (CBMApp *)AfxGetApp();
	m_sockWhole = p_App->m_sHost;
	if(m_sockWhole == INVALID_SOCKET)
	{
		InitSocket();
		if(m_sockWhole == INVALID_SOCKET)
		{
			AfxMessageBox(_T("��ó�ʼ�����׽���ʧ�ܣ�"));
			if(m_pLogin != NULL){
				((CLogin *)m_pLogin)->SendMessage(WM_LOGINFAIL,0,0);
				((CLogin *)m_pLogin)->SendMessage(WM_CURSORTONORMAL,0,0);
			}
			m_sockWhole = INVALID_SOCKET;		
			return FALSE;
		}
	}
	int nErrCode = connect(m_sockWhole,(sockaddr*)&servAddr, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == nErrCode)
	{
		if(NULL != m_pLogin){
			((CLogin *)m_pLogin)->m_status.SetWindowText(_T("���ӷ�����ʧ�ܣ�����IP��ַ�Ͷ˿��Ƿ���ȷ"));
			((CLogin *)m_pLogin)->SendMessage(WM_CURSORTONORMAL,0,0);
			((CLogin *)m_pLogin)->SendMessage(WM_LOGINFAIL,0,0);
		}
		m_sockWhole = INVALID_SOCKET;
		AfxMessageBox(_T("���ӷ�����ʧ�ܣ�"),MB_OK, 0);
		return FALSE;
	}
	if(NULL != m_pLogin){
		((CLogin *)m_pLogin)->m_status.SetWindowText(_T("���ӷ������ɹ�"));
	}
	m_bIsConnecting = TRUE;
	return TRUE;
}


UINT CSock::SendAndRecvClientThread(LPVOID pParam)		//���պͷ��������߳�
{
	SOCKET	sockClient = m_sockWhole;//�ͻ����׽���	
	if(INVALID_SOCKET == sockClient)
	{
		return 0;
	}
	FD_SET writefd;	//��д����
	FD_SET readfd;	//�ɶ�����

	while(m_bIsConnecting)
	{
		FD_ZERO(&writefd);		//����
		FD_ZERO(&readfd);		//����
		FD_SET(sockClient, &writefd);//��ӵ���д����
		FD_SET(sockClient, &readfd);	//��ӵ��ɶ�����
		
		int reVal = 0;
		reVal = select(0, &readfd, &writefd, NULL, NULL);//�ȴ��׽�����������
		if (SOCKET_ERROR == reVal)
		{
			AfxMessageBox(_T("select����"));
			return 0;
		}else if ( reVal > 0)
		{
			if (FD_ISSET(sockClient, &writefd))			//�����д������
			{
				if (FALSE == SendReq())	//��������
				{
					m_sockWhole = INVALID_SOCKET;
					AfxMessageBox(_T("��������ʧ��,�����µ�¼��"));
					m_bIsConnecting = FALSE;     //���ӶϿ� ���û����µ�¼
					m_bOnline = FALSE;        // �Ͽ��ߺ� ���Ӳ�����
					m_nameOnline.Empty();     //�Ͽ����Ӻ� ������ߵ��û���
					((CBMApp*)AfxGetApp())->m_sHost = INVALID_SOCKET;   //�����������³�ʼ��socket
					return 0;
				}			
			}			
			
			if (FD_ISSET(sockClient, &readfd))			//����ɶ�������
			{
				if(FALSE == RecvData())//��������
				{
					//AfxMessageBox(_T("����Ŀ¼��Ϣʧ�ܣ�"));
					m_sockWhole = INVALID_SOCKET;
					AfxMessageBox(_T("��������ʧ��,�����µ�¼��"));
					m_bIsConnecting = FALSE;   //���ӶϿ� ���û����µ�¼
					m_bOnline = FALSE;         // �Ͽ��ߺ� ���Ӳ�����
					m_nameOnline.Empty();     //�Ͽ����Ӻ� ������ߵ��û���
					//m_bReqAvailable = TRUE;   //ʹ���������
					((CBMApp*)AfxGetApp())->m_sHost = INVALID_SOCKET;  //�����������³�ʼ��socket
					return 0;
				}
			}			
		}
		Sleep(THREAD_SLEEP);		
	}
	
	return 0;
}

BOOL CSock::SendReq()
{
	BOOL reVal = TRUE;			//����ֵ
	switch(m_nCurReq)	//��������
	{
	case REQLOGIN:
		{
			reVal = ReqLogin();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_LOAD_USER_AUTHORITY:
		{
			reVal = ReqLoadUserAuthority();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_DELE_USERS:
		{
			reVal = ReqDelUsers();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_FINDALL_USERS:
		{
			reVal = ReqFindAllUsers();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_EMP_PERFORMANCE:
		{
			reVal = ReqFindEmpPerformance();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_FIND_ORDER_INCOMPLETE:
		{
			reVal = ReqFindOrderIncomplete();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_PROD_EX:
		{
			reVal = ReqProdForEx();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_CTM_EX:
		{
			reVal = ReqCtmForEx();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_UPDATE_PROD_BATCH:
		{
			reVal = ReqSubmitProdInfo();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_CTM_IM:
		{
			reVal = ReqSubmitCtmInfo();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_UPDATE_ORDER_BATCH:
		{
			reVal = ReqUpdateOrderIncomplete();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_EMP_IM:
		{
			reVal = ReqSubmitEmpInfo();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_EMP_EX:
		{
			reVal = ReqSearchAllEmpInfoForEx();
			m_nCurReq = REQNON;
			break;
		}
	case REQSEARCHALLEMPINFO:
		{
			reVal = ReqSearchAllEmpInfo();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_NOTE_DETAIL:
		{
			reVal = ReqDetailNote();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_EDIT_USER:
		{
			reVal = ReqPosEdit();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_POS_ADD:
		{
			reVal = ReqPosAdd();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_PSW_EDIT:
		{
			reVal = ReqPswEdit();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_SET_DEDUCT:
		{
			reVal = ReqSetDeduct();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_INIT_DEDUCT:
		{
			reVal = ReqInitDeduct();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_ORDER_EDIT:
		{
			reVal = ReqOrderEdit();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_FIND_DEAL:
		{
			reVal = ReqFindDeal();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_ORDER_NEW:
		{
			reVal = ReqOrderNew();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_FILE_SIZE:
		{
			reVal = ReqDLFile();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_UPLOADFILE:
		{
			reVal = ReqUpLoadFile();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_CHECK_FILEEXIST:
		{
			reVal = ReqCheckFileExist();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_DEL_DEAL:
		{
			reVal = ReqDelDeal();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_SERV_DEL:
		{
			reVal = ReqDelServ();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_DEL_STOREHISTORY:
		{
			reVal = ReqDelStoreHistory();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_SERV_FINDALL:
		{
			reVal = ReqFindAllServ();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_FIND_ALL_STOREHISTORY_StoryHistory:
		{
			reVal = ReqFindAllStoreHistory();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_GOODS_ALERT_NUM_StoreAlertSet:
		{
			reVal = ReqStoreAlertNumSet();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_STORE_OUT_StoreOut:
		{
			reVal = ReqOutStore();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_SERV_MODIFY_ServModify:
		{
			reVal = ReqModifyServ();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_SERV_REG_ServReg:
		{
			reVal = ReqRegServ();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_STORE_ADD_StoreAdd:
		{
			reVal = ReqAddStore();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_STORE_FINDALL_StoreInfo:
		{
			reVal = ReqFindAllStoreInfo();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_CTM_FINDALL_CtmInfo:
		{
			reVal = ReqFindAllCtmInfo();
			m_nCurReq = REQNON;
			break;
		} 
	case REQ_FCT_FINDALL_FctSet:
		{
			reVal = ReqSearchAllFctInfo();
			m_nCurReq = REQNON;
			break;
		}
	case REQKEEPHEART:
		{
			reVal = ReqKeepHeart();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_INIT_MATERIAL_TREE:
		{
			reVal = ReqInitMtTree();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_Expant_MATERIAL_TREE:
		{
			reVal = ReqExpandMtTree();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_MT_NODE_NEW:
		{
			reVal = ReqMtNodeNew();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_MT_NODE_RENAME:
		{
			reVal = ReqMtNodeRename();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_MT_NODE_DELETE:
		{
			reVal = ReqMtNodeDelete();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_MAINVIEW_NOTE_PUBLIC:
		{
			reVal = ReqMainViewNotePublic();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_INIT_NOTE_MAINVIEW:
		{
			reVal = ReqMainViewInitNote();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_DEL_NOTE_MAINVIEW:
		{
			reVal = ReqMainViewDeleteSelNote();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_FCT_DEL_FctSet:
		{
			reVal = ReqDeleteSelFct_FctSet();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_CTM_DEL_CtmInfo:
		{
			reVal = ReqDeleteSelCtm();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_EMP_DEL_EmpInfoView:
		{
			reVal = ReqDeleteSelEmpInfo_EmpInfoView();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_EMP_NEW_EmpNew:
		{
			reVal = ReqEmpNew();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_CTM_NEW_CtmNew:
		{
			reVal = ReqCtmNew();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_FCT_NEW_FctNew:
		{
			reVal = ReqFctNew();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_CTM_EDIT_CtmEdit:
		{
			reVal = ReqCtmEdit();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_EMP_EDIT_EmpNew:
		{
			reVal = ReqEmpEdit();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_FCT_EDIT_FctEdit:
		{
			reVal = ReqFctEdit();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_SERV_FIND_BY_KEYWORD:
		{
			reVal = FindServByKeyWord();
			m_nCurReq = REQNON;
			break;
		}
	case REQ_EMP_SEARCHBYKEYWORD_EmpInfoView:
		{
			reVal = SearchEmpByKeyWord();
			m_nCurReq = REQNON;
			break;
		}
	default:
		break;
	}
	return reVal;
}


BOOL CSock::RecvData()
{
	BOOL	reVal = TRUE;	//����ֵ	
	int		nErrCode;		//����ֵ
	//��ȡ��ͷ
	hdr header;
	nErrCode = recv(m_sockWhole,(char*)&header, HEADLEN,0);		
	if (SOCKET_ERROR == nErrCode || 0 == nErrCode)//�������ر���
	{
		AfxMessageBox(_T("�������رգ�"));
		reVal = FALSE;	
		return reVal;
	}	
	
	//��ȡ����
	int nDataLen = header.len - HEADLEN;//����ĳ���	
	switch(header.type)					//�������ݰ������ͷ��� �ٶ�ȡ����
	{
	case REPLY_LOGIN:				//�յ��Ļظ���Ϣ ��¼�Ƿ�ɹ�
		{
			reVal = RecvReplyOfLoginIn(nDataLen);
			break;
		}
	case REPLY_EMP_SEARCHBYKEYWORD_EmpInfoView:
	case REPLY_SEARCH_ALL_EMP_INFO:
		{
			reVal = RecvReplyOfSearchAllEmpInfo(nDataLen);
			break;
		}
	case REPLY_EMP_INFO_FOR_EX:
		{
			reVal = RecvReplyOfSearchAllEmpInfoForEx(nDataLen);
			break;
		}
	case REPLY_STORE_FINDALL_StoreInfo:
		{
			reVal = RecvReplyOfFindAllStore(nDataLen);
			break;
		}
	case REPLY_FIND_ORDER_INCOMPLETE:
		{
			reVal = RecvReplyFindOrderIncomplete(nDataLen);
			break;
		}
	case REPLY_POS_FIND_ALL:
		{
			reVal = RecvReplyOfFindAllUsers(nDataLen);
			break;
		}
	case REPLY_FIND_EMP_PERPFORMANCE:
		{
			reVal = RecvReplyOfFindEmpPerformance(nDataLen);
			break;
		}
	case REPLY_PROD_EX:
		{
			reVal = RecvReplyOfProdEx(nDataLen);
			break;
		}
	case REPLY_CTM_EX:
		{
			reVal = RecvReplyOfCtmEx(nDataLen);
			break;
		}
	case REPLY_CTM_FINDALL_CtmInfo:
		{
			reVal = RecvReplyOfFindAllCtm(nDataLen);
			break;
		}
	case REPLY_FCT_FIND_ALL:
		{
			reVal = RecvReplyOfSearchAllFctInfo(nDataLen);
			break;
		}
	case REPLY_HEART_PACKAGE:
		{
			reVal = RecvReplyOfKeepHeart(nDataLen);
			break;
		}
	case REPLY_INIT_MATERIAL_TREE:
		{
			reVal = RecvReplyOfInitMtTree(nDataLen);
			break;
		}
	case REPLY_MT_NODE_NEW:
		{
			reVal = RecvReplyOfMtNodeNew(nDataLen);
			break;
		}
	case REPLY_MT_NODE_RENAME:
		{
			reVal = RecvReplyOfMtNodeRename(nDataLen);
			break;
		}
	case REPLY_MT_NODE_DELETE:
		{
			reVal = RecvReplyOfMtNodeDelete(nDataLen);
			break;
		}
	case REPLY_NOTE_PUBLIC_MainView:
		{
			reVal = RecvReplyOfNotePublicMainView(nDataLen);
			break;
		}
	case REPLY_INIT_NOTE_MainView:
		{
			reVal = RecvReplyOfInitNote(nDataLen);
			break;
		}
	
	case REPLY_NOTE_DETAIL:
		{
			reVal = RecvReplyOfDetailNote(nDataLen);
			break;
		}
	case REPLY_DEL_NOTE_MainVIew:
		{
			reVal = RecvReplyOfDeletNote(nDataLen);
			break;
		}
	case REPLY_EMP_NEW_EmpNew:
		{
			reVal = RecvReplyOfEmpNew(nDataLen);
			break;
		}
	case REPLY_STORE_OUT_StoreOut:
		{
			reVal = RecvReplyOfOutStore(nDataLen);
			break;
		}
	case REPLY_SERV_FIND_BY_KEYWORD:
	case REPLY_SERV_FINDALL:
		{
			reVal = RecvReplyOfServFindAll(nDataLen);
			break;
		}
	case REPLY_STOREHISTORY_FINDALL:
		{
			reVal = RecvReplyOfStoreFindAll(nDataLen);
			break;
		}
	case REPLY_STORE_GOODS_ALERT_SET:
		{
			reVal = RecvReplyOfStoreAlertSet(nDataLen);
			break;
		}
	case REPLY_DEDUCT_INIT:
		{
			reVal = RecvReplyOfInitDeduct(nDataLen);
			break;
		}
	case REPLY_ORDER_FIND_DealListView:
		{
			reVal = RecvReplyOfOrderFind(nDataLen);
			break;
		}
	case REPLY_DEDUCT_SET:
		{
			reVal = RecvReplyOfDeductSet(nDataLen);
			break;
		}
	case REPLY_ORDER_EDIT_OrderEdit:
		{
			reVal = RecvReplyOfOrderEdit(nDataLen);
			break;
		}
	case REPLY_ORDER_NEW_OrderContent:
		{
			reVal = RecvReplyOfOrderNew(nDataLen);
			break;
		}
	case REPLY_SERV_REG_ServReg:
		{
			reVal = RecvReplyOfRegServ(nDataLen);
			break;
		}
	case REPLY_STORE_ADD_StoreAdd:
		{
			reVal = RecvReplyOfAddStore(nDataLen);
			break;
		}
	case REPLY_CTM_NEW_CtmNew:
		{
			reVal = RecvReplyOfCtmNew(nDataLen);
			break;
		}
	case REPLY_FCT_NEW_FctNew:
		{
			reVal = RecvReplyOfFctNew(nDataLen);
			break;
		}
	case REPLY_SERV_MODIFY_ServModify:
		{
			reVal = RecvReplyOfServModify(nDataLen);
			break;
		}
	case REPLY_CTM_EDIT_CtmEdit:
		{
			reVal = RecvReplyOfCtmEdit(nDataLen);
			break;
		}
	case REPLY_FCT_EDIT_FactoryEdit:
		{
			reVal = RecvReplyOfFctEdit(nDataLen);
			break;
		}

	case REPLY_EMP_EDIT_EmpEdit:
		{
			reVal = RecvReplyOfEmpEdit(nDataLen);
			break;
		}
	case REPLY_FILE_SIZE:
		{
			RecvReplyOfDLFile(header.flen,header.fname);
			break;
		}
	case REPLY_FILE_UPLOAD:
		{
			reVal = RecvReplyOfUploadFile(nDataLen);
			break;
		}
	case REPLY_FILE_DLINFO:
		{
			reVal = RecvReplyOfFileDLInfo(nDataLen);
			break;
		}
	case REPLY_CHECK_FILE_EXIST:
		{
			reVal = RecvReplyOfCheckFile(nDataLen);
			break;
		}
	case REPLY_EMP_INFO_IMPORT:
		{
			reVal = RecvReplyOfEmpInfoIm(nDataLen);
			break;
		}
	case REPLY_UPDATE_ORDER_BATCH:
		{
			reVal = RecvReplyOfUpdateOrderBatch(nDataLen);
			break;
		}
	case REPLY_CTM_IM:
		{
			reVal = RecvReplyOfCtmInfoIm(nDataLen);
			break;
		}
	case REPLY_PROD_IM:
		{
			reVal = RecvReplyOfProdInfoIm(nDataLen);
			break;
		}
	case REPLY_PWD_EDIT:
		{
			reVal = RecvReplyOfPswEdit(nDataLen);
			break;
		}
	case REPLY_POS_AUTHORITY:
		{
			reVal = RecvReplyOfPosAuthority(nDataLen);
			break;
		}
	case REPLY_POS_EDIT:
		{
			reVal = RecvReplyOfPosEdit(nDataLen);
			break;
		}
	case REPLY_POS_ADD:
		{
			reVal = RecvReplyOfPosAdd(nDataLen);
			break;
		}
	case REPLY_USER_INIT:
		{
			reVal = RecvReplyOfUsersInit(nDataLen);
			break;
		}
	case REPLY_POS_DEL:
		{
			reVal = RecvReplyOfUsersDel(nDataLen);
			break;
		}
	case REPLY_REQ_DEL_DEAL:
		{
			reVal = RecvReplyOfDealDel(nDataLen);
			break;
		}
	case REPLY_SERV_DEL:
		{
			reVal = RecvReplyOfServDel(nDataLen);
			break;
		}
	case REPLY_STORYHISTORY_DEL:
		{
			reVal = RecvReplyOfStoreHistoryDel(nDataLen);
			break;
		}
	case REPLY_CTM_DEL_CtmInfo:
		{
			reVal = RecvReplyOfCtmDel(nDataLen);
			break;
		}
	case REPLY_EMP_DEL_EmpInfoView:
		{
			reVal = RecvReplyOfEmpDel(nDataLen);
			break;
		}
	case REPLY_FCT_DEL_FctSet:
		{
			reVal = RecvReplyOfFctDel(nDataLen);
			break;
		}
	default:
		break;						
	}	
	if(FALSE == reVal)
	{
		AfxMessageBox(_T("�������Է������Ļظ���Ϣʧ��,��������Ͽ����ӣ������µ�¼��"));
	}
	return reVal;	
}

BOOL CSock::ReqLogin()			//������������û���������
{
	int nflag;
	hdr header;
	CLogin* plg;
	if(NULL != m_pLogin)
	{
		plg = (CLogin*) m_pLogin;
	}else{
		return TRUE;
	}
	loginInfo userInfo;
	memset(&header, 0, sizeof(header));
	memset(&userInfo, 0, sizeof(userInfo));
	userInfo = plg->m_loginInfo_Stru;
	header.type = LOGIN;
	header.len = HEADLEN + sizeof(loginInfo);
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���͵�¼��Ϣʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char *)&userInfo,sizeof(loginInfo),0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���͵�¼��Ϣʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	return TRUE;
}

BOOL CSock::FindServByKeyWord()    //���ݹؼ��ֲ��ҷ���
{
	CServiceSearch* p_dlg = (CServiceSearch*)m_pServiceSearch;
	char buff[200] = {0};
	USES_CONVERSION;
	char *p = T2A(p_dlg->m_searchByKeyWord);
	p_dlg->m_searchByKeyWord.Empty();
	strcpy_s(buff,p);
	int nflag;
	hdr header;
	header.type = SERV_FIND_BY_KEYWORD;
	header.len = HEADLEN + sizeof(buff);
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����������������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)buff,sizeof(buff),0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����������������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	p_dlg->m_tip.SetWindowText(_T("�����������������ɹ����ȴ���������Ӧ"));
	UpdateOperationStatus(_T("�����������������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::SearchEmpByKeyWord()    //���ݹؼ�������Ա����Ϣ
{
	if(m_pEmpInfoView == NULL)
	{
		UpdateOperationStatus(_T("��ȷ����Ա��������ȡ��"));
		return TRUE;
	}
	CEmpInfoView* p_dlg = (CEmpInfoView*)m_pEmpInfoView;
	char buff[200] = {0};
	USES_CONVERSION;
	char *p = T2A(p_dlg->m_searchByKeyWord);
	strcpy_s(buff,p);
	int nflag;
	hdr header;
	header.type = EMP_SEARCHBYKEYWORD_EmpInfoView;
	header.len = HEADLEN + sizeof(buff);
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���;�ȷ����Ա��������ʧ�ܣ������Ի����µ�¼"));
		UpdateOperationStatus(_T("���;�ȷ����Ա��������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)buff,sizeof(buff),0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���;�ȷ����Ա��������ʧ�ܣ������Ի����µ�¼"));
		UpdateOperationStatus(_T("���;�ȷ����Ա��������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("���;�ȷ����Ա��������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqDetailNote()    //������ҹ������ϸ��Ϣ
{
	WT;
	CMainFormView* p_dlg = (CMainFormView*)m_pMainFormView;
	char buff[MAX_PATH] = {0};
	strcpy_s(buff,T2A(p_dlg->m_note_to_find));
	int len = sizeof(buff);
	int nflag;
	hdr header;
	header.type = NOTE_DETAIL;
	header.len = HEADLEN + len;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���Ͳ鿴���������ʧ�ܣ������Ի����µ�¼"));
		UpdateOperationStatus(_T("���Ͳ鿴���������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)buff,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���Ͳ鿴���������ʧ�ܣ������Ի����µ�¼"));
		UpdateOperationStatus(_T("���Ͳ鿴���������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("���Ͳ鿴���������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqPosEdit()    //����༭�ͻ�
{
	WT;
	CPosEdit* p_dlg = (CPosEdit*)m_pPosEdit;
	if(p_dlg == NULL)
	{
		return TRUE;
	}
	char buff[1024] = {0};
	strcpy_s(buff,T2A(p_dlg->m_str_pos_edit));
	p_dlg->m_str_pos_edit.Empty();
	int len = sizeof(buff);
	hdr header;
	header.type = POS_EDIT;
	header.len = HEADLEN + len;
	CString _err = _T("���ͱ༭�û�������ʧ�ܣ������Ի����µ�¼");
	if(!SendDataToServer(m_sockWhole,(char*)&header,_err))
	{
		return FALSE;
	}
	if(!SendDataToServer(m_sockWhole,buff,_err,len))
	{
		return FALSE;
	}
	UpdateOperationStatus(_T("���ͱ༭�û�������ɹ����ȴ���������Ӧ"));
	p_dlg->m_tip.SetWindowText(_T("���ͱ༭�û�������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqPosAdd()    //��������û�
{
	WT;
	CPosAdd* p_dlg = (CPosAdd*)m_pPosAdd;
	if(p_dlg == NULL)
	{
		return TRUE;
	}
	char buff[1024] = {0};
	strcpy_s(buff,T2A(p_dlg->m_str_pos_new));
	p_dlg->m_str_pos_new.Empty();
	int len = sizeof(buff);
	int nflag;
	hdr header;
	header.type = POS_ADD;
	header.len = HEADLEN + len;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���ʹ������û�������ʧ�ܣ������Ի����µ�¼"));
		UpdateOperationStatus(_T("���ʹ������û�������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)buff,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���ʹ������û�������ʧ�ܣ������Ի����µ�¼"));
		UpdateOperationStatus(_T("���ʹ������û�������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("���ʹ������û�������ɹ����ȴ���������Ӧ"));
	p_dlg->m_tip.SetWindowText(_T("���ʹ������û�������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqPswEdit()       //�����޸�����
{
	WT;
	CPwdEdit* p_dlg = (CPwdEdit*)m_pPwdEdit;
	if(p_dlg == NULL)
	{
		return TRUE;
	}
	char buff[MAX_PATH] = {0};
	strcpy_s(buff,T2A(p_dlg->m_strPswEdit));
	int len = sizeof(buff);
	int nflag;
	hdr header;
	header.type = PWD_EDIT;
	header.len = HEADLEN + len;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����޸����������ʧ�ܣ������Ի����µ�¼"));
		UpdateOperationStatus(_T("�����޸����������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)buff,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����޸����������ʧ�ܣ������Ի����µ�¼"));
		UpdateOperationStatus(_T("�����޸����������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("�����޸����������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqSetDeduct()     //�����������
{
	CDeductSet* p_dlg = (CDeductSet*)m_pDeductSet;
	if(p_dlg == NULL)
	{
		return TRUE;
	}
	DeductInfo info =  p_dlg->m_deductInfo;
	int len = sizeof(info);
	int nflag;
	hdr header;
	header.type = DEDUCT_SET;
	header.len = HEADLEN + len;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����������ɵ�����ʧ�ܣ������Ի����µ�¼"));
		UpdateOperationStatus(_T("����������ɵ�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)&info,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����������ɵ�����ʧ�ܣ������Ի����µ�¼"));
		UpdateOperationStatus(_T("����������ɵ�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("����������ɵ�����ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqInitDeduct()     //�����ʼ�����
{
	int nflag;
	hdr header;
	header.type = DEDUCT_INIT;
	header.len = HEADLEN;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���ͳ�ʼ�����õ�����ʧ�ܣ������Ի����µ�¼"));
		UpdateOperationStatus(_T("���ͳ�ʼ�����õ�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("���ͳ�ʼ�����õ�����ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqOrderEdit()    //����༭����
{
	OrderInfo info;
	int len = sizeof(info);
	memset(&info,0,len);
	COrderEdit* p_dlg = (COrderEdit*)m_pOrderEdit;
	int nflag;
	info = p_dlg->m_orderInfo_edit;
	hdr header;
	header.type = ORDER_EDIT_OrderEdit;
	header.len = HEADLEN + len;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����������༭��������ʧ�ܣ������Ի����µ�¼"));
		UpdateOperationStatus(_T("�����������༭��������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)&info,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����������༭��������ʧ�ܣ������Ի����µ�¼"));
		UpdateOperationStatus(_T("�����������༭��������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	p_dlg->m_tip.SetWindowText(_T("����༭�������ͳɹ����ȴ���������Ӧ"));
	UpdateOperationStatus(_T("����༭�������ͳɹ����ȴ���������Ӧ"));
	return TRUE; 
}

BOOL CSock::ReqFindDeal()     //������Ҷ���
{
	WT;
	char buff[MAX_PATH] = {0};
	CDealListView* p_dlg = (CDealListView*)m_pDealListView;
	int nflag;
	strcpy_s(buff,T2A(p_dlg->m_search_Keyword));
	int len = sizeof(buff);
	hdr header;
	header.type = ORDER_FIND_DealListView;
	header.len = HEADLEN + len;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����������������������ʧ�ܣ������Ի����µ�¼"));
		UpdateOperationStatus(_T("�����������������������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)buff,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����������������������ʧ�ܣ������Ի����µ�¼"));
		UpdateOperationStatus(_T("�����������������������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	p_dlg->m_tip.SetWindowText(_T("���������������ͳɹ����ȴ���������Ӧ"));
	UpdateOperationStatus(_T("���������������ͳɹ����ȴ���������Ӧ"));
	return TRUE; 

}

BOOL CSock::ReqOrderNew()    //�����½�����
{
	OrderInfo info;
	int len = sizeof(OrderInfo);
	memset(&info,0,len);
	COrderContent* p_dlg = (COrderContent*)m_pOrderContent;
	if(p_dlg == NULL)
	{
		AfxMessageBox(_T("�½������Ѿ�ȡ��"));
		return TRUE;
	}else{
		int nflag;
		info = p_dlg->m_orderInfo;
		hdr header;
		header.type = ORDER_NEW_OrderContent;
		header.len = HEADLEN + len;
		nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
		if(nflag == SOCKET_ERROR)
		{
			AfxMessageBox(_T("������������½���������ʧ�ܣ������Ի����µ�¼"));
			UpdateOperationStatus(_T("������������½���������ʧ�ܣ������Ի����µ�¼"));
			return FALSE;
		}
		nflag = send(m_sockWhole,(const char*)&info,len,0);
		if(nflag == SOCKET_ERROR)
		{
			AfxMessageBox(_T("������������½���������ʧ�ܣ������Ի����µ�¼"));
			UpdateOperationStatus(_T("������������½���������ʧ�ܣ������Ի����µ�¼"));
			return FALSE;
		}
		p_dlg->m_tip.SetWindowText(_T("�����½��������ͳɹ����ȴ���������Ӧ"));
		UpdateOperationStatus(_T("�����½��������ͳɹ����ȴ���������Ӧ"));
		return TRUE; 
	}
}

BOOL CSock::ReqDLFile()     //���������ļ�
{
	WT;
	char buff[MAX_PATH] = {0};   //���������ļ��ַ���  ���������ź͸�����
	CDealListView* p_dlg = (CDealListView*)m_pDealListView;
	char *p = T2A(p_dlg->m_strToDLFile);
	strcpy_s(buff,p);
	int len = sizeof(buff);
	int nflag;
	hdr header;
	header.type = FILE_SIZE;
	header.len = HEADLEN + len;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����������������ļ�����ʧ�ܣ������Ի����µ�¼"));
		UpdateOperationStatus(_T("����������������ļ�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)buff,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����������������ļ�����ʧ�ܣ������Ի����µ�¼"));
		UpdateOperationStatus(_T("����������������ļ�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("���������ļ����ͳɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqUpLoadFile()    //��������ϴ��ļ�
{
	USES_CONVERSION;
	CString ulFilePath;    //�ļ�·��
	u_long ulFileSize;   //�ļ���С
	int nErrCode;
	hdr header;
	memset(&header,0,sizeof(header));
	header.type = SEND_FILEINFO;
	int len = sizeof(FileInfo);
	header.len = HEADLEN + len;
	FileInfo info;
	memset(&info,0,sizeof(info));
	if(m_pOrderContent != NULL)
	{
		COrderContent* p_dlg = (COrderContent*)m_pOrderContent;
		ulFileSize = p_dlg->m_fileULInfo.filesize;
		ulFilePath = p_dlg->m_accessory_filepath;  //�ļ�·��
		info = p_dlg->m_fileULInfo;
	}else{  //�Ѿ�ȡ���� �ϴ�����
		return TRUE;
	} 
	nErrCode = send(m_sockWhole,(char*)&header, HEADLEN, 0);
	if (SOCKET_ERROR == nErrCode)
	{	
		if(m_pOrderContent != NULL)
		{
			COrderContent* p_dlg = (COrderContent*)m_pOrderContent;
			p_dlg->SendMessage(WM_RESETUPLOAD_OrderContent,0,0);
			p_dlg->SendMessage(WM_ENDTASK_OrderContent,0,0);
			p_dlg->m_tip.SetWindowText(_T("����ʧ�ܣ�������"));
			p_dlg->m_static_upload_status.SetWindowText(_T("�ϴ�ʧ�ܣ�������"));
		}else{
			AfxMessageBox(_T("�����ļ�ʧ�ܣ�"));
		}
		return TRUE;
	}

	//���Ͱ���
	nErrCode = send(m_sockWhole,(char*)&info,len,0);
	if (SOCKET_ERROR == nErrCode)
	{
		if(m_pOrderContent != NULL)
		{
			COrderContent* p_dlg = (COrderContent*)m_pOrderContent;
			p_dlg->SendMessage(WM_RESETUPLOAD_OrderContent,0,0);
			p_dlg->SendMessage(WM_ENDTASK_OrderContent,0,0);
			p_dlg->m_tip.SetWindowText(_T("����ʧ�ܣ�������"));
			p_dlg->m_static_upload_status.SetWindowText(_T("�ϴ�ʧ�ܣ�������"));
		}else{
			AfxMessageBox(_T("�����ļ�ʧ�ܣ�"));
		}
		return TRUE;
	}
	CFile File;
	if(!File.Open(ulFilePath,CFile::modeRead|CFile::typeBinary))
	{
		if(m_pOrderContent != NULL)
		{
			COrderContent* p_dlg = (COrderContent*)m_pOrderContent;
			p_dlg->SendMessage(WM_RESETUPLOAD_OrderContent,0,0);
			p_dlg->SendMessage(WM_ENDTASK_OrderContent,0,0);
			p_dlg->m_tip.SetWindowText(_T("���ļ�ʧ�ܣ�������"));
			p_dlg->m_static_upload_status.SetWindowText(_T("�ϴ�ʧ�ܣ�ԭ����ļ�ʧ�ܣ�������"));
		}else{
			AfxMessageBox(_T("�ļ�������"));
		}
		return TRUE;
	}
	//File.Seek(0,CFile::begin);
	File.SeekToBegin();
	int		nSendTimes = ulFileSize / SEND_BUFF +1;	//���㷢�͵Ĵ���
	char	cSend[SEND_BUFF]={0};						//�����ļ����ݵĻ�����
	
	int		i = 0;									//���ʹ���
	u_long	nlTotal = 0;							//��ȡ�ļ�����
	u_long	nlRead = 0;								//ÿ�ζ�ȡ�ļ�����
	int		nReadIndex = 0;							//�����
	m_bUpLoading = TRUE;
	while (nlTotal != ulFileSize &&
					//!feof(stream) &&
					CSock::m_bIsConnecting &&
					m_bUpLoading)		//���㷢���ļ��ĳ��ȣ����߶����ļ�β
	{
		nReadIndex++;//��ȡ������1
		
		memset(cSend, 0, SEND_BUFF);
		File.Seek(nlTotal,CFile::begin);
		if (nReadIndex != nSendTimes)
		{
			nlRead = File.Read(cSend,SEND_BUFF);
		}else{
			u_long ulLeft = ulFileSize - nlTotal;			//���һ��
			nlRead = File.Read(cSend, ulLeft);		//��ȡ���� 
		}
		nlTotal += nlRead;//�����Ѷ��ļ�����
		if(NULL != m_pOrderContent)
		{
			COrderContent* p_dlg = (COrderContent*)m_pOrderContent;
			p_dlg->m_ulCurTotal = nlTotal;
		}
		//�����ͷ
		header.type = FILE_UPLOAD;
		header.len = HEADLEN + nlRead;
		//���Ͱ�ͷ
		nErrCode = send(m_sockWhole,(char*)&header, HEADLEN, 0);
		if (SOCKET_ERROR == nErrCode)
		{
						
			//fclose(stream);
			File.Close();
			m_bUpLoading = FALSE;
			if(m_pOrderContent != NULL)
			{
				COrderContent* p_dlg = (COrderContent*)m_pOrderContent;
				p_dlg->SendMessage(WM_RESETUPLOAD_OrderContent,0,0);
				p_dlg->SendMessage(WM_ENDTASK_OrderContent,0,0);
				p_dlg->m_tip.SetWindowText(_T("����ʧ�ܣ�������"));
				p_dlg->m_static_upload_status.SetWindowText(_T("�ϴ�ʧ�ܣ�������"));
			}else{
				AfxMessageBox(_T("�����ļ�ʧ�ܣ�"));
			}
			return TRUE;
		}
		
		//���Ͱ���
		nErrCode = send(m_sockWhole,cSend,nlRead, 0);
		if (SOCKET_ERROR == nErrCode)
		{
			File.Close();
			m_bUpLoading = FALSE;
			if(m_pOrderContent != NULL)
			{
				COrderContent* p_dlg = (COrderContent*)m_pOrderContent;
				p_dlg->SendMessage(WM_RESETUPLOAD_OrderContent,0,0);
				p_dlg->SendMessage(WM_ENDTASK_OrderContent,0,0);
				p_dlg->m_tip.SetWindowText(_T("����ʧ�ܣ�������"));
				p_dlg->m_static_upload_status.SetWindowText(_T("�ϴ�ʧ�ܣ�������"));
			}else{
				AfxMessageBox(_T("�����ļ�ʧ�ܣ�"));
			}
			return TRUE;
		}
		
	}	
	
	//��ʵ����
	if (nlTotal != ulFileSize)
	{
		if(m_pOrderContent != NULL)
		{
			COrderContent* p_dlg = (COrderContent*)m_pOrderContent;
			p_dlg->SendMessage(WM_RESETUPLOAD_OrderContent,0,0);
			p_dlg->SendMessage(WM_ENDTASK_OrderContent,0,0);
			p_dlg->m_tip.SetWindowText(_T("����ʧ�ܣ�������"));
			p_dlg->m_static_upload_status.SetWindowText(_T("�ϴ�ʧ�ܣ�������"));
		}else{
			AfxMessageBox(_T("�����ļ�ʧ�ܣ�"));
		}
		return TRUE;		
	}
	File.Close();	
	m_bUpLoading = FALSE;
	//���ͽ�����
	//��ͷ
	header.type = FILE_UPLOAD;
	header.len = HEADLEN;   //�����ļ�������ʶ
	//header.fpos = -1;   //�����ļ�������ʶ
	
	//���Ͱ�ͷ
	nErrCode = send(m_sockWhole,(char*)&header, HEADLEN, 0);
	if (SOCKET_ERROR == nErrCode)
	{
		if(m_pOrderContent != NULL)
		{
			COrderContent* p_dlg = (COrderContent*)m_pOrderContent;
			p_dlg->SendMessage(WM_RESETUPLOAD_OrderContent,0,0);
			p_dlg->SendMessage(WM_ENDTASK_OrderContent,0,0);
			p_dlg->m_tip.SetWindowText(_T("����ʧ�ܣ�������"));
			p_dlg->m_static_upload_status.SetWindowText(_T("�ϴ�ʧ�ܣ�������"));
		}else{
			AfxMessageBox(_T("�����ļ�ʧ�ܣ�"));
		}
		return TRUE;
	}
	if(m_pOrderContent != NULL)
	{
		COrderContent* p_dlg = (COrderContent*)m_pOrderContent;
		p_dlg->SendMessage(WM_RESETUPLOAD_OrderContent,0,0);
		p_dlg->m_static_upload_status.SetWindowText(_T("���ϴ����ȴ�����������"));
	}
	//֪ͨ���������ͻ��˲��ٷ�������
	//shutdown(s, SD_SEND);
	return TRUE;
}

BOOL CSock::ReqCheckFileExist()    //�����ѯ�ļ��Ƿ����
{
	int nflag;
	COrderContent *p_dlg = (COrderContent *)m_pOrderContent;
	OrderInfo order = p_dlg->m_orderInfo;
	int len = sizeof(order);
	hdr header;
	header.type = CHECK_FILE_EXIST;
	header.len = HEADLEN + len;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���͹��ڼ�鸽���Ƿ���ڵ�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)&order,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���͹��ڼ�鸽���Ƿ���ڵ�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("���͹��ڼ�鸽���Ƿ���ڵ�����ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqDelDeal()         //����ɾ���������߸���
{
	int nflag;
	char buff[1024*30] = {0};
	int len = sizeof(buff);
	memset(buff,0,len);
	CDealListView *p_dlg = (CDealListView *)m_pDealListView;
	USES_CONVERSION;
	char *p = T2A(p_dlg->m_strToDelDeal);
	strcpy_s(buff,p);
	hdr header;
	header.type = DEL_DEAL;
	header.len = HEADLEN + len;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���͹���ɾ�������򸽼�������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)&buff,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���͹���ɾ�������򸽼�������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	p_dlg->m_tip.SetWindowText(_T("���͹���ɾ�������򸽼�������ɹ����ȴ���������Ӧ"));
	UpdateOperationStatus(_T("���͹���ɾ�������򸽼�������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqDelServ()        //����ɾ��������Ϣ
{
	int nflag;
	char buff[1024*30] = {0};
	int len = sizeof(buff);
	memset(buff,0,len);
	CServiceSearch *p_dlg = (CServiceSearch *)m_pServiceSearch;
	USES_CONVERSION;
	char *p = T2A(p_dlg->m_strDelServ);
	strcpy_s(buff,p);
	hdr header;
	header.type = SERV_DEL;
	header.len = HEADLEN + len;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���͹���ɾ�����������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)&buff,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���͹���ɾ�����������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	p_dlg->m_tip.SetWindowText(_T("���͹���ɾ�����������ɹ����ȴ���������Ӧ"));
	UpdateOperationStatus(_T("���͹���ɾ�����������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqDelStoreHistory()    //����ɾ�������ʷ��¼��Ϣ
{
	int nflag;
	char buff[1024*30];
	int len = sizeof(buff);
	memset(buff,0,len);
	if(m_pStoreHistory == NULL)
	{
		return TRUE;
	}
	CStoreHistory *p_dlg = (CStoreHistory *)m_pStoreHistory;
	USES_CONVERSION;
	char *p = T2A(p_dlg->m_strToDelHistory);

	strcpy_s(buff,p);
	hdr header;
	header.type = STORYHISTORY_DEL;
	header.len = HEADLEN + len;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���͹���ɾ������¼������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)&buff,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���͹���ɾ������¼������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	p_dlg->m_tip.SetWindowText(_T("���͹���ɾ������¼������ɹ����ȴ���������Ӧ"));
	UpdateOperationStatus(_T("���͹���ɾ������¼������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqFindAllServ()      //�����ѯ���з���
{
	int nflag;
	hdr header;
	header.type = SERV_FINDALL;
	header.len = HEADLEN ;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���͹�������ȫ��������Ϣ������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	CServiceSearch* p_dlg = (CServiceSearch*)m_pServiceSearch;
	p_dlg->m_tip.SetWindowText(_T("���͹�������ȫ�������Ϣ������ɹ����ȴ���������Ӧ"));
	UpdateOperationStatus(_T("���͹�������ȫ�������Ϣ������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqFindAllStoreHistory()   //�������п���¼��Ϣ
{
	int nflag;
	hdr header;
	header.type = STOREHISTORY_FINDALL;
	header.len = HEADLEN ;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���͹�������ȫ������¼������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	CStoreHistory* p_dlg = (CStoreHistory*)m_pStoreHistory;
	p_dlg->m_tip.SetWindowText(_T("���͹�������ȫ������¼������ɹ����ȴ���������Ӧ"));
	UpdateOperationStatus(_T("���͹�������ȫ������¼������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqStoreAlertNumSet()    //������Ԥ����Ϣ����
{
	if(m_pStoreAlertSet == NULL)
	{
		AfxMessageBox(_T("�Ѿ�ȡ����ӿ��"));
		return FALSE;
	}
	CStoreAlertSet* p_dlg = (CStoreAlertSet*)m_pStoreAlertSet;
	StoreInfo store = p_dlg->m_goods_alert_num_set_strutct;
	memset(&p_dlg->m_goods_alert_num_set_strutct,0,sizeof(p_dlg->m_goods_alert_num_set_strutct));
	int nflag;
	hdr header;
	int len = sizeof(StoreInfo);
	header.type = STORE_GOODS_ALERT_SET;
	header.len = HEADLEN + len;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���͹������ÿ��Ԥ����Ϣ������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)&store,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���͹������ÿ��Ԥ����Ϣ������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	p_dlg->m_tip.SetWindowText(_T("���͹������ÿ��Ԥ����Ϣ������ɹ����ȴ���������Ӧ"));
	UpdateOperationStatus(_T("���͹������ÿ��Ԥ����Ϣ������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqOutStore()        //�������
{
	if(m_pStoreOut == NULL)
	{
		AfxMessageBox(_T("�Ѿ�ȡ����ӿ��"));
		return FALSE;
	}
	CStoreOut* p_dlg = (CStoreOut*)m_pStoreOut;
	StoreInfo store = p_dlg->m_goods_out_struct;
	memset(&p_dlg->m_goods_out_struct,0,sizeof(p_dlg->m_goods_out_struct));
	int nflag;
	hdr header;
	int len = sizeof(StoreInfo);
	header.type = STORE_OUT_StoreOut;
	header.len = HEADLEN + len;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���͹�����������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)&store,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���͹�����������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	p_dlg->m_tip.SetWindowText(_T("���͹�����������ɹ����ȴ���������Ӧ"));
	UpdateOperationStatus(_T("���͹�����������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqModifyServ()    //�����޸ķ���
{
	if(m_pServModify == NULL)
	{
		AfxMessageBox(_T("�Ѿ�ȡ���޸ķ���"));
		return FALSE;
	}
	CServModify* p_dlg = (CServModify*)m_pServModify;
	ServInfo serv = p_dlg->m_servInfo_struct;
	memset(&p_dlg->m_servInfo_struct,0,sizeof(p_dlg->m_servInfo_struct));
	int nflag;
	hdr header;
	int len = sizeof(ServInfo);
	header.type = SERV_MODIFY_ServModify;
	header.len = HEADLEN + len;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�޸ķ����������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)&serv,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�޸ķ����������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	p_dlg->m_tip.SetWindowText(_T("�޸ķ���������ͳɹ����ȴ���������Ӧ"));
	UpdateOperationStatus(_T("�޸ķ���������ͳɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqRegServ()   //����ע�����
{
	if(m_pServReg == NULL)
	{
		AfxMessageBox(_T("�Ѿ�ȡ����ӿ��"));
		return FALSE;
	}
	CServReg* p_dlg = (CServReg*)m_pServReg;
	ServInfo serv = p_dlg->m_servInfo_struct;
	memset(&p_dlg->m_servInfo_struct,0,sizeof(p_dlg->m_servInfo_struct));
	int nflag;
	hdr header;
	int len = sizeof(ServInfo);
	header.type = SERV_REG_ServReg;
	header.len = HEADLEN + len;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("ע������������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)&serv,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("ע������������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	p_dlg->m_tip.SetWindowText(_T("ע�����������ͳɹ����ȴ���������Ӧ"));
	UpdateOperationStatus(_T("ע�����������ͳɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqAddStore()        //���������Ʒ���
{
	if(m_pStoreAdd == NULL)
	{
		AfxMessageBox(_T("�Ѿ�ȡ����ӿ��"));
		return FALSE;
	}
	CStoreAdd* p_dlg = (CStoreAdd*)m_pStoreAdd;
	StoreInfo strore = p_dlg->m_storeAddStruct;
	memset(&p_dlg->m_storeAddStruct,0,sizeof(p_dlg->m_storeAddStruct));
	int nflag;
	hdr header;
	int len = sizeof(StoreInfo);
	header.type = STORE_ADD_StoreAdd;
	header.len = HEADLEN + len;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)&strore,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	p_dlg->m_tip.SetWindowText(_T("���������ͳɹ����ȴ���������Ӧ"));
	UpdateOperationStatus(_T("���������ͳɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqFindAllStoreInfo()     //�����������п������
{
	int nflag;
	hdr header;
	header.type = STORE_FINDALL_StoreInfo;
	header.len = HEADLEN ;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("��������ȫ��������ϵ�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	CStoreInfo* p_dlg = (CStoreInfo*)m_pStoreInfo;
	p_dlg->m_tip.SetWindowText(_T("��������ȫ��������ϵ�����ɹ����ȴ���������Ӧ"));
	UpdateOperationStatus(_T("��������ȫ��������ϵ�����ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqLoadUserAuthority()      //�����û�Ȩ��
{
	WT;
	char buff[1024] = {0};
	int len = sizeof(buff);
	CPosEdit* p_dlg = (CPosEdit*)m_pPosEdit;
	strcpy_s(buff,T2A(p_dlg->m_emp_name));
	hdr header;
	header.type = USER_INIT;
	header.len = HEADLEN + len;
	int nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���ͼ����û�Ȩ�޵�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)buff,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���ͼ����û�Ȩ�޵�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("���ͼ����û�Ȩ�޵�����ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqDelUsers()   //ɾ���û�
{
	WT;
	char buff[1024] = {0};
	int len = sizeof(buff);
	CSysPostion* p_dlg = (CSysPostion*)m_pSysPostion;
	strcpy_s(buff,T2A(p_dlg->m_users_to_delete));
	hdr header;
	header.type = POS_DEL;
	header.len = HEADLEN + len;
	int nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����ɾ���û�������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)buff,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����ɾ���û�������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("����ɾ���û�������ɹ����ȴ���������Ӧ"));
	p_dlg->m_tip.SetWindowText(_T("����ɾ���û�������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqFindAllUsers()    //���������û�
{
	WT;
	char buff[1024] = {0};
	int len = sizeof(buff);
	CSysPostion* p_dlg = (CSysPostion*)m_pSysPostion;
	strcpy_s(buff,T2A(p_dlg->m_content_to_find));
	hdr header;
	header.type = POS_FIND_ALL;
	header.len = HEADLEN + len;
	int nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�������������û�������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)buff,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�������������û�������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("�������������û�������ɹ����ȴ���������Ӧ"));
	p_dlg->m_tip.SetWindowText(_T("�������������û�������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqFindEmpPerformance()   //��ѯԱ��ҵ����
{
	WT;
	char buff[1024] = {0};
	int len = sizeof(buff);
	CPerformanceMgView* p_view = (CPerformanceMgView*)m_pEmpPerformance;
	strcpy_s(buff,T2A(p_view->m_keyword));
	p_view->m_keyword.Empty();
	hdr header;
	header.type = FIND_EMP_PERPFORMANCE;
	header.len = HEADLEN + len;
	int nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("��������Ա��ҵ��������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)buff,len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("��������Ա��ҵ��������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("��������Ա��ҵ��������ɹ����ȴ���������Ӧ"));
	p_view->m_tip.SetWindowText(_T("��������Ա��ҵ��������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqFindOrderIncomplete()    //��ѯδ��ɶ���
{
	int nflag;
	hdr header;
	header.type = FIND_ORDER_INCOMPLETE;
	header.len = HEADLEN ;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("��������δ��ɶ���������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	COrderIncompletedProgView* p_view = (COrderIncompletedProgView*)m_pOrderIncompleteView;
	p_view->m_tip.SetWindowText(_T("��������δ��ɶ���������ɹ����ȴ���������Ӧ"));
	UpdateOperationStatus(_T("��������δ��ɶ���������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqProdForEx()   //�������в�Ʒ����
{
	int nflag;
	hdr header;
	header.type = PROD_EX;
	header.len = HEADLEN ;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("��������ȫ����Ʒ���ϵ�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("��������ȫ����Ʒ���ϵ�����ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqCtmForEx()    //�������пͻ�����
{
	int nflag;
	hdr header;
	header.type = CTM_EX;
	header.len = HEADLEN ;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("��������ȫ���ͻ����ϵ�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("��������ȫ���������ϵ�����ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqFindAllCtmInfo()     //����������Ͳ�ѯ���пͻ����ϵ�����
{
	int nflag;
	hdr header;
	header.type = CTM_FINDALL_CtmInfo;
	header.len = HEADLEN ;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("��������ȫ���ͻ����ϵ�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	CCtmInfo* p_dlg = (CCtmInfo*)m_pCtmInfo;
	p_dlg->m_tip.SetWindowText(_T("��������ȫ���������ϵ�����ɹ����ȴ���������Ӧ"));
	UpdateOperationStatus(_T("��������ȫ���������ϵ�����ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqSearchAllFctInfo()   //��������������������г�����Ϣ
{ 
	int nflag;
	hdr header;
	header.type = FCT_FIND_ALL;
	header.len = HEADLEN ;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("��������ȫ�����ҵ�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("��������ȫ�����ҵ�����ɹ����ȴ���������Ӧ"));
	CFctSet* p_dlg = (CFctSet*)m_pFctSet;
	p_dlg->m_tip.SetWindowText(_T("��������ȫ�����ҵ�����ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqUpdateOrderIncomplete()    //�ύ�������ݵ����ݿ�
{
	WT;
	int nflag;
	hdr header;
	char buff[1024*10] = {0};
	int len = sizeof(buff);
	
	header.type = UPDATE_ORDER_BATCH;
	header.len = HEADLEN + len;
	COrderIncompletedProgView* p_view = (COrderIncompletedProgView*)m_pOrderIncompleteView;
	int size = p_view->m_OrderToUpdateArr.GetSize();
	
	int i = 0;
	CString temp = NULL;
	CString strSend = NULL;
	while(i<size)
	{
		int index_list = atoi(T2A(p_view->m_OrderToUpdateArr.GetAt(i)));
		temp += _T("{#[#");
		temp += p_view->m_list.GetItemText(index_list,0);
		temp += _T("#][#");
		temp += p_view->m_list.GetItemText(index_list,1);
		temp += _T("#][#");
		temp += p_view->m_list.GetItemText(index_list,2);
		temp += _T("#][#");
		temp += p_view->m_list.GetItemText(index_list,3);
		temp += _T("#][#");
		temp += p_view->m_list.GetItemText(index_list,4);
		temp += _T("#][#");
		temp += p_view->m_list.GetItemText(index_list,5);
		temp += _T("#][#");
		temp += p_view->m_list.GetItemText(index_list,6);
		temp += _T("#][#");
		temp += p_view->m_list.GetItemText(index_list,7);
		temp += _T("#][#");
		temp += p_view->m_list.GetItemText(index_list,8);
		temp += _T("#][#");
		temp += p_view->m_list.GetItemText(index_list,9);
		temp += _T("#][#");
		temp += p_view->m_list.GetItemText(index_list,10);
		temp += _T("#][#");
		temp += p_view->m_list.GetItemText(index_list,11);
		temp += _T("#][#");
		temp += p_view->m_list.GetItemText(index_list,12);
		temp += _T("#]#}");
		strSend += temp;
		temp.Empty();
		i++;
		if((i == size) ||(i%10 == 0))   //���һ�л���ÿ10������ ����һ��
		{
			strcpy_s(buff,T2A(strSend));
			nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
			if(nflag == SOCKET_ERROR)
			{
				AfxMessageBox(_T("�����������¶������ݵ�����ʧ�ܣ������Ի����µ�¼"));
				return FALSE;
			}
			nflag = send(m_sockWhole,(const char*)buff,len,0);
			if(nflag == SOCKET_ERROR)
			{
				AfxMessageBox(_T("�����������¶������ݵ�����ʧ�ܣ������Ի����µ�¼"));
				return FALSE;
			}
			strSend.Empty();
			memset(buff,0,len);
		}
	}
	
	header.len = HEADLEN;  //��־�ŷ��ͽ���
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����������¶������ݵ�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	p_view->m_OrderToUpdateArr.RemoveAll();
	p_view->m_tip.SetWindowText(_T("�����������¶������ݵ�����ɹ����ȴ���������Ӧ"));
	UpdateOperationStatus(_T("�����������¶������ݵ�����ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqSubmitProdInfo()   //���������Ʒ����
{
	WT;
	int nflag;
	hdr header;
	char buff[1024*10] = {0};
	int len = sizeof(buff);
	
	header.type = PROD_IM;
	header.len = HEADLEN + len;
	CProdInfoProp* p_dlg = (CProdInfoProp*)m_pProdBatch;
	int size = p_dlg->m_arr_prodInfoForIm.GetSize();
	
	int i = 0;
	CString temp = NULL;
	CString strSend = NULL;
	while(i<size)
	{
		int index = atoi(T2A(p_dlg->m_arr_prodInfoForIm.GetAt(i)));
		temp += _T("{#[#");
		temp += p_dlg->m_listProd.GetItemText(index,0);
		temp += _T("#][#");
		temp += p_dlg->m_listProd.GetItemText(index,1);
		temp += _T("#][#");
		temp += p_dlg->m_listProd.GetItemText(index,2);
		temp += _T("#][#");
		temp += p_dlg->m_listProd.GetItemText(index,3);
		temp += _T("#]#}");
		strSend += temp;
		temp.Empty();
		i++;
		if((i == size) ||(i%10 == 0))   //���һ�л���ÿ10������ ����һ��
		{
			strcpy_s(buff,T2A(strSend));
			nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
			if(nflag == SOCKET_ERROR)
			{
				AfxMessageBox(_T("���������ύ��Ʒ���ݵ�����ʧ�ܣ������Ի����µ�¼"));
				return FALSE;
			}
			nflag = send(m_sockWhole,(const char*)buff,len,0);
			if(nflag == SOCKET_ERROR)
			{
				AfxMessageBox(_T("���������ύ��Ʒ���ݵ�����ʧ�ܣ������Ի����µ�¼"));
				return FALSE;
			}
			strSend.Empty();
			memset(buff,0,len);
		}
	}
	header.len = HEADLEN;  //��־�ŷ��ͽ���
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���������ύ��Ʒ���ݵ�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("���������ύ��Ʒ���ݵ�����ɹ����ȴ���������Ӧ"));
	return TRUE;
}


BOOL CSock::ReqSubmitCtmInfo()   //�����ύ�ͻ����ݵ����ݿ�
{
	WT;
	int nflag;
	hdr header;
	char buff[1024*10] = {0};
	int len = sizeof(buff);
	
	header.type = CTM_IM;
	header.len = HEADLEN + len;
	CCustomInfoProp* p_dlg = (CCustomInfoProp*)m_pCtmSubmit;
	int size = p_dlg->m_ctm_to_submit_arr.GetSize();
	
	int i = 0;
	CString temp = NULL;
	CString strSend = NULL;
	while(i<size)
	{
		temp += _T("{#[#");
		temp += p_dlg->m_ctmInfoList.GetItemText(atoi(T2A(p_dlg->m_ctm_to_submit_arr.GetAt(i))),0);
		temp += _T("#][#");
		temp += p_dlg->m_ctmInfoList.GetItemText(atoi(T2A(p_dlg->m_ctm_to_submit_arr.GetAt(i))),1);
		temp += _T("#][#");
		temp += p_dlg->m_ctmInfoList.GetItemText(atoi(T2A(p_dlg->m_ctm_to_submit_arr.GetAt(i))),2);
		temp += _T("#][#");
		temp += p_dlg->m_ctmInfoList.GetItemText(atoi(T2A(p_dlg->m_ctm_to_submit_arr.GetAt(i))),3);
		temp += _T("#][#");
		temp += p_dlg->m_ctmInfoList.GetItemText(atoi(T2A(p_dlg->m_ctm_to_submit_arr.GetAt(i))),4);
		temp += _T("#][#");
		temp += p_dlg->m_ctmInfoList.GetItemText(atoi(T2A(p_dlg->m_ctm_to_submit_arr.GetAt(i))),5);
		temp += _T("#][#");
		temp += p_dlg->m_ctmInfoList.GetItemText(atoi(T2A(p_dlg->m_ctm_to_submit_arr.GetAt(i))),6);
		temp += _T("#][#");
		temp += p_dlg->m_ctmInfoList.GetItemText(atoi(T2A(p_dlg->m_ctm_to_submit_arr.GetAt(i))),7);
		temp += _T("#][#");
		temp += p_dlg->m_ctmInfoList.GetItemText(atoi(T2A(p_dlg->m_ctm_to_submit_arr.GetAt(i))),8);
		temp += _T("#][#");
		temp += p_dlg->m_ctmInfoList.GetItemText(atoi(T2A(p_dlg->m_ctm_to_submit_arr.GetAt(i))),9);
		temp += _T("#]#}");
		strSend += temp;
		temp.Empty();
		i++;
		if((i == size) ||(i%10 == 0))   //���һ�л���ÿ10������ ����һ��
		{
			strcpy_s(buff,T2A(strSend));
			nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
			if(nflag == SOCKET_ERROR)
			{
				AfxMessageBox(_T("���������ύ�ͻ����ݵ�����ʧ�ܣ������Ի����µ�¼"));
				return FALSE;
			}
			nflag = send(m_sockWhole,(const char*)buff,len,0);
			if(nflag == SOCKET_ERROR)
			{
				AfxMessageBox(_T("���������ύ�ͻ����ݵ�����ʧ�ܣ������Ի����µ�¼"));
				return FALSE;
			}
			strSend.Empty();
			memset(buff,0,len);
		}
	}
	header.len = HEADLEN;  //��־�ŷ��ͽ���
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���������ύ�ͻ����ݵ�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("���������ύ�ͻ����ݵ�����ɹ����ȴ���������Ӧ"));
	return TRUE;
}




BOOL CSock::ReqSubmitEmpInfo()    //�����ύԱ�����ݵ����ݿ�
{
	WT;
	int nflag;
	hdr header;
	char buff[1024*10] = {0};
	int len = sizeof(buff);
	
	header.type = EMP_INFO_IMPORT;
	header.len = HEADLEN + len;
	CEmpInfoProp* p_dlg = (CEmpInfoProp*)m_pEmpInfoIm;
	int size = p_dlg->m_num_to_submit_to_db.GetSize();
	
	int i = 0;
	CString temp = NULL;
	CString strSend = NULL;
	while(i<size)
	{
		temp += _T("{#[#");
		temp += p_dlg->m_listEmp.GetItemText(atoi(T2A(p_dlg->m_num_to_submit_to_db.GetAt(i))),0);
		temp += _T("#][#");
		temp += p_dlg->m_listEmp.GetItemText(atoi(T2A(p_dlg->m_num_to_submit_to_db.GetAt(i))),1);
		temp += _T("#][#");
		temp += p_dlg->m_listEmp.GetItemText(atoi(T2A(p_dlg->m_num_to_submit_to_db.GetAt(i))),2);
		temp += _T("#][#");
		temp += p_dlg->m_listEmp.GetItemText(atoi(T2A(p_dlg->m_num_to_submit_to_db.GetAt(i))),3);
		temp += _T("#][#");
		temp += p_dlg->m_listEmp.GetItemText(atoi(T2A(p_dlg->m_num_to_submit_to_db.GetAt(i))),4);
		temp += _T("#][#");
		temp += p_dlg->m_listEmp.GetItemText(atoi(T2A(p_dlg->m_num_to_submit_to_db.GetAt(i))),5);
		temp += _T("#]#}");
		strSend += temp;
		temp.Empty();
		i++;
		if((i == size) ||(i%10 == 0))   //���һ�л���ÿ10������ ����һ��
		{
			strcpy_s(buff,T2A(strSend));
			nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
			if(nflag == SOCKET_ERROR)
			{
				AfxMessageBox(_T("���������ύԱ�����ݵ�����ʧ�ܣ������Ի����µ�¼"));
				return FALSE;
			}
			nflag = send(m_sockWhole,(const char*)buff,len,0);
			if(nflag == SOCKET_ERROR)
			{
				AfxMessageBox(_T("���������ύԱ�����ݵ�����ʧ�ܣ������Ի����µ�¼"));
				return FALSE;
			}
			strSend.Empty();
			memset(buff,0,len);
		}
	}
	header.len = HEADLEN;  //��־�ŷ��ͽ���
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���������ύԱ�����ݵ�����ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("���������ύԱ�����ݵ�����ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqSearchAllEmpInfoForEx()   //���������������Ա������ Ϊ����������
{
	int nflag;
	hdr header;
	header.type = EMP_INFO_FOR_EX;
	header.len = HEADLEN ;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("��������ȫ��Ա��������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("��������ȫ��Ա��������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqSearchAllEmpInfo()		//�������������������Ա����Ϣ������
{
	int nflag;
	hdr header;
	header.type = SEARCH_ALL_EMP_INFO;
	header.len = HEADLEN ;
	nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(_T("��������ȫ��Ա��������ʧ�ܣ������Ի����µ�¼"));
		return FALSE;
	}
	UpdateOperationStatus(_T("��������ȫ��Ա��������ɹ����ȴ���������Ӧ"));
	CEmpInfoView* p_dlg = (CEmpInfoView*)m_pEmpInfoView;
	p_dlg->m_tip.SetWindowText(_T("��������ȫ��Ա��������ɹ����ȴ���������Ӧ"));
	return TRUE;
}

BOOL CSock::ReqFctEdit()   //����༭��������
{
	if(m_pFactoryEdit == NULL)
	{
		UpdateOperationStatus(_T("�Ѿ�ȡ���༭��������"));
		return TRUE;
	}
	CFactoryEdit* p_dlg = (CFactoryEdit*)m_pFactoryEdit;
	FctInfo fct;
	memset(&fct,0,sizeof(fct));
	USES_CONVERSION;
	char *p = T2A(p_dlg->m_addr_fctEdit);
	strcpy_s(fct.addr_fct,p);
	p = T2A(p_dlg->m_name_fctEdit);
	strcpy_s(fct.name_fct,p);
	p = T2A(p_dlg->m_phone_fctEdit);
	strcpy_s(fct.phone_fct,p);
	p = T2A(p_dlg->m_contact_person_fctEdit);
	strcpy_s(fct.contacts_fct,p);
	p = T2A(p_dlg->m_main_product_fctEdit);
	strcpy_s(fct.main_product_fct,p);
	p = T2A(p_dlg->m_ps_fctEdit);
	strcpy_s(fct.ps_fct,p);

	
	hdr header;
	header.type = FCT_EDIT_FactoryEdit;
	header.len = HEADLEN + sizeof(fct);
	int errcode = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("����༭�������Ϸ���ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	errcode = send(m_sockWhole,(const char*)&fct,sizeof(fct),0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("����༭�������Ϸ���ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	CString _str = _T("����༭���������ѷ��ͣ��ȴ���������Ӧ");
	UpdateOperationStatus(_str);
	p_dlg->m_tip.SetWindowText(_str);
	return TRUE;
}

BOOL CSock::ReqCtmEdit()    //����༭�ͻ�����
{
	if(m_pCtmEdit == NULL)
	{
		UpdateOperationStatus(_T("�Ѿ�ȡ���༭�ͻ�����"));
		return TRUE;
	}
	CCtmEdit* p_dlg = (CCtmEdit*)m_pCtmEdit;
	CtmInfo ctm = p_dlg->m_ctmEditStruct;
	memset(&p_dlg->m_ctmEditStruct,0,sizeof(p_dlg->m_ctmEditStruct));
	int len = sizeof(CtmInfo);
	
	hdr header;
	header.type = CTM_EDIT_CtmEdit;
	header.len = HEADLEN + len;
	int errcode = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("�����޸Ŀͻ����Ϸ���ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	errcode = send(m_sockWhole,(const char*)&ctm,len,0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("�����޸Ŀͻ����Ϸ���ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	CString _str = _T("�����޸Ŀͻ������ѷ��ͣ��ȴ���������Ӧ");
	UpdateOperationStatus(_str);
	p_dlg->m_tip.SetWindowText(_str);
	return TRUE;
}

BOOL CSock::ReqEmpEdit()     //����༭Ա��
{
	if(m_pEmpEdit == NULL)
	{
		UpdateOperationStatus(_T("�Ѿ�ȡ���༭Ա��"));
		return TRUE;
	}
	CEmpNew* p_dlg = (CEmpNew*)m_pEmpEdit;
	EmpInfo emp;
	memset(&emp,0,sizeof(emp));
	USES_CONVERSION;
	char *p = T2A(p_dlg->m_addr_emp);
	strcpy_s(emp.empAddr,p);
	p = T2A(p_dlg->m_name_emp);
	strcpy_s(emp.empName,p);
	p = T2A(p_dlg->m_num_emp);
	strcpy_s(emp.empNum,p);
	p = T2A(p_dlg->m_phone_emp);
	strcpy_s(emp.empPhone,p);
	p = T2A(p_dlg->m_pos_emp);
	strcpy_s(emp.empPos,p);
	p = T2A(p_dlg->m_ps_emp);
	strcpy_s(emp.empPS,p);

	
	hdr header;
	header.type = EMP_EDIT_EmpEdit;
	header.len = HEADLEN + sizeof(emp);
	int errcode = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("�����޸�Ա�����Ϸ���ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	errcode = send(m_sockWhole,(const char*)&emp,sizeof(emp),0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("�����޸�Ա�����Ϸ���ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	CString _str = _T("�����޸�Ա�������ѷ��ͣ��ȴ���������Ӧ");
	UpdateOperationStatus(_str);
	p_dlg->m_tip.SetWindowText(_str);
	return TRUE;
}

BOOL  CSock::ReqCtmNew()   //�����½��û�����
{
	if(m_pCtmNew == NULL)
	{
		UpdateOperationStatus(_T("�Ѿ�ȡ���½��ͻ�����"));
		return TRUE;
	}
	CCtmNew* p_dlg = (CCtmNew*)m_pCtmNew;
	int len = sizeof(CtmInfo);
	CtmInfo ctm = p_dlg->m_ctmNewStruct;
	memset(&p_dlg->m_ctmNewStruct,0,sizeof(p_dlg->m_ctmNewStruct));
	hdr header;
	header.type = CTM_NEW_CtmNew;
	header.len = HEADLEN + len;
	int errcode = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("�����½��ͻ����Ϸ���ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	errcode = send(m_sockWhole,(const char*)&ctm,len,0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("�����½��ͻ����Ϸ���ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	CString _str = _T("�����½��ͻ������ѷ��ͣ��ȴ���������Ӧ");
	UpdateOperationStatus(_str);
	p_dlg->m_tip.SetWindowText(_str);
	return TRUE;
}


BOOL CSock::ReqFctNew()      //�����½���������
{
	if(m_pFctNew == NULL)
	{
		UpdateOperationStatus(_T("�Ѿ�ȡ���½�Ա��"));
		return TRUE;
	}
	CFactoryNew* p_dlg = (CFactoryNew*)m_pFctNew;
	FctInfo fct;
	memset(&fct,0,sizeof(fct));
	USES_CONVERSION;
	char *p = T2A(p_dlg->m_addr_fctNew);
	strcpy_s(fct.addr_fct,p);
	p = T2A(p_dlg->m_name_fctNew);
	strcpy_s(fct.name_fct,p);
	p = T2A(p_dlg->m_phone_fctNew);
	strcpy_s(fct.phone_fct,p);
	p = T2A(p_dlg->m_contacts_fctNew);
	strcpy_s(fct.contacts_fct,p);
	p = T2A(p_dlg->m_mainProduct_fctNew);
	strcpy_s(fct.main_product_fct,p);
	p = T2A(p_dlg->m_ps_fctNew);
	strcpy_s(fct.ps_fct,p);

	
	hdr header;
	header.type = FCT_NEW_FctNew;
	header.len = HEADLEN + sizeof(fct);
	int errcode = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("�����½��������Ϸ���ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	errcode = send(m_sockWhole,(const char*)&fct,sizeof(fct),0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("�����½��������Ϸ���ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	CString _str = _T("�����½����������ѷ��ͣ��ȴ���������Ӧ");
	UpdateOperationStatus(_str);
	p_dlg->m_tip.SetWindowText(_str);
	return TRUE;
}

BOOL CSock::ReqEmpNew()     //�����½�Ա��
{
	if(m_pEmpNew == NULL)
	{
		UpdateOperationStatus(_T("�Ѿ�ȡ���½�Ա��"));
		return TRUE;
	}
	CEmpNew* p_dlg = (CEmpNew*)m_pEmpNew;
	EmpInfo emp;
	memset(&emp,0,sizeof(emp));
	USES_CONVERSION;
	char *p = T2A(p_dlg->m_addr_emp);
	strcpy_s(emp.empAddr,p);
	p = T2A(p_dlg->m_name_emp);
	strcpy_s(emp.empName,p);
	p = T2A(p_dlg->m_num_emp);
	strcpy_s(emp.empNum,p);
	p = T2A(p_dlg->m_phone_emp);
	strcpy_s(emp.empPhone,p);
	p = T2A(p_dlg->m_pos_emp);
	strcpy_s(emp.empPos,p);
	p = T2A(p_dlg->m_ps_emp);
	strcpy_s(emp.empPS,p);

	
	hdr header;
	header.type = EMP_NEW_EmpNew;
	header.len = HEADLEN + sizeof(emp);
	int errcode = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("�����½�Ա������ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	errcode = send(m_sockWhole,(const char*)&emp,sizeof(emp),0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("�����½�Ա������ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	CString _str = _T("�����½�Ա���ѷ��ͣ��ȴ���������Ӧ");
	UpdateOperationStatus(_str);
	p_dlg->m_tip.SetWindowText(_str);
	return TRUE;
}

BOOL CSock::ReqDeleteSelFct_FctSet()     //��������ɾ����������
{
	if(m_pFctSet == NULL)
	{
		UpdateOperationStatus(_T("�Ѿ�ȡ��ɾ��Ա������"));
		return TRUE;
	}
	CFctSet* p_dlg = (CFctSet*)m_pFctSet;
	char buff[30*1024] = {0};
	USES_CONVERSION;
	char *p = T2A(p_dlg->m_strfctToDel);
	strcpy_s(buff,p);
	
	hdr header;
	header.type = FCT_DEL_FctSet;
	header.len = HEADLEN + sizeof(buff);
	int errcode = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("����ɾ����������ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	errcode = send(m_sockWhole,(const char*)buff,sizeof(buff),0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("����ɾ����������ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	CString _str = _T("����ɾ�����������ѷ��ͣ��ȴ���������Ӧ");
	UpdateOperationStatus(_str);
	return TRUE;
}

BOOL CSock::ReqDeleteSelCtm()      //��������ɾ���ͻ�����
{
	if(m_pCtmInfo == NULL)
	{
		UpdateOperationStatus(_T("�Ѿ�ȡ��ɾ��Ա������"));
		return TRUE;
	}
	CCtmInfo* p_dlg = (CCtmInfo*)m_pCtmInfo;
	char buff[30*1024] = {0};
	USES_CONVERSION;
	char *p = T2A(p_dlg->m_strToDelCtm);
	strcpy_s(buff,p);
	
	hdr header;
	header.type = CTM_DEL_CtmInfo;
	header.len = HEADLEN + sizeof(buff);
	int errcode = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("����ɾ���ͻ�����ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	errcode = send(m_sockWhole,(const char*)buff,sizeof(buff),0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("����ɾ���ͻ�����ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	CString _str = _T("����ɾ���ͻ������ѷ��ͣ��ȴ���������Ӧ");
	UpdateOperationStatus(_str);
	p_dlg->m_tip.SetWindowText(_str);
	return TRUE;

}

BOOL CSock::ReqDeleteSelEmpInfo_EmpInfoView()   //��������ɾ��Ա������
{
	if(m_pEmpInfoView == NULL)
	{
		UpdateOperationStatus(_T("�Ѿ�ȡ��ɾ��Ա������"));
		return TRUE;
	}
	CEmpInfoView* p_dlg = (CEmpInfoView*)m_pEmpInfoView;
	char buff[30*1024] = {0};
	USES_CONVERSION;
	char *p = T2A(p_dlg->m_empToDelete);
	strcpy_s(buff,p);
	
	hdr header;
	header.type = EMP_DEL_EmpInfoView;
	header.len = HEADLEN + sizeof(buff);
	int errcode = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("����ɾ��Ա������ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	errcode = send(m_sockWhole,(const char*)buff,sizeof(buff),0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("����ɾ��Ա������ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	CString _str = _T("����ɾ��Ա�������ѷ��ͣ��ȴ���������Ӧ");
	UpdateOperationStatus(_str);
	p_dlg->m_tip.SetWindowText(_str);
	return TRUE;
}

BOOL  CSock::ReqMainViewDeleteSelNote()
{
	if(m_pMainFormView == NULL)
	{
		UpdateOperationStatus(_T("�Ѿ�ȡ��ɾ��֪ͨ"));
		return TRUE;
	}
	CMainFormView* p_dlg = (CMainFormView*)m_pMainFormView;
	char buff[30*1024] = {0};
	USES_CONVERSION;
	char *p = T2A(p_dlg->m_noteToDelete);
	strcpy_s(buff,p);
	
	hdr header;
	header.type = DEL_NOTE_MainVIew;
	header.len = HEADLEN + sizeof(buff);
	int errcode = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("����ɾ��֪ͨʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	errcode = send(m_sockWhole,(const char*)buff,sizeof(buff),0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("����ɾ��֪ͨʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	CString _str = _T("����ɾ��֪ͨ�ѷ��ͣ��ȴ���������Ӧ");
	UpdateOperationStatus(_str);
	return TRUE;
}

BOOL  CSock::ReqMainViewInitNote()  //�������֪ͨ
{
	CMainFormView* p_dlg = (CMainFormView*)m_pMainFormView;
	int total = p_dlg->m_nNoteToLook;   //����9�����֪ͨ
	hdr header;
	header.type = INIT_NOTE_MainView;
	header.len = HEADLEN + sizeof(int);
	int errcode = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("�����ʼ��֪ͨʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	errcode = send(m_sockWhole,(const char*)&total,sizeof(int),0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("�����ʼ��֪ͨʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	CString _str = _T("�����ʼ��֪ͨ�ѷ��ͣ��ȴ���������Ӧ");
	UpdateOperationStatus(_str);
	return TRUE;
}

BOOL  CSock::ReqMainViewNotePublic()      //���󷢲�֪ͨ
{
	NotePublic_MainView note;
	memset(&note,0,sizeof(note));
	CNotePublic* p_dlg;
	if(NULL != m_pNotePublic)
	{
		p_dlg = (CNotePublic*)m_pNotePublic;
	}else   //���ͻȻѡ������ֹ���� �������˱������
	{
		p_dlg = NULL;
		return TRUE;
	}
	USES_CONVERSION;
	char *p = T2A(p_dlg->m_content);
	strcpy_s(note.content,p);
	p = T2A(p_dlg->m_title);
	strcpy_s(note.title,p);
	p = T2A(p_dlg->m_personPublicName);
	strcpy_s(note.persion_public,p);
	p = T2A(p_dlg->m_cur_time);
	strcpy_s(note.time_public,p);
	
	
	CString _str = _T("�����ѷ��𣬵ȴ���������Ӧ��");
	p_dlg->m_status.SetWindowText(_str);
	UpdateOperationStatus(_str);

	hdr header;
	header.type = NOTE_PUBLIC_MainView;
	header.len = HEADLEN + sizeof(note);
	int errcode = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("���󷢲�����ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	errcode = send(m_sockWhole,(const char*)&note,sizeof(note),0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("���󷢲�����ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	return TRUE;
}
BOOL CSock::ReqMtNodeDelete()     //����ɾ������ĳ���ڵ�
{
	char buff[100] = {0};
	CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
	if(m_pMtSetProp == NULL){
		UpdateOperationStatus(_T("ȡ��ɾ�����Ͻڵ�"));
		return TRUE;
	}
	USES_CONVERSION;
	char *p = T2A(p_dlg->m_nodeName);
	strcpy_s(buff,p);
	
	CString _str = _T("���������������ɾ�������ӽڵ����󣬵ȴ���������Ӧ��");
	p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
	UpdateOperationStatus(_str);

	hdr header;
	header.type = MT_NODE_DELETE;
	header.len = HEADLEN + sizeof(buff);
	int errcode = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("��������ɾ���������ӽڵ�ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	errcode = send(m_sockWhole,(const char*)buff,sizeof(buff),0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("����ɾ���޸Ĳ������ӽڵ�ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		return FALSE;
	}
	return TRUE;
}

BOOL CSock::ReqMtNodeRename()
{
	CMtSetProp* p_dlg;
	if(m_pMtSetProp != NULL)
	{
		p_dlg = (CMtSetProp*)m_pMtSetProp;
	}else
	{
		UpdateOperationStatus(_T("�ڵ�������ȡ��"));
		return TRUE;
	}
	typedef struct _MtNodeEdit
	{
		char nodeOrgName[30];
		char nodeNewName[30];
	}MtNodeEdit;
	MtNodeEdit node;
	memset(&node,0,sizeof(node));
	USES_CONVERSION;
	char *p_nodeNewName = T2A(p_dlg->m_nodeNameNew_Edit);
	char *p_nodeOrgName = T2A(p_dlg->m_nodeNameOrg_Edit);
	strcpy_s(node.nodeOrgName,p_nodeOrgName);
	strcpy_s(node.nodeNewName,p_nodeNewName);
	hdr header;
	header.type = MT_NODE_RENAME;
	header.len = HEADLEN + sizeof(node);
	int errcode = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("���������޸Ĳ������ӽڵ�ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		return FALSE;
	}
	errcode = send(m_sockWhole,(const char*)&node,sizeof(node),0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("���������޸Ĳ������ӽڵ�ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		return FALSE;
	}
	CString _str = _T("������������������������Ͻڵ����󣬵ȴ���������Ӧ��");
	p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
	UpdateOperationStatus(_str);
	return TRUE;
}

BOOL CSock::ReqMtNodeNew()
{
	CMtSetProp* p_dlg;
	if(m_pMtSetProp != NULL)
	{
		p_dlg = (CMtSetProp*)m_pMtSetProp;
	}else
	{
		UpdateOperationStatus(_T("�Ѿ�ȡ���½����Ͻڵ������"));
		return TRUE;
	}
	typedef struct _MtNodeNew
	{
		char parentNodeName[30];
		char nodeNew[30];
	}MtNodeNew;
	MtNodeNew node;
	memset(&node,0,sizeof(node));
	USES_CONVERSION;
	char *p_nodeNewName = T2A(p_dlg->m_nodeNameNew);
	char *p_parentNode = T2A(p_dlg->m_parentNodeName);
	strcpy_s(node.nodeNew,p_nodeNewName);
	strcpy_s(node.parentNodeName,p_parentNode);
	hdr header;
	header.type = MT_NODE_NEW;
	header.len = HEADLEN + sizeof(node);
	int errcode = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("���������½��������ӽڵ�ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		//CMtSetProp* p_dlg = (CMtSetProp*)m_pVoid;
		p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
		return FALSE;
	}
	errcode = send(m_sockWhole,(const char*)&node,sizeof(node),0);
	if(errcode == SOCKET_ERROR)
	{
		CString _str = _T("���������½��������ӽڵ�ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		//CMtSetProp* p_dlg = (CMtSetProp*)m_pVoid;
		p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
		return FALSE;
	}
	CString _str = _T("�����������������Ͻڵ����󣬵ȴ���������Ӧ��");
	p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
	UpdateOperationStatus(_str);
	return TRUE;
}

BOOL CSock::ReqExpandMtTree()
{
	CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
	if(m_pMtSetProp == NULL){
		UpdateOperationStatus(_T("ȡ��չ��������"));
		return TRUE;
	}
	CString req = p_dlg->m_nodeName;
	USES_CONVERSION;
	char *p = T2A(req);
	char buff[100] = {0};
	strcpy_s(buff,p);
	hdr header;
	header.type = EXPAND_MATERIAL_TREE;
	header.len = HEADLEN + sizeof(buff);
	int nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		CString _str = _T("��������������ӽڵ�ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
		return FALSE;
	}
	nflag = send(m_sockWhole,(const char*)buff,sizeof(buff),0);
	if(nflag == SOCKET_ERROR)
	{
		CString _str = _T("��������������ӽڵ�ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
		return FALSE;
	}
	return TRUE;
}

BOOL CSock::ReqInitMtTree()
{
	hdr header;
	header.type = INIT_MATERIAL_TREE;
	header.len = HEADLEN ;
	int nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		CString _str = _T("���ͳ�ʼ�����������ݰ�ʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		if(NULL != m_pMtSetProp){
			CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
			p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
		}else{
			AfxMessageBox(_T("���ͳ�ʼ�����������ݰ�ʧ�ܣ������Ի����µ�¼"));
		}
		return FALSE;
	}
	if(NULL != m_pMtSetProp)
	{
		CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
		p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)_T("�ȴ���������Ӧ!"));
		p_dlg->SendMessage(WM_CLEARMTTREE_MtSetProp,0,0);
	}else{
		UpdateOperationStatus(_T("�����ʼ��������,�ȴ���������Ӧ!"));
	}
	return TRUE;
}

BOOL CSock::ReqKeepHeart()
{
	int heartPackage = 1;
	hdr header;
	header.type = HEART_PACKAGE;
	header.len = HEADLEN + sizeof(int);
	int nflag = send(m_sockWhole,(const char*)&header,HEADLEN,0);
	if(nflag == SOCKET_ERROR)
	{
		CString _str = _T("������������Ϣʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		//m_bReqAvailable = TRUE;   //ʹ��������� ֻҪ�н�� ���ܷ����µ�����
		return FALSE;
	}

	nflag = send(m_sockWhole,(const char*)&heartPackage,sizeof(int),0);
	if(nflag == SOCKET_ERROR)
	{
		CString _str = _T("������������Ϣʧ�ܣ������Ի����µ�¼");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		//m_bReqAvailable = TRUE;   //ʹ��������� ֻҪ�н�� ���ܷ����µ�����
		return FALSE;
	}
	CString str = _T("������������������ѷ��ͣ�");
	UpdateOperationStatus(str);
	return TRUE;
}


BOOL CSock::RecvReplyOfNotePublicMainView(int len)   //���շ��������ڷ����¹���Ļظ�
{
	int result;
	int errCode = recv(m_sockWhole,(char *)&result,len,0);
	CString tip;
	if(errCode == SOCKET_ERROR)
	{
		CString _str = _T("���շ������ظ�ʧ�ܣ�");
		AfxMessageBox(_str);
		return FALSE;
	}
	switch(result)
	{
	case -1:
		{
			tip = _T("���󷢲�����ʧ�ܣ�ԭ�����ݿ�����ʧ��,������");
			break;
		}
	case 1:
		{
			tip = _T("��ϲ�������ɹ���");
			break;
		}
	case 0:
		{
			tip = _T("���󷢲�����ʧ�ܣ�δ֪ԭ��,�����Ի���ϵ����Ա");
			break;
		}
	default:
		break;
	}
	if(NULL != m_pNotePublic)
	{
		((CNotePublic*)m_pNotePublic)->m_status.SetWindowText(tip);
		if(result == 1)
		{
			((CNotePublic*)m_pNotePublic)->SendMessage(WM_NOTEPUBLICSUCCESS_NotePublic,0,0);
		}
	}
	UpdateOperationStatus(tip);
	return TRUE;
}

BOOL CSock::RecvReplyOfMtNodeDelete(int len)
{
	int result;
	int errCode = recv(m_sockWhole,(char *)&result,len,0);
	if(errCode == SOCKET_ERROR)
	{
		CString _str = _T("���ղ�������Ϣʧ�ܣ�");
		AfxMessageBox(_str);
		m_pMtSetProp = NULL;
		//m_bReqAvailable = TRUE;   //ʹ��������� ֻҪ�н�� ���ܷ����µ�����
		return FALSE;
	}
	switch(result)
	{
	case 0:
		{
			CString _str = _T("ɾ������ʧ�ܣ����ݿ�����ʧ��,������");
			if(m_pMtSetProp!= NULL){
				CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
				p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
				p_dlg->SendMessage(WM_ENDREQMT_MtSetProp,0,0);
			}
			UpdateOperationStatus(_str);
			break;
		}
	case 1:
		{
			CString _str = _T("��ϲ��ɾ���ڵ�ɹ���");
			if(m_pMtSetProp!= NULL){
				CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
				p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
				p_dlg->SendMessage(WM_ENDREQMT_MtSetProp,0,0);
			}
			UpdateOperationStatus(_str);
			break;
		}
	case -1:
		{
			CString _str = _T("ɾ������ʧ�ܣ�����δ֪ԭ����ɵ�ʧ�ܣ�������");
			if(m_pMtSetProp!= NULL){
				CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
				p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
				p_dlg->SendMessage(WM_ENDREQMT_MtSetProp,0,0);
			}
			UpdateOperationStatus(_str);
			break;
		}
	default:
		break;
	}
	m_pMtSetProp = NULL;
	//m_bReqAvailable = TRUE;   //ʹ��������� ֻҪ�н�� ���ܷ����µ�����
	return TRUE;
}

BOOL CSock::RecvReplyOfMtNodeRename(int len)
{
	int result;
	int errCode = recv(m_sockWhole,(char *)&result,len,0);
	if(errCode == SOCKET_ERROR)
	{
		CString _str = _T("���ղ�������Ϣʧ�ܣ�");
		AfxMessageBox(_str);
		m_pMtSetProp = NULL;
		//m_bReqAvailable = TRUE;   //ʹ��������� ֻҪ�н�� ���ܷ����µ�����
		return FALSE;
	}
	CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
	if(m_pMtSetProp == NULL)
	{
		return TRUE;
	}
	switch(result)
	{
	case 0:
		{
			CString _str = _T("�޸�����ʧ�ܣ��½ڵ����Ѵ���");
			//CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
			p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
			p_dlg->SendMessage(WM_ENDREQMT_MtSetProp,0,0);
			UpdateOperationStatus(_str);
			break;
		}
	case 1:
		{
			CString _str = _T("��ϲ���޸Ľڵ�ɹ���");
			//CMtSetProp* p_dlg = (CMtSetProp*)m_pVoid;
			p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
			p_dlg->SendMessage(WM_ENDREQMT_MtSetProp,0,0);
			UpdateOperationStatus(_str);
			break;
		}
	default:
		break;
	}
	m_pMtSetProp = NULL;
	//m_bReqAvailable = TRUE;   //ʹ��������� ֻҪ�н�� ���ܷ����µ�����
	return TRUE;
}

BOOL CSock::RecvReplyOfMtNodeNew(int len)   //�����½��������Ľڵ���Ϣ
{
	int result;
	int errCode = recv(m_sockWhole,(char *)&result,len,0);
	if(errCode == SOCKET_ERROR)
	{
		CString _str = _T("���ղ�������Ϣʧ�ܣ�");
		AfxMessageBox(_str);
		if(m_pMtSetProp != NULL){
			CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
			p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
		}//m_bReqAvailable = TRUE;   //ʹ��������� ֻҪ�н�� ���ܷ����µ�����
		return FALSE;
	}
	switch (result)
	{
	case -1:
		{
			CString _str = _T("���ϼ��ڵ㲻���ڣ������½ڵ�ʧ��");
			if(m_pMtSetProp != NULL){
				CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
				p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
				p_dlg->SendMessage(WM_ENDREQMT_MtSetProp,0,0);
			}
			UpdateOperationStatus(_str);
			break;
		}
	case 0:
		{
			CString _str = _T("�½��ڵ��Ѿ����ڣ�����ʧ��");
			if(m_pMtSetProp != NULL){
				CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
				p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
				p_dlg->SendMessage(WM_ENDREQMT_MtSetProp,0,0);
			}
			UpdateOperationStatus(_str);
			break;
		}
	case 1:
		{
			CString _str = _T("��ϲ���½��ڵ�ɹ���");
			if(m_pMtSetProp != NULL){
				CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
				p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
				p_dlg->SendMessage(WM_ENDREQMT_MtSetProp,0,0);
			}
			UpdateOperationStatus(_str);
			break;
		}
	default:
		break;
	}
	//m_bReqAvailable = TRUE;   //ʹ��������� ֻҪ�н�� ���ܷ����µ�����
	return TRUE;
}

BOOL CSock::RecvReplyOfInitMtTree(int len)
{
	if(len)
	{
		char buff[1024*55];
		int errCode = recv(m_sockWhole,(char *)buff,len,0);
		if(errCode == SOCKET_ERROR)
		{
			CString _str = _T("���ղ�������Ϣʧ�ܣ�");
			AfxMessageBox(_str);
			if(m_pMtSetProp != NULL){
				CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
				p_dlg->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
			}
			m_pMtSetProp  = NULL;
			return FALSE;
		}
		USES_CONVERSION;
		CString temp = NULL;
		temp = A2T(buff);
		if(m_pMtSetProp != NULL){
			CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
			p_dlg->m_strMtInfo = temp;
			p_dlg->SendMessage(WM_ENDREQMT_MtSetProp,0,0);
		}else{
			UpdateOperationStatus(_T("�������ѻ�Ӧ��ʼ������������"));
		}
	}else{   //�������
		CString  _str = _T("���ղ�������Ϣ��ϣ�");
		if(m_pMtSetProp != NULL)
		{
			((CMtSetProp*)m_pMtSetProp)->SendMessage(WM_UPDATESTATUS_MtSetProp,0,(LPARAM)(LPCTSTR)_str);
			CMtSetProp* p_dlg = (CMtSetProp*)m_pMtSetProp;
			p_dlg->SendMessage(WM_PAITMTTREE,0,0);
			m_pMtSetProp = NULL;
		}
	}
	
	return TRUE;
}

BOOL CSock::RecvReplyOfKeepHeart(int len)
{
	BOOL conning = FALSE;
	int errCode = recv(m_sockWhole,(char *)&conning,len,0);
	if(errCode == SOCKET_ERROR)
	{
		CString _str = _T("���ձ����������Ļظ���Ϣʧ��");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		//m_bReqAvailable = TRUE;   //ʹ��������� ֻҪ�н�� ���ܷ����µ�����
		return FALSE;
	}
	if(FALSE == conning )
	{
		CString _str = _T("��������Ͽ����ӣ������µ�¼��");
		AfxMessageBox(_str);
		UpdateOperationStatus(_str);
		//m_bReqAvailable = TRUE;   //ʹ��������� ֻҪ�н�� ���ܷ����µ�����
		return FALSE;
	}
	CString _str = _T("�����������������");
	UpdateOperationStatus(_str);
	return TRUE;
}

BOOL CSock::RecvReplyOfServModify(int len)   //�޸ķ���
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����޸ķ���Ļظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{

	case -1:            //�޸Ŀͻ�����ʧ��ԭ�� ���ݿ����ƴ���
		{
			tip = _T("�޸Ŀͻ�����ʧ��,ԭ�������ݿ����ƴ���");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("�޸Ŀͻ�����ʧ��,δ֪ԭ��");
			break;	
		}
	case 1:
		{
			tip = _T("��ϲ���޸Ŀͻ����ϳɹ���");
			break;		
		}
	default:
		break;
	}
	if(NULL != m_pServModify)
	{
		CServModify* pDlg = (CServModify*)m_pServModify;
		//pDlg->SendMessage(WM_ENDTASK_ServModify,0,0);
		pDlg->m_tip.SetWindowText(tip);
		m_pServModify = NULL;
	}
	UpdateOperationStatus(tip);
	return TRUE;
}

BOOL CSock::RecvReplyOfCtmEdit(int len)   //�����޸Ŀͻ����ϵĽ��
{
	CString tip = NULL;
	int flag;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���ձ༭�ͻ����ϵĻظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -1:            //�޸Ŀͻ�����ʧ��ԭ�� ���ݿ����ƴ���
		{
			tip = _T("�޸Ŀͻ�����ʧ��,ԭ�������ݿ����ƴ���");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("�޸Ŀͻ�����ʧ��,δ֪ԭ��");
			break;	
		}
	case 1:
		{
			tip = _T("��ϲ���޸Ŀͻ����ϳɹ���");
			break;		
		}
	default:
		break;
	}
	if(NULL != m_pCtmEdit)
	{
		CCtmEdit* pDlg = (CCtmEdit*)m_pCtmEdit;
		//pDlg->SendMessage(WM_ENDTASK_CtmEdit,0,0);
		pDlg->m_tip.SetWindowText(tip);
		m_pCtmEdit = NULL;
	}else{
		AfxMessageBox(tip);
	}
	UpdateOperationStatus(tip);
	return TRUE;
}

BOOL CSock::RecvReplyOfFctEdit(int len)      //���շ����������޸ĳ������ϵĻظ�
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���ձ༭�������ϵĻظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -1:            //�޸ĳ�������ʧ��ԭ�� ���ݿ����ƴ���
		{
			tip = _T("�޸ĳ�������ʧ��,ԭ�������ݿ����ƴ���");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("�޸�Ա������ʧ��,ԭ��δ֪�������ԣ�");
			break;	
		}
	case 1:
		{
			tip = _T("��ϲ���޸ĸ�Ա�����ϳɹ�");
			break;	
		}
	default:
		break;
	}
	if(NULL != m_pFactoryEdit)
	{
		CFactoryEdit* pDlg = (CFactoryEdit*)m_pFactoryEdit;
		//pDlg->SendMessage(WM_ENDTASK_FctEdit,0,0);
		pDlg->m_tip.SetWindowText(_T("��ϲ���޸ĸ�Ա�����ϳɹ�"));
		m_pFactoryEdit = NULL;
	}else{
		AfxMessageBox(_T("��ϲ���޸ĸ�Ա�����ϳɹ�"));
	}
	UpdateOperationStatus(_T("��ϲ���޸ĸ�Ա�����ϳɹ�"));
	return TRUE;
}

/*
 *	�����ļ��߳�
 */
DWORD CSock::DownloadFileThread(void* pParam)
{
	WT;
	pFileDownloadParam pFileDownload = (pFileDownloadParam)pParam;
	unsigned short usID = pFileDownload->ID;		//�߳����
	SOCKET sFileDownload = pFileDownload->s;		//�׽���
	hdr header = pFileDownload->header;				//��ͷ
	CString strFile = A2T(pFileDownload->strFilePath);	//�����ļ�
	char buff[MAX_PATH] = {0};
	strcpy_s(buff,pFileDownload->strFilePath);
	int len = sizeof(buff);
	CDealListView *p_dlg = (CDealListView *)pFileDownload->ptr;		//ָ��
	if(NULL != pFileDownload){
		delete pFileDownload;//�ͷ��ڴ�
		pFileDownload = NULL;
	}
	int nErrCode;//����ֵ

	//���Ͱ�ͷ
	nErrCode = send(sFileDownload, (char*)&header, HEADLEN, 0);
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("�����ļ������������ݰ�ʧ�ܣ�"));
		return 0;
	}
	
	//���Ͱ���
	nErrCode = send(sFileDownload, buff, len, 0);
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("�����ļ������������ݰ�ʧ�ܣ�"));
		return 0;
	}

	FD_SET readfd;//�ɶ�����
	FD_SET writefd;   //��д����
	//�����ļ�
	while (CSock::m_bIsConnecting && CSock::m_bOnline)
	{
		FD_ZERO(&readfd);
		FD_ZERO(&writefd);						//��ռ���
		FD_SET(sFileDownload, &readfd);					//���뼯��
		FD_SET(sFileDownload,&writefd);
		nErrCode = select(0, &readfd, &writefd, NULL, NULL);//�ȴ�
		extern int errno;
		if (SOCKET_ERROR == nErrCode)					//����
		{
			int err = WSAGetLastError();
			CString _err_1;
			_err_1.Format(_T("�����ļ�ʱ��select socketʧ��,SOCKET_ERROR����%d"),err);
			AfxMessageBox(_err_1);
			return 0;
		}
		
		if (nErrCode > 0)
		{
			if (FD_ISSET(sFileDownload, &readfd)&& CSock::m_bOnline)						//���Զ��ļ�
			{
				int nErr = RecvFileData(sFileDownload, usID,p_dlg);	//�����ļ�
				if (EXCEPT == nErr)
				{
					AfxMessageBox(_T("�����ļ������쳣���ѹر�����"));
					return 0;
				}else if (FINISH == nErr)								//���ؽ���
				{
					return 0;
				}
			}
		}
		Sleep(THREAD_SLEEP);
	}
	return 0;
}

/*
 * �����ļ������߳�
 */
DWORD CSock::CreateDownloadFileThread(void *pParam)
{
	WT;
	CDealListView* p_dlg = (CDealListView*)pParam;
	HANDLE  hThreadFileDL[MAX_RECVFILE_THREAD];			//�����ļ��߳̾������
	SOCKET  sFileDL[MAX_RECVFILE_THREAD];				//�����ļ��׽�������

	u_long ulFileSize = p_dlg->m_ulFileSize;		//�ļ�����
	CString strFile = p_dlg->m_ulFilePath;				//�����ļ�·�����ļ���
	char buff[MAX_PATH] = {0};
	int len = sizeof(buff);
	u_long ulSegment = ulFileSize / MAX_RECVFILE_THREAD;//ÿ���߳������ļ�ƽ������

	hdr header[MAX_RECVFILE_THREAD];					//�����ͷ
	for (int i = 0; i < MAX_RECVFILE_THREAD; ++i)
	{
		memset(&header[i], 0, sizeof(hdr));
		header[i].type = REQ_FILE_DOWNLOAD;				//��������
		header[i].len = HEADLEN + len;		//���ݰ�����
		header[i].fpos = i * ulSegment;					//�����ļ���ʼλ��
		if (i != MAX_RECVFILE_THREAD -1)				//�����ļ�����
		{
			header[i].flen = ulSegment;
		}else
		{
			header[i].flen = ulFileSize - ulSegment * i;//���һ���߳�����ʣ���ļ�����
		}
		
		SOCKET sFileData = INVALID_SOCKET;
		if (FALSE == p_dlg->CreateSocket(sFileData))	//�����׽���
		{
			AfxMessageBox(_T("���������׽���ʧ�ܣ�"));
			return FALSE;
		}
		sFileDL[i] = sFileData;

		//�����̺߳������ݲ���
		pFileDownloadParam pThreadPara= new FileDownloadParam();
		pThreadPara->ID = i;
		pThreadPara->header = header[i];
		pThreadPara->s = sFileDL[i];
		pThreadPara->ptr = p_dlg;
		strcpy_s(pThreadPara->strFilePath,T2A(strFile));

		//���������ļ��߳�
		DWORD dwThread;		
		hThreadFileDL[i] = CreateThread(NULL, 0, DownloadFileThread, pThreadPara, 0, &dwThread);
	}

	//�ȴ��ļ������̵߳��˳�
	WaitForMultipleObjects(MAX_RECVFILE_THREAD, hThreadFileDL, TRUE, INFINITE);	

	AssemblyFile(p_dlg);							//�ϲ��ļ�
	p_dlg->SendMessage(WM_VALID_FILEDL_DealListView,0,0);
	//p_dlg->m_tip.SetWindowText(_T("�����ļ�����!"));//��ʾ��Ϣ

	//pClient->EnableSomeControl(TRUE);					//ʹ�ؼ���Ч
	
	//p_dlg->ResetCurFileDL();							//���ؽ�����
	
	for (int i = 0; i < MAX_RECVFILE_THREAD; ++i)			//������Դ
	{
		CloseHandle(hThreadFileDL[i]);
		closesocket(sFileDL[i]);
	}
	return 0;
}

void CSock::PrepareFileDownload(void)
{
	DWORD dwThreadID;
	m_hThreadFileDL = CreateThread(NULL, 0, CreateDownloadFileThread, m_pDealListView, 0, &dwThreadID);
	CloseHandle(m_hThreadFileDL);
}

BOOL CSock::RecvReplyOfDLFile(int len,char *strFilePath)        //���������ļ��Ļظ�
{
	WT;
	CDealListView* p_view = (CDealListView*)m_pDealListView;
	p_view->m_ulFileSize = len;	//�����ļ���С
	p_view->m_ulFilePath = A2T(strFilePath);
	if(len == -1)
	{
		p_view->SendMessage(WM_ENDDLOAD_DealListView,0,0);
		p_view->m_tip.SetWindowText(_T("��Ǹ���������˸ø��������Ѿ�����ɾ���ˣ��޷��������"));
		return TRUE;
	}else{
		PrepareFileDownload();		//׼�������ļ������߳�
		m_nCurReq = REQNON;			//���÷��ͱ�־
		return TRUE;
	}
}
	/*
	CDealListView* p_view = (CDealListView*)m_pDealListView;
	char nRecv[SEND_BUFF] = {0};
	int nReadLen = 0;
	if(len == 0)   //�û��ϴ��ļ��Ѿ�����
	{
		p_view->SendMessage(WM_VALID_FILEDL_DealListView,0,0);
		return TRUE;
	}else{   //�����ļ� ��д��
		u_long nlTotal = 0;
		CString strTemp = p_view->m_strFilePath + p_view->m_fileDlInfo.filename;  //�����ļ�·��
		CFile file(strTemp, CFile::modeCreate|CFile::modeWrite| CFile::typeBinary|CFile::modeNoTruncate);
		while (CSock::m_bIsConnecting && nlTotal != len)
		{
			memset(nRecv, 0, SEND_BUFF);
			nReadLen = recv(m_sockWhole,(char *)&nRecv,len,0);//׼������1024*10���ֽڳ���
			if (SOCKET_ERROR == nReadLen)
			{
				p_view->SendMessage(WM_ENDTASK_DealListView,0,0);
				p_view->SendMessage(WM_RESETDLSTATUS_DealListView,0,0);
				p_view->m_tip.SetWindowText(_T("�����ļ���������������"));
				memset(&nRecv,0,sizeof(nRecv));
				return TRUE;
			}else if (0 == nReadLen)
			{
				int err = WSAGetLastError();
				p_view->SendMessage(WM_ENDTASK_DealListView,0,0);
				p_view->SendMessage(WM_RESETDLSTATUS_DealListView,0,0);
				p_view->m_tip.SetWindowText(_T("�����ļ���������������"));
				memset(&nRecv,0,sizeof(nRecv));
				return TRUE;
			}
			file.SeekToEnd();
			//file.Write(nRecv,nReadLen);
			file.Write(nRecv,nReadLen);
			nlTotal += nReadLen;//��������ֽ���
			p_view->m_ulCurTotal += nlTotal;
		}
		file.Close();
		return TRUE;
	}
	*/


BOOL CSock::RecvReplyOfUploadFile(int len)    //�ϴ��ļ��Ľ��
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����ϴ��ļ��Ľ��ʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -2:
		{
			tip = _T("�ϴ�ʧ�ܣ��ļ��Ѿ��𻵣��������ϴ���");
			break;
		}
	case -1:            //ɾ������ʧ��ԭ�� ���ݿ����ƴ���
		{
			tip = _T("�ϴ��ɹ�,��δ�ܼ��뵽���ݿ⣬���ݿ�����ʧ�ܣ������ԣ�");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("�ϴ��ɹ�,��δ�ܼ��뵽���ݿ⣬���ݿ����ʧ�ܣ�������");
			break;			
		}
	case 1:
		{
			tip = _T("��ϲ���ϴ��ɹ�");
			break;
		}
	default:
		break;
	}
	if(m_pOrderContent != NULL){
		COrderContent* pDlg = (COrderContent*)m_pOrderContent;
		pDlg->SendMessage(WM_ENDTASK_OrderContent,0,0);
		pDlg->m_tip.SetWindowText(tip);
		if(flag == 1){
			pDlg->m_static_upload_status.SetWindowText(_T("�ϴ��ɹ�"));
		}else{
			pDlg->m_static_upload_status.SetWindowText(_T("�ϴ�ʧ��"));
		}
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfFileDLInfo(int len)   //���������ļ�����Ϣ
{
	CDealListView* p_view = (CDealListView*)m_pDealListView;
	FileInfo  file;
	memset(&file,0,sizeof(FileInfo));
	int errCode = recv(m_sockWhole,(char *)&file,len,0);
	if(errCode == SOCKET_ERROR)
	{
		p_view->SendMessage(WM_ENDTASK_DealListView,0,0);
		p_view->SendMessage(WM_RESETDLSTATUS_DealListView,0,0);
		p_view->m_tip.SetWindowText(_T("���������ļ�����Ϣʧ��,��������"));
		return TRUE;
	}else if(errCode == 0){
		p_view->SendMessage(WM_ENDTASK_DealListView,0,0);
		p_view->SendMessage(WM_RESETDLSTATUS_DealListView,0,0);
		p_view->m_tip.SetWindowText(_T("���������ļ�����Ϣʧ��,������"));
		return TRUE;
	}else{
		memset(&p_view->m_fileDlInfo,0,sizeof(FileInfo));
		p_view->m_fileDlInfo = file;
		if( 0 == strlen(file.filename))   //���ظ����ļ��� Ϊ�� ����������� û���ҵ�Ҫ���ص��ļ�
		{
			p_view->SendMessage(WM_ENDTASK_DealListView,0,0);
			p_view->SendMessage(WM_RESETDLSTATUS_DealListView,0,0);
			p_view->m_tip.SetWindowText(_T("��Ǹ����Ҫ���صĸ����Ѿ���ɾ�����޷�����"));
			return TRUE;
		}
		p_view->m_ulFileSize = p_view->m_fileDlInfo.filesize;   //�ļ����ܴ�С
		return TRUE;
	}
}

BOOL CSock::RecvReplyOfCheckFile(int len)   //�ظ����ļ��Ƿ���ڵĽ��
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���ռ���ļ��Ƿ���ڵĻظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -2:
		{
			tip = _T("�ö������и�����");
			break;
		}
	case -1:            //ɾ������ʧ��ԭ�� ���ݿ����ƴ���
		{
			tip = _T("У��ʧ��,�����ԣ�");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("У��ʧ�ܣ�������");
			break;			
		}
	case 1:
		{
			tip = _T("�ö�����ʱ��û�и���");
			break;
		}
	default:
		break;
	}
	if(m_pOrderContent != NULL){
		COrderContent* pDlg = (COrderContent*)m_pOrderContent;
		pDlg->SendMessage(WM_ENDTASK_OrderContent,0,0);
		pDlg->m_tip.SetWindowText(tip);
		pDlg->m_static_upload_status.SetWindowText(_T("У�����"));
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfUpdateOrderBatch(int len)     //�������¶������ݵĻظ�
{
	WT;
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����������¶������ݵĻظ���Ϣʧ��"));
		return FALSE;
	}
	
	switch (flag)
	{
	case -1:
		{
			tip = _T("��������ʧ�ܣ�ԭ���������ݿ�ʧ�ܣ������Ի���ϵ����Ա");
			break;
		}
	case 1:
		{
			tip = _T("�������ݳɹ�");
			break;
		}
	case 0:
		{
			tip = _T("��������ʧ�ܣ�δ֪ԭ�������Ի���ϵ����Ա");
			break;
		}
	default:
		break;
	}
	COrderIncompletedProgView* pDlg = (COrderIncompletedProgView*)m_pOrderIncompleteView;
	if(pDlg != NULL)
	{
		//pDlg->SendMessage(WM_ENDTASK_OrderIncomplete,0,0);
		pDlg->m_tip.SetWindowText(tip);
		m_pOrderIncompleteView = NULL;
	}else{
		AfxMessageBox(tip);
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfCtmInfoIm(int len)    //�����ύ�ͻ����ݵ����ݿ�
{
	WT;
	char buff[1024] = {0};
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)buff,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���������ύ�ͻ����ݵĻظ���Ϣʧ��"));
		return FALSE;
	}
	tip = A2T(buff);
	CCustomInfoProp* pDlg = (CCustomInfoProp*)m_pCtmSubmit;
	if(pDlg != NULL)
	{
		pDlg->SendMessage(WM_ENDTASK_CtmIM,0,0);
		pDlg->m_tip.SetWindowText(_T("����"));
	}
	AfxMessageBox(tip);
	return TRUE;
}

BOOL CSock::RecvReplyOfEmpInfoIm(int len)    //��������Ա�����ݵĻظ�
{
	WT;
	char buff[1024] = {0};
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)buff,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("������������Ա�����ݵĻظ���Ϣʧ��"));
		return FALSE;
	}
	tip = A2T(buff);
	CEmpInfoProp* pDlg = (CEmpInfoProp*)m_pEmpInfoIm;
	if(pDlg != NULL)
	{
		pDlg->SendMessage(WM_ENDTASK_EmpInfoProp,0,0);
		pDlg->m_tip.SetWindowText(_T("����"));
	}
	AfxMessageBox(tip);
	return TRUE;
}

BOOL CSock::RecvReplyOfProdInfoIm(int len)   //���������Ʒ���ݵĽ��
{
	WT;
	char buff[1024] = {0};
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)buff,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�������������Ʒ���ݵĻظ���Ϣʧ��"));
		return FALSE;
	}
	tip = A2T(buff);
	CProdInfoProp* pDlg = (CProdInfoProp*)m_pProdBatch;
	if(pDlg != NULL)
	{
		pDlg->SendMessage(WM_ENDTASK_ProdIm,0,0);
		pDlg->m_tip.SetWindowText(_T("����"));
	}
	AfxMessageBox(tip);
	return TRUE;
}

BOOL CSock::RecvReplyOfPswEdit(int len)    //�޸�����Ľ��
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����޸�����Ļظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -2:
		{
			tip = _T("�޸�����ʧ��,��������ȷ�����룡");
			break;
		}
	case -1:            //�޸�����ʧ��ԭ�� ���ݿ����ƴ���
		{
			tip = _T("�޸�����,ԭ�������ݿ����ƴ���");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("�޸�����ʧ��,δ֪ԭ���������������״̬������");
			break;			
		}
	case 1:
		{
			tip = _T("��ϲ���޸ĳɹ��������µ�¼");
			m_bIsConnecting = FALSE;     //���ӶϿ� ���û����µ�¼
			m_bOnline = FALSE;        // �Ͽ��ߺ� ���Ӳ�����
			m_nameOnline.Empty();     //�Ͽ����Ӻ� ������ߵ��û���
					//m_bReqAvailable = TRUE;   //ʹ���������
			((CBMApp*)AfxGetApp())->m_sHost = INVALID_SOCKET; 
			closesocket(m_sockWhole);
			m_sockWhole = INVALID_SOCKET;

			break;
		}
	default:
		break;
	}
	CPwdEdit* pDlg = (CPwdEdit*)m_pPwdEdit;
	if(pDlg != NULL)
	{
		pDlg->SendMessage(WM_ENDTASK_PwdEdit,0,0);
		pDlg->m_tip.SetWindowText(tip);
	}else{
		AfxMessageBox(tip);
	}
	
	return TRUE;
}

BOOL CSock::RecvReplyOfPosAuthority(int len)     //�����û�Ȩ��
{
	CString tip = NULL;
	char buff[1024] = {0};
	int errCode = recv(m_sockWhole,buff,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����û�Ȩ�޵Ļظ���Ϣʧ��"));
		return FALSE;
	}
	InitUserAuthority(buff);
	return TRUE;
}

void CSock::InitUserAuthority(char *p)
{
	WT;
	if( NULL == m_pPosAuthority)
	{
		m_pPosAuthority = new Pos_Authority;
	}
	CString authority = A2T(p);
	for(int i=0;i<NUM_AUTHORITY;i++)
	{
		CString temp = GetItemFromString(authority,i+1);
		if(temp.IsEmpty())
		{
			m_pPosAuthority->autority[i] = FALSE;
		}else if(IsNum(temp,FALSE))
		{
			if(atoi(T2A(temp)) == 0)
			{
				m_pPosAuthority->autority[i] = FALSE;
			}else if(atoi(T2A(temp)) == 1)
			{
				m_pPosAuthority->autority[i] = TRUE;
			}else{
				if(NULL != m_pPosAuthority)
				{
					delete m_pPosAuthority;
					m_pPosAuthority = NULL;
				}
				break;
			}
		}else{
			if(NULL != m_pPosAuthority)
			{
				delete m_pPosAuthority;
				m_pPosAuthority = NULL;
			}
			break;
		}
	}
	m_pPosAuthority->bLoadSuccess = TRUE;
	UpdateOperationStatus(_T("�û�Ȩ�޼������"));
}

CString CSock::GetItemFromString(CString source,int index)     //���ַ�����ȡ����������
{
	CString _str_source = source;
	CString subItem = NULL;
	CString sub_str_start = _T("[#");
	CString sub_str_end = _T("#]");
	CString temp = NULL;
	int i = 0;
	while(TRUE)
	{
		int index_t = _str_source.Find(sub_str_start);
		if(-1 == index_t)   //��ʾû�ҵ� ��ζ�� ������
		{
			break;
		}else{
			i++;
			if( i == index)   //�ҵ��˶�Ӧ������
			{
				_str_source = _str_source.Mid(index_t+2);
				index_t = _str_source.Find(sub_str_end);
				subItem = _str_source.Mid(0,index_t);
				break;
			}else{   //û�ҵ� ����
				_str_source = _str_source.Mid(index_t+2);
			}
		}
	}	
	return subItem;
}

BOOL CSock::RecvReplyOfPosEdit(int len)     //�����޸��û��Ļظ�
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���ձ༭�û��Ļظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -1:            //�������û�ʧ��ԭ�� ���ݿ����ƴ���
		{
			tip = _T("�༭�û�ʧ��,ԭ�����������ݿ�ʧ�ܣ������ԣ�");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("�༭�û�ʧ��,δ֪ԭ���������������״̬������");
			break;			
		}
	case 1:
		{
			tip = _T("��ϲ���༭�û��ɹ�");		
			break;
		}
	default:
		break;
	}
	CPosEdit* pDlg = (CPosEdit*)m_pPosEdit;
	//pDlg->SendMessage(WM_ENDTASK_PosEdit,0,0);
	pDlg->m_tip.SetWindowText(tip);
	m_pPosEdit = NULL;
	return TRUE;
}

BOOL CSock::RecvReplyOfPosAdd(int len)    //�������û��Ļظ�
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���մ������û��Ļظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -2:
		{
			tip = _T("�������û�ʧ��,ԭ���Ǹ��û����Ѵ��ڣ�������������");
			break;
		}
	case -1:            //�������û�ʧ��ԭ�� ���ݿ����ƴ���
		{
			tip = _T("�������û�ʧ��,ԭ�����������ݿ�ʧ�ܣ������ԣ�");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("������û�ʧ��,δ֪ԭ���������������״̬������");
			break;			
		}
	case 1:
		{
			tip = _T("��ϲ��������û��ɹ�");		
			break;
		}
	default:
		break;
	}
	CPosAdd* pDlg = (CPosAdd*)m_pPosAdd;
	//pDlg->SendMessage(WM_ENDTASK_PosAdd,0,0);
	pDlg->m_tip.SetWindowText(tip);
	m_pPosAdd = NULL;
	return TRUE;
}

BOOL CSock::RecvReplyOfUsersInit(int len)      //���շ������������û�Ȩ��
{
	WT;
	CString tip = NULL;
	char  buff[1024] = {0};
	int errCode = recv(m_sockWhole,(char *)buff,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����û�Ȩ�޵Ļظ���Ϣʧ��"));
		return FALSE;
	}
	
	if(NULL != m_pPosEdit)
	{
		tip = _T("���յ��������������û�Ȩ�ޣ����ڳ�ʼ���û���Ϣ");
		CPosEdit* pDlg = (CPosEdit*)m_pPosEdit;
		pDlg->SendMessage(WM_ENDTASK_PosEdit,0,0);
		pDlg->m_tip.SetWindowText(tip);
		pDlg->m_str_pos_authorities = A2T(buff);
		pDlg->SendMessage(WM_INITUSER_AUTHORITY_PosEdit,0,0);
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfUsersDel(int len)    //�ظ�ɾ���û�
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����ɾ���û��Ļظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -1:            //ɾ������ʧ��ԭ�� ���ݿ����ƴ���
		{
			tip = _T("ɾ��ʧ��,ԭ�������ݿ����ӳ���");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("ɾ��ʧ��,δ֪ԭ���������������״̬������");
			break;			
		}
	case 1:
		{
			tip = _T("��ϲ��ɾ���ɹ�");
			break;
		}
	default:
		break;
	}
	if(NULL != m_pSysPostion)
	{
		CSysPostion* pDlg = (CSysPostion*)m_pSysPostion;
		//pDlg->SendMessage(WM_ENDTASK_SysPostion,0,0);
		pDlg->m_tip.SetWindowText(tip);
		if(1 == flag)
		{
			pDlg->SendMessage(WM_DEL_USERS_SysPostion,0,0);
		}
		m_pSysPostion = NULL;
	}
	UpdateOperationStatus(tip);
	return TRUE;
}

BOOL CSock::RecvReplyOfDealDel(int len)      //�ظ�ɾ������������
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����ɾ����Ϣ�Ļظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -1:            //ɾ������ʧ��ԭ�� ���ݿ����ƴ���
		{
			tip = _T("ɾ��ʧ��,ԭ�������ݿ����ƴ���");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("ɾ��ʧ��,δ֪ԭ���������������״̬������");
			break;			
		}
	case 1:
		{
			tip = _T("��ϲ��ɾ���ɹ�");
			CDealListView* pDlg = (CDealListView*)m_pDealListView;
			pDlg->SendMessage(WM_DEL_DEAL_DealListView,0,0);
			break;
		}
	default:
		break;
	}
	CDealListView* pDlg = (CDealListView*)m_pDealListView;
	//pDlg->SendMessage(WM_ENDTASK_DealListView,0,0);
	pDlg->m_tip.SetWindowText(tip);
	m_pDealListView = NULL;
	return TRUE;
}

BOOL CSock::RecvReplyOfServDel(int len)   //�ظ�ɾ�����������
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����ɾ��������Ϣ�Ļظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -1:            //ɾ������ʧ��ԭ�� ���ݿ����ƴ���
		{
			tip = _T("ɾ������ʧ��,ԭ�������ݿ����ƴ���");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("ɾ������ʧ��,δ֪ԭ���������������״̬������");
			break;			
		}
	case 1:
		{
			tip = _T("��ϲ��ɾ������ɹ�");
			CServiceSearch* pDlg = (CServiceSearch*)m_pServiceSearch;
			pDlg->SendMessage(WM_DELSERV_ServiceSearch,0,0);
			break;
		}
	default:
		break;
	}
	CServiceSearch* pDlg = (CServiceSearch*)m_pServiceSearch;
	//pDlg->SendMessage(WM_ENDTASK_ServiceSearch,0,0);
	pDlg->m_tip.SetWindowText(tip);
	m_pServiceSearch = NULL;
	UpdateOperationStatus(tip);
	return TRUE;
}

BOOL CSock::RecvReplyOfStoreHistoryDel(int len)   //����ɾ�����ֿ����ʷ��¼��Ϣ
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����ɾ�������ʷ��¼�Ļظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -1:            //ɾ���ͻ�����ʧ��ԭ�� ���ݿ����ƴ���
		{
			tip = _T("ɾ�������ʷ��¼ʧ��,ԭ�������ݿ����ƴ���");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("ɾ�������ʷ��¼ʧ��,δ֪ԭ���������������״̬������");
			break;			
		}
	case 1:
		{
			tip = _T("��ϲ��ɾ�������ʷ��¼�ɹ�");
			if(NULL != m_pStoreHistory)
			{
				CStoreHistory* pDlg = (CStoreHistory*)m_pStoreHistory;
				pDlg->SendMessage(WM_DELHISTORY_StoreHistory,0,0);
			}
			break;
		}
	default:
		break;
	}
	if(NULL != m_pStoreHistory)
	{
		CStoreHistory* pDlg = (CStoreHistory*)m_pStoreHistory;
		//pDlg->SendMessage(WM_ENDTASK_StoreHistory,0,0);
		pDlg->m_tip.SetWindowText(tip);
		m_pStoreHistory = NULL;
	}else{
		AfxMessageBox(tip);
	}
	UpdateOperationStatus(tip);
	return TRUE;
}

BOOL CSock::RecvReplyOfCtmDel(int len)      //���շ�������Ӧɾ���ͻ�����
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����ɾ���ͻ����ϵĻظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -1:            //ɾ���ͻ�����ʧ��ԭ�� ���ݿ����ƴ���
		{
			tip = _T("ɾ���ͻ�����ʧ��,ԭ�������ݿ����ƴ���");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("ɾ���ͻ�����ʧ��,δ֪ԭ���������������״̬������");
			break;			
		}
	case 1:
		{
			tip = _T("��ϲ��ɾ���ͻ����ϳɹ�");
			if(NULL != m_pCtmInfo)
			{
				CCtmInfo* pDlg = (CCtmInfo*)m_pCtmInfo;
				pDlg->SendMessage(WM_DELCTM_CtmInfo,0,0);
			}
			break;
		}
	default:
		break;
	}
	if(NULL != m_pCtmInfo)
	{
		CCtmInfo* pDlg = (CCtmInfo*)m_pCtmInfo;
		///pDlg->SendMessage(WM_ENDTASK_CtmInfo,0,0);
		pDlg->m_tip.SetWindowText(tip);
		m_pCtmInfo = NULL;
	}else{
		AfxMessageBox(tip);
	}
	UpdateOperationStatus(tip);
	return TRUE;
}
 
BOOL CSock::RecvReplyOfEmpDel(int len)
{
	int flag;
	CString tip;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����ɾ��Ա�����ϵĻظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -1:            //ɾ��Ա������ʧ��ԭ�� ���ݿ����ƴ���
		{
			tip = _T("ɾ����������ʧ��,ԭ�������ݿ����ƴ���");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("ɾ��Ա������ʧ�ܣ�δ֪ԭ����������ԣ�");
			break;		
		}
	case 1:
		{
			tip = _T("��ϲ���ɹ�ɾ��Ա������");
			break;
		}
	default:
		break;
	}
	if(NULL != m_pEmpInfoView)
	{
		CEmpInfoView* pDlg = (CEmpInfoView*)m_pEmpInfoView;
		//pDlg->SendMessage(WM_ENDTASK_EmpInfoView,0,0);
		pDlg->m_tip.SetWindowText(tip);
		if(flag == 1)
		{
			pDlg->SendMessage(WM_DELSELEMPINFO,0,0);
		}
		m_pEmpInfoView = NULL;
	}else{
		AfxMessageBox(_T("��ϲ��ɾ���������ϳɹ���"));
	}
	UpdateOperationStatus(_T("��ϲ��ɾ���������ϳɹ���"));
	return TRUE;
}

BOOL CSock::RecvReplyOfFctDel(int len)      //����ɾ���������ϵĻ�Ӧ
{
	int flag;
	CString tip;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����ɾ���������ϵĻظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -1:            //ɾ����������ʧ��ԭ�� ���ݿ����ƴ���
		{
			tip = _T("ɾ����������ʧ��,ԭ�������ݿ����ƴ���");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("ɾ����������ʧ�ܣ�δ֪ԭ����������ԣ�");
			break;		
		}
	case 1:
		{
			tip = _T("��ϲ��ɾ���������ϳɹ���");
			break;
		}
	default:
		break;
	}
	if(NULL != m_pFctSet)
	{
		CFctSet* pDlg = (CFctSet*)m_pFctSet;
		pDlg->SendMessage(WM_ENDTASK_FctEdit,0,0);
		pDlg->m_tip.SetWindowText(tip);
		if(flag == 1)
		{
			pDlg->SendMessage(WM_DEL_FCT_FctSet,0,0);
		}
		
	}else{
		AfxMessageBox(_T("ɾ����������ʧ�ܣ�δ֪ԭ����������ԣ�"));
		UpdateOperationStatus(_T("ɾ����������ʧ�ܣ�δ֪ԭ����������ԣ�"));
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfEmpEdit(int len)     //���շ����������޸�Ա�����ϵĻظ�
{
	CString tip = NULL;
	int flag;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���ձ༭Ա�����ϵĻظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -1:            //�޸�Ա��ʧ��ԭ�� ���ݿ����ƴ���
		{
			tip = _T("�޸�Ա������ʧ��,ԭ�������ݿ����ƴ���");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("�޸�Ա������ʧ��,ԭ��δ֪�������ԣ�");
			break;	
		}
	case 1:
		{
			tip = _T("��ϲ���޸ĸ�Ա�����ϳɹ�");
			break;	
		}
	default:
		break;
	}
	if(NULL != m_pEmpEdit)
	{
		CEmpEdit* pDlg = (CEmpEdit*)m_pEmpEdit;
		//pDlg->SendMessage(WM_ENDTASK_EmpEdit,0,0);
		pDlg->m_tip.SetWindowText(_T("��ϲ���޸ĸ�Ա�����ϳɹ�"));
		m_pEmpEdit = NULL;
	}else{
		AfxMessageBox(_T("��ϲ���޸�Ա�����ϳɹ�"));
	}
	UpdateOperationStatus(_T("��ϲ���޸�Ա�����ϳɹ�"));
	return TRUE;
}


BOOL CSock::RecvReplyOfOutStore(int len)    //�������
{
	CString tip = NULL;
	int flag;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���������Ʒ�������Ļظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -3:
		{
			tip = _T("����ʧ�ܣ�ԭ�����д���Ʒû���㹻������");
			break;
		}
	case -2:
		{
			tip = _T("����ʧ�ܣ�ԭ������û�д���Ʒ��¼���������");
			break;
		}
	case -1:            //���ݿ�����ʧ��
		{
			tip = _T("����ʧ�ܣ�ԭ�����ݿ�����ʧ�ܣ�������");
			break;
		}
	case 0:             //�����Ʒ�������ʧ�ܣ�ԭ���޸���Ʒ�����Ϣʧ�ܣ�������
		{
			tip = _T("����ʧ�ܣ�ԭ��������ݿ�ʧ�ܣ�������");
			break;	
		}
	case 1:
		{
			tip = _T("��ϲ�������ɹ�");
			break;	
		}
	default:
		break;
	}
	if(NULL != m_pStoreOut)
	{
		CStoreOut* pDlg = (CStoreOut*)m_pStoreOut;
		//pDlg->SendMessage(WM_ENDTASK_StoreOut,0,0);
		pDlg->m_tip.SetWindowText(tip);
		m_pStoreOut = NULL;
	}else{
		AfxMessageBox(tip);
	}
	UpdateOperationStatus(tip);
	return TRUE;
}

BOOL CSock::RecvReplyOfStoreAlertSet(int len)    //���չ����û�����Ԥ����Ϣ�Ļظ�
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���չ����û����ÿ��Ԥ����Ϣ������Ļظ�ʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -1:            //���ݿ�����ʧ��
		{
			tip =  _T("���ÿ��Ԥ����Ϣʧ�ܣ�ԭ�����ݿ�����ʧ�ܣ�������");
			break;	
		}
	case 0:             //���ÿ��Ԥ����Ϣʧ�� ԭ��δ֪
		{
			tip =  _T("���ÿ��Ԥ����Ϣʧ�ܣ�ԭ��δ֪��������"); 
			break;	
		}
	case 1:
		{
			tip =  _T("��ϲ���ɹ����ÿ��Ԥ����Ϣ"); 
			break;	
		}
	default:
		break;
	}
	if(NULL != m_pStoreAlertSet)
	{
		CStoreAlertSet* pDlg = (CStoreAlertSet*)m_pStoreAlertSet;
		//pDlg->SendMessage(WM_ENDTASK_StoreAlertSet,0,0);
		pDlg->m_tip.SetWindowText(tip);
		m_pStoreAlertSet = NULL;
	}else{
		AfxMessageBox(tip);
	}
	UpdateOperationStatus(tip);
	
	return TRUE;
}

BOOL CSock::RecvReplyOfDeductSet(int len)     //����������ɵĻظ�
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���������������Ļظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -1:            //���ݿ�����ʧ��
		{
			tip = _T("�������ʧ�ܣ�ԭ�����ݿ�����ʧ�ܣ�������");
			break;	
		}
	case 0:             //�������ʧ�ܣ�δ֪ԭ��������
		{
			tip = _T("�������ʧ�ܣ�δ֪ԭ��������");
			break;	
		}
	case 1:
		{
			tip = _T("��ϲ��������ɶ����ɹ�");
			
			break;	
		}
	default:
		break;
	}
	if(NULL != m_pDeductSet)
	{
		CDeductSet* pDlg = (CDeductSet*)m_pDeductSet;
		pDlg->SendMessage(WM_ENDTASK_DeductSet,0,0);
		pDlg->m_tip.SetWindowText(tip);
	}else{
		UpdateOperationStatus(tip);
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfOrderEdit(int len)    //�༭�����Ļظ�
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���ձ༭��������Ļظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -1:            //���ݿ�����ʧ��
		{
			tip = _T("�༭����ʧ�ܣ�ԭ�����ݿ�����ʧ�ܣ�������");
			break;	
		}
	case 0:             //�༭����ʧ�ܣ�δ֪ԭ��������
		{
			tip = _T("�༭����ʧ�ܣ�δ֪ԭ��������");
			break;	
		}
	case 1:
		{
			tip = _T("��ϲ���༭�����ɹ�");
			
			break;	
		}
	default:
		break;
	}
	if(NULL != m_pOrderEdit)
	{
		COrderEdit* pDlg = (COrderEdit*)m_pOrderEdit;
		//pDlg->SendMessage(WM_ENDTASK_OrderEdit,0,0);
		pDlg->m_tip.SetWindowText(tip);
	}else{
		UpdateOperationStatus(tip);
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfOrderNew(int len)    //�ظ��½�����
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����½���������Ļظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -2:            //�������Ѿ�����  
		{
			tip = _T("�½�����ʧ�ܣ�ԭ��ö������Ѿ�����");
			break;	
		}
	case -1:            //���ݿ�����ʧ��
		{
			tip = _T("�½�����ʧ�ܣ�ԭ�����ݿ�����ʧ�ܣ�������");
			break;	
		}
	case 0:             //�½�����ʧ�ܣ�δ֪ԭ��������
		{
			tip = _T("�½�����ʧ�ܣ�δ֪ԭ��������");
			break;	
		}
	case 1:
		{
			tip = _T("��ϲ���½������ɹ�");
			
			break;	
		}
	default:
		break;
	}
	if(NULL != m_pOrderContent)
	{
		COrderContent* pDlg = (COrderContent*)m_pOrderContent;
		//pDlg->SendMessage(WM_ENDTASK_OrderContent,0,0);
		pDlg->m_tip.SetWindowText(tip);
		m_pOrderContent = NULL;
	}else{
		UpdateOperationStatus(tip);
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfRegServ(int len)   //�ظ�����ע�����
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����ע���������Ļظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -2:            //ע�����ʧ�ܣ�ԭ�򣺸÷��񵥺��Ѿ�����
		{
			tip = _T("ע�����ʧ�ܣ��÷��񵥺��Ѿ�����");
			break;	
		}
	case -1:            //���ݿ�����ʧ��
		{
			tip = _T("ע�����ʧ�ܣ�ԭ�����ݿ�����ʧ�ܣ�������");
			break;	
		}
	case 0:             //ע�����ʧ��ʧ�ܣ�ԭ���޸���Ʒ�����Ϣʧ�ܣ�������
		{
			tip = _T("ע�����ʧ�ܣ�δ֪ԭ��������");
			break;	
		}
	case 1:
		{
			tip = _T("��ϲ��ע�����ɹ�");
			
			break;	
		}
	default:
		break;
	}
	if(NULL != m_pServReg)
	{
		CServReg* pDlg = (CServReg*)m_pServReg;
		//pDlg->SendMessage(WM_ENDTASK_ServReg,0,0);
		pDlg->m_tip.SetWindowText(tip);
		m_pServReg = NULL;
	}
	UpdateOperationStatus(tip);
	return TRUE;
}

BOOL CSock::RecvReplyOfAddStore(int len)    //���������Ʒ�����Ϣ
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���������Ʒ�������Ļظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -2:            //�����Ʒ�������ʧ�ܣ�ԭ���½���Ʒ�����Ϣʧ��
		{
			tip = _T("�����Ʒ�������ʧ�ܣ�������");
			break;	
		}
	case -1:            //���ݿ�����ʧ��
		{
			tip = _T("�����Ʒ�������ʧ�ܣ�ԭ�����ݿ�����ʧ�ܣ�������");
			break;	
		}
	case 0:             //�����Ʒ�������ʧ�ܣ�ԭ���޸���Ʒ�����Ϣʧ�ܣ�������
		{
			tip = _T("�����Ʒ�������ʧ�ܣ�ԭ���޸���Ʒ�����Ϣʧ�ܣ�������");
			break;	
		}
	case 1:
		{
			tip = _T("��ϲ�������Ʒ������ϳɹ�");
			
			break;	
		}
	default:
		break;
	}
	if(NULL != m_pStoreAdd)
	{
		CStoreAdd* pDlg = (CStoreAdd*)m_pStoreAdd;
		//pDlg->SendMessage(WM_ENDTASK_StoreAdd,0,0);
		pDlg->m_tip.SetWindowText(tip);
		m_pStoreAdd= NULL;
	}
	UpdateOperationStatus(tip);
	return TRUE;
}

BOOL CSock::RecvReplyOfCtmNew(int len)   //���շ����½��ͻ����ϵĽ��
{
	CString tip = NULL;
	int flag;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����½��ͻ���������Ļظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -2:            //�½��ͻ�����ʧ��ԭ�� �ͻ��Ѿ�����
		{
			tip = _T("�½��ͻ�ʧ��,ԭ���Ǵ˿ͻ�����Ѿ����ڣ�");
			break;	
		}
	case -1:            //
		{
			tip = _T("�½��ͻ�ʧ��,ԭ�������ݿ�����ʧ�ܣ�");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("�½��ͻ�ʧ��,ԭ����");
			break;	
		}
	case 1:
		{
			tip = _T("��ϲ���½��ͻ��ɹ�");
			
			break;		
		}
	default:
		break;
	}
	if(NULL != m_pCtmNew)
	{
		CCtmNew* pDlg = (CCtmNew*)m_pCtmNew;
		//pDlg->SendMessage(WM_ENDTASK_CtmNew,0,0);
		pDlg->m_tip.SetWindowText(tip);
		m_pCtmNew = NULL;
	}else{
		AfxMessageBox(tip);
	}
	UpdateOperationStatus(tip);
	return TRUE;
}

BOOL CSock::RecvReplyOfFctNew(int len)
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����½�������������Ļظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -2:            //�½�Ա��ʧ��ԭ�� Ա���Ѿ�����
		{
			tip = _T("�½�����ʧ��,ԭ���Ǵ˳����Ѿ����ڣ�");
			break;	
		}
	case -1:            //
		{
			tip = _T("�½�����ʧ��,ԭ�������ݿ����ӣ�");
			break;
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("�½�����ʧ��,δ֪ԭ��");
			break;	
		}
	case 1:
		{
			tip = _T("��ϲ���½����ҳɹ���");
			break;	
		}
	default:
		break;
	}
	if(NULL != m_pFctNew)
	{
		CFactoryNew* pDlg = (CFactoryNew*)m_pFctNew;
		//pDlg->SendMessage(WM_ENDTASK_FctNew,0,0);
		pDlg->m_tip.SetWindowText(_T("��ϲ���½����ҳɹ���"));
		m_pFctNew = NULL;
	}else{
		AfxMessageBox(_T("��ϲ���½����ҳɹ���"));
	}
	UpdateOperationStatus(_T("��ϲ���½����ҳɹ���"));
	return TRUE;
}

BOOL CSock::RecvReplyOfEmpNew(int len)     //�����½�Ա��
{
	int flag;
	CString tip = NULL;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����½�Ա����������Ļظ���Ϣʧ��"));
		return FALSE;
	}
	switch (flag)
	{
	case -2:            //�½�Ա��ʧ��ԭ�� Ա���Ѿ�����
		{
			tip = _T("�½�Ա��ʧ��,ԭ���Ǵ�Ա�������Ѿ����ڣ�");
			break;	
		}
	case -1:            //�½�Ա��ʧ��ԭ�� ���ݿ����ƴ���
		{
			tip = _T("�½�Ա��ʧ��,ԭ�������ݿ����ƴ���");
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			tip = _T("�½�Ա��ʧ��,δ֪ԭ��");
			break;	
			//m_bReqAvailable = TRUE;   //ʹ��������� ֻҪ�н�� ���ܷ����µ�����
			break;
		}
	case 1:
		{
			tip = _T("��ϲ���½�Ա���ɹ���");
			break;	
		}
	default:
		break;
	}
	if(NULL != m_pEmpNew)
	{
		CEmpNew* pDlg = (CEmpNew*)m_pEmpNew;
		//pDlg->SendMessage(WM_REQEMPNEWEND_EmpNew,0,0);
		pDlg->m_tip.SetWindowText(tip);
		m_pEmpNew = NULL;
	}else{
		AfxMessageBox(_T("�½�Ա��ʧ��,δ֪ԭ��"));
	}
	UpdateOperationStatus(_T("�½�Ա��ʧ��,δ֪ԭ��"));
	return TRUE;
}


BOOL CSock::RecvReplyOfDetailNote(int len)    //�ظ��û��鿴֪ͨ
{
	if(len)
	{
		NotePublic_MainView note;
		memset(&note,0,sizeof(NotePublic_MainView));
		int errCode = recv(m_sockWhole,(char *)&note,len,0);
		if(errCode == SOCKET_ERROR)
		{
			AfxMessageBox(_T("���չ�����Ϣ�Ļظ���Ϣʧ��"));
			return FALSE;
		}
		USES_CONVERSION;
		CString num;
		if(m_pMainFormView == NULL)
		{
			UpdateOperationStatus(_T("�Ѿ�ȡ���鿴����"));
			return TRUE;
		}
		CMainFormView* pView = (CMainFormView*)m_pMainFormView;
		pView->m_time_note_public = A2T(note.time_public);
		pView->m_persion_public_note = A2T(note.persion_public);
		pView->m_title_note = A2T(note.title);
		pView->m_content_note = A2T(note.content);
		pView->SendMessage(WM_SHOWNOTEINEDIT_MainView,0,0);
		//pView->SendMessage(WM_REQINITNOTEEND_MainView,0,0);
		pView->GetDlgItem(IDC_STATIC_TIP)->SetWindowText(_T(""));
		UpdateOperationStatus(_T("���ع������"));
	}else{   //�������
		if(m_pMainFormView != NULL){
			CMainFormView* p_dlg = (CMainFormView*)m_pMainFormView;
			//p_dlg->SendMessage(WM_REQINITNOTEEND_MainView,0,0);
			p_dlg->GetDlgItem(IDC_STATIC_TIP)->SetWindowText(_T("���ع���ʧ�ܣ���鿴����״̬������"));	
		}
		UpdateOperationStatus(_T("���ع���ʧ��"));
	}
	return TRUE;
}


BOOL CSock::RecvReplyOfDeletNote(int len)
{
	int flag;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���յ�¼�Ļظ���Ϣʧ��"));
		//m_bReqAvailable = TRUE;   //ʹ��������� ֻҪ�н�� ���ܷ����µ�����
		return FALSE;
	}
	switch (flag)
	{
	case -1:            //��¼ʧ��ԭ�� ���ݿ����ƴ���
		{
			if(NULL != m_pMainFormView)
			{
				CMainFormView* pDlg = (CMainFormView*)m_pMainFormView;
				UpdateOperationStatus(_T("ɾ��֪ͨʧ�ܣ����ݿ����ƴ���"));
				//pDlg->SendMessage(WM_REQINITNOTEEND_MainView,0,0);
			}else{
				AfxMessageBox(_T("ɾ��ʧ�ܣ����ݿ����ƴ���,Ҫ�ҵ����ݿⲻ���ڣ�"));
			}
			break;	
		}
	case 0:             //δ֪ԭ�� ������
		{
			if(NULL != m_pMainFormView)
			{
				CMainFormView* pDlg = (CMainFormView*)m_pMainFormView;
				//pDlg->SendMessage(WM_REQINITNOTEEND_MainView,0,0);
				UpdateOperationStatus(_T("δ֪ԭ��ʧ�ܣ�������"));
			}else
			{
				AfxMessageBox(_T("δ֪ԭ��ʧ�ܣ�������"));
			}
			//m_bReqAvailable = TRUE;   //ʹ��������� ֻҪ�н�� ���ܷ����µ�����
			break;
		}
	case 1:
		{
			if(NULL != m_pMainFormView)
			{
				CMainFormView* pDlg = (CMainFormView*)m_pMainFormView;
				//pDlg->SendMessage(WM_REQINITNOTEEND_MainView,0,0);
				UpdateOperationStatus(_T("ɾ��֪ͨ�ɹ�"));
				pDlg->SendMessage(WM_DELSELNOTE_MainView,0,0);
			}else
			{
				AfxMessageBox(_T("ɾ��֪ͨ�ɹ�"));
			}
			//m_bReqAvailable = TRUE;   //ʹ��������� ֻҪ�н�� ���ܷ����µ�����
			break;
		}
	default:
		break;
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfLoginIn(int len)		////���ջظ���Ϣ ���ڵ�¼�Ƿ�ɹ���
{
	//CLogin* pDlg = (CLogin *)m_pVoid;
	int flag;
	int errCode = recv(m_sockWhole,(char *)&flag,len,0);
	if(errCode == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���յ�¼�Ļظ���Ϣʧ��"));
		//m_bReqAvailable = TRUE;   //ʹ��������� ֻҪ�н�� ���ܷ����µ�����
		return FALSE;
	}
	switch (flag)
	{
	case -2:            //��¼ʧ��ԭ�� ���ݿ����ƴ���
		{
			if(NULL != m_pLogin)
			{
				CLogin* pDlg = (CLogin*)m_pLogin;
				pDlg->SendMessage(WM_CURSORTONORMAL,0,0);
				pDlg->m_status.SetWindowText(_T("��¼ʧ�ܣ����ݿ����ƴ���,����˵���һҳ�޸����ݿ����ƣ�"));
				pDlg->SendMessage(WM_LOGINFAIL,0,0);
			}else{
				AfxMessageBox(_T("��¼ʧ�ܣ����ݿ����ƴ���,����˵���һҳ�޸����ݿ����ƣ�"));
			}
			break;	
		}
	case -1:             //��¼ʧ��ԭ�� �������
		{
			if(NULL != m_pLogin)
			{
				CLogin* pDlg = (CLogin*)m_pLogin;
				pDlg->SendMessage(WM_CURSORTONORMAL,0,0);
				pDlg->m_status.SetWindowText(_T("��¼ʧ�ܣ��������"));
			//AfxMessageBox(_T("��¼ʧ��,�û������������"));
				pDlg->SendMessage(WM_LOGINFAIL,0,0);
			}else
			{
				AfxMessageBox(_T("��¼ʧ�ܣ��������"));
			}
			//m_bReqAvailable = TRUE;   //ʹ��������� ֻҪ�н�� ���ܷ����µ�����
			break;
		}
	case 0:
		{
			if(NULL != m_pLogin)
			{
				CLogin* pDlg = (CLogin*)m_pLogin;
				pDlg->SendMessage(WM_CURSORTONORMAL,0,0);
				pDlg->m_status.SetWindowText(_T("��¼ʧ�ܣ��û������߽�ɫѡ�����"));
			//AfxMessageBox(_T("��¼ʧ��,�û������������"));
				pDlg->SendMessage(WM_LOGINFAIL,0,0);
			}else
			{
				AfxMessageBox(_T("��¼ʧ�ܣ��û������߽�ɫѡ�����"));
			}
			//m_bReqAvailable = TRUE;   //ʹ��������� ֻҪ�н�� ���ܷ����µ�����
			break;
		}
	case 1:
		{
			if(NULL != m_pLogin)
			{
				CLogin* pDlg = (CLogin*)m_pLogin;
				pDlg->m_status.SetWindowText(_T("��ϲ������¼�ɹ���"));
				//m_bReqAvailable = TRUE;    //ʹ��������� ���������������
				pDlg->SendMessage(WM_CURSORTONORMAL,0,0);
				pDlg->SendMessage(WM_LOGINSUCCESS,0,0);
				UpdateOperationStatus(_T("��¼�ɹ����Ѿ���"));
			}else
			{
				AfxMessageBox(_T("��ϲ������¼�ɹ���"));
			}
			break;
		}
	default:
		break;
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfInitNote(int len)
{
	if(len)
	{
		NotePublic_MainView note;
		memset(&note,0,sizeof(NotePublic_MainView));
		int errCode = recv(m_sockWhole,(char *)&note,len,0);
		if(errCode == SOCKET_ERROR)
		{
			AfxMessageBox(_T("���ճ�ʼ��֪ͨ���Ļظ���Ϣʧ��"));
			return FALSE;
		}
		USES_CONVERSION;
		CString num;
		if(m_pMainFormView == NULL)
		{
			UpdateOperationStatus(_T("�Ѿ�ȡ����ʼ��֪ͨ��"));
			return TRUE;
		}
		CMainFormView* pView = (CMainFormView*)m_pMainFormView;
		int nCount = pView->m_list.GetItemCount();
		num.Format(_T("%d"),(nCount+1));
		pView->m_list.InsertItem(nCount,_T(""));//�����µ�һ��
		pView->m_list.SetItemText(nCount,0,num);
		pView->m_list.SetItemText(nCount,1,A2T(note.title));
		pView->m_list.SetItemText(nCount,2,A2T(note.time_public));
		pView->m_list.SetItemText(nCount,3,A2T(note.persion_public));
		if(nCount == 0)   //���û������Ϣ ��ʾ���µ���Ϣ
		{
			pView->m_time_note_public = A2T(note.time_public);
			pView->m_persion_public_note = A2T(note.persion_public);
			pView->m_title_note = A2T(note.title);
			pView->m_content_note = A2T(note.content);
			pView->SendMessage(WM_SHOWNOTEINEDIT_MainView,0,0);
		}
		UpdateOperationStatus(_T("���ڼ���֪ͨ��"));
	}else{   //�������
		if(m_pMainFormView != NULL){
			CMainFormView* p_dlg = (CMainFormView*)m_pMainFormView;
			//p_dlg->SendMessage(WM_REQINITNOTEEND_MainView,0,0);
			int count = p_dlg->m_list.GetItemCount();
			if(count == 0){
				p_dlg->GetDlgItem(IDC_STATIC_TIP)->SetWindowText(_T("��֪ͨ"));
			}else{
				CString num;
				num.Format(_T("���µ�%d��֪ͨ"),count);
				p_dlg->GetDlgItem(IDC_STATIC_TIP)->SetWindowText(num);
			}
		}
		UpdateOperationStatus(_T("֪ͨ���������"));
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfFindAllStore(int len)     //���������������
{
	if(len)   //�������û�н���
	{
		StoreInfo store;
		memset(&store,0,sizeof(StoreInfo));
		int errCode = recv(m_sockWhole,(char *)&store,len,0);
		if(errCode == SOCKET_ERROR)
		{
			AfxMessageBox(_T("��������������ϵĻظ���Ϣʧ��"));
			return FALSE;
		}
		USES_CONVERSION;
		CStoreInfo* pdlg = (CStoreInfo*)m_pStoreInfo;
		if(m_pStoreInfo == NULL){
			UpdateOperationStatus(_T("����������ϵ������Ѿ�ȡ��"));
			return TRUE;
		}
		int nCount = pdlg->m_list.GetItemCount();
		pdlg->m_list.InsertItem(nCount,_T(""));//�����µ�һ��
		pdlg->m_list.SetItemText(nCount,0,A2T(store.Store_Name));
		pdlg->m_list.SetItemText(nCount,1,A2T(store.Store_Num));
		pdlg->m_list.SetItemText(nCount,2,A2T(store.Store_Alert_NUM));
	}else{    //��������Ѿ�����
		if(m_pStoreInfo != NULL){
			CStoreInfo* pDlg = (CStoreInfo*)m_pStoreInfo;
			//pDlg->SendMessage(WM_ENDTASK_StoreInfo,0,0);
			pDlg->m_tip.SetWindowTextW(_T("�������������Ϣ���"));
			m_pStoreInfo = NULL;
		}
		UpdateOperationStatus(_T("�������������Ϣ���"));
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfInitDeduct(int len)   //�ظ���ʼ�����
{
	if(len)   //�������û�н���
	{
		DeductInfo info;
		memset(&info,0,sizeof(info));
		int errCode = recv(m_sockWhole,(char *)&info,len,0);
		if(errCode == SOCKET_ERROR)
		{
			AfxMessageBox(_T("���ճ�ʼ��������õĻظ���Ϣʧ��"));
			return FALSE;
		}
		CDeductSet* p_dlg = (CDeductSet*)m_pDeductSet;
		if(p_dlg != NULL)
		{
			p_dlg->m_deductInfo = info;
		}
	}else{    //��������Ѿ�����
		CDeductSet* pDlg = (CDeductSet*)m_pDeductSet;
		if(pDlg != NULL){
			pDlg->SendMessage(WM_ENDTASK_DeductSet,0,0);
			pDlg->m_tip.SetWindowText(_T("�������"));
			pDlg->SendMessage(WM_LOADSETOVER_DeductSet,0,0);
			UpdateOperationStatus(_T("���"));
		}else{
			UpdateOperationStatus(_T("���"));
		}
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfOrderFind(int len)   //�ظ���������
{
	if(len)   //�������û�н���
	{
		OrderInfo order;
		memset(&order,0,sizeof(OrderInfo));
		int errCode = recv(m_sockWhole,(char *)&order,len,0);
		if(errCode == SOCKET_ERROR)
		{
			AfxMessageBox(_T("�������������Ļظ���Ϣʧ��"));
			return FALSE;
		}
		USES_CONVERSION;
		CDealListView* pdlg = (CDealListView*)m_pDealListView;
		int nCount = pdlg->m_list.GetItemCount();
		pdlg->m_list.InsertItem(nCount,_T(""));//�����µ�һ��
		pdlg->m_list.SetItemText(nCount,0,A2T(order.NO_Order));
		pdlg->m_list.SetItemText(nCount,1,A2T(order.date_accept_order));
		pdlg->m_list.SetItemText(nCount,2,A2T(order.date_finished_order));
		pdlg->m_list.SetItemText(nCount,3,A2T(order.name_person_charge_order));
		pdlg->m_list.SetItemText(nCount,4,A2T(order.base_ps_order));
		pdlg->m_list.SetItemText(nCount,5,A2T(order.ctm_from));
		pdlg->m_list.SetItemText(nCount,6,A2T(order.name_intr));
		pdlg->m_list.SetItemText(nCount,7,A2T(order.phone_intr));
		pdlg->m_list.SetItemText(nCount,8,A2T(order.name_serv_persion));
		pdlg->m_list.SetItemText(nCount,9,A2T(order.name_emp));
		pdlg->m_list.SetItemText(nCount,10,A2T(order.call_ctm));
		pdlg->m_list.SetItemText(nCount,11,A2T(order.name_ctm));
		pdlg->m_list.SetItemText(nCount,12,A2T(order.phone_ctm));
		pdlg->m_list.SetItemText(nCount,13,A2T(order.addr_ctm));
		pdlg->m_list.SetItemText(nCount,14,A2T(order.ps_ctm));
		pdlg->m_list.SetItemText(nCount,15,A2T(order.NO_contract));
		pdlg->m_list.SetItemText(nCount,16,A2T(order.prog_business));
		pdlg->m_list.SetItemText(nCount,17,A2T(order.price_total_contract));
		pdlg->m_list.SetItemText(nCount,18,A2T(order.money_already_take));
		pdlg->m_list.SetItemText(nCount,19,A2T(order.date_first_test_book));
		pdlg->m_list.SetItemText(nCount,20,A2T(order.persion_first_test));
		pdlg->m_list.SetItemText(nCount,21,A2T(order.persion_first_design));
		pdlg->m_list.SetItemText(nCount,22,A2T(order.type_early_modify));
		pdlg->m_list.SetItemText(nCount,23,A2T(order.persion_early_modify));
		pdlg->m_list.SetItemText(nCount,24,A2T(order.persion_budget));
		pdlg->m_list.SetItemText(nCount,25,A2T(order.persion1_discuss_order));
		pdlg->m_list.SetItemText(nCount,26,A2T(order.persion2_discuss_order));
		pdlg->m_list.SetItemText(nCount,27,A2T(order.date_final_scheme));
		pdlg->m_list.SetItemText(nCount,28,A2T(order.date_book));
		pdlg->m_list.SetItemText(nCount,29,A2T(order.person_exact_measure));
		pdlg->m_list.SetItemText(nCount,30,A2T(order.date_out_order_book));
		pdlg->m_list.SetItemText(nCount,31,A2T(order.person_out_order));
		pdlg->m_list.SetItemText(nCount,32,A2T(order.factory_choose));
		pdlg->m_list.SetItemText(nCount,33,A2T(order.pay_deal_choice));
		pdlg->m_list.SetItemText(nCount,34,A2T(order.date_install_book));
		pdlg->m_list.SetItemText(nCount,35,A2T(order.persion_install));
		pdlg->m_list.SetItemText(nCount,36,A2T(order.problems_install));
		pdlg->m_list.SetItemText(nCount,37,A2T(order.filepath_accessory));
	}else{    //��������Ѿ�����
		CDealListView* pDlg = (CDealListView*)m_pDealListView;
		//pDlg->SendMessage(WM_ENDTASK_DealListView,0,0);
		int count= pDlg->m_list.GetItemCount();
		if(0 == count)
		{
			pDlg->m_tip.SetWindowText(_T("û�з��������Ľ��"));
		}else{
			CString tip = NULL;
			tip.Format(_T("��������%d�����"),count);
			pDlg->m_tip.SetWindowText(tip);
		}
		UpdateOperationStatus(_T("����������Ϣ���"));
	}
	return TRUE;
}


BOOL CSock::RecvReplyOfServFindAll(int len)    //����ȫ��������Ϣ
{ 
	if(len)   //�������û�н���
	{
		ServInfo serv;
		memset(&serv,0,sizeof(ServInfo));
		int errCode = recv(m_sockWhole,(char *)&serv,len,0);
		if(errCode == SOCKET_ERROR)
		{
			AfxMessageBox(_T("��������ȫ������Ļظ���Ϣʧ��"));
			return FALSE;
		}
		USES_CONVERSION;
		CServiceSearch* pdlg = (CServiceSearch*)m_pServiceSearch;
		int nCount = pdlg->m_list.GetItemCount();
		pdlg->m_list.InsertItem(nCount,_T(""));//�����µ�һ��
		pdlg->m_list.SetItemText(nCount,0,A2T(serv.serv_NO));
		pdlg->m_list.SetItemText(nCount,1,A2T(serv.prog));
		pdlg->m_list.SetItemText(nCount,2,A2T(serv.serv_type));
		pdlg->m_list.SetItemText(nCount,3,A2T(serv.req_serv_date));
		pdlg->m_list.SetItemText(nCount,4,A2T(serv.delay_date));
		pdlg->m_list.SetItemText(nCount,5,A2T(serv.client_type));
		pdlg->m_list.SetItemText(nCount,6,A2T(serv.ctm_name));
		pdlg->m_list.SetItemText(nCount,7,A2T(serv.client_name));
		pdlg->m_list.SetItemText(nCount,8,A2T(serv.ctm_sex));
		pdlg->m_list.SetItemText(nCount,9,A2T(serv.client_phone));
		pdlg->m_list.SetItemText(nCount,10,A2T(serv.addr));
		pdlg->m_list.SetItemText(nCount,11,A2T(serv.charge));
		pdlg->m_list.SetItemText(nCount,12,A2T(serv.serv_name));
		pdlg->m_list.SetItemText(nCount,13,A2T(serv.serv_phone));
		pdlg->m_list.SetItemText(nCount,14,A2T(serv.serv_content));
		pdlg->m_list.SetItemText(nCount,15,A2T(serv.ps));
	}else{    //��������Ѿ�����
		CServiceSearch* pDlg = (CServiceSearch*)m_pServiceSearch;
		//pDlg->SendMessage(WM_ENDTASK_ServiceSearch,0,0);
		int count= pDlg->m_list.GetItemCount();
		if(0 == count)
		{
			pDlg->m_tip.SetWindowText(_T("û�з��������Ľ��"));
		}else{
			CString tip = NULL;
			tip.Format(_T("��������%d�����"),count);
			pDlg->m_tip.SetWindowText(tip);
		}
		UpdateOperationStatus(_T("����������Ϣ���"));
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfStoreFindAll(int len)    //�ظ��û�����ȫ�������ʷ��¼
{
	if(len)   //�������û�н���
	{
		StoreHistory history;
		memset(&history,0,sizeof(StoreHistory));
		int errCode = recv(m_sockWhole,(char *)&history,len,0);
		if(errCode == SOCKET_ERROR)
		{
			AfxMessageBox(_T("�������������ʷ��¼���ϵĻظ���Ϣʧ��"));
			return FALSE;
		}
		USES_CONVERSION;
		CStoreHistory* pdlg = (CStoreHistory*)m_pStoreHistory;
		if(m_pStoreHistory == NULL){
			UpdateOperationStatus(_T("���������ʷ��¼���ϵ������Ѿ�ȡ��"));
			return TRUE;
		}
		int nCount = pdlg->m_list.GetItemCount();
		pdlg->m_list.InsertItem(nCount,_T(""));//�����µ�һ��
		pdlg->m_list.SetItemText(nCount,0,A2T(history.Store_Name));
		pdlg->m_list.SetItemText(nCount,1,A2T(history.num_change));
		pdlg->m_list.SetItemText(nCount,2,A2T(history.status));
		pdlg->m_list.SetItemText(nCount,3,A2T(history.time));
	}else{    //��������Ѿ�����
		if(m_pStoreHistory != NULL){
			CStoreHistory* pDlg = (CStoreHistory*)m_pStoreHistory;
			//pDlg->SendMessage(WM_ENDTASK_StoreHistory,0,0);
			pDlg->m_tip.SetWindowTextW(_T("���������ʷ��¼��Ϣ���"));
			m_pStoreHistory = NULL;
		}
		UpdateOperationStatus(_T("���������ʷ��¼��Ϣ���"));
	}
	return TRUE;
}

BOOL CSock::RecvReplyFindOrderIncomplete(int len)    //����δ��ɶ����Ļظ�
{
	if(len)    //û�н�����
	{
		WT;
		char buff[1024*10] = {0};
		int errCode = recv(m_sockWhole,(char *)buff,len,0);
		if(errCode == SOCKET_ERROR)
		{
			AfxMessageBox(_T("��������δ��ɶ����Ļظ���Ϣʧ��"));
			return FALSE;
		}else if(errCode == 0)
		{
			AfxMessageBox(_T("��������δ��ɶ����Ļظ���Ϣʧ��,�������ѹر�"));
			return FALSE;
		}else if(errCode >0){
			COrderIncompletedProgView* p_view = (COrderIncompletedProgView*)m_pOrderIncompleteView;
			p_view->m_list_IncompleteOrder += A2T(buff);
			p_view->m_tip.SetWindowText(_T("���յ����������ص�����"));
			return TRUE;
		}
		return TRUE;
	}else{
		COrderIncompletedProgView* p_view = (COrderIncompletedProgView*)m_pOrderIncompleteView;
		//p_view->SendMessage(WM_ENDTASK_OrderIncomplete,0,0);
		p_view->SendMessage(WM_FILLLIST_OrderIncomplete,0,0);
		m_pOrderIncompleteView = NULL;
		return TRUE;
	}
}

BOOL CSock::RecvReplyOfFindAllUsers(int len)      //Ѱ�������û�
{
	WT;
	if(len)   //�������û�н���
	{	
		char buff[1024*10] = {0};
		int errCode = recv(m_sockWhole,(char *)buff,len,0);
		if(errCode == SOCKET_ERROR)
		{
			AfxMessageBox(_T("�����û���Ϣ�Ļظ���Ϣʧ��"));
			return FALSE;
		}else if(errCode == 0)
		{
			AfxMessageBox(_T("�����û���Ϣ�Ļظ���Ϣʧ��,�������ѹر�"));
			return FALSE;
		}else if(errCode >0){
			if(NULL != m_pSysPostion)
			{
				CSysPostion* p_dlg = (CSysPostion*)m_pSysPostion;
				p_dlg->m_pos_batch += A2T(buff);
				p_dlg->m_tip.SetWindowText(_T("���ڽ��շ��������ص��û�����"));
				return TRUE;
			}
			return TRUE;
		}
		return TRUE;
	}else{    //��������Ѿ�����
		if(NULL != m_pSysPostion)
		{
			CSysPostion* p_dlg = (CSysPostion*)m_pSysPostion;
			//p_dlg->SendMessage(WM_ENDTASK_SysPostion,0,0);
			p_dlg->SendMessage(WM_FILLLIST_SysPostion,0,0);
			m_pSysPostion = NULL;
		}
		UpdateOperationStatus(_T("�����û���Ϣ���"));
		return TRUE;
	}
}

BOOL CSock::RecvReplyOfFindEmpPerformance(int len)   //Ѱ��Ա��ҵ���Ļظ�
{
	WT;
	if(len)   //�������û�н���
	{	
		char buff[1024*10] = {0};
		int errCode = recv(m_sockWhole,(char *)buff,len,0);
		if(errCode == SOCKET_ERROR)
		{
			AfxMessageBox(_T("����Ա��ҵ����Ϣ�Ļظ���Ϣʧ��"));
			return FALSE;
		}else if(errCode == 0)
		{
			AfxMessageBox(_T("����Ա��ҵ����Ϣ�Ļظ���Ϣʧ��,�������ѹر�"));
			return FALSE;
		}else if(errCode >0){
			if(NULL != m_pEmpPerformance)
			{
				CPerformanceMgView* p_dlg = (CPerformanceMgView*)m_pEmpPerformance;
				p_dlg->m_str_emp_performance_batch += A2T(buff);
				p_dlg->m_tip.SetWindowText(_T("���ڽ��շ��������ص�Ա��ҵ������"));
				return TRUE;
			}
			return TRUE;
		}
		return TRUE;
	}else{    //��������Ѿ�����
		if(NULL != m_pEmpPerformance)
		{
			CPerformanceMgView* p_dlg = (CPerformanceMgView*)m_pEmpPerformance;
			//p_dlg->SendMessage(WM_ENDTASK_EmpPerformance,0,0);
			p_dlg->SendMessage(WM_FILLDATATOLIST_EmpPerformance,0,0);
			m_pEmpPerformance = NULL;
		}
		UpdateOperationStatus(_T("����Ա��ҵ����Ϣ���"));
		return TRUE;
	}
			
}

BOOL CSock::RecvReplyOfProdEx(int len)     //��������������Ʒ����
{
	WT;
	if(len)   //�������û�н���
	{	
		char buff[1024*10] = {0};
		int errCode = recv(m_sockWhole,(char *)buff,len,0);
		if(errCode == SOCKET_ERROR)
		{
			AfxMessageBox(_T("��������������Ʒ���ϵĻظ���Ϣʧ��"));
			return FALSE;
		}else if(errCode == 0)
		{
			AfxMessageBox(_T("��������������Ʒ���ϵĻظ���Ϣʧ��,�������ѹر�"));
			return FALSE;
		}else if(errCode >0){
			if(NULL != m_pProdEx)
			{
				CProdInfoExProp* p_dlg = (CProdInfoExProp*)m_pProdEx;
				p_dlg->m_prod_batch += A2T(buff);
				p_dlg->m_tip.SetWindowText(_T("���ڽ��շ��������ص�����"));
				return TRUE;
			}
			return TRUE;
		}
		return TRUE;
	}else{    //��������Ѿ�����
		if(m_pProdEx != NULL){
			CProdInfoExProp* p_dlg = (CProdInfoExProp*)m_pProdEx;
			p_dlg->SendMessage(WM_ENDTASK_ProdInfoExProp,0,0);
			p_dlg->SendMessage(WM_HANDLE_BATCH_ProdEx,0,0);
		}
		UpdateOperationStatus(_T("������Ʒ������Ϣ���"));
		return TRUE;
	}
			
}

BOOL CSock::RecvReplyOfCtmEx(int len)     //���ڿͻ�������������
{
	if(len)   //�������û�н���
	{
		WT;
		char buff[1024*10] = {0};
		CString _err = _T("���������ͻ����ϵĻظ���Ϣʧ��");
		if(!RecvDataFromServer(m_sockWhole,buff,len,_err))
		{
			return FALSE;
		}
		if(NULL != m_pCtmEx)
		{
			CCustomInfoExProp* p_dlg = (CCustomInfoExProp*)m_pCtmEx;
			p_dlg->m_ctm_batch_from_db += A2T(buff);
			p_dlg->m_tip.SetWindowText(_T("���ڽ��շ��������ص�����"));
		}	
	}else{    //��������Ѿ�����
		if(m_pCtmEx != NULL){
			CCustomInfoExProp* pDlg = (CCustomInfoExProp*)m_pCtmEx;
			pDlg->SendMessage(WM_ENDTASK_CustomExProp,0,0);
			pDlg->SendMessage(WM_HANDLE_BATCH_CTM_CtmEx,0,0);
		}
		UpdateOperationStatus(_T("�����ͻ�������Ϣ���"));
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfFindAllCtm(int len)      //���������ͻ����ϵĻظ�
{
	if(len)   //�������û�н���
	{
		CtmInfo info;
		memset(&info,0,sizeof(CtmInfo));
		int errCode = recv(m_sockWhole,(char *)&info,len,0);
		if(errCode == SOCKET_ERROR)
		{
			AfxMessageBox(_T("���������ͻ����ϵĻظ���Ϣʧ��"));
			return FALSE;
		}
		USES_CONVERSION;
		CCtmInfo* pdlg = (CCtmInfo*)m_pCtmInfo;
		if(m_pCtmInfo == NULL){
			UpdateOperationStatus(_T("�����ͻ����ϵ������Ѿ�ȡ��"));
			return TRUE;
		}
		int nCount = pdlg->m_list.GetItemCount();
		pdlg->m_list.InsertItem(nCount,_T(""));//�����µ�һ��
		pdlg->m_list.SetItemText(nCount,0,A2T(info.NO));
		pdlg->m_list.SetItemText(nCount,1,A2T(info.call_ctm));
		pdlg->m_list.SetItemText(nCount,2,A2T(info.name));
		pdlg->m_list.SetItemText(nCount,3,A2T(info.sex));
		pdlg->m_list.SetItemText(nCount,4,A2T(info.phone));
		pdlg->m_list.SetItemText(nCount,5,A2T(info.pay_times));
		pdlg->m_list.SetItemText(nCount,6,A2T(info.pay_total));
		pdlg->m_list.SetItemText(nCount,7,A2T(info.first_pay_time));
		pdlg->m_list.SetItemText(nCount,8,A2T(info.late_pay_time));
		pdlg->m_list.SetItemText(nCount,9,A2T(info.ps)); 
	}else{    //��������Ѿ�����
		if(m_pCtmInfo != NULL){
			CCtmInfo* pDlg = (CCtmInfo*)m_pCtmInfo;
			//pDlg->SendMessage(WM_ENDTASK_CtmInfo,0,0);
			pDlg->m_tip.SetWindowTextW(_T("�����ͻ�������Ϣ���"));
			m_pCtmInfo = NULL;
		}
		UpdateOperationStatus(_T("�����ͻ�������Ϣ���"));
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfSearchAllFctInfo(int len)
{
	if(len)   //�������û�н���
	{
		FctInfo info;
		memset(&info,0,sizeof(FctInfo));
		int errCode = recv(m_sockWhole,(char *)&info,len,0);
		if(errCode == SOCKET_ERROR)
		{
			AfxMessageBox(_T("��������Ա���Ļظ���Ϣʧ��"));
			return FALSE;
		}
		USES_CONVERSION;
		CFctSet* pdlg = (CFctSet*)m_pFctSet;
		if(m_pFctSet == NULL){
			UpdateOperationStatus(_T("����Ա���Ѿ�ȡ��"));
			return TRUE;
		}
		int nCount = pdlg->m_list.GetItemCount();
		pdlg->m_list.InsertItem(nCount,_T(""));//�����µ�һ��
		pdlg->m_list.SetItemText(nCount,0,A2T(info.name_fct));
		pdlg->m_list.SetItemText(nCount,1,A2T(info.addr_fct));
		pdlg->m_list.SetItemText(nCount,2,A2T(info.contacts_fct));
		pdlg->m_list.SetItemText(nCount,3,A2T(info.main_product_fct));
		pdlg->m_list.SetItemText(nCount,4,A2T(info.phone_fct));
		pdlg->m_list.SetItemText(nCount,5,A2T(info.ps_fct));
	}else{    //��������Ѿ�����
		if(m_pFctSet != NULL){
			CFctSet* pDlg = (CFctSet*)m_pFctSet;
			pDlg->SendMessage(WM_ENDTASK_FctSet,0,0);
			pDlg->m_tip.SetWindowTextW(_T("����������Ϣ���"));
		}
		UpdateOperationStatus(_T("����������Ϣ���"));
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfSearchAllEmpInfoForEx(int len)    //��������Ա�������Թ�����
{
	if(len)   //�������û�н���
	{
		EmpInfo empinfo;
		memset(&empinfo,0,sizeof(EmpInfo));
		int errCode = recv(m_sockWhole,(char *)&empinfo,len,0);
		if(errCode == SOCKET_ERROR)
		{
			AfxMessageBox(_T("��������Ա���Ļظ���Ϣʧ��"));
			return FALSE;
		}

		USES_CONVERSION;
		CEmpInfoExProp* pDlg = (CEmpInfoExProp*)m_pEmpInfoEx;
		if(m_pEmpInfoEx == NULL){
			UpdateOperationStatus(_T("����Ա���Ѿ�ȡ��"));
			return TRUE;
		}
		int nCount = pDlg->m_list.GetItemCount();
		pDlg->m_list.InsertItem(nCount,_T(""));//�����µ�һ��
		pDlg->m_list.SetItemText(nCount,0,A2T(empinfo.empNum));
		pDlg->m_list.SetItemText(nCount,1,A2T(empinfo.empName));
		pDlg->m_list.SetItemText(nCount,2,A2T(empinfo.empAddr));
		pDlg->m_list.SetItemText(nCount,3,A2T(empinfo.empPos));
		pDlg->m_list.SetItemText(nCount,4,A2T(empinfo.empPhone));
		pDlg->m_list.SetItemText(nCount,5,A2T(empinfo.empPS));
	}else{    //��������Ѿ�����
		if(m_pEmpInfoEx != NULL){
			CEmpInfoExProp* pDlg = (CEmpInfoExProp*)m_pEmpInfoEx;
			pDlg->SendMessage(WM_ENDTASK_EmpInfoExProp,0,0);
		}
		UpdateOperationStatus(_T("����Ա����Ϣ���"));
	}
	return TRUE;
}

BOOL CSock::RecvReplyOfSearchAllEmpInfo(int len)
{
	if(len)   //�������û�н���
	{
		EmpInfo empinfo;
		memset(&empinfo,0,sizeof(EmpInfo));
		int errCode = recv(m_sockWhole,(char *)&empinfo,len,0);
		if(errCode == SOCKET_ERROR)
		{
			AfxMessageBox(_T("��������Ա���Ļظ���Ϣʧ��"));
			return FALSE;
		}

		USES_CONVERSION;
		CEmpInfoView* pView = (CEmpInfoView*)m_pEmpInfoView;
		if(m_pEmpInfoView == NULL){
			UpdateOperationStatus(_T("����Ա���Ѿ�ȡ��"));
			return TRUE;
		}
		int nCount = pView->m_list.GetItemCount();
		pView->m_list.InsertItem(nCount,_T(""));//�����µ�һ��
		pView->m_list.SetItemText(nCount,0,A2T(empinfo.empNum));
		pView->m_list.SetItemText(nCount,1,A2T(empinfo.empName));
		pView->m_list.SetItemText(nCount,2,A2T(empinfo.empAddr));
		pView->m_list.SetItemText(nCount,3,A2T(empinfo.empPos));
		pView->m_list.SetItemText(nCount,4,A2T(empinfo.empPhone));
		pView->m_list.SetItemText(nCount,5,A2T(empinfo.empPS));
	}else{    //��������Ѿ�����
		if(m_pEmpInfoView != NULL){
			CEmpInfoView* pDlg = (CEmpInfoView*)m_pEmpInfoView;
			pDlg->SendMessage(WM_CURSORBACKNORMAL,0,0);
			//pDlg->SendMessage(WM_ENDTASK_EmpInfoView,0,0);
			pDlg->m_tip.SetWindowText(_T("����Ա����Ϣ���"));
			m_pEmpInfoView = NULL;
		}
		UpdateOperationStatus(_T("����Ա����Ϣ���"));
		return TRUE;
	}
	return TRUE;
}

void CSock::UpdateOperationStatus(CString _status)  //���Խ���ǰ������Ϣ���µ�״̬��
{
	CBMApp *p_App = (CBMApp *)AfxGetApp();
	p_App->m_pMainWnd->SendMessage(WM_UPDATEOPERATIONSTATUS,0,(LPARAM)(LPCTSTR)_status);
}


BOOL CSock::IsItemValidity(CString _source,CString _item_name,BOOL bCheckEmpty,BOOL bCheckNum,BOOL bCheckDateFormat,int str_len_max)    //true  ��Ч ������Ч  
	//������Ƿ�Ϊ�� �Ƿ������� �Լ������Ƿ񳬹�����  �����Ҫ����Ƿ������ֵĻ� ��ô��У���Ƿ���������ַ�  ������Ƿ�������ڸ�ʽ
{
	WT;
	if(bCheckEmpty)    //TRUE  ������Ҫ����Ƿ�Ϊ�� ������Ϊ��
	{
		if(_source.IsEmpty())   //
		{
			CString err = _item_name+_T("����Ϊ��");
			AfxMessageBox(err);
			return FALSE;
		}
	}
	if(!_source.IsEmpty())
	{
		if(bCheckNum)    //��Ҫ����Ƿ�Ϊ����
		{
			if(!IsNum(_source))
			{
				CString err = _item_name+_T("����Ϊ����");
				AfxMessageBox(err);
				return FALSE;
			}
		}
		if(ContainsCharsRemain(_source))
		{
			return FALSE;
		}

		if(_source.GetLength()>str_len_max)  //������ݳ���
		{
			CString err;
			err.Format(_T("%s���ݳ��Ȳ��ܳ���%d"),_item_name,str_len_max);
			AfxMessageBox(err);
			return FALSE;
		}
		if(bCheckDateFormat)   //����Ƿ�������ڸ�ʽ
		{
			CString _err2 = _item_name+_T("���������ڸ�ʽ����׼��ʽ�磺2014-10-05");
			CString str = _source;
			int  index = _source.Find('-');
			if(index == -1)   //û�ҵ�
			{
				AfxMessageBox(_err2);
				return FALSE;
			}else{
				CString left = str.Mid(0,index);
				str = str.Mid(index+1);
				if(left.GetLength()!=4)
				{
					AfxMessageBox(_err2);
					return FALSE;
				}else{
					if(!IsNum(left))
					{
						AfxMessageBox(_err2);
						return FALSE;
					}else if(atoi(T2A(left))<2000 ||atoi(T2A(left))>3000){
						CString err3 = _item_name+_T("��ݱ���Ϊ2000��3000֮��");
						AfxMessageBox(err3);
						return FALSE;
					}else{    //ǰ�滹��Ϸ���
						index = str.Find('-');
						if(index == -1)   //û�ҵ�
						{
							AfxMessageBox(_err2);
							return FALSE;
						}else{
							left = str.Mid(0,index);
							str = str.Mid(index+1);
							if(IsNum(left)&&IsNum(str))
							{
								if(atoi(T2A(left))<1||atoi(T2A(left))>12)
								{
									CString err3 = _item_name+_T("�·ݱ���Ϊ1��12֮��");
									AfxMessageBox(err3);
									return FALSE;
								}else if(atoi(T2A(left))<1||atoi(T2A(left))>31)
								{
									CString err3 = _item_name+_T("�����Ϊ1��31֮��");
									AfxMessageBox(err3);
									return FALSE;
								}
							}else{
								AfxMessageBox(_err2);
								return FALSE;
							}
						}
					}
				}
			}
		}
	}
	return TRUE;
}


BOOL CSock::ContainsCharsRemain(CString str)     //����ַ����Ƿ�������ַ���
{
	CString temp1 = _T("[#");
	CString temp2 = _T("#]");
	CString temp3 = _T("{#");
	CString temp4 = _T("#}");
	int flag = 0;
	flag = str.Find(temp1);
	if(flag != -1)
	{
		AfxMessageBox(_T("�����в��ܰ�����[#���ַ�"));
		return TRUE;
	}
	flag = str.Find(temp2);
	if(flag != -1)
	{
		AfxMessageBox(_T("�����в��ܰ�����#]���ַ�"));
		return TRUE;
	}
	flag = str.Find(temp3);
	if(flag != -1)
	{
		AfxMessageBox(_T("�����в��ܰ�����#}���ַ�"));
		return TRUE;
	}
	flag = str.Find(temp4);
	if(flag != -1)
	{
		AfxMessageBox(_T("�����в��ܰ�����{#���ַ�"));
		return TRUE;
	}
	return FALSE;
}

BOOL CSock::IsNum(CString str)    //����һ���ַ��� ������Ƿ�Ϊ����
{
	WT;
	char *p = T2A(str);
	int i = 0;
	int count = str.GetLength();
	while(count){
		if(p[i]>'9'||p[i]<'0')
		{
			if(p[i] != '.')
			{
				return FALSE;
			}
			
		}
		count--;
		i++;
	}
	return TRUE;
}

BOOL CSock::RecvDataFromServer(SOCKET s,char* p_recv,int data_len,CString message)
{
	int nflag = recv(s,p_recv,data_len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(message);
		UpdateOperationStatus(message);
		return FALSE;
	}else if(nflag == 0)
	{
		AfxMessageBox(message);
		UpdateOperationStatus(message);
		return FALSE;
	}else if(nflag >0)
	{
		return TRUE;
	}
	return TRUE;
}

BOOL CSock::SendDataToServer(SOCKET s,char* p_send,CString message,int data_len)
{
	int nflag = send(s,p_send,data_len,0);
	if(nflag == SOCKET_ERROR)
	{
		AfxMessageBox(message);
		UpdateOperationStatus(message);
		return FALSE;
	}
	return TRUE;
}

BOOL CSock::IsNum(CString _source,BOOL bCheckDot)
{
	WT;
	char *p = T2A(_source);
	int i = 0;
	int count = _source.GetLength();
	while(count){
		if(p[i]>'9'||p[i]<'0')
		{
			if(bCheckDot)    //ֻ������Ҫ����Ƿ�Ϊ���ʱ��ż��
			{
				if(p[i] != '.')
				{
					return FALSE;
				}
			}else{
				return FALSE;
			}
			
			
		}
		count--;
		i++;
	}
	return TRUE;
}

BOOL CSock::IsUserHasAuthority(int n_authority)
{
	CString tip;
	if(NULL == m_pPosAuthority)
	{
		tip = _T("�û�Ȩ�޼���ʧ�ܣ������˳�����״̬�������µ�¼��");
		AfxMessageBox(tip);
		m_sockWhole = INVALID_SOCKET;
		m_bIsConnecting = FALSE;     //���ӶϿ� ���û����µ�¼
		m_bOnline = FALSE;        // �Ͽ��ߺ� ���Ӳ�����
		m_nameOnline.Empty();     //�Ͽ����Ӻ� ������ߵ��û���
		((CBMApp*)AfxGetApp())->m_sHost = INVALID_SOCKET;   //�����������³�ʼ��socket
		return FALSE;
	}
	if(!m_pPosAuthority->bLoadSuccess)
	{
		tip = _T("�û�Ȩ�޼���ʧ�ܣ������˳�����״̬�������µ�¼��");
		AfxMessageBox(tip);
		m_sockWhole = INVALID_SOCKET;
		m_bIsConnecting = FALSE;     //���ӶϿ� ���û����µ�¼
		m_bOnline = FALSE;        // �Ͽ��ߺ� ���Ӳ�����
		m_nameOnline.Empty();     //�Ͽ����Ӻ� ������ߵ��û���
		((CBMApp*)AfxGetApp())->m_sHost = INVALID_SOCKET;   //�����������³�ʼ��socket
		return FALSE;
	}
	if(n_authority < 0 || n_authority > 43)
	{
		tip = _T("ע�⣬Ȩ���������ںϷ���Χ��");
		AfxMessageBox(tip);
		return FALSE;
	}
	if(FALSE == m_pPosAuthority->autority[n_authority])
	{
		tip = _T("��Ǹ���������д˲�����Ȩ�ޣ�����ϵͳ����Ա������ӦȨ�ޣ�");
		AfxMessageBox(tip);
		return FALSE;
	}
	return TRUE;
}


/*
 * �����ļ�������0:����1:�쳣2:�������ݽ���
 */
int CSock::RecvFileData(SOCKET s, unsigned short ID,void* ptr)
{
	int nErrCode;	//���ش���
	hdr header;		//��ͷ
	
	//���հ�ͷ
	nErrCode = recv(s, (char*)&header, HEADLEN, 0);
	if (SOCKET_ERROR == nErrCode)
	{	
		int err = WSAGetLastError();
		CString _err_1;
		_err_1.Format(_T("���������ļ����ݰ�ͷʧ��,SOCKET_ERROR����%d"),err);
		AfxMessageBox(_err_1);
		return EXCEPT;
	}	
	if (REPLY_REQ_FILE_DOWNLOAD != header.type)
	{
		AfxMessageBox(_T("�����������ļ�����"));
		return EXCEPT;
	}
	
	//�����ļ�����
	if (0 == header.fpos && 0 == header.flen )
	{
		return FINISH;
	}


	unsigned long ulFileSeg = header.flen;	//�ļ�����
	unsigned long ulFilePos = header.fpos;	//�ļ�λ��(���λ��)
	CDealListView* p_dlg = (CDealListView*)ptr;
	p_dlg->m_ulCurTotal += ulFileSeg;				//�����ļ��ܳ���

	unsigned long nlTotal = 0;				//ÿ�ν��������ļ��ܳ���
	unsigned long nRead = 0;				//���ճ���
	char cBuf[RECV_BUFF] = {0};
	while (CSock::m_bIsConnecting && nlTotal != ulFileSeg)
	{
		memset(cBuf, 0, RECV_BUFF);
		nRead = recv(s, cBuf, ulFileSeg, 0);//׼������1024*20���ֽڳ���
		if (SOCKET_ERROR == nRead)
		{
			int err = WSAGetLastError();
			CString _err_1;
			_err_1.Format(_T("�����ļ�����ʧ��,SOCKET_ERROR����%d"),err);
			AfxMessageBox(_err_1);
			return EXCEPT;
		}else if (0 == nRead)
		{
			int err = WSAGetLastError();
			CString _err_1;
			_err_1.Format(_T("�����ļ�����ʧ��,SOCKET_ERROR����%d"),err);
			AfxMessageBox(_err_1);
			return EXCEPT;
		}

		SaveFile(ID, cBuf, nRead, ulFilePos + nlTotal,ptr);//������ʱ�ļ�
		nlTotal += nRead;//��������ֽ���
	}
	return NORMAL;
}

/*
 * ������ʱ�ļ�
 */
void CSock::SaveFile(u_short nIndexThread, const char* pBuf, u_long ulLen, u_long ulPos,void* ptr)
{
	CDealListView* p_dlg = (CDealListView*)ptr;
	WT;
	FILE *stream = NULL;
	CString strTemp = p_dlg->m_strFilePath;	//�����ļ�·��
	for(int i= 0;i<MAX_RECVFILE_THREAD;i++)
	{
		if(i == nIndexThread)
		{
			strTemp += p_dlg->m_DLFileTempName;
			CString temp = NULL;
			temp.Format(_T("%d.dl"),i);
			strTemp += temp;    //��i����ʱ�ļ���
			break;
		}
	}
	//stream = fopen(strTemp.c_str(), "ab+");		//���ļ�
	errno_t err = fopen_s(&stream,T2A(strTemp),"ab+");
	ASSERT(err == 0);
	//ASSERT(stream);
	
	int nErrCode = fseek(stream,ulPos,SEEK_SET);//�ƶ��ļ�ָ��
	ASSERT(nErrCode == 0);
	
	nErrCode = fwrite(pBuf, 1, ulLen, stream);	//д�ļ�
	ASSERT(nErrCode == ulLen);

	fflush(stream);								//����ļ�������
	fclose(stream);								//�ر��ļ�
}


void CSock::AssemblyFile(void* ptr)      //�ϲ������ļ����̺߳���
{
	WT;
	//�ļ�ָ��	
	//�õ��ļ���
	CDealListView* p_dlg = (CDealListView*)ptr;
	int nIndex = p_dlg->m_strToDLFile.Find(',');//�ҵ�ĩβ��'\'	
	CString strFileName = p_dlg->m_strToDLFile.Mid(nIndex + 1);   //�ļ���	
	CString strFile = p_dlg->m_strFilePath;//�ļ�·��
	strFile += strFileName;

	//�����ļ��Ƿ����
	CFileFind find;
	BOOL flag = find.FindFile(strFile);
	if(flag)   //���������ļ������ǾͰ����ص��ļ���������
	{
		nIndex = strFile.ReverseFind('.');
		CString _str_temp = strFile.Mid(0,nIndex)+_T("1");
		_str_temp += strFile.Mid(nIndex+1);
		strFile = _str_temp;     //������Ϊ�ļ���+1���ļ�
	}
	
	FILE *streamIn = NULL;//д
	//streamIn =  fopen(strFile.c_str(), "wb+");//���ļ�
	errno_t err = fopen_s(&streamIn,T2A(strFile), "wb+");
	ASSERT(streamIn);
	int threadNum = MAX_RECVFILE_THREAD;   //�������߳���
	u_long file_len = 0;   //�ļ�����
	for(int i =0;i<threadNum;i++)
	{
		FILE* stream = NULL;
		CString strTemp = p_dlg->m_strFilePath;    //��i����ʱ�ļ�
		strTemp += p_dlg->m_DLFileTempName;
		CString _str_temp = NULL;
		_str_temp.Format(_T("%d"),i);
		_str_temp += _T(".dl");
		strTemp += _str_temp;

		errno_t err1 = fopen_s(&stream,T2A(strTemp), "rb");   //���ļ�
		ASSERT(stream);
		u_long	ulFileLen = AssembleLine(streamIn, file_len, stream);  //д���ļ�
		file_len += ulFileLen;
		fclose(stream);
		//ɾ����ʱ�ļ�	
		DeleteFile(strTemp);
	
	}
	fclose(streamIn);
}

u_long  CSock::AssembleLine(FILE* destFile, int startPos, FILE* resoFile)
{
	//��ȡ���ļ��ĳ���
	fseek(resoFile, 0, SEEK_END);
	unsigned long resoFileLen = ftell(resoFile);
	
	unsigned long  nOffsetLen = 0;	//�Ѿ���ȡ�ֽ��� 
	unsigned long  nReadLen = 0;	//fread��ȡ�ֽ���

	char buf[BUF_SIZE];				//��ʱ����
	memset(buf, 0, BUF_SIZE);		//���
	while (resoFileLen != nOffsetLen && !feof(resoFile))
	{
		fseek(resoFile,0 + nOffsetLen,SEEK_SET);		//�ƶ����ļ�ָ��
		nReadLen = fread(buf,1,BUF_SIZE, resoFile);		//��������
		fseek(destFile,startPos + nOffsetLen,SEEK_SET);	//�ƶ�д�ļ�ָ��
		fwrite(buf,1,nReadLen,destFile);				//д������
		nOffsetLen += nReadLen;							//�����Ѷ�����
		memset(buf, 0, BUF_SIZE);						//���
	}

	return nOffsetLen;									//����ʵ���ļ�����
}