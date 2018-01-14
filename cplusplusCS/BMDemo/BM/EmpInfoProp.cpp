// EmpInfoProp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "EmpInfoProp.h"
#include "afxdialogex.h"
#include "ADOExcel.h"
#include "DataImportPropSheet.h"
// CEmpInfoProp �Ի���

IMPLEMENT_DYNAMIC(CEmpInfoProp, CPropertyPage)

CEmpInfoProp::CEmpInfoProp()
	: CPropertyPage(CEmpInfoProp::IDD)
{

}

CEmpInfoProp::~CEmpInfoProp()
{
}

void CEmpInfoProp::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EMP, m_listEmp);
	DDX_Control(pDX, IDC_SPLIT_OPERATION2, m_splitEmp);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
}


BEGIN_MESSAGE_MAP(CEmpInfoProp, CPropertyPage)
	//ON_BN_CLICKED(IDC_BUTTON1, &CEmpInfoProp::OnBnClickedButton1)
	//ON_BN_CLICKED(IDC_BUTTON1, &CEmpInfoProp::OnBnClickedButton1)
	//ON_BN_CLICKED(IDC_BUTTON2, &CEmpInfoProp::OnBnClickedButton2)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CEmpInfoProp::OnLvnItemchangedList1)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CEmpInfoProp::OnLvnItemchangedList1)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CEmpInfoProp::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BTN_EMPIMPORT, &CEmpInfoProp::OnClickedBtnEmpImport)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_SUBMIT, &CEmpInfoProp::OnBnClickedBtnSubmit)
	ON_WM_TIMER()
	ON_MESSAGE(WM_STARTTASK_EmpInfoProp, &CEmpInfoProp::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_EmpInfoProp, &CEmpInfoProp::OnEndTask)
	ON_COMMAND(ID_CHOOSE_ALL, &CEmpInfoProp::OnChooseAll)
	ON_COMMAND(ID_REVERSE_CHOOSE, &CEmpInfoProp::OnReverseChoose)
	ON_COMMAND(ID_CANCEL_CHOOSE, &CEmpInfoProp::OnCancelChoose)
	ON_COMMAND(ID_DEL, &CEmpInfoProp::OnDel)
	ON_COMMAND(ID_CLEAR, &CEmpInfoProp::OnClear)
END_MESSAGE_MAP()


// CEmpInfoProp ��Ϣ�������


BOOL CEmpInfoProp::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	InitList();
	InitTipCtrl();
	InitSplit();

	return false;
}

void CEmpInfoProp::InitTipCtrl()
{
	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	font.Detach();
}

