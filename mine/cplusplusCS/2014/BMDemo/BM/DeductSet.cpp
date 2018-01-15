// DeductSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "DeductSet.h"
#include "afxdialogex.h"


// CDeductSet �Ի���

IMPLEMENT_DYNAMIC(CDeductSet, CDialogEx)

CDeductSet::CDeductSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDeductSet::IDD, pParent)
	, m_has_inner_modify(0)
	, m_measure(0)
	, m_exact_test_person(0)
	, m_emp(0)
	, m_discuss_deal_person(0)
	, m_decorate_company(0)
	, m_no_inner_modify(0)
{

}

CDeductSet::~CDeductSet()
{
}

void CDeductSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
	DDX_Text(pDX, IDC_EDIT_DECORATE_COMPANY, m_decorate_company);
	DDX_Text(pDX, IDC_EDIT_DISCUSS_DEAL_PERSON, m_discuss_deal_person);
	DDX_Text(pDX, IDC_EDIT_EMP, m_emp);
	DDX_Text(pDX, IDC_EDIT_EXACT_TEST_PERSON, m_exact_test_person);
	DDX_Text(pDX, IDC_EDIT_HAS_INNER_MODIFY_DESIGN, m_has_inner_modify);
	DDX_Text(pDX, IDC_EDIT_MEASURE, m_measure);
	DDX_Text(pDX, IDC_EDIT_NO_INNER_MODIFY_DESIGN, m_no_inner_modify);
}


BEGIN_MESSAGE_MAP(CDeductSet, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_STARTTASK_DeductSet, &CDeductSet::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_DeductSet, &CDeductSet::OnEndTask)
	ON_MESSAGE(WM_LOADSETOVER_DeductSet, &CDeductSet::OnLoadSetOver)
	
	ON_BN_CLICKED(IDC_BTN_SAVE, &CDeductSet::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_CANCAL, &CDeductSet::OnBnClickedBtnCancal)
END_MESSAGE_MAP()


// CDeductSet ��Ϣ�������


HBRUSH CDeductSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CDeductSet::OnTimer(UINT_PTR nIDEvent)
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

void CDeductSet::ShowTip()
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

void CDeductSet::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CSock::m_pDeductSet = NULL;
	CDialogEx::OnClose();
}


afx_msg LRESULT CDeductSet::OnLoadSetOver(WPARAM wParam, LPARAM lParam)
{
	WT;
	m_decorate_company = atof(m_deductInfo.decorate_company);
	m_discuss_deal_person = atof(m_deductInfo.discuss_deal_person);
	m_emp = atof(m_deductInfo.emp);
	m_exact_test_person = atof(m_deductInfo.exact_test_person);
	m_has_inner_modify = atof(m_deductInfo.has_inner_modify);
	m_measure = atof(m_deductInfo.measure);
	m_no_inner_modify = atof(m_deductInfo.no_inner_modify);
	UpdateData(FALSE);
	return 0;
}

afx_msg LRESULT CDeductSet::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CDeductSet::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	KillTimer(1);
	return 0;
}

BOOL CDeductSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InitTipCtrl();
	memset(&m_deductInfo,0,sizeof(m_deductInfo));
	CSock::StartReqInitDeduct(this);
	return TRUE;
}

void CDeductSet::InitTipCtrl()
{
	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	font.Detach();
}

void CDeductSet::OnBnClickedBtnSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	WT;
	UpdateData(TRUE);
	memset(&m_deductInfo,0,sizeof(m_deductInfo));
	/*
	double total = m_decorate_company + m_discuss_deal_person + m_emp + m_exact_test_person + m_has_inner_modify + m_measure + m_no_inner_modify;
	if(total != 100)
	{
		MessageBox(_T("�ٷֱ��ܺ�Ӧ����100%,����������"));
		return ;
	}*/
	CString temp;
	temp.Format(_T("%.2f"),m_decorate_company);
	strcpy_s(m_deductInfo.decorate_company,T2A(temp));
	temp.Format(_T("%.2f"),m_discuss_deal_person);
	strcpy_s(m_deductInfo.discuss_deal_person,T2A(temp));
	temp.Format(_T("%.2f"),m_emp);
	strcpy_s(m_deductInfo.emp,T2A(temp));
	temp.Format(_T("%.2f"),m_exact_test_person);
	strcpy_s(m_deductInfo.exact_test_person,T2A(temp));
	temp.Format(_T("%.2f"),m_has_inner_modify);
	strcpy_s(m_deductInfo.has_inner_modify,T2A(temp));
	temp.Format(_T("%.2f"),m_measure);
	strcpy_s(m_deductInfo.measure,T2A(temp));
	temp.Format(_T("%.2f"),m_no_inner_modify);
	strcpy_s(m_deductInfo.no_inner_modify,T2A(temp));

	CSock::StartReqSetDeduct(this);
}


void CDeductSet::OnBnClickedBtnCancal()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSock::m_pDeductSet = NULL;
	CDialogEx::OnCancel();
}
