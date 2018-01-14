// CtmInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "CtmInfo.h"
#include "afxdialogex.h"
#include "CtmNew.h"
#include "CtmEdit.h"



// CCtmInfo �Ի���

IMPLEMENT_DYNAMIC(CCtmInfo, CDialogEx)

CCtmInfo::CCtmInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCtmInfo::IDD, pParent)
{

}



CCtmInfo::~CCtmInfo()
{
}

void CCtmInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CTMINFO, m_list);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
}


BOOL CCtmInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

void CCtmInfo::InitList()
{
	m_list.SetBkColor(CONCTRLBKCOLOR);
	m_list.SetExtendedStyle( m_list.GetExtendedStyle()| LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.SetTextColor(RGB(139, 90, 43));
	m_list.SetTextBkColor(RGB(255, 236, 139));
	
	m_list.InsertColumn(0, _T("�ͻ����"), LVCFMT_LEFT, 150);    
    m_list.InsertColumn(1, _T("�ͻ�����"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(2, _T("�˿�����"), LVCFMT_LEFT, 100);
    m_list.InsertColumn(3, _T("�Ա�"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(4, _T("�绰"), LVCFMT_LEFT, 150);
	m_list.InsertColumn(5, _T("���۴���"), LVCFMT_LEFT, 100);   
	m_list.InsertColumn(6, _T("���"), LVCFMT_LEFT, 100);    
	m_list.InsertColumn(7, _T("�״���������"), LVCFMT_LEFT, 100);    
	m_list.InsertColumn(8, _T("�����������"), LVCFMT_LEFT, 100);    
	m_list.InsertColumn(9, _T("��ע"), LVCFMT_LEFT, 100);    

	//m_list.InsertItem(0, _T("00000"));    
   // m_list.SetItemText(0, 1, _T("����"));    
    //m_list.SetItemText(0, 2, _T("�Ͼ�"));    
    //m_list.SetItemText(0, 3, _T("�ܾ���"));    
    //m_list.SetItemText(0, 4, _T("12345678901")); 
	//m_list.SetItemText(0, 5, _T("��"));
}

BEGIN_MESSAGE_MAP(CCtmInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_NEW, &CCtmInfo::OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDIT, &CCtmInfo::OnBnClickedBtnEdit)
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_MESSAGE(WM_STARTTASK_CtmInfo, &CCtmInfo::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_CtmInfo, &CCtmInfo::OnEndTask)
	ON_BN_CLICKED(IDC_BTN_SEARCHALL, &CCtmInfo::OnBnClickedBtnSearchall)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CCtmInfo::OnBnClickedBtnDelete)
	ON_MESSAGE(WM_DELCTM_CtmInfo, &CCtmInfo::OnDelCtm)
END_MESSAGE_MAP()


// CCtmInfo ��Ϣ�������


void CCtmInfo::OnBnClickedBtnNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CCtmNew dlg(this);
	dlg.DoModal();
}


void CCtmInfo::OnBnClickedBtnEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString	  NO = NULL;   //��Ҫ
	CString   call = NULL;
	CString   name = NULL;
	CString   sex = NULL;
	CString   phone = NULL;
	CString   times = NULL;
	CString   paytotal = NULL;
	CString   firsttime = NULL;
	CString   latetime = NULL;
	CString   ps = NULL;

	int count = 0;
	for(int i=0; i<m_list.GetItemCount(); i++)
	{
		if(m_list.GetCheck(i))
		{	
			count++ ;
			if(count > 1)  //��ʾ�ж��ѡ����
			{
				CString str;
				str.Format(_T("��ǰ�ж��ѡ���Ĭ�Ͻ��༭��һ��ѡ����ͻ����Ϊ��%s��ȷ�ϼ�����"),NO);
				if(IDYES == MessageBox(str,_T("��ʾ"),MB_YESNO)){
					break;
				}else
				{
					return;
				}
			}
			NO = m_list.GetItemText(i,0);
			call = m_list.GetItemText(i,1);
			name = m_list.GetItemText(i,2);
			sex = m_list.GetItemText(i,3);
			phone = m_list.GetItemText(i,4);
			times = m_list.GetItemText(i,5);
			paytotal = m_list.GetItemText(i,6);
			firsttime = m_list.GetItemText(i,7);
			latetime = m_list.GetItemText(i,8);
			ps = m_list.GetItemText(i,9);
		}
	}
	if(NO.IsEmpty())
	{
		MessageBox(_T("��ǰû��ѡ���������ѡ��һ���ͻ����б༭"));
		return;
	}
	USES_CONVERSION;
	char *p = NULL;
	CCtmEdit dlg(this);
	dlg.m_ctmNM = name;
	p = T2A(NO);
	dlg.m_ctmNum = atoi(p);
	dlg.m_ctmCall = call;
	//dlg.LoadCombOfSex(sex);
	dlg.m_phone = phone;
	dlg.m_sexflag = sex;
	dlg.m_times = atoi(T2A(times));
	dlg.m_price = atoi(T2A(paytotal));
	dlg.m_timeFirst = firsttime;
	dlg.m_timeLate = latetime;
	dlg.m_ps = ps;
	dlg.DoModal();
}




HBRUSH CCtmInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)  
	{
		pDC->SetBkMode(TRANSPARENT);  
		//hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
		HBRUSH b_static=CreateSolidBrush(RGB(185,211,255));	
		return b_static;	
	}
	if(nCtlColor == CTLCOLOR_DLG){
		pDC->SetTextColor(RGB(0,0,0)); 
		pDC->SetBkColor(RGB(185,211,255)); 
		HBRUSH b=CreateSolidBrush(RGB(185,211,255)); 
		return b;
	}
	return hbr;
}


