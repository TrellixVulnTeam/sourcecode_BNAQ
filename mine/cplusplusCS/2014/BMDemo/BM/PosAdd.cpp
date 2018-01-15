// PosAdd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "PosAdd.h"
#include "afxdialogex.h"


// CPosAdd �Ի���

IMPLEMENT_DYNAMIC(CPosAdd, CDialogEx)

CPosAdd::CPosAdd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPosAdd::IDD, pParent)
	, m_emp_num(_T(""))
	, m_emp_name(_T(""))
	, m_password_confirm(_T(""))
	, m_emp_ps(_T(""))
	, m_emp_password(_T(""))
{

}

CPosAdd::~CPosAdd()
{
}

void CPosAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
	DDX_Text(pDX, IDC_ET_POSNO, m_emp_num);
	DDX_Text(pDX, IDC_ET_PASSWORD_CONFIRM, m_password_confirm);
	DDX_Text(pDX, IDC_ET_EMPPS, m_emp_ps);
	DDX_Text(pDX, IDC_ET_EMPNM, m_emp_name);
	DDX_Text(pDX, IDC_ET_EMP_PASSWORD, m_emp_password);
	DDX_Control(pDX, IDC_COMBO_POS_NAME, m_pos_name);
}

BEGIN_MESSAGE_MAP(CPosAdd, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_SAVE_POS, &CPosAdd::OnBnClickedBtnSavePos)
	ON_WM_TIMER()
	ON_MESSAGE(WM_STARTTASK_PosAdd, &CPosAdd::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_PosAdd, &CPosAdd::OnEndTask)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CPosAdd::OnBnClickedBtnCancel)
END_MESSAGE_MAP()


// CPosAdd ��Ϣ�������


HBRUSH CPosAdd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

BOOL CPosAdd::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InitTipCtrl();
	InitPosCombox();
	return TRUE;	
}

void CPosAdd::InitPosCombox()
{
	m_pos_name.AddString(_T("ϵͳ����Ա"));
	m_pos_name.AddString(_T("�ܾ���"));
	m_pos_name.AddString(_T("�ͻ�����"));
	m_pos_name.AddString(_T("���ʦ"));
	m_pos_name.AddString(_T("��ͨԱ��"));
	m_pos_name.SetCurSel(4);
}


void CPosAdd::OnBnClickedBtnSavePos()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_str_pos_new.Empty();
	if(!IsItemValidity(m_emp_num,_T("��ɫ���"),TRUE,TRUE,FALSE,20))
	{
		return;
	}
	AddItemToString(m_str_pos_new,m_emp_num,DATA_START);
	CString temp;
	m_pos_name.GetWindowText(temp);
	AddItemToString(m_str_pos_new,temp,DATA_MID);
	if(!IsItemValidity(m_emp_name,_T("Ա������"),TRUE,FALSE,FALSE,20))
	{
		return;
	}
	AddItemToString(m_str_pos_new,m_emp_name,DATA_MID);
	if(!IsItemValidity(m_emp_password,_T("��¼����"),TRUE,FALSE,FALSE,13))
	{
		
		return;
	}
	if(m_emp_password.GetLength()<3)
	{
		MessageBox(_T("��¼���벻��̫�̣����鲻������3���ַ���"));
		return ;
	}
	if(m_emp_password != m_password_confirm)
	{
		MessageBox(_T("������������벻һ�£�����������"));
		m_password_confirm = _T("");
		UpdateData(FALSE);
		return;
	}
	AddItemToString(m_str_pos_new,m_emp_password,DATA_MID);
	
	if(!IsItemValidity(m_emp_ps,_T("��ע"),FALSE,FALSE,FALSE,200))
	{
		return;
	}
	AddItemToString(m_str_pos_new,m_emp_ps,DATA_MID);

	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_DEAL_NEW))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}

	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_EDIT_DEAL))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}

	
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_FIND_DEAL))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_DEL_DEAL))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_UPLOAD_FILE))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}

	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_DOWNLOAD_FILE))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_DEL_FILE))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}

	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_FIND_DEAL_INCOMPLETE))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_EDIT_DEAL_INCOMPLETE))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}

	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_FIND_STORE))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_ALERT_SET))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}

	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_STORE_ADD))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}

	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_STORE_OUT))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_HISTORY_FIND))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_DEL_HISTORY))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_FIND_EMP))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_EDIT_EMP))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_EMP_NEW))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}

	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_DEL_EMP))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}

	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_FIND_EMP_PERFERENCE))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}

	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_FIND_CTM))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}

	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_CTM_NEW))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}

	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_EDIT_CTM))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}

	
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_DEL_CTM))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_POS_ADD))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_FIND_POS))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_DEL_POS))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_EDIT_POS))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_PROD_IM))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_PROD_EX))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_CTM_IM))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}

	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_CTM_EX))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_EMP_IM))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_EMP_EX))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_MT_FIND))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_NODE_NEW))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_NODE_EDIT))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_DEL_NODE))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_FIND_FCT))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_FCT_NEW))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_EDIT_FCT))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_DEL_FCT))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_NOTE_PUBLIC))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_MID);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_MID);
	}
	if(1 == ((CButton*)GetDlgItem(IDC_CHECK_NOTE_DEL))->GetCheck())
	{
		AddItemToString(m_str_pos_new,_T("1"),DATA_END);
	}else{
		AddItemToString(m_str_pos_new,_T("0"),DATA_END);
	}
	CSock::StartReqPosAdd(this);
}



