// CustomInfoExProp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "CustomInfoExProp.h"
#include "afxdialogex.h"
#include "DataExportPropSheet.h"

// CCustomInfoExProp �Ի���

IMPLEMENT_DYNAMIC(CCustomInfoExProp, CPropertyPage)

CCustomInfoExProp::CCustomInfoExProp()
	: CPropertyPage(CCustomInfoExProp::IDD)
{

}

CCustomInfoExProp::~CCustomInfoExProp()
{
}

void CCustomInfoExProp::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CTMINFO, m_list);
	DDX_Control(pDX, IDC_SPLIT_OPERATION, m_split);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
}



BEGIN_MESSAGE_MAP(CCustomInfoExProp, CPropertyPage)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_MESSAGE(WM_STARTTASK_CustomExProp, &CCustomInfoExProp::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_CustomExProp, &CCustomInfoExProp::OnEndTask)
	ON_COMMAND(ID_CHOOSE_ALLL, &CCustomInfoExProp::OnChooseAlll)
	ON_COMMAND(ID_CHOOSE_NONE, &CCustomInfoExProp::OnChooseNone)
	ON_COMMAND(ID_REVERSE_CHOOSE, &CCustomInfoExProp::OnReverseChoose)
	ON_COMMAND(ID_DEL_FROM_LIST, &CCustomInfoExProp::OnDelFromList)
	ON_COMMAND(ID_CLEAR_LIST, &CCustomInfoExProp::OnClearList)
	ON_BN_CLICKED(IDC_BTN_FIND_ALLCTM, &CCustomInfoExProp::OnBnClickedBtnFindAllctm)
	ON_MESSAGE(WM_HANDLE_BATCH_CTM_CtmEx, &CCustomInfoExProp::OnHandleBatchCtm)
	ON_BN_CLICKED(IDC_BTN_DATAEXPORT, &CCustomInfoExProp::OnBnClickedBtnDataExport)
END_MESSAGE_MAP()


// CCustomInfoExProp ��Ϣ�������


HBRUSH CCustomInfoExProp::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

BOOL CCustomInfoExProp::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	InitList();
	InitSplit();
	InitTipCtrl();
	return TRUE;
}

void CCustomInfoExProp::InitTipCtrl()
{
	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	font.Detach();
}

