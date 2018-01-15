// SysPostion.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "SysPostion.h"
#include "afxdialogex.h"
#include "PosAdd.h"
#include "PosEdit.h"


// CSysPostion �Ի���

IMPLEMENT_DYNAMIC(CSysPostion, CDialogEx)

CSysPostion::CSysPostion(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSysPostion::IDD, pParent)
{

}

CSysPostion::~CSysPostion()
{
}

void CSysPostion::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SYSPOSTION, m_list);
	DDX_Control(pDX, IDC_SPLIT, m_split);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
}

BEGIN_MESSAGE_MAP(CSysPostion, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD, &CSysPostion::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT, &CSysPostion::OnBnClickedBtnEdit)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_MESSAGE(WM_ENDTASK_SysPostion, &CSysPostion::OnEndTask)
	ON_MESSAGE(WM_STARTTASK_SysPostion, &CSysPostion::OnStartTask)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_FIND_ALL, &CSysPostion::OnBnClickedBtnFindAll)
	ON_COMMAND(ID_CHOOSE_ALL, &CSysPostion::OnChooseAll)
	ON_COMMAND(ID_CHOOSE_NONE, &CSysPostion::OnChooseNone)
	ON_COMMAND(ID_REVERSE_CHOOSE, &CSysPostion::OnReverseChoose)
	ON_COMMAND(ID_DEL_ALLL, &CSysPostion::OnDelAlll)
	ON_COMMAND(ID_DEL_FROM_LIST, &CSysPostion::OnDelFromList)
	ON_MESSAGE(WM_FILLLIST_SysPostion, &CSysPostion::OnFillList)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CSysPostion::OnBnClickedBtnDelete)
	ON_MESSAGE(WM_DEL_USERS_SysPostion, &CSysPostion::OnDelUsers)
END_MESSAGE_MAP()


// CSysPostion ��Ϣ�������

HBRUSH CSysPostion::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CSysPostion::InitList() 
{
	m_list.SetBkColor(CONCTRLBKCOLOR);
	m_list.SetExtendedStyle( m_list.GetExtendedStyle()| LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.SetTextColor(RGB(139, 90, 43));
	m_list.SetTextBkColor(RGB(255, 236, 139));
	CRect rect;
	m_list.GetClientRect(&rect);

	m_list.InsertColumn(0, _T("��ɫ���"), LVCFMT_LEFT, rect.Width()/3);    
    m_list.InsertColumn(1, _T("��ɫ����"), LVCFMT_LEFT, rect.Width()/3);
	m_list.InsertColumn(2, _T("Ա������"), LVCFMT_LEFT, rect.Width()/3);
}


BOOL CSysPostion::OnInitDialog() 
{
	CDialogEx::OnInitDialog();
	InitList();
	InitTipCtrl();
	InitSplit();
	return TRUE;
}

void CSysPostion::InitSplit()
{
	m_split.SetDropDownMenu(IDM_SYSPOSTION_MG,0);
}

void CSysPostion::InitTipCtrl()
{
	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	font.Detach();
}

void CSysPostion::OnBnClickedBtnAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPosAdd posAdd;
	posAdd.DoModal();
}


void CSysPostion::OnBnClickedBtnEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	WT;
	CString temp;
	CString username = NULL; //�������
	CString user_no = NULL;
	CString pos_name = NULL;
	int count = 0;
	for(int i=0; i<m_list.GetItemCount(); i++)
	{
		if(m_list.GetCheck(i))
		{	
			count++ ;
			if(count > 1)  //��ʾ�ж��ѡ����
			{
				CString str;
				str.Format(_T("��ǰ�ж��ѡ���Ĭ�Ͻ��༭��һ��ѡ������û���Ϊ��%s��ȷ�ϼ�����"),username);
				if(IDYES == MessageBox(str,_T("��ʾ"),MB_YESNO)){
					break;
				}else
				{
					return;
				}
			}
			user_no = m_list.GetItemText(i,0);
			username = m_list.GetItemText(i,2);
			pos_name = m_list.GetItemText(i,1);
		}
	}
	if(username.IsEmpty())
	{
		MessageBox(_T("��ǰû��ѡ���������ѡ��һ���û����б༭"));
		return;
	}

	CPosEdit dlg;
	dlg.m_str_pos_name = pos_name;
	dlg.m_emp_num = user_no;
	dlg.m_emp_name = username;
	dlg.DoModal();
}

