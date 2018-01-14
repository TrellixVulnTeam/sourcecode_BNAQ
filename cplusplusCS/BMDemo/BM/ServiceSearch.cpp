// ServiceSearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "ServiceSearch.h"
#include "ServSearch.h"
#include "ServModify.h"
// CServiceSearch

IMPLEMENT_DYNCREATE(CServiceSearch, CFormView)

CServiceSearch::CServiceSearch()
	: CFormView(CServiceSearch::IDD)
	//, m_keyword(_T(""))
{

}

CServiceSearch::~CServiceSearch()
{
}

void CServiceSearch::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TIMECHOOSE, m_dateType);
	DDX_Control(pDX, IDC_DATETIME_DEADLINE, m_dateEnd);
	DDX_Control(pDX, IDC_DATETIME_START, m_dateStart);
	//DDX_Text(pDX, IDC_EDIT_KEYWORD, m_keyword);
	DDX_Control(pDX, IDC_LIST_SERVICE, m_list);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
}

BEGIN_MESSAGE_MAP(CServiceSearch, CFormView)
	//ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_EDIT, &CServiceSearch::OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CServiceSearch::OnBnClickedBtnSearch)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_STARTTASK_ServiceSearch, &CServiceSearch::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_ServiceSearch, &CServiceSearch::OnEndTask)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CServiceSearch::OnBnClickedBtnDelete)
	ON_MESSAGE(WM_DELSERV_ServiceSearch, &CServiceSearch::OnDelServ)
	ON_BN_CLICKED(IDC_BTN_SEARCH_COMM, &CServiceSearch::OnBnClickedBtnSearchComm)
END_MESSAGE_MAP()



// CServiceSearch ���

#ifdef _DEBUG
void CServiceSearch::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CServiceSearch::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG




// CServiceSearch ��Ϣ�������
void CServiceSearch::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	InitList();
	InitCombDate();
	InitTipCtrl();
}

void CServiceSearch::InitTipCtrl()
{
	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	font.Detach();
}

void CServiceSearch::InitCombDate()
{
	m_dateType.AddString(_T("Ҫ���������"));
	m_dateType.AddString(_T("��������"));
	m_dateType.SetCurSel(0);

	m_dateEnd.SetFormat(_T("yyyy-MM-dd"));
	m_dateStart.SetFormat(_T("yyyy-MM-dd"));
}

void CServiceSearch::InitList()
{
	m_list.SetBkColor(CONCTRLBKCOLOR);
	m_list.SetExtendedStyle( m_list.GetExtendedStyle()| LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.SetTextColor(RGB(139, 90, 43));
	m_list.SetTextBkColor(RGB(255, 236, 139));
	
	CRect rect;
	m_list.GetClientRect(rect);
	m_list.InsertColumn(0, _T("���񵥺�"), LVCFMT_LEFT, rect.Width()/16);    
    m_list.InsertColumn(1, _T("����"), LVCFMT_LEFT, rect.Width()/16);
	m_list.InsertColumn(2, _T("��������"), LVCFMT_LEFT, rect.Width()/16);
    m_list.InsertColumn(3, _T("Ҫ���������"), LVCFMT_LEFT, rect.Width()/16);
	m_list.InsertColumn(4, _T("��������"), LVCFMT_LEFT, rect.Width()/16);
	m_list.InsertColumn(5, _T("�ͻ�����"), LVCFMT_LEFT, rect.Width()/16);
	m_list.InsertColumn(6, _T("�ͻ�����"), LVCFMT_LEFT, rect.Width()/16);
	m_list.InsertColumn(7, _T("�˿�����"), LVCFMT_LEFT, rect.Width()/16);
	m_list.InsertColumn(8, _T("�Ա�"), LVCFMT_LEFT, rect.Width()/16);
	m_list.InsertColumn(9, _T("�˿͵绰"), LVCFMT_LEFT, rect.Width()/16);
	m_list.InsertColumn(10, _T("��ַ"), LVCFMT_LEFT, rect.Width()/16);
	m_list.InsertColumn(11, _T("�տ���"), LVCFMT_LEFT, rect.Width()/16);
	m_list.InsertColumn(12, _T("������Ա����"), LVCFMT_LEFT, rect.Width()/16);
	m_list.InsertColumn(13, _T("������Ա�绰"), LVCFMT_LEFT, rect.Width()/16);
	m_list.InsertColumn(14, _T("��������"), LVCFMT_LEFT, rect.Width()/16);
	m_list.InsertColumn(15, _T("��ע"), LVCFMT_LEFT, rect.Width()/16);	   
}

void CServiceSearch::OnBnClickedBtnEdit()
{
	CServModify dlg;
	USES_CONVERSION;
	int count = 0;
	CString serv_no = NULL;
	for(int i=0; i<m_list.GetItemCount(); i++)
	{
		//if( m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED ||m_list.GetCheck(i))
		if(m_list.GetCheck(i))
		{	
			count++ ;
			if(count > 1)  //��ʾ�ж��ѡ����
			{
				CString str;
				str.Format(_T("��ǰ�ж��ѡ���Ĭ�Ͻ��༭��һ��ѡ������񵥺�Ϊ��'%s'��ȷ�ϼ�����"),serv_no);
				if(IDYES == MessageBox(str,_T("��ʾ"),MB_YESNO)){
					break;
				}else
				{
					return;
				}
			}
			serv_no = m_list.GetItemText(i,0);
			dlg.m_servNO = serv_no;
			dlg.m_strProg = m_list.GetItemText(i,1);
			dlg.m_servType = m_list.GetItemText(i,2);
			dlg.m_strDateReq = m_list.GetItemText(i,3);
			dlg.m_strDateDelay = m_list.GetItemText(i,4);
			dlg.m_strCtmType = m_list.GetItemText(i,5);
			dlg.m_ctmNM = m_list.GetItemText(i,6);
			dlg.m_clientNM = m_list.GetItemText(i,7);
			dlg.m_strCtmSex = m_list.GetItemText(i,8);
			dlg.m_phone = m_list.GetItemText(i,9);
			dlg.m_addr = m_list.GetItemText(i,10);
			dlg.m_charge = atof(T2A(m_list.GetItemText(i,11)));
			dlg.m_servNM = m_list.GetItemText(i,12);
			dlg.m_servPhone = m_list.GetItemText(i,13);
			dlg.m_servContent = m_list.GetItemText(i,14);
			dlg.m_ps = m_list.GetItemText(i,15);
		}
	}
	if(serv_no.IsEmpty())
	{
		MessageBox(_T("��ǰû��ѡ���������ѡ��һ�������б༭"));
		return;
	}
	dlg.DoModal();
}

void CServiceSearch::FindAllServ()
{
	CSock::StartFindAllServ(this);
}

void CServiceSearch::OnBnClickedBtnSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CServSearch servSearchDlg(this);
	servSearchDlg.DoModal();
}


