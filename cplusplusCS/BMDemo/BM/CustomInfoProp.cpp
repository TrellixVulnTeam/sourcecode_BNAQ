// CustomInfoProp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "CustomInfoProp.h"
#include "afxdialogex.h"
#include "DataImportPropSheet.h"

// CCustomInfoProp �Ի���

IMPLEMENT_DYNAMIC(CCustomInfoProp, CPropertyPage)

CCustomInfoProp::CCustomInfoProp()
	: CPropertyPage(CCustomInfoProp::IDD)
{

}

CCustomInfoProp::~CCustomInfoProp()
{
}

void CCustomInfoProp::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_SPLIT_OPERATION, m_split);
	DDX_Control(pDX, IDC_SPLIT_OPERATION, m_spOperation);
	DDX_Control(pDX, IDC_LIST_CTMINFO, m_ctmInfoList);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
}


BEGIN_MESSAGE_MAP(CCustomInfoProp, CPropertyPage)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CTMINFO, &CCustomInfoProp::OnLvnItemchangedListCtminfo)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_CHOOSE_ALL, &CCustomInfoProp::OnChooseAll)
	ON_COMMAND(ID_CHOOSE_NONE, &CCustomInfoProp::OnChooseNone)
	ON_COMMAND(ID_REVERSE_CHOOSE, &CCustomInfoProp::OnReverseChoose)
	ON_COMMAND(ID_DEL_FROM_LIST, &CCustomInfoProp::OnDelFromList)
	ON_COMMAND(ID_CLEAR_LIST, &CCustomInfoProp::OnClearList)
	ON_BN_CLICKED(IDC_BTN_DATAIMPORT, &CCustomInfoProp::OnBnClickedBtnDataImport)
	ON_WM_TIMER()
	ON_MESSAGE(WM_STARTTASK_CtmIm, &CCustomInfoProp::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_CtmIM, &CCustomInfoProp::OnEndTask)
	ON_BN_CLICKED(IDC_BTN_SUBMIT, &CCustomInfoProp::OnBnClickedBtnSubmit)
END_MESSAGE_MAP()



// CCustomInfoProp ��Ϣ�������

HBRUSH CCustomInfoProp::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

BOOL CCustomInfoProp::OnInitDialog()
{
	    
    //m_ctmInfoList.GetClientRect(&rect); 
	CPropertyPage::OnInitDialog();
	InitList();
	SetSplitCtrl();
	InitTipCtrl();
	return TRUE;
}

void CCustomInfoProp::InitList(){
	//DWORD listStyle = m_ctmInfoList.GetExtendedStyle();
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ���� 
	m_ctmInfoList.SetBkColor(CONCTRLBKCOLOR);
	m_ctmInfoList.SetExtendedStyle( m_ctmInfoList.GetExtendedStyle()| LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctmInfoList.SetTextColor(RGB(139, 90, 43));
	m_ctmInfoList.SetTextBkColor(RGB(255, 236, 139));
	
	m_ctmInfoList.InsertColumn(0, _T("�ͻ����"), LVCFMT_LEFT, 75);    
    m_ctmInfoList.InsertColumn(1, _T("�ͻ�����"), LVCFMT_LEFT, 75);
	m_ctmInfoList.InsertColumn(2, _T("�˿�����"), LVCFMT_LEFT, 75);
    m_ctmInfoList.InsertColumn(3, _T("�Ա�"), LVCFMT_LEFT, 50);
	m_ctmInfoList.InsertColumn(4, _T("�绰"), LVCFMT_LEFT, 100);
	m_ctmInfoList.InsertColumn(5, _T("����"), LVCFMT_LEFT, 50);    
    m_ctmInfoList.InsertColumn(6, _T("���"), LVCFMT_LEFT, 100);
	m_ctmInfoList.InsertColumn(7, _T("�״���������"), LVCFMT_LEFT, 100);
    m_ctmInfoList.InsertColumn(8, _T("�����������"), LVCFMT_LEFT, 100);
	m_ctmInfoList.InsertColumn(9, _T("��ע"), LVCFMT_LEFT, 300);
}

void CCustomInfoProp::SetSplitCtrl() {
	m_spOperation.SetDropDownMenu(IDM_CTM_IM_OPERATION,0);
}

void CCustomInfoProp::OnChooseAll()
{
	// TODO: �ڴ���������������
	int count = m_ctmInfoList.GetItemCount();
	for(int i=0;i<count;i++)
	{
		m_ctmInfoList.SetCheck(i,TRUE);
	}
}


void CCustomInfoProp::OnChooseNone()
{
	// TODO: �ڴ���������������
	int count = m_ctmInfoList.GetItemCount();
	for(int i=0;i<count;i++)
	{
		m_ctmInfoList.SetCheck(i,FALSE);
	}
}


void CCustomInfoProp::OnReverseChoose()
{
	// TODO: �ڴ���������������
	int count = m_ctmInfoList.GetItemCount();
	for(int i=0;i<count;i++)
	{
		if(m_ctmInfoList.GetCheck(i))
		{
			m_ctmInfoList.SetCheck(i,FALSE);
		}else{
			m_ctmInfoList.SetCheck(i,TRUE);
		}
		
	}
}


void CCustomInfoProp::OnDelFromList()
{
	// TODO: �ڴ���������������
	CStringArray arr;
	arr.RemoveAll();
	int count = m_ctmInfoList.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		if(m_ctmInfoList.GetCheck(i))
		{
			arr.Add(m_ctmInfoList.GetItemText(i,0));
		}
	}

	int size = arr.GetSize();
	for(int i = 0;i<size;i++)
	{
		int cur_count = m_ctmInfoList.GetItemCount();
		for(int j= 0;j<cur_count;j++)
		{
			if(m_ctmInfoList.GetItemText(j,0) == arr.GetAt(i))
			{
				m_ctmInfoList.DeleteItem(j);
				break;
			}
		}
	}
}