void CSysPostion::OnTimer(UINT_PTR nIDEvent)
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

void CSysPostion::ShowTip()
{
	m_time_take++;
	CString time =NULL;
	time.Format(_T("��ʱ��%d��"),m_time_take);
	m_tip.SetWindowText(time);
	if(m_time_take == 30)
	{
		OnEndTask(0,0);
		m_tip.SetWindowText(_T("����ʱ�������Ի����������ӷ�����"));
	}
}

afx_msg LRESULT CSysPostion::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CSysPostion::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


void CSysPostion::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CSock::m_pSysPostion = NULL;
	CDialogEx::OnClose();
}


void CSysPostion::OnBnClickedBtnFindAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_content_to_find = _T("{#[#����ȫ��#]#}");
	m_pos_batch.Empty();
	CSock::StartFindAllUser(this);
}


void CSysPostion::OnChooseAll()
{
	// TODO: �ڴ���������������
	int count = m_list.GetItemCount();
	for (int i = 0;i<count;i++)
	{	
		m_list.SetCheck(i,TRUE);
	}
}


void CSysPostion::OnChooseNone()
{
	// TODO: �ڴ���������������
	int count = m_list.GetItemCount();
	for (int i = 0;i<count;i++)
	{	
		m_list.SetCheck(i,FALSE);
	}
}


void CSysPostion::OnReverseChoose()
{
	// TODO: �ڴ���������������
	int count = m_list.GetItemCount();
	for (int i = 0;i<count;i++)
	{
		if(m_list.GetCheck(i))
		{
			m_list.SetCheck(i,FALSE);
		}else{
			m_list.SetCheck(i,TRUE);
		}
	}
}


void CSysPostion::OnDelAlll()
{
	// TODO: �ڴ���������������
	m_list.DeleteAllItems();
}


void CSysPostion::OnDelFromList()
{
	// TODO: �ڴ���������������
	CStringArray arr;
	arr.RemoveAll();
	int count = m_list.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		if(m_list.GetCheck(i))
		{
			arr.Add(m_list.GetItemText(i,1));
		}
	}

	int size = arr.GetSize();
	for(int i = 0;i<size;i++)
	{
		int cur_count = m_list.GetItemCount();
		for(int j= 0;j<cur_count;j++)
		{
			if(m_list.GetItemText(j,1) == arr.GetAt(i))
			{
				m_list.DeleteItem(j);
				break;
			}
		}
	}
}


void CSysPostion::FillDataToList()
{
	m_tip.SetWindowText(_T("���ڴ�������ݿ��ж��������ݣ������ĵȴ�����"));
	CString _str = m_pos_batch;
	m_pos_batch.Empty();
	if(_str.IsEmpty())
	{
		m_tip.SetWindowText(_T("û������"));
		CString temp = _T("û�ж�����Ч�����ݣ�ԭ������У�\r\n");
		temp += _T("1:���ݿ���û���û����ݣ�\r\n");
		temp += _T("2:���ȷ�����û����ݣ���ô�����ݿ��ж�ȡ�û�����ʧ�ܣ������Ի���ϵ����Ա��\r\n");
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
			temp += _T("1:���ݿ���û���û����ݣ�\r\n");
			temp += _T("2:���ȷ�����û����ݣ���ô�����ݿ��ж�ȡ�û�����ʧ�ܣ������Ի���ϵ����Ա��\r\n");
			MessageBox(temp);
		}else{
			int size = _str_arr.GetSize();
			m_list.DeleteAllItems();
			for(int i = 0;i<size;i++)
			{
				m_list.InsertItem(i,_T(""));//�����µ�һ��
				CString _str = _str_arr.GetAt(i);
				for(int j = 0;j<3;j++)
				{
					m_list.SetItemText(i,j,GetItemFromArray(_str,j+1));
				}
			}
			int _count = m_list.GetItemCount();
			CString _str_message;
			_str_message.Format(_T("������%d����¼"),_count);
			m_tip.SetWindowText(_str_message);
		}
	}
}