HBRUSH CServiceSearch::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
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


void CServiceSearch::OnTimer(UINT_PTR nIDEvent)
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

void CServiceSearch::ShowTip()
{
	m_time_take++;
	CString time = NULL;
	time.Format(_T("��ʱ��%d��"),m_time_take);
	m_tip.SetWindowText(time);
	if(m_time_take == 120)
	{
		OnEndTask(0,0);
		m_tip.SetWindowText(_T("����ʱ�������Ի����������ӷ�����"));
	}
}


void CServiceSearch::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CFormView::OnClose();
}


afx_msg LRESULT CServiceSearch::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CServiceSearch::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


void CServiceSearch::OnBnClickedBtnDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int count = 0;
	CString num;
	CString  lineToDelete = _T("��Ҫ��ɾ������ĵ����ǣ�");
	m_strDelServ.Empty();
	int total = m_list.GetItemCount();
	for(int i=0; i< total; i++)
	{
		//if( m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED ||m_list.GetCheck(i))
		if(m_list.GetCheck(i))
		{	
			count++;
			m_strDelServ += m_list.GetItemText(i,0);
			m_strDelServ += ",";   //����ʱ��εķָ���
		}
	}
	if(count == 0)
	{
		MessageBox(_T("�������ٹ�ѡһ������Ȼ����ɾ��"));
		return;
	}else{   //��ѡ����
		CString total;
		total.Format(_T("����%d��ѡ���"),count);
		lineToDelete +=  m_strDelServ + _T("ȷ��ɾ����");
		if(IDYES == MessageBox(total+lineToDelete,_T("����"),MB_YESNO))
		{
			CSock::StartDelServ(this);
		}else{
			return;
		}
	}
}


afx_msg LRESULT CServiceSearch::OnDelServ(WPARAM wParam, LPARAM lParam)
{
	CString _strToDelete = m_strDelServ;
	m_strDelServ.Empty();
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


void CServiceSearch::OnBnClickedBtnSearchComm()     //��ͨ����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str = NULL;
	m_dateType.GetWindowText(str);
	m_searchByKeyWord.Empty();
	m_searchByKeyWord = _T("��ͨ����,");
	if(_T("Ҫ���������") == str)
	{
		m_searchByKeyWord += _T("Ҫ���������,");
	}else{
		m_searchByKeyWord += _T("��������,");
	}
	CTime timeTime;
	USES_CONVERSION;
	DWORD dwResult = m_dateStart.GetTime(timeTime);
	if (dwResult == GDT_VALID)
	{
		// the user checked the box and specified data
		
		// is it a time-only control, or a date-only control?
		if ((m_dateStart.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}else{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}
		m_searchByKeyWord += T2A(str) ;
		m_searchByKeyWord += _T(",");
	}else
	{
		MessageBox(_T("��ѡ��ʼ����"));
		return;
	}
	dwResult = m_dateEnd.GetTime(timeTime);
	if (dwResult == GDT_VALID)
	{
		if ((m_dateEnd.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}else{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}
		m_searchByKeyWord += T2A(str) ;
	}else
	{
		MessageBox(_T("��ѡ���ֹ����"));
		return;
	}
	CSock::StartFindServByKeyWord(this);
}
