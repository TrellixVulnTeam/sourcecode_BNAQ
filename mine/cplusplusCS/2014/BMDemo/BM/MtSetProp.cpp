// MtSetProp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "MtSetProp.h"
#include "afxdialogex.h"
#include "MtNoteNew.h"
#include "MtNoteEdit.h"
#include "MtAndFctSheet.h"

// CMtSetProp �Ի���

IMPLEMENT_DYNAMIC(CMtSetProp, CPropertyPage)

CMtSetProp::CMtSetProp()
	: CPropertyPage(CMtSetProp::IDD)
{
	m_strMtInfo = _T("");
	timeTake = 0;
	m_hItemChecked = NULL;
}

CMtSetProp::~CMtSetProp()
{
}

void CMtSetProp::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_MATERIAL, m_treeMaterial);
	//DDX_Control(pDX, IDC_STATIC_STATUS, m_status);
	//DDX_Control(pDX, IDC_ET_STATUS, m_status);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_status);
	DDX_Control(pDX, IDC_STATIC_TIME_TAKE, m_timeTakeStatus);
}


BEGIN_MESSAGE_MAP(CMtSetProp, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_NEW, &CMtSetProp::OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_MTEDIT, &CMtSetProp::OnBnClickedBtnMtEdit)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CMtSetProp::OnBnClickedBtnRefresh)
	ON_MESSAGE(WM_PAITMTTREE, &CMtSetProp::OnPaitMtTree)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE_MATERIAL, &CMtSetProp::OnItemExpandingTreeMt)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(WM_UPDATESTATUS_MtSetProp, &CMtSetProp::OnUpdateStatus)
	ON_MESSAGE(WM_REQNOTENEW_MtSetProp, &CMtSetProp::OnReqNoteNew)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_MESSAGE(WM_STRATREQMT_MtSetProp, &CMtSetProp::OnStratReqMt)
	ON_MESSAGE(WM_ENDREQMT_MtSetProp, &CMtSetProp::OnEndReqMt)
	ON_MESSAGE(WM_CLEARMTTREE_MtSetProp, &CMtSetProp::OnClearMtTree)
	//ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_MATERIAL, &CMtSetProp::OnTvnSelchangedTreeMaterial)
	//ON_NOTIFY(NM_CLICK, IDC_TREE_MATERIAL, &CMtSetProp::OnNMClickTreeMaterial)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_MATERIAL, &CMtSetProp::OnNMDblclkTreeMaterial)
	ON_MESSAGE(WM_REQNODEEDIT_MtSetProp, &CMtSetProp::OnReqNodeEdit)
	ON_BN_CLICKED(IDC_BTN_MTDELETE, &CMtSetProp::OnBnClickedBtnMtDelete)
END_MESSAGE_MAP()


// CMtSetProp ��Ϣ�������

BOOL CMtSetProp::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	
	CFont font;
	LOGFONT m_tempfont={20,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_status.SetFont(&font);
	m_timeTakeStatus.SetFont(&font);
	font.Detach();
	
	InitTree();
	return TRUE;
}

void CMtSetProp::InitTree()
{
	m_treeMaterial.SetBkColor(CONCTRLBKCOLOR);
	m_treeMaterial.InsertItem(_T("������"),TVI_ROOT,TVI_LAST);
	
	m_hItemCur = m_treeMaterial.GetRootItem();
	m_treeMaterial.SetItemState(m_hItemCur,INDEXTOSTATEIMAGEMASK(0),   TVIS_STATEIMAGEMASK);
	void* dlg = this;
	CSock::StartRefreshMtTree(dlg);
}


void CMtSetProp::OnBnClickedBtnNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMtNoteNew mtNoteNewDlg(this);
	//mtNoteNewDlg.m_persion
	mtNoteNewDlg.DoModal();
}