void CCustomInfoProp::OnClearList()
{
	// TODO: �ڴ���������������
	m_ctmInfoList.DeleteAllItems();
}


void CCustomInfoProp::OnBnClickedBtnDataImport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog fileDlg(TRUE);
	fileDlg.m_ofn.lpstrTitle = _T("��������ͻ�����");
	fileDlg.m_ofn.lpstrFilter = _T("Excel 2003(*.xls)\0*.xls\0Excel 2007(*.xlsx)\0*.xlsx\0\0");
	if(IDOK == fileDlg.DoModal())
	{
		if(IDYES == MessageBox(_T("��ȷ��Excel���ǰû�б����ټ���������"),_T("��ܰ��ʾ"),MB_YESNO))
		{
			CString pathName = fileDlg.GetPathName();
			CString fileExt = fileDlg.GetFileExt();
			CADOExcel ado;
			ado.SetFileType(fileExt);
			ado.SetExcelFilePath(pathName);
			if(!ado.OnInitConnect())
			{
				CString err = _T("����Excel��ʧ�ܣ�����ԭ�����£�\r\n");
				err += _T("1����ȷ��ִ�д˲���֮ǰ���Ѿ���װ�����ݿ��������棻\r\n"); 
				err += _T("2����ȷ��Ҫ���ӵ�Excel����Ѿ����ڹر�״̬��\r\n");
				MessageBox(err);
				return;
			}
			try{
				CString importSQL = _T("select * from [�ͻ���Ϣ��$]"); 
				ado.m_pRecordset = ado.GetRecordSet(importSQL);
				if(NULL == ado.m_pRecordset)
				{
					MessageBox(_T("��ȷ�ϴ򿪵�Excel���пͻ���Ϣ��������"));
					ado.ExitConnect();
					return;
				}
			}
			catch(_com_error e)
			{
				CString erro;
				erro.Format(_T("��ȡ�ͻ���¼��ʧ�ܣ�������Ϣ�ǣ�%s�����������ǣ�%s"),e.ErrorMessage(),(LPCTSTR)e.Description());
				MessageBox(erro);
				ado.ExitConnect();
				return;
			}
			int nCount = 0;
			m_ctmInfoList.DeleteAllItems();
			while(!ado.m_pRecordset->adoEOF)
			{
				try{
					//_variant_t var
					m_ctmInfoList.InsertItem(nCount,_T(""));//�����µ�һ��
					m_ctmInfoList.SetItemText(nCount,0,SafeReadDataFromExcel(ado.m_pRecordset->GetCollect("�ͻ����")));
					m_ctmInfoList.SetItemText(nCount,1,SafeReadDataFromExcel(ado.m_pRecordset->GetCollect("�ͻ�����")));
					m_ctmInfoList.SetItemText(nCount,2,SafeReadDataFromExcel(ado.m_pRecordset->GetCollect("�˿�����")));
					m_ctmInfoList.SetItemText(nCount,3,SafeReadDataFromExcel(ado.m_pRecordset->GetCollect("�ͻ��Ա�")));
					m_ctmInfoList.SetItemText(nCount,4,SafeReadDataFromExcel(ado.m_pRecordset->GetCollect("�ƶ��绰")));
					m_ctmInfoList.SetItemText(nCount,5,SafeReadDataFromExcel(ado.m_pRecordset->GetCollect("���Ѵ���")));
					m_ctmInfoList.SetItemText(nCount,6,SafeReadDataFromExcel(ado.m_pRecordset->GetCollect("���ѽ��")));
					m_ctmInfoList.SetItemText(nCount,7,SafeReadDataFromExcel(ado.m_pRecordset->GetCollect("�״�����ʱ��")));
					m_ctmInfoList.SetItemText(nCount,8,SafeReadDataFromExcel(ado.m_pRecordset->GetCollect("�������ʱ��")));
					m_ctmInfoList.SetItemText(nCount,9,SafeReadDataFromExcel(ado.m_pRecordset->GetCollect("��ע")));
				}catch(_com_error e)
				{
					CString erro;
					erro.Format(_T("����Ա����¼��ʧ�ܣ�������Ϣ�ǣ�%s�����������ǣ�%s"),e.ErrorMessage(),(LPCTSTR)e.Description());
					MessageBox(erro);
					ado.ExitConnect();
					return;
				}
				ado.m_pRecordset->MoveNext();
			}
			ado.ExitConnect();
			m_tip.SetWindowText(_T("�������"));
		}else{
			return;
		}
	}else
	{
		return;
	}
}

