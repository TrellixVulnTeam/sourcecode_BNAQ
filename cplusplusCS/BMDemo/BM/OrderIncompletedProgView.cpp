// OrderIncompletedProgView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "OrderIncompletedProgView.h"


// COrderIncompletedProgView

IMPLEMENT_DYNCREATE(COrderIncompletedProgView, CFormView)

COrderIncompletedProgView::COrderIncompletedProgView()
	: CFormView(COrderIncompletedProgView::IDD)
{

}

COrderIncompletedProgView::~COrderIncompletedProgView()
{
}

void COrderIncompletedProgView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ORDER_INCOMPLETED_PROG, m_list);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
	DDX_Control(pDX, IDC_SPLIT_OPERATION, m_split);
}

BEGIN_MESSAGE_MAP(COrderIncompletedProgView, CFormView)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_MESSAGE(WM_STARTTASK_OrderIncomplete, &COrderIncompletedProgView::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_OrderIncomplete, &COrderIncompletedProgView::OnEndTask)
	ON_BN_CLICKED(IDC_BTN_FIND_DEAL_INCOMPLETE, &COrderIncompletedProgView::OnBnClickedBtnFindDealIncomplete)
	ON_MESSAGE(WM_FILLLIST_OrderIncomplete, &COrderIncompletedProgView::OnFillList)
	ON_BN_CLICKED(IDC_BTN_SAVE, &COrderIncompletedProgView::OnBnClickedBtnSave)
	ON_COMMAND(ID_CHOOSE_ALL, &COrderIncompletedProgView::OnChooseAll)
	ON_COMMAND(ID_REVERSE_CHOOSE, &COrderIncompletedProgView::OnReverseChoose)
	ON_COMMAND(ID_CHOOSE_NONE, &COrderIncompletedProgView::OnChooseNone)
	ON_COMMAND(ID_DEL_FROM_LIST, &COrderIncompletedProgView::OnDelFromList)
	ON_COMMAND(ID_CLEAR_LIST, &COrderIncompletedProgView::OnClearList)
END_MESSAGE_MAP()


// COrderIncompletedProgView ���

#ifdef _DEBUG
void COrderIncompletedProgView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void COrderIncompletedProgView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG




HBRUSH COrderIncompletedProgView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		pDC->SetBkColor(RGB(185,211,255)); 
		HBRUSH b=CreateSolidBrush(RGB(185,211,255)); 
		return b;
	}
	return hbr;
}

// COrderIncompletedProgView ��Ϣ�������
void COrderIncompletedProgView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	InitList();
	InitTipCtrl();
	InitSplit();
}

void COrderIncompletedProgView::InitSplit()
{
	m_split.SetDropDownMenu(IDM_ORDER_INCOMPLETE_OPERATION,0);
}