void CMtSetProp::OnBnClickedBtnMtEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(NULL == m_hItemChecked){
		m_status.SetWindowText(_T("����˫��ѡ��һ���ڵ㣬ѡ��һ����Ч�Ľڵ㣬���ڵ���⣡"));
		return;
	}
	CString curSelNode = NULL;
	curSelNode = m_treeMaterial.GetItemText(m_hItemChecked); 
	if(curSelNode == "������" || curSelNode.IsEmpty())
	{
		m_status.SetWindowText(_T("����ѡ��һ����Ч�Ľڵ㣬���ڵ���⣡"));
		return;
	}
	CMtNoteEdit mtSetEditDlg(this);
	mtSetEditDlg.m_nodeOrgName = curSelNode;
	mtSetEditDlg.DoModal();
}


void CMtSetProp::OnBnClickedBtnRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//m_status.SetWindowText(_T("����������������ʼ����������"));
	m_hItemCur = m_treeMaterial.GetRootItem();
	void* dlg = this;
	CSock::StartRefreshMtTree(dlg);
}


afx_msg LRESULT CMtSetProp::OnPaitMtTree(WPARAM wParam, LPARAM lParam)
{	
	m_strArr.RemoveAll();
	TransferSecondNode();
	PaintTree(m_hItemCur);		//�������
	m_status.SetWindowText(_T("�������"));
	m_treeMaterial.EnableWindow(TRUE);  //ʹ����ͼ��Ч
	return 0;
}

void CMtSetProp::PaintTree(HTREEITEM hItem)		//�������
{
	int size = m_strArr.GetSize();
	for(int i = 0; i < size; i++)
	{
		CString strSubDir = m_strArr.GetAt(i);      //�Ӷ���Ŀ¼������ȡ��һ��Ŀ¼(��������������Ŀ¼)
		CString strFind = _T("\\");					//����Ŀ¼������Ŀ¼�ķָ���
		int rootPos = strSubDir.Find(strFind);	//�ҵ��ָ���λ��
		if (-1 != rootPos)  //����ҵ��˷ָ���
		{
			CString strSecondNode = strSubDir.Mid(0,rootPos);
			HTREEITEM hChild = m_treeMaterial.InsertItem(strSecondNode,hItem,TVI_LAST);
			strSubDir = strSubDir.Mid(rootPos+1);
			while(TRUE)  //��ȡ����Ŀ¼ �������ͼ
			{
				int index = strSubDir.Find(_T("|"));
				if(-1 == index)
				{
					break;
				}else{
					CString strThirdNode = strSubDir.Mid(0,index);
					m_treeMaterial.InsertItem(strThirdNode,hChild,TVI_LAST);
					strThirdNode.Empty();
					strSubDir = strSubDir.Mid(index+1);
					continue;
				}
			}
		}
	}
	m_treeMaterial.Expand(hItem,TVE_EXPAND);	
}

void CMtSetProp::TransferSecondNode()
{
	m_strArr.RemoveAll();
	CString _strTreeInfo = m_strMtInfo;
	CString temp;
	while(TRUE)
	{
		CString strFind = _T("<");
		int _strBegin = _strTreeInfo.Find(strFind);
		if(_strBegin == -1)  //û�ҵ�
		{
			break;
		}else{   //�ҵ����ַ�����ʼ��λ�� 
			 int _strEnd = _strTreeInfo.Find(_T(">"));
			 if(_strEnd == -1)  //û�ҵ�
			 {
				 break;
			 }else{ //�ҵ����ַ���������λ��  ��ʼ��ȡ
				 temp = _strTreeInfo.Mid(_strBegin+1,(_strEnd -_strBegin-1));
				 m_strArr.Add(temp);
				 temp.Empty();
				 _strTreeInfo = _strTreeInfo.Mid(_strEnd+1);
				 continue;
			 }
		}
	}
}

