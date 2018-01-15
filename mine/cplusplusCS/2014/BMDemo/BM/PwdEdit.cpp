// PwdEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "PwdEdit.h"
#include "afxdialogex.h"


// CPwdEdit �Ի���

IMPLEMENT_DYNAMIC(CPwdEdit, CDialogEx)

CPwdEdit::CPwdEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPwdEdit::IDD, pParent)
	, m_password(_T(""))
	, m_psw_new(_T(""))
	, m_psw_confirm(_T(""))
{

}

CPwdEdit::~CPwdEdit()
{
}

void CPwdEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO_LOGIN_POS, m_pos);
	//DDX_Control(pDX, IDC_COMBO_LOGIN_USERNAME, m_username);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDX_Text(pDX, IDC_EDIT_PSWNEW, m_psw_new);
	DDX_Text(pDX, IDC_EDIT_PSWNEW_CONFIRM, m_psw_confirm);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
}


BEGIN_MESSAGE_MAP(CPwdEdit, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPwdEdit::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDCANCEL, &CPwdEdit::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_STARTTASK_PwdEdit, &CPwdEdit::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_PwdEdit, &CPwdEdit::OnEndTask)
END_MESSAGE_MAP()


// CPwdEdit ��Ϣ�������



BOOL CPwdEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HICON hIcon=AfxGetApp()->LoadIcon(IDI_ICON_BMMAIN);
	
	this->SetIcon(hIcon,TRUE);
	this->SetIcon(hIcon,FALSE);
	InitTipCtrl();
	//InitComb();

	return TRUE;
}


HBRUSH CPwdEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CPwdEdit::InitTipCtrl()
{
	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	font.Detach();
}

/*
void CPwdEdit::InitComb()
{
	WT;
	m_pos.AddString(_T("ϵͳ����Ա"));
	m_pos.AddString(_T("�ܾ���"));
	m_pos.AddString(_T("�ͻ�����"));
	m_pos.AddString(_T("���ʦ"));
	m_pos.AddString(_T("��ͨԱ��"));

	int index = m_pos.FindStringExact(0,CSock::m_user_pos);
	if(index != CB_ERR)
	{
		m_pos.SetCurSel(index);
	}else{
		m_pos.SetCurSel(0);
	}

	m_username.AddString(CSock::m_nameOnline);
	m_username.SetCurSel(0);
}*/

void CPwdEdit::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSock::m_pPwdEdit = NULL;
	CDialogEx::OnCancel();
}


void CPwdEdit::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_password.IsEmpty())
	{
		MessageBox(_T("ԭ���벻��Ϊ��"));
		return ;
	}else if(m_password.GetLength()>13){
		MessageBox(_T("ԭ���벻�ܳ���13���ַ�������������"));
		m_password = _T("");
		UpdateData(FALSE);
		return ;
	}else if(m_password.GetLength()<6)
	{
		MessageBox(_T("ԭ���벻������6���ַ�������������"));
		m_password = _T("");
		UpdateData(FALSE);
		return ;
	}else{
		int index = m_password.Find(',');
		if(index != -1)
		{
			MessageBox(_T("ԭ�����в��ܺ���','���ַ�������������"));
			m_password = _T("");
			UpdateData(FALSE);
			return ;
		}
	}


	if(m_psw_new.IsEmpty())
	{
		MessageBox(_T("�����벻��Ϊ��"));
		return ;
	}else if(m_psw_new == m_password){
		MessageBox(_T("�������ԭ���벻��һ��������������"));
		m_psw_new = _T("");
		UpdateData(FALSE);
		return ;
	}else if(m_psw_new != m_psw_confirm){
		MessageBox(_T("�����������ȷ�ϲ�һ��������������"));
		m_psw_confirm = _T("");
		UpdateData(FALSE);
		return ;
	}else if(m_psw_new.GetLength()>13){
		MessageBox(_T("�����벻�ܳ���13���ַ�������������"));
		m_psw_new = _T("");
		UpdateData(FALSE);
		return ;
	}else if(m_psw_new.GetLength()<6)
	{
		MessageBox(_T("�����벻������6���ַ�������������"));
		m_psw_new = _T("");
		UpdateData(FALSE);
		return ;
	}else{
		int index = m_psw_new.Find(',');
		if(index != -1)
		{
			MessageBox(_T("�������в��ܺ���','���ַ�������������"));
			m_psw_new = _T("");
			UpdateData(FALSE);
			return ;
		}
	}

	m_strPswEdit = CSock::m_nameOnline + _T(",") + m_password + _T(",") + m_psw_new;
	CSock::StartReqPswEdit(this);
}



void CPwdEdit::OnTimer(UINT_PTR nIDEvent)
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


void CPwdEdit::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CSock::m_pPwdEdit = NULL;
	CDialogEx::OnClose();
}

void CPwdEdit::ShowTip()
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

afx_msg LRESULT CPwdEdit::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CPwdEdit::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}