void CEmpInfoProp::InitList()
{
	m_listEmp.SetBkColor(CONCTRLBKCOLOR);
	m_listEmp.SetExtendedStyle( m_listEmp.GetExtendedStyle()| LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listEmp.SetTextColor(RGB(139, 90, 43));
	m_listEmp.SetTextBkColor(RGB(255, 236, 139));
	
	CRect rect;
	m_listEmp.GetClientRect(rect);
	m_listEmp.InsertColumn(0, _T("Ա������"), LVCFMT_LEFT, 100);    
    m_listEmp.InsertColumn(1, _T("Ա������"), LVCFMT_LEFT, 100);
	m_listEmp.InsertColumn(2, _T("�����ص�"), LVCFMT_LEFT, 100);
    m_listEmp.InsertColumn(3, _T("ְ��"), LVCFMT_LEFT, 100);
	m_listEmp.InsertColumn(4, _T("��ϵ�绰"), LVCFMT_LEFT, 100);
	m_listEmp.InsertColumn(5, _T("��ע"), LVCFMT_LEFT, rect.Width()-500);    
    
	/*
	m_listEmp.InsertItem(0, _T("00000"));    
    m_listEmp.SetItemText(0, 1, _T("����"));    
    m_listEmp.SetItemText(0, 2, _T("�Ͼ�"));    
    m_listEmp.SetItemText(0, 3, _T("�ܾ���"));    
    m_listEmp.SetItemText(0, 4, _T("12345678901")); 
	m_listEmp.SetItemText(0, 5, _T("��"));    
   
	m_listEmp.InsertItem(0, _T("00001"));    
    m_listEmp.SetItemText(0, 1, _T("����"));    
    m_listEmp.SetItemText(0, 2, _T("�Ͼ�"));    
    m_listEmp.SetItemText(0, 3, _T("���ܾ���"));    
    m_listEmp.SetItemText(0, 4, _T("1234564477")); 
	m_listEmp.SetItemText(0, 5, _T("��")); 
	*/
}


void CEmpInfoProp::InitSplit()
{
	m_splitEmp.SetDropDownMenu(IDM_EMP_IMPORT_OPERATION,0);
}


void CEmpInfoProp::OnClickedBtnEmpImport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog fileDlg(TRUE);
	fileDlg.m_ofn.lpstrTitle = _T("��������Ա������");
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
				CString importSQL = _T("select * from [Ա����Ϣ��$]"); 
				ado.m_pRecordset = ado.GetRecordSet(importSQL);
				if(NULL == ado.m_pRecordset)
				{
					MessageBox(_T("��ȷ�ϴ򿪵�Excel����Ա����Ϣ��������"));
					ado.ExitConnect();
					return;
				}
			}
			catch(_com_error e)
			{
				CString erro;
				erro.Format(_T("��ȡԱ����¼��ʧ�ܣ�������Ϣ�ǣ�%s�����������ǣ�%s"),e.ErrorMessage(),(LPCTSTR)e.Description());
				MessageBox(erro);
				ado.ExitConnect();
				return;
			}
			int nCount = 0;
			m_listEmp.DeleteAllItems();
			

			while(!ado.m_pRecordset->adoEOF)
			{
				CString empNum = NULL;
				CString empName = NULL;
				CString empAddr = NULL;
				CString empPos = NULL;
				CString empPhone = NULL;
				CString empPs = NULL;
				try{
					//_variant_t var
					_variant_t temp =  ado.m_pRecordset->GetCollect("Ա������");
					if(VT_NULL != temp.vt)
					{
						empNum = (LPCTSTR)(_bstr_t)temp;
					}
					temp =  ado.m_pRecordset->GetCollect("Ա������");
					if(VT_NULL != temp.vt)
					{
						empName = (LPCTSTR)(_bstr_t)temp;
					}
					temp =  ado.m_pRecordset->GetCollect("�����ص�");
					if(VT_NULL != temp.vt)
					{
						empAddr = (LPCTSTR)(_bstr_t)temp;
					}
					temp =  ado.m_pRecordset->GetCollect("ְ��");
					if(VT_NULL != temp.vt)
					{
						empPos = (LPCTSTR)(_bstr_t)temp;
					}
					temp =  ado.m_pRecordset->GetCollect("��ϵ�绰");
					if(VT_NULL != temp.vt)
					{
						empPhone = (LPCTSTR)(_bstr_t)temp;
					}
					temp =  ado.m_pRecordset->GetCollect("��ע");
					if(VT_NULL != temp.vt)
					{
						empPs = (LPCTSTR)(_bstr_t)temp;
					}
				}catch(_com_error e)
				{
					CString erro;
					erro.Format(_T("����Ա����¼��ʧ�ܣ�������Ϣ�ǣ�%s�����������ǣ�%s"),e.ErrorMessage(),(LPCTSTR)e.Description());
					MessageBox(erro);
					ado.ExitConnect();
					return;
				}
				
				m_listEmp.InsertItem(nCount,_T(""));//�����µ�һ��
				m_listEmp.SetItemText(nCount,0,empNum);
				m_listEmp.SetItemText(nCount,1,empName);
				m_listEmp.SetItemText(nCount,2,empAddr);
				m_listEmp.SetItemText(nCount,3,empPos);
				m_listEmp.SetItemText(nCount,4,empPhone);
				m_listEmp.SetItemText(nCount,5,empPs);
				
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


HBRUSH CEmpInfoProp::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CEmpInfoProp::OnBnClickedBtnSubmit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_num_to_submit_to_db.RemoveAll();
	int count = m_listEmp.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		if(m_listEmp.GetCheck(i))
		{
			CString num = NULL;
			num = m_listEmp.GetItemText(i,0);
			if(!num.IsEmpty())
			{
				if(!IsNum(num))
				{
					CString temp;
					temp.Format(_T("��%d�е�Ա�����Ų������֣��ύʧ��"),i+1);
					MessageBox(temp);
					return;
				}
			}else{
				CString temp;
				temp.Format(_T("��%d�е�Ա������Ϊ�գ��ύʧ��"),i+1);
				MessageBox(temp);
				return;
			}
			CString temp = m_listEmp.GetItemText(i,1);   //Ա������
			if(!temp.IsEmpty())
			{
				if(temp.GetLength()>25)
				{
					MessageBox(_T("Ա���������ܳ���25���ַ�"));
					return;
				}else if(ContainsCharsRemain(temp))
				{
					MessageBox(_T("Ա���������ܰ�����{#��,��#}��,��[#��,��#]����Щ�ַ�"));
					return;
				}
			}
			temp = m_listEmp.GetItemText(i,2);   //�����ص�
			if(!temp.IsEmpty())
			{
				if(temp.GetLength()>50)
				{
					MessageBox(_T("Ա�������ص㲻�ܳ���50���ַ�"));
					return;
				}else if(ContainsCharsRemain(temp))
				{
					MessageBox(_T("Ա�������ص㲻�ܰ�����{#��,��#}��,��[#��,��#]����Щ�ַ�"));
					return;
				}
			}
			temp = m_listEmp.GetItemText(i,3);   //ְ��
			if(!temp.IsEmpty())
			{
				if(temp.GetLength()>40)
				{
					MessageBox(_T("Ա��ְ���ܳ���40���ַ�"));
					return;
				}else if(ContainsCharsRemain(temp))
				{
					MessageBox(_T("Ա��ְ���ܰ�����{#��,��#}��,��[#��,��#]����Щ�ַ�"));
					return;
				}
			}
			temp = m_listEmp.GetItemText(i,4);   //��ϵ�绰
			if(!temp.IsEmpty())
			{
				if(temp.GetLength()>20)
				{
					MessageBox(_T("Ա����ϵ�绰���ܳ���20���ַ�"));
					return;
				}else if(!IsNum(temp))
				{
					MessageBox(_T("Ա����ϵ�绰����Ϊ����"));
					return;
				}
			}
			temp = m_listEmp.GetItemText(i,5);   //��ע
			if(!temp.IsEmpty())
			{
				if(temp.GetLength()>300)
				{
					MessageBox(_T("Ա����ע���ܳ���300���ַ�"));
					return;
				}else if(ContainsCharsRemain(temp))
				{
					MessageBox(_T("Ա����ע���ܰ�����{#��,��#}��,��[#��,��#]����Щ�ַ�"));
					return;
				}
			}
			CString strTemp;
			strTemp.Format(_T("%d"),i);
			m_num_to_submit_to_db.Add(strTemp);
		}
	}
	if(m_num_to_submit_to_db.GetSize() == 0)
	{
		MessageBox(_T("�ύʧ�ܣ�û��ѡ����Ч������"));
	}else{
		CSock::StartImportEmpInfo(this);
	}
}