void CMtSetProp::OnItemExpandingTreeMt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	//NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM hTreeItem = pNMTreeView->itemNew.hItem;		//ѡ�е�������

	if (m_hItemCur == hTreeItem)							//չ����Ϊ��ǰ��
	{
		return;												//�۵���չ��֮���л�
	}else
	{
		m_hItemCur = hTreeItem;								//�޸ĵ�ǰ����Ϊչ����
		m_treeMaterial.SelectItem(m_hItemCur);					//���ø���Ϊѡ��״̬
	}

	HTREEITEM hChild = m_treeMaterial.GetChildItem(hTreeItem);	//��һ���ڶ���Ŀ¼;
	BOOL bHasThirdDir = FALSE;								//��ʼֵ����Ϊû������Ŀ¼
	while (hChild != NULL)
	{
		 bHasThirdDir = m_treeMaterial.ItemHasChildren(hChild);	//�����ڵ�
		if (TRUE == bHasThirdDir)							//���������ڵ�
		{
			break;
		}		
 		hChild = m_treeMaterial.GetNextSiblingItem(hChild);		//��һ������Ŀ¼
	}
	
	//���ڵ������ڵ�
	if (TRUE == bHasThirdDir)
	{
		return;//�۵���չ��֮���л�
	}


	//�����ڵ������ڵ�
	m_treeMaterial.EnableWindow(FALSE);				//�������ӽڵ��ڼ��ֹ��������
	m_nodeName = m_treeMaterial.GetItemText(hTreeItem);
	CSock::StartExpandMtTree(this);
	
	//ɾ���ڶ����ڵ�
	hChild = m_treeMaterial.GetChildItem(hTreeItem);	//��һ�������ڵ�					
	while (hChild != NULL)
	{
		HTREEITEM hTreeItemTemp	= m_treeMaterial.GetNextSiblingItem(hChild);//��һ�������ڵ�
		m_treeMaterial.DeleteItem(hChild);
		hChild = hTreeItemTemp;
	}
	*pResult = 0;
}


HBRUSH CMtSetProp::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor==CTLCOLOR_STATIC)  
	{
		pDC->SetBkMode(TRANSPARENT);  
		//hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
		HBRUSH b_static=CreateSolidBrush(BACKGROUNDCOLOR);
		pDC->SetTextColor(RGB(21,21,21));
		return b_static;
		
	}
	
	if(nCtlColor == CTLCOLOR_DLG){
		pDC->SetTextColor(RGB(0,0,0)); 
		pDC->SetBkColor(BACKGROUNDCOLOR); 
		HBRUSH b=CreateSolidBrush(BACKGROUNDCOLOR); 
		return b;
	}
	return hbr;
}


afx_msg LRESULT CMtSetProp::OnUpdateStatus(WPARAM wParam, LPARAM lParam)
{
	CString status = (LPCTSTR)lParam;
	m_status.SetWindowText(status);
	return 0;
}


afx_msg LRESULT CMtSetProp::OnReqNoteNew(WPARAM wParam, LPARAM lParam)
{
	CSock::StartReqMtNodeNew(this);
	return 0;
}




void CMtSetProp::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPropertyPage::OnClose();
}

void CMtSetProp::EnableParentDlgShutDownBtn(BOOL nEnable)   //��������ҳ�رմ��ڰ�ť
{
	CMtAndFctSheet * p_parentDlg = (CMtAndFctSheet *)GetParent();
	//TRUE��ʾ���� FALSE��ʾ������   
	p_parentDlg->SetCloseBtnEable(nEnable);

}



void CMtSetProp::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
		{
			m_status.SetWindowText(_T("����ʱ�����������������״̬"));
			OnEndReqMt(0,0);
			CSock::m_pNotePublic = NULL;  //���ָ��
			break;
		}
	case 2:
		{
			ShowTimeTakeStatus();
			break;
		}
	default:
		break;
	}
	CPropertyPage::OnTimer(nIDEvent);
}

void CMtSetProp::ShowTimeTakeStatus()
{
	//m_timeTakeStatus.ShowWindow(SW_SHOW);
	timeTake++;
	CString time;
	time.Format(_T("��ʱ��%d��"),timeTake);
	m_timeTakeStatus.SetWindowText(time);
}