void CCtmInfo::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CSock::m_pCtmInfo = NULL;
	CDialogEx::OnClose();
}


void CCtmInfo::OnTimer(UINT_PTR nIDEvent)
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
	CDialogEx::OnTimer(nIDEvent);
}


afx_msg LRESULT CCtmInfo::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CCtmInfo::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T("����"));
	return 0;
}

void CCtmInfo::ShowTip()
{
	m_time_take++;
	CString time =NULL;
	time.Format(_T("��ʱ��%d��"),m_time_take);
	m_tip.SetWindowTextW(time);
	if(m_time_take == 120)
	{
		OnEndTask(0,0);
		m_tip.SetWindowTextW(_T("����ʱ�������Ի����������ӷ�����"));
	}
}

void CCtmInfo::OnBnClickedBtnSearchall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSock::StartFindAllCtm(this);
}


void CCtmInfo::OnBnClickedBtnDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int count = 0;
	CString num;
	CString  lineToDelete = _T("��Ҫ��ɾ���Ŀͻ��ı���ǣ�");
	m_strToDelCtm.Empty();
	int total = m_list.GetItemCount();
	for(int i=0; i< total; i++)
	{
		if(m_list.GetCheck(i))
		{	
			count++;
			m_strToDelCtm += m_list.GetItemText(i,0);
			m_strToDelCtm += ",";   //����ʱ��εķָ���
		}
	}
	if(count == 0)
	{
		MessageBox(_T("�������ٹ�ѡһ��Ա����Ȼ����ɾ��"));
		return;
	}else{   //��ѡ����
		CString total;
		total.Format(_T("����%d��ѡ���"),count);
		lineToDelete +=  m_strToDelCtm + _T("ȷ��ɾ����");
		if(IDYES == MessageBox(total+lineToDelete,_T("����"),MB_YESNO))
		{
			CSock::StartDelCtm(this);
		}else{
			return;
		}
	}
}


afx_msg LRESULT CCtmInfo::OnDelCtm(WPARAM wParam, LPARAM lParam)
{
	CString _strToDelete = m_strToDelCtm;
	CString _strToFind = _T(",");    //�ҵ������ı�־λ �����ַ��εĽ�ȡ
	while(TRUE){
		int _strEnd = _strToDelete.Find(_strToFind);
		if(-1 == _strEnd)   //û���ҵ�
		{
			break;
		}else{
			CString temp = _strToDelete.Mid(0,_strEnd);
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
