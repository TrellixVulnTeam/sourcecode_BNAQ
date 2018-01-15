// StoreHistory.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "StoreHistory.h"
#include "afxdialogex.h"


// CStoreHistory �Ի���

IMPLEMENT_DYNAMIC(CStoreHistory, CDialogEx)

CStoreHistory::CStoreHistory(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStoreHistory::IDD, pParent)
{

}

CStoreHistory::~CStoreHistory()
{
}

void CStoreHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STORE_HISTORY, m_list);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
}


BEGIN_MESSAGE_MAP(CStoreHistory, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_FIND_ALL, &CStoreHistory::OnBnClickedBtnFindAll)
	
	ON_BN_CLICKED(IDC_BTN_DEL_HISTORY, &CStoreHistory::OnBnClickedBtnDelHistory)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_STARTTASK_StoreHistory, &CStoreHistory::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_StoreHistory, &CStoreHistory::OnEndTask)
	ON_MESSAGE(WM_DELHISTORY_StoreHistory, &CStoreHistory::OnDelHistory)
END_MESSAGE_MAP()


// CStoreHistory ��Ϣ�������

void CStoreHistory::InitList()
{
	m_list.SetBkColor(CONCTRLBKCOLOR);
	m_list.SetExtendedStyle( m_list.GetExtendedStyle()| LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.SetTextColor(RGB(139, 90, 43));
	m_list.SetTextBkColor(RGB(255, 236, 139));
	
	CRect rect;
	m_list.GetClientRect(rect);
	m_list.InsertColumn(0, _T("����"), LVCFMT_LEFT, rect.Width()/4);    
    m_list.InsertColumn(1, _T("�䶯����"), LVCFMT_LEFT, rect.Width()/4);
	m_list.InsertColumn(2, _T("״̬"), LVCFMT_LEFT, rect.Width()/4);
    m_list.InsertColumn(3, _T("ʱ��"), LVCFMT_LEFT, rect.Width()/4);
	
}

BOOL CStoreHistory::OnInitDialog()
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

HBRUSH CStoreHistory::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)  
	{
		pDC->SetBkMode(TRANSPARENT);  
		//hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
		HBRUSH b_static=CreateSolidBrush(BACKGROUNDCOLOR);	
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


void CStoreHistory::OnBnClickedBtnFindAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSock::StartFindAllStoreHistory(this);
}

void CStoreHistory::OnBnClickedBtnDelHistory()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int count = 0;
	CString num;
	CString  lineToDelete = _T("��Ҫ��ɾ����¼�Ĵ浵ʱ���ǣ�");
	m_strToDelHistory.Empty();
	int total = m_list.GetItemCount();
	for(int i=0; i< total; i++)
	{
		//if( m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED ||m_list.GetCheck(i))
		if(m_list.GetCheck(i))
		{	
			count++;
			m_strToDelHistory += m_list.GetItemText(i,3);
			m_strToDelHistory += ",";   //����ʱ��εķָ���
		}
	}
	if(count == 0)
	{
		MessageBox(_T("�������ٹ�ѡһ����¼��Ȼ����ɾ��"));
		return;
	}else{   //��ѡ����
		CString total;
		total.Format(_T("����%d��ѡ���"),count);
		lineToDelete +=  m_strToDelHistory + _T("ȷ��ɾ����");
		if(IDYES == MessageBox(total+lineToDelete,_T("����"),MB_YESNO))
		{
			CSock::StartDelHistory(this);
		}else{
			return;
		}
	}
}


void CStoreHistory::OnTimer(UINT_PTR nIDEvent)
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

void CStoreHistory::ShowTip()
{
	m_time_take++;
	CString time =NULL;
	time.Format(_T("��ʱ��%d��"),m_time_take);
	m_tip.SetWindowText(time);
	if(m_time_take == 120)
	{
		OnEndTask(0,0);
		m_tip.SetWindowText(_T("����ʱ�������Ի����������ӷ�����"));
	}
}

void CStoreHistory::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CSock::m_pStoreHistory = NULL;
	CDialogEx::OnClose();
}


afx_msg LRESULT CStoreHistory::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CStoreHistory::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T("����"));
	return 0;
}


afx_msg LRESULT CStoreHistory::OnDelHistory(WPARAM wParam, LPARAM lParam)
{
	CString _strToDelete = m_strToDelHistory;
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
				if(temp == m_list.GetItemText(i,3))
				{
					m_list.DeleteItem(i);
				}
			}
			_strToDelete = _strToDelete.Mid(_strEnd+1);
		}
	}
	return 0;
}