void CSysPostion::TransferStrToArr(CString source,CStringArray &des)    //���ַ����⿪  ���array��ʽ������
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



afx_msg LRESULT CSysPostion::OnFillList(WPARAM wParam, LPARAM lParam)
{
	FillDataToList();
	return 0;
}


void CSysPostion::OnBnClickedBtnDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	int count = 0;
	CString num;
	CString  lineToDelete = _T("��Ҫ��ɾ�����û����û����ǣ�");
	m_users_to_delete.Empty();
	CStringArray _users_arr;
	_users_arr.RemoveAll();
	int total = m_list.GetItemCount();
	for(int i=0; i< total; i++)
	{
		if(m_list.GetCheck(i))
		{	
			_users_arr.Add(m_list.GetItemText(i,2));
		}
	}
	count = _users_arr.GetSize();
	if(count == 0)
	{
		MessageBox(_T("��������ѡ��һ��Ҫɾ���Ķ���Ȼ�����ɾ��"));
		return;
	}else{   //��ѡ����
		CString total;
		total.Format(_T("����%d��ѡ���"),count);
		CString users_to_del;
		FormatDataByAddComma(_users_arr,users_to_del);
		lineToDelete +=  users_to_del + _T("ȷ��Ҫɾ����");
		if(IDYES == MessageBox(total+lineToDelete,_T("����"),MB_YESNO))
		{
			PackageData(_users_arr,m_users_to_delete);
			CSock::StartDelUsers(this);
		}else{
			return;
		}
	}
}


void CSysPostion::FormatDataByAddComma(CStringArray &_data_source_arr,CString &_result)
{
	_result.Empty();
	int size = _data_source_arr.GetSize();
	for(int i = 0;i<size;i++)
	{
		_result += _data_source_arr.GetAt(i);
		_result += _T("��");
	}
}

void CSysPostion::PackageData(CStringArray &_data_source_arr,CString &_result)
{
	CString _data_start = _T("{#[#");
	CString _data_mid = _T("#][#");
	CString _data_end = _T("#]#}");
	int size = _data_source_arr.GetSize();
	for(int i = 0;i<size;i++)
	{
		if(i == 0)
		{
			_result += _data_start;
			CString temp ;
			temp.Format(_T("%d"),size);
			_result += temp;
			_result += _data_mid;
			_result += _data_source_arr.GetAt(i);
			if((i+1) == size)    //Ҳ����ֻ��һ��ɾ����
			{
				_result += _data_end;
			}else{
				_result += _data_mid;
			}
		}else if(i == (size-1))
		{
			_result += _data_source_arr.GetAt(i);
			_result += _data_end;
		}else{
			_result += _data_source_arr.GetAt(i);
			_result += _data_mid;
		}
	}
}

afx_msg LRESULT CSysPostion::OnDelUsers(WPARAM wParam, LPARAM lParam)
{
	DelUsersFromList();
	return 0;
}


void CSysPostion::DelUsersFromList()
{
	WT;
	CString _str = m_users_to_delete;
	CString _data_start = _T("{#");
	CString _data_end = _T("#}");
	int index = _str.Find(_data_start);
	_str = _str.Mid(index+2);
	index = _str.Find(_data_end);
	_str = _str.Mid(0,index);
	int size = atoi(T2A(GetItemFromArray(_str,1)));
	for(int i = 0;i<size;i++)
	{
		int count = m_list.GetItemCount();
		for(int j = 0;j<count;j++)
		{
			CString temp1 = GetItemFromArray(_str,i+2);
			CString temp2 = m_list.GetItemText(j,2);
			if(temp1 == temp2)
			{
				m_list.DeleteItem(j);
				break;
			}
		}
	}
}

CString CSysPostion::GetItemFromArray(CString source,int index)     //���ַ�����ȡ����������
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