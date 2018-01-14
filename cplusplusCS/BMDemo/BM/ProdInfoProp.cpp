// ProdInfoProp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "ProdInfoProp.h"
#include "afxdialogex.h"
#include "DataImportPropSheet.h"
  
// CProdInfoProp �Ի���

IMPLEMENT_DYNAMIC(CProdInfoProp, CPropertyPage)

CProdInfoProp::CProdInfoProp()
	: CPropertyPage(CProdInfoProp::IDD)
{

}

CProdInfoProp::~CProdInfoProp()
{
}

void CProdInfoProp::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROD, m_listProd);
	DDX_Control(pDX, IDC_SPLIT_OPER2, m_split);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
}


BEGIN_MESSAGE_MAP(CProdInfoProp, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_PRODINFOIMPORT, &CProdInfoProp::OnBnClickedBtnProdinfoimport)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_DATASUBMIT, &CProdInfoProp::OnBnClickedBtnDatasubmit)
	ON_WM_TIMER()
	ON_MESSAGE(WM_STARTTASK_ProdIm, &CProdInfoProp::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_ProdIm, &CProdInfoProp::OnEndTask)
	ON_COMMAND(ID_CHOOSE_ALL, &CProdInfoProp::OnChooseAll)
	ON_COMMAND(ID_REVERSE_CHOOSE, &CProdInfoProp::OnReverseChoose)
	ON_COMMAND(ID_CHOOSE_NONE, &CProdInfoProp::OnChooseNone)
	ON_COMMAND(ID_DEL_FROM_LIST, &CProdInfoProp::OnDelFromList)
	ON_COMMAND(ID_CLEAR_LIST, &CProdInfoProp::OnClearList)
END_MESSAGE_MAP()


// CProdInfoProp ��Ϣ�������

HBRUSH CProdInfoProp::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CProdInfoProp::OnBnClickedBtnProdinfoimport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog fileDlg(TRUE);
	fileDlg.m_ofn.lpstrTitle = _T("���������Ʒ����");
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
				CString importSQL = _T("select * from [��Ʒ��Ϣ��$]"); 
				ado.m_pRecordset = ado.GetRecordSet(importSQL);
				if(NULL == ado.m_pRecordset)
				{
					MessageBox(_T("��ȷ�ϴ򿪵�Excel���в�Ʒ��Ϣ��������"));
					ado.ExitConnect();
					return;
				}
			}
			catch(_com_error e)
			{
				CString erro;
				erro.Format(_T("��ȡ��Ʒ��¼��ʧ�ܣ�������Ϣ�ǣ�%s�����������ǣ�%s"),e.ErrorMessage(),(LPCTSTR)e.Description());
				MessageBox(erro);
				ado.ExitConnect();
				return;
			}
			int nCount = 0;
			m_listProd.DeleteAllItems();
			while(!ado.m_pRecordset->adoEOF)
			{
				try{
					//_variant_t var
					m_listProd.InsertItem(nCount,_T(""));//�����µ�һ��
					//m_listProd.SetItemText(nCount,0,SafeReadDataFromExcel(ado.m_pRecordset->GetCollect("��ƷID")));
					m_listProd.SetItemText(nCount,0,SafeReadDataFromExcel(ado.m_pRecordset->GetCollect("��Ʒ����")));
					m_listProd.SetItemText(nCount,1,SafeReadDataFromExcel(ado.m_pRecordset->GetCollect("��Ʒ����")));
					m_listProd.SetItemText(nCount,2,SafeReadDataFromExcel(ado.m_pRecordset->GetCollect("��Ӧ��")));
					m_listProd.SetItemText(nCount,3,SafeReadDataFromExcel(ado.m_pRecordset->GetCollect("��ע")));
					
				}catch(_com_error e)
				{
					CString erro;
					erro.Format(_T("�����Ʒ��¼��ʧ�ܣ�������Ϣ�ǣ�%s�����������ǣ�%s"),e.ErrorMessage(),(LPCTSTR)e.Description());
					MessageBox(erro);
					ado.ExitConnect();
					return;
				}
				ado.m_pRecordset->MoveNext();
			}
			ado.ExitConnect();
			CString _strTip;
			_strTip.Format(_T("������%d������"),m_listProd.GetItemCount());
			m_tip.SetWindowText(_strTip);
		}else{
			return;
		}
	}else
	{
		return;
	}
}

//}
void CProdInfoProp::InitSplit() 
{
	m_split.SetDropDownMenu(IDM_PROD_IM_OPERATION,0);
}
void CProdInfoProp::InitList() 
{
	m_listProd.SetBkColor(CONCTRLBKCOLOR);
	m_listProd.SetExtendedStyle( m_listProd.GetExtendedStyle()| LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listProd.SetTextColor(RGB(139, 90, 43));
	m_listProd.SetTextBkColor(RGB(255, 236, 139));
	
	CRect rect;
	m_listProd.GetClientRect(rect);
	//m_listProd.InsertColumn(0, _T("��ƷID"), LVCFMT_LEFT, 100);    
	m_listProd.InsertColumn(0, _T("��Ʒ����"), LVCFMT_LEFT, 100);    
    m_listProd.InsertColumn(1, _T("��Ʒ����"), LVCFMT_LEFT, 150);
	m_listProd.InsertColumn(2, _T("��Ӧ��"), LVCFMT_LEFT, 150);
    m_listProd.InsertColumn(3, _T("��ע"), LVCFMT_LEFT, rect.Width()-400);
}

BOOL CProdInfoProp::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	InitSplit();
	InitList();
	InitTipCtrl();
	return 0;
}