void CCustomInfoExProp::InitList()
{
	m_list.SetBkColor(CONCTRLBKCOLOR);
	m_list.SetExtendedStyle( m_list.GetExtendedStyle()| LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.SetTextColor(RGB(139, 90, 43));
	m_list.SetTextBkColor(RGB(255, 236, 139));
	
	m_list.InsertColumn(0, _T("�ͻ����"), LVCFMT_LEFT, 100);    
    m_list.InsertColumn(1, _T("�ͻ�����"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(2, _T("�˿�����"), LVCFMT_LEFT, 100);
    m_list.InsertColumn(3, _T("�Ա�"), LVCFMT_LEFT, 150);
	m_list.InsertColumn(4, _T("�绰"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(5, _T("����"), LVCFMT_LEFT, 100);    
    m_list.InsertColumn(6, _T("���"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(7, _T("�״���������"), LVCFMT_LEFT, 100);
    m_list.InsertColumn(8, _T("�����������"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(9, _T("��ע"), LVCFMT_LEFT, 100);

}

void CCustomInfoExProp::InitSplit()
{
	m_split.SetDropDownMenu(IDM_CTM_EX_OPERATION,0);

}

void CCustomInfoExProp::ShowTip()
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

void CCustomInfoExProp::OnTimer(UINT_PTR nIDEvent)
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

void CCustomInfoExProp::EnableParentDlgShutDownBtn(BOOL Enable)
{
	CDataExportPropSheet * p_parentDlg = (CDataExportPropSheet *)GetParent();
	//TRUE��ʾ���� FALSE��ʾ������   
	p_parentDlg->SetCloseBtnEable(Enable);
}

afx_msg LRESULT CCustomInfoExProp::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	EnableParentDlgShutDownBtn(FALSE);
	//SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CCustomInfoExProp::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	EnableParentDlgShutDownBtn(TRUE);
	//KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}

void CCustomInfoExProp::TransferStrToArr(CString source,CStringArray &des)    //���ַ����⿪  ���array��ʽ������
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

CString CCustomInfoExProp::GetItemFromArray(CString source,int index)     //���ַ�����ȡ����������
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


void CCustomInfoExProp::OnChooseAlll()
{
	// TODO: �ڴ���������������
	int count = m_list.GetItemCount();
	for (int i = 0;i<count;i++)
	{
		m_list.SetCheck(i,TRUE);
		
	}
}


void CCustomInfoExProp::OnChooseNone()
{
	// TODO: �ڴ���������������
	int count = m_list.GetItemCount();
	for (int i = 0;i<count;i++)
	{
		m_list.SetCheck(i,FALSE);
		
	}
}


void CCustomInfoExProp::OnReverseChoose()
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


void CCustomInfoExProp::OnDelFromList()
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


void CCustomInfoExProp::OnClearList()
{
	// TODO: �ڴ���������������
	m_list.DeleteAllItems();
}


void CCustomInfoExProp::OnBnClickedBtnFindAllctm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSock::StartFindCtmForEx(this);
}


afx_msg LRESULT CCustomInfoExProp::OnHandleBatchCtm(WPARAM wParam, LPARAM lParam)
{
	FillDataToList();

	return 0;
}

void CCustomInfoExProp::FillDataToList()
{
	m_tip.SetWindowText(_T("���ڴ�������ݿ��ж��������ݣ������ĵȴ�����"));
	CString _str = m_ctm_batch_from_db;
	m_ctm_batch_from_db.Empty();
	if(_str.IsEmpty())
	{
		m_tip.SetWindowText(_T("û������"));
		CString temp = _T("û�ж�����Ч�����ݣ�ԭ������У�");
		temp += _T("\r\n1:���ݿ���û�пͻ����ݣ�");
		temp += _T("\r\n2:�����ݿ��ж�ȡ�ͻ�����ʧ�ܣ������Ի���ϵ����Ա��\r\n");
		MessageBox(temp);
	}else
	{
		CStringArray _str_arr;
		_str_arr.RemoveAll();
		TransferStrToArr(_str,_str_arr);
		if(_str_arr.IsEmpty())
		{
			m_tip.SetWindowText(_T("û������"));
			CString temp = _T("û�ж�����Ч�����ݣ�ԭ������У�");
			temp += _T("\r\n1:���ݿ���û�пͻ����ݣ�");
			temp += _T("\r\n2:�����ݿ��ж�ȡ�ͻ�����ʧ�ܣ������Ի���ϵ����Ա��\r\n");
			MessageBox(temp);
		}else{
			int size = _str_arr.GetSize();
			m_list.DeleteAllItems();
			for(int i = 0;i<size;i++)
			{
				m_list.InsertItem(i,_T(""));//�����µ�һ��
				CString  _str = _str_arr.GetAt(i);
				for(int j = 0;j<10;j++)
				{
					m_list.SetItemText(i,j,GetItemFromArray(_str,j+1));
				}
			}
			int _count = m_list.GetItemCount();
			CString _str_message;
			_str_message.Format(_T("����ѯ��%d���ͻ���¼"),_count);
			m_tip.SetWindowText(_str_message);
		}
	}
}

void CCustomInfoExProp::OnBnClickedBtnDataExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	WT;
	CStringArray empArr;
	empArr.RemoveAll();
	for(int i=0; i<m_list.GetItemCount(); i++)
	{
		if(m_list.GetCheck(i))
		{	
			CString num = NULL;
			num	= m_list.GetItemText(i,0);
			if(!num.IsEmpty())
			{
				CString _strTemp;
				_strTemp.Format(_T("%d"),i);
				empArr.Add(_strTemp);
			}
		}
	}
	int size = empArr.GetSize();
	if(size == 0)
	{
		MessageBox(_T("��ǰû��Ҫ�����Ŀͻ����ݣ���ѡ����Ч�Ŀͻ�����"));
		return;
	}
	if(IDYES == MessageBox(_T("�����½�һ���ձ���Ҫ���κβ������½�����رձ����������Ѿ���һ���ձ��ȷ�Ϻ��ټ���"),_T("��ܰ��ʾ"),MB_YESNO))
	{
		//CFileDialog fileDlg(FALSE, _T("xls"), _T("Ա����Ϣ��"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL,NULL );
		CFileDialog fileDlg(TRUE);
		fileDlg.m_ofn.lpstrTitle = _T("��ѡ��һ���ձ��");
		fileDlg.m_ofn.lpstrFilter = _T("Excel 2003(*.xls)\0*.xls\0Excel 2007(*.xlsx)\0*.xlsx\0\0");
		fileDlg.m_ofn.lpstrDefExt = _T("xls");
		//fileDlg.m_ofn.lpstrFile = _T("Ա����Ϣ��");
		if(IDOK == fileDlg.DoModal())
		{
			//CFile file(fileDlg.GetPathName(),CFile::modeCreate | CFile::modeReadWrite);
			//file.Close();
			CString pathName = fileDlg.GetPathName();
			CString fileExt = fileDlg.GetFileExt();
			CADOExcel ado;
			ado.SetFileType(fileExt);
			ado.SetExcelFilePath(pathName);
			CFileFind find;
			BOOL  flag = find.FindFile(pathName);
			if(!flag)
			{
				AfxMessageBox(_T("���ļ�������"));
				return ;
			}
			if(!ado.OnInitConnect())
			{
				CString err;
				err = _T("�������ԭ��:\r\n");
				err += _T("1����ȷ���Ѿ���װ�����ݿ�����\r\n");
				err += _T("2���ļ�δ�رգ��볢���ȹر��ļ����ٵ������ϣ�\r\n");
				err += _T("3����������ɹ�������ϵ����Ա��\r\n");
				MessageBox(err);
				return;
			}

			try
			{
				CString sql = _T("select * from [�ͻ���Ϣ��$]");
				_bstr_t bstrSQL = (_bstr_t)sql;

				if(ado.m_pConnection==NULL)
				{
					ado.OnInitConnect();
				}
				ado.m_pRecordset.CreateInstance(_uuidof(Recordset));
				ado.m_pRecordset->Open(bstrSQL,ado.m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			}
			catch(_com_error e)
			{
				CString creatTable;
				creatTable = _T("CREATE TABLE �ͻ���Ϣ��(�ͻ���� char(50), �˿����� char(50),�ͻ����� char(50),�ͻ��Ա� char(10),�ƶ��绰 char(20),���Ѵ��� char(20),���ѽ�� char(20),�״�����ʱ�� char(30),�������ʱ�� char(30),��ע char(250));");
				
				if(!ado.ExecuteSQL(creatTable))
				{
					MessageBox(_T("�����ͻ���Ϣ���ʧ��"));
					ado.ExitConnect();
					return;
				}
			}
			CString sql = _T("select * from [�ͻ���Ϣ��$]");
			ado.m_pRecordset = ado.GetRecordSet(sql);
			if(ado.m_pRecordset == NULL)
			{
				MessageBox(_T("��ȡ�ͻ���Ϣ���ʧ��"));
				ado.ExitConnect();
				return;
			}
			CString _sql = NULL;
			for(int i = 0; i< size;i++)
			{
				int index = atoi(T2A(empArr.GetAt(i)));
				CString ctm_num = m_list.GetItemText(index,0);
				CString ctm_name = m_list.GetItemText(index,1);
				CString ctm_call = m_list.GetItemText(index,2);
				CString ctm_sex = m_list.GetItemText(index,3);
				CString ctm_phone = m_list.GetItemText(index,4);
				CString ctm_pay_time = m_list.GetItemText(index,5);
				CString ctm_pay_total = m_list.GetItemText(index,6);
				CString ctm_time_first_pay = m_list.GetItemText(index,7);
				CString ctm_time_late_pay = m_list.GetItemText(index,8);
				CString ctm_ps = m_list.GetItemText(index,9);
				/*
				CString temp;
				temp.Format(_T("INSERT INTO [�ͻ���Ϣ��$](�ͻ����, �˿�����,�ͻ�����,�ͻ��Ա�,�ƶ��绰,���Ѵ���,���ѽ��,�״�����ʱ��,�������ʱ��,��ע)VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s');"),
					ctm_num,
					ctm_name,
					ctm_call,
					ctm_sex,
					ctm_phone,
					ctm_pay_time,
					ctm_pay_total,
					ctm_time_first_pay,
					ctm_time_late_pay,
					ctm_ps);
				_sql += temp;
				*/
				try{
					ado.m_pRecordset->AddNew();
					ado.m_pRecordset->PutCollect("�ͻ����",(const _variant_t)ctm_num);
					ado.m_pRecordset->PutCollect("�˿�����",(const _variant_t)ctm_name);
					ado.m_pRecordset->PutCollect("�ͻ�����",(const _variant_t)ctm_call);
					ado.m_pRecordset->PutCollect("�ͻ��Ա�",(const _variant_t)ctm_sex);
					ado.m_pRecordset->PutCollect("�ƶ��绰",(const _variant_t)ctm_phone);
					ado.m_pRecordset->PutCollect("���Ѵ���",(const _variant_t)ctm_pay_time);	
					ado.m_pRecordset->PutCollect("���ѽ��",(const _variant_t)ctm_pay_total);
					ado.m_pRecordset->PutCollect("�״�����ʱ��",(const _variant_t)ctm_time_first_pay);
					ado.m_pRecordset->PutCollect("�������ʱ��",(const _variant_t)ctm_time_late_pay);
					ado.m_pRecordset->PutCollect("��ע",(const _variant_t)ctm_ps);		
					ado.m_pRecordset->Update();
				}catch(_com_error e)
				{
					CString erro;
					erro.Format(_T("����Ա����¼��ʧ�ܣ�������Ϣ�ǣ�%s�����������ǣ�%s"),e.ErrorMessage(),(LPCTSTR)e.Description());
					MessageBox(erro);
					ado.ExitConnect();
					return;
				}
				
			}
			/*
			if(!ado.ExecuteSQL(_sql))
			{
				MessageBox(_T("��������ʧ�ܣ�����ղ�������"));
				return;
			}*/
			ado.ExitConnect();
			m_tip.SetWindowText(_T("����Ա�����ݳɹ�"));
		}else
		{
			return ;
		}
	}else
	{
		return;
	}
}