afx_msg LRESULT CMtSetProp::OnStratReqMt(WPARAM wParam, LPARAM lParam)
{
	EnableParentDlgShutDownBtn(FALSE);
	//SetTimer(1,20*1000,NULL);
	//SetTimer(2,1000,NULL);
	timeTake = 0;
	m_timeTakeStatus.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CMtSetProp::OnEndReqMt(WPARAM wParam, LPARAM lParam)
{
	EnableParentDlgShutDownBtn(TRUE);
	//KillTimer(1);
	//KillTimer(2);
	m_timeTakeStatus.SetWindowText(_T(""));
	timeTake = 0;
	return 0;
}


afx_msg LRESULT CMtSetProp::OnClearMtTree(WPARAM wParam, LPARAM lParam)
{
	//ɾ���ڶ����ڵ�
	HTREEITEM hChild = m_treeMaterial.GetChildItem(m_hItemCur);	//��һ�������ڵ�					
	while (hChild != NULL)
	{
		HTREEITEM hTreeItemTemp	= m_treeMaterial.GetNextSiblingItem(hChild);//��һ�������ڵ�
		m_treeMaterial.DeleteItem(hChild);
		hChild = hTreeItemTemp;
	}
	return 0;
}

/*
void CMtSetProp::OnTvnSelchangedTreeMaterial(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
		*pResult = 0;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	HTREEITEM hitemTemp = m_treeMaterial.GetSelectedItem();
	BOOL b= m_treeMaterial.GetCheck(hitemTemp);
	m_treeMaterial.SetCheck(hitemTemp,!b);
	AfxMessageBox(m_treeMaterial.GetItemText(hitemTemp));

}
*/
/*
void CMtSetProp::OnNMClickTreeMaterial(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	
	CPoint point;
    UINT uFlag;   //�����йص�����Ե���Ϣ������
    HTREEITEM hTree;
    BOOL bCheck;
    GetCursorPos(&point);    //��ȡ��Ļ�������
	m_treeMaterial.ScreenToClient(&point);           //ת���ɿͻ�����
	//point.Offset(-150,50);
	hTree = m_treeMaterial.HitTest(point,&uFlag);    //������CtreeCtrl�����Ĺ��ĵ�ǰλ�ú;��
	if((NULL!=hTree))
	{
		CString str = m_treeMaterial.GetItemText(hTree);
		 AfxMessageBox(str);
	}
    if ((NULL!=hTree) && (TVHT_ONITEMSTATEICON == uFlag))  //���и�ѡ��
    {
          bCheck = m_treeMaterial.GetCheck(hTree);      //��ȡ��ǰ��ѡ״̬
		  m_hItemChecked = hTree;
		  CString str = m_treeMaterial.GetItemText(m_hItemChecked);
		  AfxMessageBox(str);
		  //SetChildCheck(hTree,!bCheck);                  //�������ѡ״̬
     }
	 
}
*/

void CMtSetProp::OnNMDblclkTreeMaterial(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	HTREEITEM hitemTemp = m_treeMaterial.GetSelectedItem();
	BOOL b= m_treeMaterial.GetCheck(hitemTemp);
	m_treeMaterial.SetCheck(hitemTemp,!b);
	m_hItemChecked = hitemTemp;
	//AfxMessageBox(m_treeMaterial.GetItemText(hitemTemp));
}


afx_msg LRESULT CMtSetProp::OnReqNodeEdit(WPARAM wParam, LPARAM lParam)
{
	CSock::StartReqMtNodeEdit(this);
	return 0;
}


void CMtSetProp::OnBnClickedBtnMtDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(NULL == m_hItemChecked){
		m_status.SetWindowText(_T("����˫��ѡ��һ���ڵ㣬ѡ��һ����Ч�Ľڵ㣬���ڵ���⣡"));
		return;
	}
	CString curSelNode = NULL;
	curSelNode = m_treeMaterial.GetItemText(m_hItemChecked); 
	if(curSelNode == "������" || curSelNode.IsEmpty())
	{
		m_status.SetWindowText(_T("����ѡ��һ����Ч�Ľڵ㣬���ڵ���⣡"));
		return;
	}
	m_nodeName = curSelNode;
	CString _strTip;
	_strTip.Format(_T("��ѡ��ɾ���Ľڵ��ǣ�%s"),m_nodeName);
	if(IDYES == MessageBox(_strTip,_T("��ʾ"),MB_YESNO))  //���ȷ��Ҫɾ��
	{
		CSock::StartReqDeleteNode(this);
	}else{
		return;
	}
}