void COrderIncompletedProgView::InitTipCtrl()
{
	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	font.Detach();
}
void COrderIncompletedProgView::InitList()
{
	m_list.SetBkColor(CONCTRLBKCOLOR);
	m_list.SetExtendedStyle( m_list.GetExtendedStyle()| LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.SetTextColor(RGB(139, 90, 43));
	m_list.SetTextBkColor(RGB(255, 236, 139));
	CString editCol = _T("1#2#3#4#5#6#7#8#9#10#11#12#");   //��Щ�ж����Ա༭
	m_list.SetItemEdit(TRUE,editCol);

	CRect rect;
	m_list.GetClientRect(rect);
	m_list.InsertColumn(0, _T("�������"), LVCFMT_LEFT, rect.Width()/13);    
    m_list.InsertColumn(1, _T("��������"), LVCFMT_LEFT, rect.Width()/13);
	m_list.InsertColumn(2, _T("��һ������"), LVCFMT_LEFT, rect.Width()/13);
	m_list.InsertColumn(3, _T("��һ������Ԥ���ʱ��"), LVCFMT_LEFT, rect.Width()/13);
    m_list.InsertColumn(4, _T("�����ܼ�"), LVCFMT_LEFT, rect.Width()/13);
	m_list.InsertColumn(5, _T("���ս��"), LVCFMT_LEFT, rect.Width()/13);
	m_list.InsertColumn(6, _T("�ͻ�����"), LVCFMT_LEFT, rect.Width()/13);
	m_list.InsertColumn(7, _T("�˿�����"), LVCFMT_LEFT, rect.Width()/13);
	m_list.InsertColumn(8, _T("�˿͵绰"), LVCFMT_LEFT, rect.Width()/13);
	m_list.InsertColumn(9, _T("�˿͵�ַ"), LVCFMT_LEFT, rect.Width()/13);
	m_list.InsertColumn(10, _T("����������"), LVCFMT_LEFT, rect.Width()/13);
	m_list.InsertColumn(11, _T("�����˵绰"), LVCFMT_LEFT, rect.Width()/13);
	m_list.InsertColumn(12, _T("��ע"), LVCFMT_LEFT, rect.Width()/13); 
}

void COrderIncompletedProgView::OnTimer(UINT_PTR nIDEvent)
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

void COrderIncompletedProgView::ShowTip()
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


afx_msg LRESULT COrderIncompletedProgView::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT COrderIncompletedProgView::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


void COrderIncompletedProgView::FillDataToList()
{
	m_tip.SetWindowText(_T("���ڴ�������ݿ��ж��������ݣ������ĵȴ�����"));
	CString _str = m_list_IncompleteOrder;
	m_list_IncompleteOrder.Empty();
	if(_str.IsEmpty())
	{
		m_tip.SetWindowText(_T("û������"));
		CString temp = _T("û�ж�����Ч�����ݣ�ԭ������У�\r\n");
		temp += _T("1:���ݿ���û��δ��ɵĶ������ݣ�\r\n");
		temp += _T("2:���ݿ��л�û�ж������ݣ�\r\n");
		temp += _T("3:���ȷ����δ��ɵĶ�������ô�����ݿ��ж�ȡ��������ʧ�ܣ������Ի���ϵ����Ա��\r\n");
		MessageBox(temp);
	}else
	{
		CStringArray _str_arr;
		_str_arr.RemoveAll();
		TransferStrToArr(_str,_str_arr);
		if(_str_arr.IsEmpty())
		{
			m_tip.SetWindowText(_T("û������"));
			CString temp = _T("û�ж�����Ч�����ݣ�ԭ������У�\r\n");
			temp += _T("1:���ݿ���û��δ��ɵĶ������ݣ�\r\n");
			temp += _T("2:���ݿ��л�û�ж������ݣ�\r\n");
			temp += _T("3:���ȷ����δ��ɵĶ�������ô�����ݿ��ж�ȡ��������ʧ�ܣ������Ի���ϵ����Ա��\r\n");
			MessageBox(temp);
		}else{
			int size = _str_arr.GetSize();
			m_list.DeleteAllItems();
			for(int i = 0;i<size;i++)
			{
				m_list.InsertItem(i,_T(""));//�����µ�һ��
				CString _str = _str_arr.GetAt(i);
				for(int j = 0;j<13;j++)
				{
					m_list.SetItemText(i,j,GetItemFromArray(_str,j+1));
				}
			}
			int _count = m_list.GetItemCount();
			CString _str_message;
			_str_message.Format(_T("������%d��δ��ɶ�����¼"),_count);
			m_tip.SetWindowText(_str_message);
		}
	}
}


void COrderIncompletedProgView::TransferStrToArr(CString source,CStringArray &des)    //���ַ����⿪  ���array��ʽ������
{
	CString strSource = source;
	des.RemoveAll();
	CString sub_str_start = _T("{#");
	CString sub_str_end = _T("#}");
	CString temp = NULL;
	while(TRUE)
	{
		int index = strSource.Find(sub_str_start);
		if(-1 == index)   //��ʾû�ҵ� ��ζ�� ������
		{
			break;
		}else{
			strSource = strSource.Mid(index+2);
			index = strSource.Find(sub_str_end);
			temp = strSource.Mid(0,index);
			des.Add(temp);
			temp.Empty();
			strSource = strSource.Mid(index+2);
		}
	}
}

CString COrderIncompletedProgView::GetItemFromArray(CString source,int index)     //���ַ�����ȡ����������
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

void COrderIncompletedProgView::OnBnClickedBtnFindDealIncomplete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSock::FindDealIncomplete(this);
}


afx_msg LRESULT COrderIncompletedProgView::OnFillList(WPARAM wParam, LPARAM lParam)
{
	FillDataToList();
	return 0;
}


