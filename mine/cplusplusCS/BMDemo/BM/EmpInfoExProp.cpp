// EmpInfoExProp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "EmpInfoExProp.h"
#include "afxdialogex.h"
#include "DataExportPropSheet.h"
#include "ADOExcel.h"


// CEmpInfoExProp �Ի���

IMPLEMENT_DYNAMIC(CEmpInfoExProp, CPropertyPage)

CEmpInfoExProp::CEmpInfoExProp()
	: CPropertyPage(CEmpInfoExProp::IDD)
{

}

CEmpInfoExProp::~CEmpInfoExProp()
{
}

void CEmpInfoExProp::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EMP, m_list);
	//  DDX_Control(pDX, IDC_SPLIT_OPERATION2, m_split);
	DDX_Control(pDX, IDC_SPLIT_OPERATION2, m_split);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
}

void CEmpInfoExProp::InitList()
{
	m_list.SetBkColor(CONCTRLBKCOLOR);
	m_list.SetExtendedStyle( m_list.GetExtendedStyle()| LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.SetTextColor(RGB(139, 90, 43));
	m_list.SetTextBkColor(RGB(255, 236, 139));
	
	CRect rect;
	m_list.GetClientRect(rect);
	m_list.InsertColumn(0, _T("Ա������"), LVCFMT_LEFT, rect.Width()/6);    
    m_list.InsertColumn(1, _T("Ա������"), LVCFMT_LEFT, rect.Width()/6);
	m_list.InsertColumn(2, _T("�����ص�"), LVCFMT_LEFT, rect.Width()/6);
    m_list.InsertColumn(3, _T("ְ��"), LVCFMT_LEFT, rect.Width()/6);
	m_list.InsertColumn(4, _T("��ϵ�绰"), LVCFMT_LEFT, rect.Width()/6);
	m_list.InsertColumn(5, _T("��ע"), LVCFMT_LEFT, rect.Width()/6);      
    
}

void CEmpInfoExProp::InitSplit()
{
	m_split.SetDropDownMenu(IDM_EMP_EX_OPERATION,0);

}

BOOL CEmpInfoExProp::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	InitList();
	InitTipCtrl();
	InitSplit();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CEmpInfoExProp, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_EMPEXPORT, &CEmpInfoExProp::OnBnClickedBtnEmpexport)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_EMPSEARCH, &CEmpInfoExProp::OnBnClickedBtnEmpsearch)
	ON_WM_TIMER()
	ON_MESSAGE(WM_STARTTASK_EmpInfoExProp, &CEmpInfoExProp::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_EmpInfoExProp, &CEmpInfoExProp::OnEndTask)
	ON_COMMAND(ID_32793, &CEmpInfoExProp::OnChooseAll)
	ON_COMMAND(ID_32794, &CEmpInfoExProp::OnReverseChoose)
	ON_COMMAND(ID_CANCEL_CHOOSE_EMPINFOEX, &CEmpInfoExProp::OnCancelChoose)
	ON_COMMAND(ID_DEL_EMP_EX, &CEmpInfoExProp::OnDelEmp)
	ON_COMMAND(ID_CLEAR_ALL, &CEmpInfoExProp::OnClearAll)
END_MESSAGE_MAP()


// CEmpInfoExProp ��Ϣ�������

void CEmpInfoExProp::InitTipCtrl()
{
	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	font.Detach();
}


void CEmpInfoExProp::OnBnClickedBtnEmpexport()
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
		MessageBox(_T("��ǰû��Ҫ������Ա�����ݣ���ѡ����Ч��Ա������"));
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
				CString err = _T("����Excel��ʧ�ܣ�����ԭ�����£�\r\n");
				err += _T("1����ȷ��ִ�д˲���֮ǰ���Ѿ���װ�����ݿ��������棻\r\n"); 
				err += _T("2����ȷ��Ҫ���ӵ�Excel����Ѿ����ڹر�״̬��\r\n");
				MessageBox(err);
				return;
			}

			try
			{
				CString sql = _T("select * from [Ա����Ϣ��$]");
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
				creatTable = "CREATE TABLE Ա����Ϣ��(Ա������ char(20), Ա������ char(20),�����ص� char(200),ְ�� char(50),��ϵ�绰 char(20),��ע char(200));";
				if(!ado.ExecuteSQL(creatTable))
				{
					MessageBox(_T("�������ʧ��"));
					ado.ExitConnect();
					return;
				}
			}
			CString sql = _T("select * from [Ա����Ϣ��$]");
			ado.m_pRecordset = ado.GetRecordSet(sql);
			
			
			for(int i = 0; i< size;i++)
			{
				int index = atoi(T2A(empArr.GetAt(i)));
				CString strNum = m_list.GetItemText(index,0);
				CString strName = m_list.GetItemText(index,1);
				CString strAddr = m_list.GetItemText(index,2);
				CString strPos = m_list.GetItemText(index,3);
				CString strPhone = m_list.GetItemText(index,4);
				CString strPS = m_list.GetItemText(index,5);
				try{
					ado.m_pRecordset->AddNew();
					ado.m_pRecordset->PutCollect("Ա������",(const _variant_t)strNum);
					ado.m_pRecordset->PutCollect("Ա������",(const _variant_t)strName);
					ado.m_pRecordset->PutCollect("�����ص�",(const _variant_t)strAddr);
					ado.m_pRecordset->PutCollect("ְ��",(const _variant_t)strPos);
					ado.m_pRecordset->PutCollect("��ϵ�绰",(const _variant_t)strPhone);
					ado.m_pRecordset->PutCollect("��ע",(const _variant_t)strPS);		
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


HBRUSH CEmpInfoExProp::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CEmpInfoExProp::OnBnClickedBtnEmpsearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSock::StartReqFindEmpForEx(this);

}

void CEmpInfoExProp::EnableParentDlgShutDownBtn(BOOL nEnable)   //��������ҳ�رմ��ڰ�ť
{
	CDataExportPropSheet * p_parentDlg = (CDataExportPropSheet *)GetParent();
	//TRUE��ʾ���� FALSE��ʾ������   
	p_parentDlg->SetCloseBtnEable(nEnable);

}

void CEmpInfoExProp::OnTimer(UINT_PTR nIDEvent)
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


void CEmpInfoExProp::ShowTip()
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

afx_msg LRESULT CEmpInfoExProp::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	EnableParentDlgShutDownBtn(FALSE);
	//SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CEmpInfoExProp::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	EnableParentDlgShutDownBtn(TRUE);
	//KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


void CEmpInfoExProp::OnChooseAll()
{
	// TODO: �ڴ���������������
	int count = m_list.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		m_list.SetCheck(i,TRUE);
	}
}


void CEmpInfoExProp::OnReverseChoose()
{
	// TODO: �ڴ���������������
	int count = m_list.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		if(m_list.GetCheck(i)){
			m_list.SetCheck(i,FALSE);
		}else{
			m_list.SetCheck(i,TRUE);
		}
	}
}


void CEmpInfoExProp::OnCancelChoose()
{
	// TODO: �ڴ���������������
	int count = m_list.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		m_list.SetCheck(i,FALSE);
	}
}


void CEmpInfoExProp::OnDelEmp()
{
	// TODO: �ڴ���������������
	int count = m_list.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		if(m_list.GetCheck(i))
		{
			m_list.DeleteItem(i);
		}
	}
}


void CEmpInfoExProp::OnClearAll()
{
	// TODO: �ڴ���������������
	m_list.DeleteAllItems();
}