void CProdInfoProp::InitTipCtrl()
{
	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	font.Detach();
}


void CProdInfoProp::OnBnClickedBtnDatasubmit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		// TODO: �ڴ���ӿؼ�֪ͨ����������
		// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_arr_prodInfoForIm.RemoveAll();

	int count = m_listProd.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		CString temp;
		temp.Format(_T("�ύʧ�ܣ���%d�е����ݲ����Ϲ淶�������¼���ٴ��ύ��"),i+1);
		if(m_listProd.GetCheck(i))
		{
			if(!CSock::IsItemValidity(m_listProd.GetItemText(i,0),_T("��Ʒ����"),TRUE,FALSE,FALSE,25))
			{
				MessageBox(temp);
				return;
			}
			if(!CSock::IsItemValidity(m_listProd.GetItemText(i,1),_T("��Ʒ����"),FALSE,FALSE,FALSE,50))
			{
				MessageBox(temp);
				return;
			}
			if(!CSock::IsItemValidity(m_listProd.GetItemText(i,2),_T("��Ӧ��"),FALSE,FALSE,FALSE,50))
			{
				MessageBox(temp);
				return;
			}
			if(!CSock::IsItemValidity(m_listProd.GetItemText(i,3),_T("��ע"),FALSE,FALSE,FALSE,200))
			{
				MessageBox(temp);
				return;
			}
			CString strTemp;
			strTemp.Format(_T("%d"),i);
			m_arr_prodInfoForIm.Add(strTemp);
		}
	}
	if(m_arr_prodInfoForIm.GetSize() == 0)
	{
		MessageBox(_T("�ύʧ�ܣ�û��ѡ����Ч������"));
	}else{
		//CSock::StartSubmitCtmInfo(this);
		CSock::StartSubmitProd(this);
	}
}

CString CProdInfoProp::SafeReadDataFromExcel(_variant_t var)    //�Խ�Ϊ��ȫ�ķ�ʽ��EXCEL���ж�ȡ����
{
	CString _str_res;
	_str_res.Empty();
	if(VT_NULL != var.vt)
	{
		_str_res = (LPCTSTR)(_bstr_t)var;
	}
	return _str_res;
}

void CProdInfoProp::OnTimer(UINT_PTR nIDEvent)
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

void   CProdInfoProp::ShowTip()
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

afx_msg LRESULT CProdInfoProp::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	EnableParentDlgShutDownBtn(FALSE);
	//SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CProdInfoProp::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	EnableParentDlgShutDownBtn(TRUE);
	//KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


void CProdInfoProp::EnableParentDlgShutDownBtn(BOOL bEnbale)
{
	CDataImportPropSheet * p_parentDlg = (CDataImportPropSheet *)GetParent();
	//TRUE��ʾ���� FALSE��ʾ������   
	p_parentDlg->SetCloseBtnEable(bEnbale);
}

void CProdInfoProp::OnChooseAll()
{
	// TODO: �ڴ���������������
	int count  = m_listProd.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		m_listProd.SetCheck(i,TRUE);
	}
}


void CProdInfoProp::OnReverseChoose()
{
	// TODO: �ڴ���������������
	int count  = m_listProd.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		if(m_listProd.GetCheck(i))
		{
			m_listProd.SetCheck(i,FALSE);
		}else{
			m_listProd.SetCheck(i,TRUE);
		}
	}
}


void CProdInfoProp::OnChooseNone()
{
	// TODO: �ڴ���������������
	int count  = m_listProd.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		m_listProd.SetCheck(i,FALSE);
	}
}


void CProdInfoProp::OnDelFromList()
{
	// TODO: �ڴ���������������
	CStringArray arr;
	arr.RemoveAll();
	int count = m_listProd.GetItemCount();
	for(int i = 0;i<count;i++)
	{
		if(m_listProd.GetCheck(i))
		{
			arr.Add(m_listProd.GetItemText(i,0));
		}
	}

	int size = arr.GetSize();
	for(int i = 0;i<size;i++)
	{
		int cur_count = m_listProd.GetItemCount();
		for(int j= 0;j<cur_count;j++)
		{
			if(m_listProd.GetItemText(j,0) == arr.GetAt(i))
			{
				m_listProd.DeleteItem(j);
				break;
			}
		}
	}
}


void CProdInfoProp::OnClearList()
{
	// TODO: �ڴ���������������
	m_listProd.DeleteAllItems();
}
