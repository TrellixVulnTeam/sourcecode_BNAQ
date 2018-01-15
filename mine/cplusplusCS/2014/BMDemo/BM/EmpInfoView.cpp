// EmpInfoView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "EmpInfoView.h"
#include "EmpInfoSearch.h"
#include "EmpNew.h"
#include "EmpEdit.h"
// CEmpInfoView

IMPLEMENT_DYNCREATE(CEmpInfoView, CFormView)

CEmpInfoView::CEmpInfoView()
	: CFormView(CEmpInfoView::IDD)
{

}

CEmpInfoView::~CEmpInfoView()
{
}

void CEmpInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EMP, m_list);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
}

BEGIN_MESSAGE_MAP(CEmpInfoView, CFormView)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(WM_CURSORBACKNORMAL,&CEmpInfoView::OnCursorToNormal)
	ON_BN_CLICKED(IDC_BTN_EMP_NEW, &CEmpInfoView::OnBnClickedBtnEmpNew)
	ON_BN_CLICKED(IDC_BTN_EMP_EDIT, &CEmpInfoView::OnBnClickedBtnEmpEdit)
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CEmpInfoView::OnBnClickedBtnSearch)
	ON_WM_TIMER()
	ON_MESSAGE(WM_STARTTASK_EmpInfoView, &CEmpInfoView::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_EmpInfoView, &CEmpInfoView::OnEndTask)
	ON_BN_CLICKED(IDC_BTN_EMP_DEL, &CEmpInfoView::OnBnClickedBtnEmpDel)
	ON_MESSAGE(WM_DELSELEMPINFO, &CEmpInfoView::OnDelSelEmpInfo)
END_MESSAGE_MAP()


// CEmpInfoView ���

#ifdef _DEBUG
void CEmpInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CEmpInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CEmpInfoView ��Ϣ�������
void CEmpInfoView::InitList()
{
	m_list.SetBkColor(RGB(223, 223, 223));
	m_list.SetExtendedStyle( m_list.GetExtendedStyle()| LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.SetTextColor(RGB(139, 90, 43));
	m_list.SetTextBkColor(RGB(255, 236, 139));
	
	CRect rect;
	m_list.GetClientRect(rect);
	m_list.InsertColumn(0, _T("Ա������"), LVCFMT_LEFT, rect.Width()/4);    
    m_list.InsertColumn(1, _T("Ա������"), LVCFMT_LEFT, rect.Width()/4);
	m_list.InsertColumn(2, _T("�����ص�"), LVCFMT_LEFT, rect.Width()/4);
    m_list.InsertColumn(3, _T("ְ��"), LVCFMT_LEFT, rect.Width()/4);
	m_list.InsertColumn(4, _T("��ϵ�绰"), LVCFMT_LEFT, rect.Width()/4);
	m_list.InsertColumn(5, _T("��ע"), LVCFMT_LEFT, rect.Width()/4);
	
	/*
	m_list.InsertItem(0, _T("0001"));    
    m_list.SetItemText(0, 1, _T("����"));    
    m_list.SetItemText(0, 2, _T("�Ͼ�"));    
    m_list.SetItemText(0, 3, _T("�ܾ���")); 
	m_list.SetItemText(0, 4, _T("12345678901"));
	m_list.SetItemText(0, 5, _T("��")); 
	*/
}


void CEmpInfoView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	
	CFont font;
	LOGFONT m_tempfont={22,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	font.Detach();

	InitList();
}

HBRUSH CEmpInfoView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)  
	{
		pDC->SetBkMode(TRANSPARENT);  
		//hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
		HBRUSH b_static=CreateSolidBrush(RGB(185,211,255));	
		return b_static;	
	}
	if(nCtlColor == CTLCOLOR_DLG)   //���ĶԻ��򱳾�ɫ 
	{ 
		pDC->SetTextColor(RGB(0,0,0)); 
		pDC->SetBkColor(RGB(185,211,255)); 
		HBRUSH b=CreateSolidBrush(RGB(185,211,255)); 
		return b; 
	} 
	return hbr;
}


void CEmpInfoView::OnBnClickedBtnEmpNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//m_empNewDlg.SetBackgroundColor(RGB(185,211,255));
	//m_empNewDlg.DoModal();
	CEmpNew dlg(this);
	dlg.DoModal();
}


