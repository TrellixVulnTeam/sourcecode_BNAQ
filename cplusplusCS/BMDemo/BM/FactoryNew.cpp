// FactoryNew.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "FactoryNew.h"
#include "afxdialogex.h"


// CFactoryNew �Ի���

IMPLEMENT_DYNAMIC(CFactoryNew, CDialogEx)

CFactoryNew::CFactoryNew(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFactoryNew::IDD, pParent)
	, m_addr_fctNew(_T(""))
	, m_contacts_fctNew(_T(""))
	, m_mainProduct_fctNew(_T(""))
	, m_name_fctNew(_T(""))
	, m_phone_fctNew(_T(""))
	, m_ps_fctNew(_T(""))
{

	m_time_take = 0;
}

CFactoryNew::CFactoryNew(CFctSet* pfactorySet,CWnd* pParent)
	: CDialogEx(CFactoryNew::IDD, pParent)
{
	m_pfactorySet = pfactorySet;
	m_time_take = 0;

}
 
CFactoryNew::~CFactoryNew()
{
	m_pfactorySet = NULL;
}

void CFactoryNew::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ADDR_FCTORY_FctNew, m_addr_fctNew);
	DDX_Text(pDX, IDC_EDIT_CONTACTS_FctNew, m_contacts_fctNew);
	DDX_Text(pDX, IDC_EDIT_MAIN_PRODUCT_FctNew, m_mainProduct_fctNew);
	DDX_Text(pDX, IDC_EDIT_NAME_FCTORY_FctNew, m_name_fctNew);
	DDX_Text(pDX, IDC_EDIT_PHONE_FctNew, m_phone_fctNew);
	DDX_Text(pDX, IDC_EDIT_PS_FctNew, m_ps_fctNew);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
}


BEGIN_MESSAGE_MAP(CFactoryNew, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_NEW, &CFactoryNew::OnBnClickedBtnNew)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_MESSAGE(WM_STARTTASK_FctNew, &CFactoryNew::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_FctNew, &CFactoryNew::OnEndTask)
	ON_BN_CLICKED(IDC_BTN_QUIT, &CFactoryNew::OnBnClickedBtnQuit)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CFactoryNew ��Ϣ�������


void CFactoryNew::OnBnClickedBtnNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_addr_fctNew.IsEmpty())
	{
		if(IDYES == MessageBox(_T("���ҵ�ַΪ��,ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO)){
			m_addr_fctNew = _T("��");
		}else
		{
			return;
		}
	}
	if(m_addr_fctNew.GetLength()>100)
	{
		MessageBox(_T("���ҵ�ַ���������ܳ���100���ַ�"));
		return;
	}
	if(m_contacts_fctNew.IsEmpty())
	{
		if(IDYES == MessageBox(_T("������ϵ��Ϊ��,ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO)){
			m_contacts_fctNew = _T("��");
		}else
		{
			return;
		}
	}
	if(m_contacts_fctNew.GetLength()>25)
	{
		MessageBox(_T("������ϵ�˲��ܳ���25���ַ�"));
		return;
	}
	if(m_mainProduct_fctNew.IsEmpty())
	{
		if(IDYES == MessageBox(_T("��Ҫ��ƷΪ��,ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO)){
			m_mainProduct_fctNew = _T("��");
		}else
		{
			return;
		}
	}
	if(m_contacts_fctNew.GetLength()>100)
	{
		MessageBox(_T("������ϵ�˹��࣬���ܳ���100���ַ�"));
		return;
	}
	if(m_name_fctNew.IsEmpty())
	{
		if(IDYES == MessageBox(_T("��������Ϊ��,ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO)){
			m_name_fctNew = _T("��");
		}else
		{
			return;
		}
	}
	if(m_name_fctNew.GetLength()>50)
	{
		MessageBox(_T("�������ֹ��������ܳ���50���ַ�"));
		return;
	}
	if(m_ps_fctNew.IsEmpty())
	{
		if(IDYES == MessageBox(_T("���ұ�עΪ��,ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO)){
			m_ps_fctNew = _T("��");
		}else
		{
			return;
		}
	}
	if(m_ps_fctNew.GetLength()>200)
	{
		MessageBox(_T("���ұ�ע���������ܳ���200���ַ�"));
		return;
	}
	if(m_phone_fctNew.IsEmpty())
	{
		if(IDYES == MessageBox(_T("��ϵ�绰Ϊ��,ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO)){
			m_phone_fctNew = _T("��");
		}else
		{
			return;
		}
	}else{
		if(m_phone_fctNew.GetLength() != 11){
			MessageBox(_T("��ϵ�绰λ������"));
			m_phone_fctNew = _T("��");
			return;
		}else{
			USES_CONVERSION;
			char *p = T2A(m_phone_fctNew);
			for(int i = 0;i<11;i++)
			{
				if(p[i] <'0'||p[i]>'9')
				{
					MessageBox(_T("��ϵ�绰���ܰ�������������������ַ�"));
					m_phone_fctNew = _T("��");
					return;
				}
			}
		}
	}
	CSock::StartReqFctNew(this);
}


HBRUSH CFactoryNew::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CFactoryNew::OnTimer(UINT_PTR nIDEvent)
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

BOOL CFactoryNew::OnInitDialog()
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

void CFactoryNew::ShowTip()
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

afx_msg LRESULT CFactoryNew::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CFactoryNew::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T("����"));
	return 0;
}


void CFactoryNew::OnBnClickedBtnQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CFactoryNew::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CSock::m_pFctNew = NULL;
	CDialogEx::OnClose();
}