void COrderIncompletedProgView::OnBnClickedBtnSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_OrderToUpdateArr.RemoveAll();

	int count = m_list.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		CString temp;
		temp.Format(_T("�ύʧ�ܣ���%d�е����ݲ����Ϲ淶�������¼���ٴ��ύ��"),i+1);
		if(m_list.GetCheck(i))
		{
			if(!CSock::IsItemValidity(m_list.GetItemText(i,0),_T("�������"),TRUE,TRUE,FALSE,20))
			{
				MessageBox(temp);
				return;
			}
			if(!CSock::IsItemValidity(m_list.GetItemText(i,1),_T("��������"),TRUE,FALSE,FALSE,20))
			{
				MessageBox(temp);
				return;
			}else{
				if(!IsOrderProgVality(m_list.GetItemText(i,1)))
				{
					MessageBox(temp);
					return;
				}
			}
			if(!CSock::IsItemValidity(m_list.GetItemText(i,2),_T("��һ������"),FALSE,FALSE,FALSE,150))
			{
				MessageBox(temp);
				return;
			}
			if(!CSock::IsItemValidity(m_list.GetItemText(i,3),_T("��һ������Ԥ���ʱ��"),FALSE,FALSE,TRUE,20))
			{
				MessageBox(temp);
				return;
			}
			if(!CSock::IsItemValidity(m_list.GetItemText(i,4),_T("�����ܼ�"),FALSE,TRUE,FALSE,20))
			{
				MessageBox(temp);
				return;
			}
			if(!CSock::IsItemValidity(m_list.GetItemText(i,5),_T("���ս��"),FALSE,TRUE,FALSE,20))
			{
				MessageBox(temp);
				return;
			}
			if(!CSock::IsItemValidity(m_list.GetItemText(i,6),_T("�ͻ�����"),FALSE,FALSE,FALSE,20))
			{
				MessageBox(temp);
				return;
			}
			if(!CSock::IsItemValidity(m_list.GetItemText(i,7),_T("�˿�����"),FALSE,FALSE,FALSE,20))
			{
				MessageBox(temp);
				return;
			}
			if(!CSock::IsItemValidity(m_list.GetItemText(i,8),_T("�˿͵绰"),FALSE,TRUE,FALSE,20))
			{
				MessageBox(temp);
				return;
			}
			if(!CSock::IsItemValidity(m_list.GetItemText(i,9),_T("�˿͵�ַ"),FALSE,FALSE,FALSE,50))
			{
				MessageBox(temp);
				return;
			}
			if(!CSock::IsItemValidity(m_list.GetItemText(i,10),_T("����������"),FALSE,FALSE,FALSE,20))
			{
				MessageBox(temp);
				return;
			}
			if(!CSock::IsItemValidity(m_list.GetItemText(i,11),_T("�����˵绰"),FALSE,TRUE,FALSE,20))
			{
				MessageBox(temp);
				return;
			}
			if(!CSock::IsItemValidity(m_list.GetItemText(i,12),_T("��ע"),FALSE,FALSE,FALSE,200))
			{
				MessageBox(temp);
				return;

			}
			
			CString strTemp;
			strTemp.Format(_T("%d"),i);
			m_OrderToUpdateArr.Add(strTemp);
		}
	}
	if(m_OrderToUpdateArr.GetSize() == 0)
	{
		MessageBox(_T("�ύʧ�ܣ�û��ѡ����Ч������"));
	}else{
		CSock::StartUpdateOrderIncomplete(this);
	}
}


BOOL COrderIncompletedProgView::IsOrderProgVality(CString source)    //У������Ķ��������Ƿ�Ϸ�
{
	if(source == _T("����ͻ�")
		|| source == _T("�Ѷ���")
		|| source == _T("�ѳ���")
		|| source == _T("��ǩ��ͬ")
		|| source == _T("��ȷ�����շ���")
		|| source == _T("�ѷ�������")
		|| source == _T("�ѷ���")
		|| source == _T("�ѻص�")
		|| source == _T("�Ѱ�װ")
		|| source == _T("�����"))
	{
		return TRUE;
	}else{
		CString str = _T("�������ȱ���Ϊ����֮һ��\r\n");
		str += _T("1:����ͻ�\r\n");
		str += _T("2:�Ѷ���\r\n");
		str += _T("3:�ѳ���\r\n");
		str += _T("4:��ǩ��ͬ\r\n");
		str += _T("5:��ȷ�����շ���\r\n");
		str += _T("6:�ѷ�������\r\n");
		str += _T("7:�ѷ���\r\n");
		str += _T("8:�ѻص�\r\n");
		str += _T("9:�Ѱ�װ\r\n");
		str += _T("10:�����\r\n");
		MessageBox(str);
		return FALSE;
	}
}

void COrderIncompletedProgView::OnChooseAll()
{
	// TODO: �ڴ���������������
	int count = m_list.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		m_list.SetCheck(i,TRUE);
	}
}


void COrderIncompletedProgView::OnReverseChoose()
{
	// TODO: �ڴ���������������
	int count = m_list.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		if(m_list.GetCheck(i))
		{
			m_list.SetCheck(i,FALSE);
		}else{
			m_list.SetCheck(i,TRUE);
		}
		
	}
}


void COrderIncompletedProgView::OnChooseNone()
{
	// TODO: �ڴ���������������
	int count = m_list.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		m_list.SetCheck(i,FALSE);
	}
}


void COrderIncompletedProgView::OnDelFromList()
{
	// TODO: �ڴ���������������
	CStringArray arr;
	arr.RemoveAll();
	int count = m_list.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		if(m_list.GetCheck(i))
		{
			arr.Add(m_list.GetItemText(i,0));
		}
	}

	int size = arr.GetSize();
	for(int i = 0;i<size;i++)
	{
		int cur_count = m_list.GetItemCount();
		for(int j= 0;j<cur_count;j++)
		{
			if(m_list.GetItemText(j,0) == arr.GetAt(i))
			{
				m_list.DeleteItem(j);
				break;
			}
		}
	}
}


void COrderIncompletedProgView::OnClearList()
{
	// TODO: �ڴ���������������
	m_list.DeleteAllItems();
}