void CEmpInfoView::OnBnClickedBtnEmpEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString	  num_emp_ToEdit = NULL;   //��Ҫ
	CString   name_emp_ToEdit = NULL;
	CString   pos_emp_ToEdit = NULL;
	CString   phone_emp_ToEdit = NULL;
	CString   ps_emp_ToEdit = NULL;
	CString   addr_emp_ToEdit = NULL;
	int count = 0;
	for(int i=0; i<m_list.GetItemCount(); i++)
	{
		if(m_list.GetCheck(i))
		{	
			count++ ;
			if(count > 1)  //��ʾ�ж��ѡ����
			{
				CString str;
				str.Format(_T("��ǰ�ж��ѡ���Ĭ�Ͻ��༭��һ��ѡ���Ա����Ϊ��%s��ȷ�ϼ�����"),num_emp_ToEdit);
				if(IDYES == MessageBox(str,_T("��ʾ"),MB_YESNO)){
					break;
				}else
				{
					return;
				}
			}
			num_emp_ToEdit = m_list.GetItemText(i,0);
			name_emp_ToEdit = m_list.GetItemText(i,1);
			addr_emp_ToEdit = m_list.GetItemText(i,2);
			pos_emp_ToEdit = m_list.GetItemText(i,3);
			phone_emp_ToEdit = m_list.GetItemText(i,4);
			ps_emp_ToEdit = m_list.GetItemText(i,5);
		}
	}
	if(num_emp_ToEdit.IsEmpty())
	{
		MessageBox(_T("��ǰû��ѡ���������ѡ��һ��Ա�����б༭"));
		return;
	}
	CEmpEdit dlg(this);
	dlg.m_num_emp = num_emp_ToEdit;
	dlg.m_name_emp = name_emp_ToEdit;
	dlg.m_pos_emp = pos_emp_ToEdit;
	dlg.m_addr_emp = addr_emp_ToEdit;
	dlg.m_ps_emp = ps_emp_ToEdit;
	dlg.m_phone_emp = phone_emp_ToEdit;
	dlg.DoModal();
}


void CEmpInfoView::OnBnClickedBtnSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEmpInfoSearch empSearchDlg(this);
	empSearchDlg.DoModal();
}

afx_msg LRESULT CEmpInfoView::OnCursorToNormal(WPARAM wParam, LPARAM lParam)
{
	SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR ,(LONG)LoadCursor(NULL , IDC_ARROW));
	return 0;
}

void CEmpInfoView::OnTimer(UINT_PTR nIDEvent)
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
	CFormView::OnTimer(nIDEvent);
}

void CEmpInfoView::ShowTip()
{
	m_time_take++;
	CString tip;
	tip.Format(_T("��ʱ��%d��"),m_time_take);
	m_tip.SetWindowText(tip);
	if(m_time_take == 60)
	{
		m_time_take = 0;
		KillTimer(1);
		m_tip.SetWindowText(_T("���ӳ�ʱ���������������״̬������"));
	}
}


afx_msg LRESULT CEmpInfoView::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CEmpInfoView::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T("����"));
	return 0;
}


void CEmpInfoView::OnBnClickedBtnEmpDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int count = 0;
	CString num;
	CString  lineToDelete = _T("��Ҫ��ɾ����Ա���Ĺ����ǣ�");
	m_empToDelete.Empty();
	int total = m_list.GetItemCount();
	for(int i=0; i< total; i++)
	{
		//if( m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED ||m_list.GetCheck(i))
		if(m_list.GetCheck(i))
		{	
			count++;
			m_empToDelete += m_list.GetItemText(i,0);
			m_empToDelete += ",";   //����Ա��֮��ķָ���
		}
	}
	if(count == 0)
	{
		MessageBox(_T("�������ٹ�ѡһ��Ա����Ȼ����ɾ��"));
		return;
	}else{   //��ѡ����
		CString total;
		total.Format(_T("����%d��ѡ���"),count);
		lineToDelete += m_empToDelete + _T("ȷ��ɾ����");
		if(IDYES == MessageBox(total+lineToDelete,_T("����"),MB_YESNO))
		{
			CSock::StartDelEmpInfo(this);
		}else{
			return;
		}
	}
}




afx_msg LRESULT CEmpInfoView::OnDelSelEmpInfo(WPARAM wParam, LPARAM lParam)
{
	CString _strToDelete = m_empToDelete;
	CString _strToFind = _T(",");    //�ҵ������ı�־λ �����ַ��εĽ�ȡ
	while(TRUE)
	{
		int _strEnd = _strToDelete.Find(_strToFind);
		if(-1 == _strEnd)   //û���ҵ�
		{
			break;
		}else{
			CString temp = _strToDelete.Mid(0,_strEnd);
			int num = m_list.GetItemCount();
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