CString CCustomInfoProp::SafeReadDataFromExcel(_variant_t var)
{
	CString _str;
	_str.Empty();
	if(VT_NULL != var.vt)
	{
		_str = (LPCTSTR)(_bstr_t)var;
	}
	return  _str;
}

void CCustomInfoProp::OnTimer(UINT_PTR nIDEvent)
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


afx_msg LRESULT CCustomInfoProp::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	EnableParentDlgShutDownBtn(FALSE);
	//SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}

void CCustomInfoProp::EnableParentDlgShutDownBtn(BOOL bEnble)
{	
	CDataImportPropSheet * p_parentDlg = (CDataImportPropSheet *)GetParent();
	//TRUE��ʾ���� FALSE��ʾ������   
	p_parentDlg->SetCloseBtnEable(bEnble);
}

afx_msg LRESULT CCustomInfoProp::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	EnableParentDlgShutDownBtn(TRUE);
	//KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}

void CCustomInfoProp::ShowTip()
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
void CCustomInfoProp::InitTipCtrl()
{
	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	font.Detach();
}

void CCustomInfoProp::OnBnClickedBtnSubmit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ctm_to_submit_arr.RemoveAll();

	int count = m_ctmInfoList.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		CString temp;
		temp.Format(_T("�ύʧ�ܣ���%d�е����ݲ����Ϲ淶�������¼���ٴ��ύ��"),i+1);
		if(m_ctmInfoList.GetCheck(i))
		{
			if(!IsItemValidity(m_ctmInfoList.GetItemText(i,0),_T("�ͻ����"),TRUE,TRUE,FALSE,25))
			{
				MessageBox(temp);
				return;
			}
			if(!IsItemValidity(m_ctmInfoList.GetItemText(i,1),_T("�ͻ�����"),FALSE,FALSE,FALSE,25))
			{
				MessageBox(temp);
				return;
			}
			if(!IsItemValidity(m_ctmInfoList.GetItemText(i,2),_T("�˿�����"),FALSE,FALSE,FALSE,25))
			{
				MessageBox(temp);
				return;
			}
			if(!IsItemValidity(m_ctmInfoList.GetItemText(i,3),_T("�ͻ��Ա�"),FALSE,FALSE,FALSE,10))
			{
				MessageBox(temp);
				return;
			}else{
				CString sex = m_ctmInfoList.GetItemText(i,3);
				if(sex != _T("��") && sex!= _T("Ů") && !sex.IsEmpty())
				{
					MessageBox(_T("�ͻ��Ա�ǿյĻ� �ͱ���Ϊ�л���Ů"));
					MessageBox(temp);
					return;
				}
			}
			if(!IsItemValidity(m_ctmInfoList.GetItemText(i,4),_T("�ƶ��绰"),FALSE,TRUE,FALSE,20))
			{
				MessageBox(temp);
				return;
			}
			if(!IsItemValidity(m_ctmInfoList.GetItemText(i,5),_T("���Ѵ���"),FALSE,TRUE,FALSE,20))
			{
				MessageBox(temp);
				return;
			}
			if(!IsItemValidity(m_ctmInfoList.GetItemText(i,6),_T("���ѽ��"),FALSE,TRUE,FALSE,20))
			{
				MessageBox(temp);
				return;
			}
			if(!IsItemValidity(m_ctmInfoList.GetItemText(i,7),_T("�״�����ʱ��"),FALSE,FALSE,TRUE,30))
			{
				MessageBox(temp);
				return;
			}
			if(!IsItemValidity(m_ctmInfoList.GetItemText(i,8),_T("�������ʱ��"),FALSE,FALSE,TRUE,30))
			{
				MessageBox(temp);
				return;
			}
			if(!IsItemValidity(m_ctmInfoList.GetItemText(i,9),_T("��ע"),FALSE,FALSE,FALSE,300))
			{
				MessageBox(temp);
				return;
			}
			
			CString strTemp;
			strTemp.Format(_T("%d"),i);
			m_ctm_to_submit_arr.Add(strTemp);
		}
	}
	if(m_ctm_to_submit_arr.GetSize() == 0)
	{
		MessageBox(_T("�ύʧ�ܣ�û��ѡ����Ч������"));
	}else{
		CSock::StartSubmitCtmInfo(this);
	}
}

