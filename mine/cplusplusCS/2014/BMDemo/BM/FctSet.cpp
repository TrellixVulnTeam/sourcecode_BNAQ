// FctSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "FctSet.h"
#include "afxdialogex.h"
#include "FactoryNew.h"
#include "FactoryEdit.h"
#include "MtAndFctSheet.h"
// CFctSet �Ի���

IMPLEMENT_DYNAMIC(CFctSet, CPropertyPage)

CFctSet::CFctSet()
	: CPropertyPage(CFctSet::IDD)
{

}

CFctSet::~CFctSet()
{
}

void CFctSet::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FCTORY_INFO, m_list);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
}


BEGIN_MESSAGE_MAP(CFctSet, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_FCTNEW, &CFctSet::OnBnClickedBtnFctNew)
	ON_BN_CLICKED(IDC_BTN_FCTEDIT, &CFctSet::OnBnClickedBtnFctEdit)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_SEARCHALL, &CFctSet::OnBnClickedBtnSearchAll)
	ON_WM_TIMER()
	ON_MESSAGE(WM_STARTTASK_FctSet, &CFctSet::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_FctSet, &CFctSet::OnEndTask)
	ON_BN_CLICKED(IDC_BTN_FCTDELETE, &CFctSet::OnBnClickedBtnFctdelete)
	ON_MESSAGE(WM_DEL_FCT_FctSet, &CFctSet::OnDelFct)
END_MESSAGE_MAP()


// CFctSet ��Ϣ�������

BOOL CFctSet::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	
	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	font.Detach();
	
	InitList();
	return TRUE;
}

void CFctSet::InitList()
{
	m_list.SetBkColor(RGB(223,223,223));
	m_list.SetExtendedStyle( m_list.GetExtendedStyle()| LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.SetTextColor(RGB(139, 90, 43));
	m_list.SetTextBkColor(RGB(255, 236, 139));
	
	CRect rect;
	m_list.GetClientRect(rect);
	m_list.InsertColumn(0, _T("��������"), LVCFMT_LEFT, rect.Width()/4);    
    m_list.InsertColumn(1, _T("��ַ"), LVCFMT_LEFT, rect.Width()/4);
	m_list.InsertColumn(2, _T("��ϵ��"), LVCFMT_LEFT, rect.Width()/4);
    m_list.InsertColumn(3, _T("��Ҫ��Ʒ"), LVCFMT_LEFT, rect.Width()/4);
	m_list.InsertColumn(4, _T("��ϵ�绰"), LVCFMT_LEFT, rect.Width()/4);
	m_list.InsertColumn(5, _T("��ע"), LVCFMT_LEFT, rect.Width()/4);
	
	
	/*
	m_list.InsertItem(0, _T("���"));    
    m_list.SetItemText(0, 1, _T("�Ͼ�"));    
    m_list.SetItemText(0, 2, _T("����"));    
    m_list.SetItemText(0, 3, _T("���")); 
	m_list.SetItemText(0, 4, _T("12345678901"));
	m_list.SetItemText(0, 5, _T("��")); 
	*/
}

void CFctSet::OnBnClickedBtnFctNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFactoryNew ftNewDlg(this);
	ftNewDlg.DoModal();
}


void CFctSet::OnBnClickedBtnFctEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString	  name_fct = NULL;   //��Ҫ
	CString   addr_fct = NULL;
	CString   contacts_fct = NULL;
	CString   main_products_fct = NULL;
	CString   phone_fct = NULL;
	CString   ps_fct = NULL;
	int count = 0;
	for(int i=0; i<m_list.GetItemCount(); i++)
	{
		//if( m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED ||m_list.GetCheck(i))
		if(m_list.GetCheck(i))
		{	
			count++ ;
			if(count > 1)  //��ʾ�ж��ѡ����
			{
				CString str;
				str.Format(_T("��ǰ�ж��ѡ���Ĭ�Ͻ��༭��һ��ѡ�����������Ϊ��'%s'��ȷ�ϼ�����"),name_fct);
				if(IDYES == MessageBox(str,_T("��ʾ"),MB_YESNO)){
					break;
				}else
				{
					return;
				}
			}
			name_fct = m_list.GetItemText(i,0);
			addr_fct = m_list.GetItemText(i,1);
			contacts_fct = m_list.GetItemText(i,2);
			main_products_fct = m_list.GetItemText(i,3);
			phone_fct = m_list.GetItemText(i,4);
			ps_fct = m_list.GetItemText(i,5);
		}
	}
	if(name_fct.IsEmpty())
	{
		MessageBox(_T("��ǰû��ѡ���������ѡ��һ�����ҽ��б༭"));
		return;
	}
	CFactoryEdit dlg(this);
	dlg.m_name_fctEdit = name_fct;
	dlg.m_addr_fctEdit = addr_fct;
	dlg.m_contact_person_fctEdit = contacts_fct;
	dlg.m_main_product_fctEdit = main_products_fct;
	dlg.m_phone_fctEdit = phone_fct;
	dlg.m_ps_fctEdit = ps_fct;
	dlg.DoModal();

}