BOOL CEmpInfoProp::ContainsCharsRemain(CString str)     //����ַ����Ƿ�������ַ���
{
	CString temp1 = _T("[#");
	CString temp2 = _T("#]");
	CString temp3 = _T("{#");
	CString temp4 = _T("#}");
	int flag = 0;
	flag = str.Find(temp1);
	if(flag != -1)
	{
		MessageBox(_T("Ա�������в��ܰ�����[#���ַ�"));
		return TRUE;
	}
	flag = str.Find(temp2);
	if(flag != -1)
	{
		MessageBox(_T("Ա�������в��ܰ�����#]���ַ�"));
		return TRUE;
	}
	flag = str.Find(temp3);
	if(flag != -1)
	{
		MessageBox(_T("Ա�������в��ܰ�����#}���ַ�"));
		return TRUE;
	}
	flag = str.Find(temp4);
	if(flag != -1)
	{
		MessageBox(_T("Ա�������в��ܰ�����{#���ַ�"));
		return TRUE;
	}
	return FALSE;
}

BOOL CEmpInfoProp::IsNum(CString str)
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

void CEmpInfoProp::OnTimer(UINT_PTR nIDEvent)
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

void CEmpInfoProp::ShowTip()
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

afx_msg LRESULT CEmpInfoProp::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	EnableParentDlgShutDownBtn(FALSE);
	//SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}

void CEmpInfoProp::EnableParentDlgShutDownBtn(BOOL bEnable)
{
	CDataImportPropSheet * p_parentDlg = (CDataImportPropSheet *)GetParent();
	//TRUE��ʾ���� FALSE��ʾ������   
	p_parentDlg->SetCloseBtnEable(bEnable);
}



afx_msg LRESULT CEmpInfoProp::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	EnableParentDlgShutDownBtn(TRUE);
	//KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


void CEmpInfoProp::OnChooseAll()
{
	// TODO: �ڴ���������������
	int count  = m_listEmp.GetItemCount();
	for(int i = 0; i<count;i++)
	{
		m_listEmp.SetCheck(i,TRUE);
	}
}


void CEmpInfoProp::OnReverseChoose()
{
	// TODO: �ڴ���������������
	int count  = m_listEmp.GetItemCount();
	for(int i = 0; i<count;i++)
	{
		if(m_listEmp.GetCheck(i))
		{
			m_listEmp.SetCheck(i,FALSE);
		}else{
			m_listEmp.SetCheck(i,TRUE);
		}
	}
}


void CEmpInfoProp::OnCancelChoose()
{
	// TODO: �ڴ���������������
	int count  = m_listEmp.GetItemCount();
	for(int i = 0; i<count;i++)
	{
		m_listEmp.SetCheck(i,FALSE);
		
	}
}


void CEmpInfoProp::OnDel()
{
	// TODO: �ڴ���������������
	int count  = m_listEmp.GetItemCount();
	for(int i = 0; i<count;i++)
	{
		if(m_listEmp.GetCheck(i)){
			m_listEmp.DeleteItem(i);
		}
	}
}


void CEmpInfoProp::OnClear()
{
	// TODO: �ڴ���������������
	m_listEmp.DeleteAllItems();
}