BOOL CCustomInfoProp::IsItemValidity(CString _source,CString _item_name,BOOL bCheckEmpty,BOOL bCheckNum,BOOL bCheckDateFormat,int str_len_max)    //true  ��Ч ������Ч  
	//������Ƿ�Ϊ�� �Ƿ������� �Լ������Ƿ񳬹�����  �����Ҫ����Ƿ������ֵĻ� ��ô��У���Ƿ���������ַ�  ������Ƿ�������ڸ�ʽ
{
	if(bCheckEmpty)    //TRUE  ������Ҫ����Ƿ�Ϊ�� ������Ϊ��
	{
		if(_source.IsEmpty())   //
		{
			CString err = _item_name+_T("����Ϊ��");
			MessageBox(err);
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
				MessageBox(err);
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
			MessageBox(err);
			return FALSE;
		}
		if(bCheckDateFormat)   //����Ƿ�������ڸ�ʽ
		{
			CString _err2 = _item_name+_T("���������ڸ�ʽ����׼��ʽ�磺2014-10-05");
			CString str = _source;
			int  index = _source.Find('-');
			if(index == -1)   //û�ҵ�
			{
				MessageBox(_err2);
				return FALSE;
			}else{
				CString left = str.Mid(0,index);
				str = str.Mid(index+1);
				if(left.GetLength()!=4)
				{
					MessageBox(_err2);
					return FALSE;
				}else{
					if(!IsNum(left))
					{
						MessageBox(_err2);
						return FALSE;
					}else{    //ǰ�滹��Ϸ���
						index = str.Find('-');
						if(index == -1)   //û�ҵ�
						{
							MessageBox(_err2);
							return FALSE;
						}else{
							left = str.Mid(0,index);
							str = str.Mid(index+1);
							if(IsNum(left)&&IsNum(str))
							{
								return TRUE;
							}else{
								MessageBox(_err2);
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
BOOL CCustomInfoProp::ContainsCharsRemain(CString str)     //����ַ����Ƿ�������ַ���
{
	CString temp1 = _T("[#");
	CString temp2 = _T("#]");
	CString temp3 = _T("{#");
	CString temp4 = _T("#}");
	int flag = 0;
	flag = str.Find(temp1);
	if(flag != -1)
	{
		MessageBox(_T("�����в��ܰ�����[#���ַ�"));
		return TRUE;
	}
	flag = str.Find(temp2);
	if(flag != -1)
	{
		MessageBox(_T("�����в��ܰ�����#]���ַ�"));
		return TRUE;
	}
	flag = str.Find(temp3);
	if(flag != -1)
	{
		MessageBox(_T("�����в��ܰ�����#}���ַ�"));
		return TRUE;
	}
	flag = str.Find(temp4);
	if(flag != -1)
	{
		MessageBox(_T("�����в��ܰ�����{#���ַ�"));
		return TRUE;
	}
	return FALSE;
}

BOOL CCustomInfoProp::IsNum(CString str)
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