HBRUSH CFctSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)  
	{
		pDC->SetBkMode(TRANSPARENT);  
		//hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
		HBRUSH b_static=CreateSolidBrush(BACKGROUNDCOLOR);	
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

void CFctSet::EnableParentDlgShutDownBtn(BOOL nEnable)   //��������ҳ�رմ��ڰ�ť
{
	CMtAndFctSheet * p_parentDlg = (CMtAndFctSheet *)GetParent();
	//TRUE��ʾ���� FALSE��ʾ������   
	p_parentDlg->SetCloseBtnEable(nEnable);
}

void CFctSet::OnBnClickedBtnSearchAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSock::StartFindALLFct(this);
}


void CFctSet::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
		{
			ShowTip();
			break;
		}
	default:
		break;
	}
	CPropertyPage::OnTimer(nIDEvent);
}

void CFctSet::ShowTip()
{
	m_time_take++;
	CString tip;
	tip.Format(_T("��ʱ��%d��"),m_time_take);
	m_tip.SetWindowTextW(tip);
	if(m_time_take == 60)
	{
		OnEndTask(0,0);
		m_tip.SetWindowText(_T("����ʱ�������¼�����������״̬��������"));
	}
}

afx_msg LRESULT CFctSet::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	EnableParentDlgShutDownBtn(FALSE);
	//SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CFctSet::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	EnableParentDlgShutDownBtn(TRUE);
	//KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


void CFctSet::OnBnClickedBtnFctdelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int count = 0;
	CString num;
	CString  lineToDelete = _T("��Ҫ��ɾ���ĳ��ҵ������ǣ�");
	m_strfctToDel.Empty();
	int total = m_list.GetItemCount();
	for(int i=0; i< total; i++)
	{
		if(m_list.GetCheck(i))
		{	
			count++;
			m_strfctToDel += m_list.GetItemText(i,0);
			m_strfctToDel += ",";   //�������ֶεķָ���
		}
	}
	if(count == 0)
	{
		MessageBox(_T("�������ٹ�ѡһ�����ң�Ȼ����ɾ��"));
		return;
	}else{   //��ѡ����
		lineToDelete += m_strfctToDel + _T("ȷ��ɾ����");
		if(IDYES == MessageBox(lineToDelete,_T("����"),MB_YESNO))
		{
			CSock::StartDelFct(this);
		}else{
			return;
		}
	}
}


afx_msg LRESULT CFctSet::OnDelFct(WPARAM wParam, LPARAM lParam)
{
	CString _strToDelete = m_strfctToDel;
	CString temp; 
	CString _strToFind = _T(",");    //�ҵ������ı�־λ �����ַ��εĽ�ȡ
	while(TRUE)
	{
		int _strEnd = _strToDelete.Find(_strToFind);
		if(-1 == _strEnd)   //û���ҵ�
		{
			break;
		}else{
			temp = _strToDelete.Mid(0,_strEnd);
			int num =m_list.GetItemCount();
			for(int i = 0;i< num;i++){
				if(temp == m_list.GetItemText(i,0))
				{
					m_list.DeleteItem(i);
				}
			}
			_strToDelete = _strToDelete.Mid(_strEnd+1);
		}
	}
	return 0;
}

