// StoreAdd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "StoreAdd.h"
#include "afxdialogex.h"


// CStoreAdd �Ի���

IMPLEMENT_DYNAMIC(CStoreAdd, CDialogEx)

CStoreAdd::CStoreAdd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStoreAdd::IDD, pParent)
	, m_name_store(_T(""))
	, m_num_add(_T(""))
	, m_num_alert(_T(""))
{

}

CStoreAdd::~CStoreAdd()
{
}

void CStoreAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IDENTIFY, m_name_store);
	DDX_Text(pDX, IDC_EDIT_NUMADD, m_num_add);
	DDX_Text(pDX, IDC_EDIT_NUMALERT, m_num_alert);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
}


BEGIN_MESSAGE_MAP(CStoreAdd, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_CANCLE, &CStoreAdd::OnBnClickedBtnCancle)
	ON_BN_CLICKED(IDC_BTN_STOREADD, &CStoreAdd::OnBnClickedBtnStoreadd)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_STARTTASK_StoreAdd, &CStoreAdd::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_StoreAdd, &CStoreAdd::OnEndTask)
END_MESSAGE_MAP()


// CStoreAdd ��Ϣ�������


HBRUSH CStoreAdd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CStoreAdd::OnBnClickedBtnCancle()
{
	CDialogEx::OnCancel();
}


void CStoreAdd::OnBnClickedBtnStoreadd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_name_store.IsEmpty())
	{
		MessageBox(_T("�����Ʒ���Ʋ���Ϊ��"));
		return ;
	}
	if(m_name_store.GetLength()>25)
	{
		MessageBox(_T("�����Ʒ���Ƴ��Ȳ��ܴ���25���ַ�"));
		return ;
	}
	if(m_num_add.IsEmpty())
	{
		MessageBox(_T("�����Ʒ�䶯��������Ϊ��"));
		return ;
	}
	if(m_num_add.GetLength()>18)
	{
		MessageBox(_T("�����Ʒ�䶯�������Ȳ��ܳ���18���ַ�"));
		return ;
	}
	USES_CONVERSION;
	char *p = T2A(m_num_add);
	int len = m_num_add.GetLength();
	for(int i = 0;i < len;i++)
	{
		if(p[i] <'0'||p[i]>'9')
		{
			MessageBox(_T("�����Ʒ�䶯��������Ϊ����"));
			return;
		}
	}
	if(m_num_alert.IsEmpty())
	{
		if(IDYES == MessageBox(_T("�����ƷԤ������Ϊ�գ�ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO))
		{
			m_num_alert = _T("0");
		}else{
			return ;
		}
	}else if(m_num_alert.GetLength()>18)
	{
		MessageBox(_T("�����ƷԤ���������Ȳ��ܳ���18���ַ�"));
		return ;
	}else{
		p = T2A(m_num_alert);
		int len = m_num_alert.GetLength();
		for(int i = 0;i < len;i++)
		{
			if(p[i] <'0'||p[i]>'9')
			{
				MessageBox(_T("�����ƷԤ����������Ϊ����"));
				return;
			}
		}
	}
	p = T2A(m_name_store);
	strcpy_s(m_storeAddStruct.Store_Name,p);
	p = T2A(m_num_add);
	strcpy_s(m_storeAddStruct.Store_Num,p);
	p = T2A(m_num_alert);
	strcpy_s(m_storeAddStruct.Store_Alert_NUM,p);

	CSock::StartReqStoreAdd(this);
}


void CStoreAdd::OnTimer(UINT_PTR nIDEvent)
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

void CStoreAdd::ShowTip()
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

BOOL CStoreAdd::OnInitDialog()
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

void CStoreAdd::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CSock::m_pStoreAdd = NULL;
	CDialogEx::OnClose();
}


afx_msg LRESULT CStoreAdd::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CStoreAdd::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T("����"));
	return 0;
}
