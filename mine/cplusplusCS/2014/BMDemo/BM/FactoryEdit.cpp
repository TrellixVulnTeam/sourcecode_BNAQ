// FactoryEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "FactoryEdit.h"
#include "afxdialogex.h"


// CFactoryEdit �Ի���

IMPLEMENT_DYNAMIC(CFactoryEdit, CDialogEx)

CFactoryEdit::CFactoryEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFactoryEdit::IDD, pParent)
{

}

CFactoryEdit::CFactoryEdit(CFctSet* pFactorySet,CWnd* pParent)
	: CDialogEx(CFactoryEdit::IDD, pParent)
	, m_addr_fctEdit(_T(""))
	, m_contact_person_fctEdit(_T(""))
	, m_main_product_fctEdit(_T(""))
	, m_name_fctEdit(_T(""))
	, m_phone_fctEdit(_T(""))
	, m_ps_fctEdit(_T(""))
{
	m_pFactorySet = pFactorySet;
}


CFactoryEdit::~CFactoryEdit()
{
	m_pFactorySet = NULL;
}

void CFactoryEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_ADDR_FCT, m_addr_fct);
	//  DDX_Text(pDX, IDC_EDIT_CONTACT_PERSON_FCT, m_contact_person_fct);
	//  DDX_Text(pDX, IDC_EDIT_MAIN_PRODUCT_FCT, m_main_product);
	DDX_Text(pDX, IDC_EDIT_MAIN_PRODUCT_FCT, m_main_product_fctEdit);
	DDX_Text(pDX, IDC_EDIT_NAME_FCT, m_name_fctEdit);
	DDX_Text(pDX, IDC_EDIT_PHONE_FCT, m_phone_fctEdit);
	DDX_Text(pDX, IDC_EDIT_PS_FCT, m_ps_fctEdit);
	DDX_Text(pDX, IDC_EDIT_ADDR_FCT, m_addr_fctEdit);
	DDX_Text(pDX, IDC_EDIT_CONTACT_PERSON_FCT, m_contact_person_fctEdit);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
}


BEGIN_MESSAGE_MAP(CFactoryEdit, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_STARTTASK_FctEdit, &CFactoryEdit::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_FctEdit, &CFactoryEdit::OnEndTask)
	ON_BN_CLICKED(IDC_BTN_QUIT, &CFactoryEdit::OnBnClickedBtnQuit)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CFactoryEdit::OnBnClickedBtnSave)
END_MESSAGE_MAP()


// CFactoryEdit ��Ϣ�������


HBRUSH CFactoryEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CFactoryEdit::OnTimer(UINT_PTR nIDEvent)
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

void CFactoryEdit::ShowTip()
{
	m_time_take++;
	CString tip;
	tip.Format(_T("��ʱ��%d��"),m_time_take);
	m_tip.SetWindowText(tip);
	if(m_time_take == 60)
	{
		OnEndTask(0,0);
		m_tip.SetWindowText(_T("����ʱ�������������������״̬������"));
	}
}

void CFactoryEdit::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CSock::m_pFactoryEdit = NULL;
	CDialogEx::OnClose();
}


afx_msg LRESULT CFactoryEdit::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CFactoryEdit::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


void CFactoryEdit::OnBnClickedBtnQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CFactoryEdit::OnBnClickedBtnSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_addr_fctEdit.IsEmpty())
	{
		if(IDYES == MessageBox(_T("���ҵ�ַΪ��,ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO)){
			m_addr_fctEdit = _T("��");
		}else
		{
			return;
		}
	}
	if(m_addr_fctEdit.GetLength()>100)
	{
		MessageBox(_T("���ҵ�ַ���������ܳ���100���ַ�"));
		return;
	}
	if(m_contact_person_fctEdit.IsEmpty())
	{
		if(IDYES == MessageBox(_T("������ϵ��Ϊ��,ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO)){
			m_contact_person_fctEdit = _T("��");
		}else
		{
			return;
		}
	}
	if(m_contact_person_fctEdit.GetLength()>25)
	{
		MessageBox(_T("������ϵ�˲��ܳ���25���ַ�"));
		return;
	}
	if(m_main_product_fctEdit.IsEmpty())
	{
		if(IDYES == MessageBox(_T("��Ҫ��ƷΪ��,ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO)){
			m_main_product_fctEdit = _T("��");
		}else
		{
			return;
		}
	}
	if(m_main_product_fctEdit.GetLength()>100)
	{
		MessageBox(_T("������ϵ�˲��ܳ���100���ַ�"));
		return;
	}
	if(m_ps_fctEdit.IsEmpty())
	{
		if(IDYES == MessageBox(_T("���ұ�עΪ��,ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO)){
			m_ps_fctEdit = _T("��");
		}else
		{
			return;
		}
	}
	if(m_ps_fctEdit.GetLength()>200)
	{
		MessageBox(_T("���ұ�ע���������ܳ���200���ַ�"));
		return;
	}
	if(m_phone_fctEdit.IsEmpty())
	{
		if(IDYES == MessageBox(_T("��ϵ�绰Ϊ��,ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO)){
			m_phone_fctEdit = _T("��");
		}else
		{
			return;
		}
	}else{
		if(m_phone_fctEdit.GetLength() != 11){
			MessageBox(_T("��ϵ�绰λ������"));
			m_phone_fctEdit = _T("��");
			return;
		}else{
			USES_CONVERSION;
			char *p = T2A(m_phone_fctEdit);
			for(int i = 0;i<11;i++)
			{
				if(p[i] <'0'||p[i]>'9')
				{
					MessageBox(_T("��ϵ�绰���ܰ�������������������ַ�"));
					m_phone_fctEdit = _T("��");
					return;
				}
			}
		}
	}
	CSock::StartReqFctEdit(this);
}


BOOL CFactoryEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	font.Detach();
	return TRUE;
}