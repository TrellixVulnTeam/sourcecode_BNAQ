// StoreOut.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "StoreOut.h"
#include "afxdialogex.h"


// CStoreOut �Ի���

IMPLEMENT_DYNAMIC(CStoreOut, CDialogEx)

CStoreOut::CStoreOut(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStoreOut::IDD, pParent)
	, m_numOut(0)
	, m_name_goods(_T(""))
{

}

CStoreOut::~CStoreOut()
{
}

void CStoreOut::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT_IDENTIFY, m_id);
	DDX_Text(pDX, IDC_EDIT_NUM_OUT, m_numOut);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
	DDV_MinMaxInt(pDX, m_numOut, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_IDENTIFY, m_name_goods);
}


BEGIN_MESSAGE_MAP(CStoreOut, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_STARTTASK_StoreOut, &CStoreOut::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_StoreOut, &CStoreOut::OnEndTask)
	ON_BN_CLICKED(IDC_BTN_STORE_OUT, &CStoreOut::OnBnClickedBtnStoreOut)
	ON_BN_CLICKED(IDC_BTN_CANCLE, &CStoreOut::OnBnClickedBtnCancle)
END_MESSAGE_MAP()


// CStoreOut ��Ϣ�������


HBRUSH CStoreOut::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CStoreOut::OnTimer(UINT_PTR nIDEvent)
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

void CStoreOut::ShowTip()
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

void CStoreOut::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CSock::m_pStoreOut = NULL;
	CDialogEx::OnClose();
}

BOOL CStoreOut::OnInitDialog()
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

afx_msg LRESULT CStoreOut::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CStoreOut::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T("����"));
	return 0;
}


void CStoreOut::OnBnClickedBtnStoreOut()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_name_goods.IsEmpty())
	{
		MessageBox(_T("�����Ʒ���Ʋ���Ϊ��"));
		return ;
	}
	if(m_name_goods.GetLength()>25)
	{
		MessageBox(_T("�����Ʒ���Ƴ��Ȳ��ܴ���25���ַ�"));
		return ;
	}
	if(m_name_goods.IsEmpty())
	{
		MessageBox(_T("�����Ʒ�䶯��������Ϊ��"));
		return ;
	}
	USES_CONVERSION;
	memset(&m_goods_out_struct,0,sizeof(m_goods_out_struct));
	char *p = T2A(m_name_goods);
	strcpy_s(m_goods_out_struct.Store_Name,p);
	CString num = NULL;
	num.Format(_T("%d"),m_numOut);
	p = T2A(num);
	strcpy_s(m_goods_out_struct.Store_Num,p);
	CSock::StartReqStoreOut(this);
}


void CStoreOut::OnBnClickedBtnCancle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