void CPosAdd::OnTimer(UINT_PTR nIDEvent)
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

void CPosAdd::ShowTip()
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

void CPosAdd::InitTipCtrl()
{
	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	font.Detach();
}

afx_msg LRESULT CPosAdd::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CPosAdd::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}

void CPosAdd::AddItemToString(CString &_source,CString item_new,int flag)
{
	CString _start = _T("{#[#");
	CString _mid = _T("#][#");
	CString _end = _T("#]#}");
	switch (flag)
	{
	case -1:
		{
			_source += _start;
			_source += item_new;
			_source += _mid;
			break;
		}
	case 0:
		{
			_source += item_new;
			_source += _mid;
			break;
		}
	case 1:
		{
			_source += item_new;
			_source += _end;
			break;
		}
	default:
		break;
	}
}


BOOL CPosAdd::IsItemValidity(CString _source,CString _item_name,BOOL bCheckEmpty,BOOL bCheckNum,BOOL bCheckDateFormat,int str_len_max)    //true  ��Ч ������Ч  
	//������Ƿ�Ϊ�� �Ƿ������� �Լ������Ƿ񳬹�����  �����Ҫ����Ƿ������ֵĻ� ��ô��У���Ƿ���������ַ�  ������Ƿ�������ڸ�ʽ
{
	WT;
	if(bCheckEmpty)    //TRUE  ������Ҫ����Ƿ�Ϊ�� ������Ϊ��
	{
		if(_source.IsEmpty())   //
		{
			CString err = _item_name+_T("����Ϊ��");
			AfxMessageBox(err);
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
				AfxMessageBox(err);
				return FALSE;
			}
		}
		if(ContainsCharsRemain(_source))
		{
			return FALSE;
		}
		
		int len = _source.GetLength();
		if(len>str_len_max)  //������ݳ���
		{
			CString err;
			err.Format(_T("%s���ݳ��Ȳ��ܳ���%d"),_item_name,str_len_max);
			AfxMessageBox(err);
			return FALSE;
		}
		if(bCheckDateFormat)   //����Ƿ�������ڸ�ʽ
		{
			CString _err2 = _item_name+_T("���������ڸ�ʽ����׼��ʽ�磺2014-10-05");
			CString str = _source;
			int  index = _source.Find('-');
			if(index == -1)   //û�ҵ�
			{
				AfxMessageBox(_err2);
				return FALSE;
			}else{
				CString left = str.Mid(0,index);
				str = str.Mid(index+1);
				if(left.GetLength()!=4)
				{
					AfxMessageBox(_err2);
					return FALSE;
				}else{
					if(!IsNum(left))
					{
						AfxMessageBox(_err2);
						return FALSE;
					}else if(atoi(T2A(left))<2000 ||atoi(T2A(left))>3000){
						CString err3 = _item_name+_T("��ݱ���Ϊ2000��3000֮��");
						AfxMessageBox(err3);
						return FALSE;
					}else{    //ǰ�滹��Ϸ���
						index = str.Find('-');
						if(index == -1)   //û�ҵ�
						{
							AfxMessageBox(_err2);
							return FALSE;
						}else{
							left = str.Mid(0,index);
							str = str.Mid(index+1);
							if(IsNum(left)&&IsNum(str))
							{
								if(atoi(T2A(left))<1||atoi(T2A(left))>12)
								{
									CString err3 = _item_name+_T("�·ݱ���Ϊ1��12֮��");
									AfxMessageBox(err3);
									return FALSE;
								}else if(atoi(T2A(left))<1||atoi(T2A(left))>31)
								{
									CString err3 = _item_name+_T("�����Ϊ1��31֮��");
									AfxMessageBox(err3);
									return FALSE;
								}
							}else{
								AfxMessageBox(_err2);
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

BOOL CPosAdd::ContainsCharsRemain(CString str)     //����ַ����Ƿ�������ַ���
{
	CString temp1 = _T("[#");
	CString temp2 = _T("#]");
	CString temp3 = _T("{#");
	CString temp4 = _T("#}");
	int flag = 0;
	flag = str.Find(temp1);
	if(flag != -1)
	{
		AfxMessageBox(_T("�����в��ܰ�����[#���ַ�"));
		return TRUE;
	}
	flag = str.Find(temp2);
	if(flag != -1)
	{
		AfxMessageBox(_T("�����в��ܰ�����#]���ַ�"));
		return TRUE;
	}
	flag = str.Find(temp3);
	if(flag != -1)
	{
		AfxMessageBox(_T("�����в��ܰ�����#}���ַ�"));
		return TRUE;
	}
	flag = str.Find(temp4);
	if(flag != -1)
	{
		AfxMessageBox(_T("�����в��ܰ�����{#���ַ�"));
		return TRUE;
	}
	return FALSE;
}

BOOL CPosAdd::IsNum(CString str)    //����һ���ַ��� ������Ƿ�Ϊ����
{
	WT;
	char *p = T2A(str);
	int i = 0;
	int count = str.GetLength();
	while(count){
		if(p[i]>'9'||p[i]<'0')
		{
				return FALSE;
		}
		count--;
		i++;
	}
	return TRUE;
}

void CPosAdd::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CSock::m_pPosAdd = NULL;
	CDialogEx::OnClose();
}


void CPosAdd::OnBnClickedBtnCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSock::m_pPosAdd = NULL;
	CDialogEx::OnCancel();
}
