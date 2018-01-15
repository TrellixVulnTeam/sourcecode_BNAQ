// CtmEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "CtmEdit.h"
#include "afxdialogex.h"
#include "CtmInfo.h"

// CCtmEdit �Ի���

IMPLEMENT_DYNAMIC(CCtmEdit, CDialogEx)

CCtmEdit::CCtmEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCtmEdit::IDD, pParent)
	, m_ctmCall(_T(""))
	, m_ctmNM(_T(""))
	, m_ctmNum(0)
	, m_ps(_T(""))
	, m_phone(_T(""))
	, m_times(0)
	, m_timeFirst(_T(""))
	, m_timeLate(_T(""))
{

}

CCtmEdit::CCtmEdit(CCtmInfo* pDlg,CWnd* pParent /*=NULL*/)
	: CDialogEx(CCtmEdit::IDD, pParent)
	, m_ctmCall(_T(""))
	, m_ctmNM(_T(""))
	, m_ctmNum(0)
	, m_ps(_T(""))
	, m_phone(_T(""))
	, m_times(0)
	, m_timeFirst(_T(""))
	, m_timeLate(_T(""))
	
{
	m_pParentDlg = pDlg;
}


CCtmEdit::~CCtmEdit()
{
	m_pParentDlg = NULL;
}

void CCtmEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CTMSEX, m_combSex);
	DDX_Text(pDX, IDC_EDIT_CTMCALL, m_ctmCall);
	DDX_Text(pDX, IDC_EDIT_CTMNM, m_ctmNM);
	DDX_Text(pDX, IDC_EDIT_CTMNO, m_ctmNum);
	DDX_Text(pDX, IDC_EDIT_PS, m_ps);
	DDX_Text(pDX, IDC_EDIT_PRICE, m_price);
	DDX_Text(pDX, IDC_EDIT_PHONENO, m_phone);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
	DDX_Text(pDX, IDC_EDIT_TIMES, m_times);
	DDV_MinMaxInt(pDX, m_times, 0, 100000000);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FIRST_DEAL, m_first_deal);
	DDX_Control(pDX, IDC_DATETIMEPICKER_LATE_DEAL, m_late_deal);
}


BEGIN_MESSAGE_MAP(CCtmEdit, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_SAVE, &CCtmEdit::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_CANCLE, &CCtmEdit::OnBnClickedBtnCancle)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_STARTTASK_CtmEdit, &CCtmEdit::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_CtmEdit, &CCtmEdit::OnEndTask)
END_MESSAGE_MAP()


// CCtmEdit ��Ϣ�������


HBRUSH CCtmEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CCtmEdit::OnBnClickedBtnSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(!IsItemValidity(m_ctmNM,_T("�˿�����"),TRUE,FALSE,FALSE,15,0))
	{
		return;
	}
	if(!IsItemValidity(m_ctmCall,_T("�ͻ�����"),FALSE,FALSE,FALSE,24,0))
	{
		return;
	}
	if(!IsItemValidity(m_phone,_T("�˿͵绰"),FALSE,TRUE,FALSE,11,0))
	{
		return;
	}
	if(!IsItemValidity(m_ps,_T("�ͻ���ע"),FALSE,FALSE,FALSE,150,0))
	{
		return;
	}
	
	if(m_price<0)
	{
		MessageBox(_T("���ѽ���С����"));
		return;
	}

	
	USES_CONVERSION;
	memset(&m_ctmEditStruct,0,sizeof(CtmInfo));
	char *p = NULL;
	CTime timeTime;
	DWORD dwResult = m_first_deal.GetTime(timeTime);
	CString str;
	if (dwResult == GDT_VALID)
	{
		// the user checked the box and specified data
		
		// is it a time-only control, or a date-only control?
		if ((m_first_deal.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}else{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}
		p = T2A(str);
		strcpy_s(m_ctmEditStruct.first_pay_time,p);
	}else
	{
		MessageBox(_T("��ѡ���״�����ʱ��"));
		return;
	}


	dwResult = m_late_deal.GetTime(timeTime);
	if (dwResult == GDT_VALID)
	{
		// the user checked the box and specified data
		
		// is it a time-only control, or a date-only control?
		if ((m_late_deal.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}else{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}
		p = T2A(str);
		strcpy_s(m_ctmEditStruct.late_pay_time,p);
	}else{
		MessageBox(_T("��ѡ���������ʱ��"));
		return;
	}
	CString temp ;

	temp.Format(_T("%d"),m_ctmNum);
	p = T2A(temp);
	strcpy_s(m_ctmEditStruct.NO,p);
	p = T2A(m_ctmCall);
	strcpy_s(m_ctmEditStruct.call_ctm,p);
	p = T2A(m_ctmNM);
	strcpy_s(m_ctmEditStruct.name,p);
	int sel = m_combSex.GetCurSel();
	m_combSex.GetLBText(sel,temp);
	p = T2A(temp);
	strcpy_s(m_ctmEditStruct.sex,p);
	p = T2A(m_phone);
	strcpy_s(m_ctmEditStruct.phone,p);
	temp.Format(_T("%d"),m_times);
	p = T2A(temp);
	strcpy_s(m_ctmEditStruct.pay_times,p);
	temp.Format(_T("%.2f"),m_price);
	p = T2A(temp);
	strcpy_s(m_ctmEditStruct.pay_total,p);
	p = T2A(m_ps);
	strcpy_s(m_ctmEditStruct.ps,p);
	p = T2A(m_timeFirst);
	strcpy_s(m_ctmEditStruct.first_pay_time,p);
	p = T2A(m_timeLate);
	strcpy_s(m_ctmEditStruct.late_pay_time,p);

	CSock::StartReqCtmEdit(this);
}


BOOL CCtmEdit::IsItemValidity(CString _source,CString _item_name,BOOL bCheckEmpty,BOOL bCheckNum,BOOL bCheckDateFormat,int str_len_max,int data_min_len,BOOL bCheckDot)
{
	if(bCheckEmpty)    //TRUE  ������Ҫ����Ƿ�Ϊ�� ������Ϊ��
	{
		if(_source.IsEmpty())   //
		{
			CString err = _item_name+_T("����Ϊ��");
			MessageBox(err);
			return FALSE;
		}
	}
	if(!_source.IsEmpty())
	{
		if(bCheckNum)    //��Ҫ����Ƿ�Ϊ����
		{
			if(!IsNum(_source,bCheckDot))
			{
				CString err = _item_name+_T("����Ϊ����");
				MessageBox(err);
				return FALSE;
			}
		}
		if(ContainsCharsRemain(_source))
		{
			return FALSE;
		}
		

		if(_source.GetLength()>str_len_max)  //������ݳ���
		{
			CString err;
			err.Format(_T("%s���ݳ��Ȳ��ܳ���%d"),_item_name,str_len_max);
			MessageBox(err);
			return FALSE;
		}
		if(_source.GetLength() < data_min_len)  //������ݳ���
		{
			CString err;
			err.Format(_T("%s���ݳ��Ȳ�������%d"),_item_name,data_min_len);
			MessageBox(err);
			return FALSE;
		}
		if(bCheckDateFormat)   //����Ƿ�������ڸ�ʽ
		{
			CString _err2 = _item_name+_T("���������ڸ�ʽ����׼��ʽ�磺2014-10-05");
			CString str = _source;
			int  index = _source.Find('-');
			if(index == -1)   //û�ҵ�
			{
				MessageBox(_err2);
				return FALSE;
			}else{
				CString left = str.Mid(0,index);
				str = str.Mid(index+1);
				if(left.GetLength()!=4)
				{
					MessageBox(_err2);
					return FALSE;
				}else{
					if(!IsNum(left,FALSE))
					{
						MessageBox(_err2);
						return FALSE;
					}else{    //ǰ�滹��Ϸ���
						index = str.Find('-');
						if(index == -1)   //û�ҵ�
						{
							MessageBox(_err2);
							return FALSE;
						}else{
							left = str.Mid(0,index);
							str = str.Mid(index+1);
							if(IsNum(left,FALSE)&&IsNum(str,FALSE))
							{
								return TRUE;
							}else{
								MessageBox(_err2);
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

BOOL CCtmEdit::ContainsCharsRemain(CString str)     //����ַ����Ƿ�������ַ���
{
	CString temp1 = _T("[#");
	CString temp2 = _T("#]");
	CString temp3 = _T("{#");
	CString temp4 = _T("#}");
	int flag = 0;
	flag = str.Find(temp1);
	if(flag != -1)
	{
		MessageBox(_T("�����в��ܰ�����[#���ַ�"));
		return TRUE;
	}
	flag = str.Find(temp2);
	if(flag != -1)
	{
		MessageBox(_T("�����в��ܰ�����#]���ַ�"));
		return TRUE;
	}
	flag = str.Find(temp3);
	if(flag != -1)
	{
		MessageBox(_T("�����в��ܰ�����#}���ַ�"));
		return TRUE;
	}
	flag = str.Find(temp4);
	if(flag != -1)
	{
		MessageBox(_T("�����в��ܰ�����{#���ַ�"));
		return TRUE;
	}
	return FALSE;
}

BOOL CCtmEdit::IsNum(CString str,BOOL bCheckDot)
{
	WT;
	char *p = T2A(str);
	int i = 0;
	int count = str.GetLength();
	while(count){
		if(p[i]>'9'||p[i]<'0')
		{
			if(bCheckDot)
			{
				if(p[i] != '.')
				{
					return FALSE;
				}
			}else
			{
				return FALSE;
			}
		}
		count--;
		i++;
	}
	return TRUE;
}

void CCtmEdit::OnBnClickedBtnCancle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSock::m_pCtmEdit = NULL;
	CDialogEx::OnCancel();
}


void CCtmEdit::OnTimer(UINT_PTR nIDEvent)
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

BOOL CCtmEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	font.Detach();

	LoadCombOfSex();

	LoadDateDeal(m_timeFirst,m_first_deal);
	LoadDateDeal(m_timeLate,m_late_deal);

	return TRUE;
}

void CCtmEdit::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CSock::m_pCtmEdit = NULL;
	CDialogEx::OnClose();
}

void CCtmEdit:: LoadCombOfSex()
{
	
	m_combSex.AddString(_T("��"));
	m_combSex.AddString(_T("Ů"));
	if(_T("��") == m_sexflag)
	{
		m_combSex.SetCurSel(0);
	}else{
		m_combSex.SetCurSel(1);
	}
}

void CCtmEdit::LoadDateDeal(CString _strTime,CDateTimeCtrl &date)
{
	date.SetFormat(_T("yyyy-MM-dd"));
	CString year;
	CString month;
	CString day;
	CString temp = _strTime;
	USES_CONVERSION;
	int index = temp.Find(_T("-"));
	if(index != -1){
		year = temp.Mid(0,index);
		temp = temp.Mid(index+1);
		index = temp.Find(_T("-"));
		if(index != -1){
			month = temp.Mid(0,index);
			day = temp.Mid(index+1);
			CTime  time(atoi(T2A(year)),atoi(T2A(month)),atoi(T2A(day)),0,0,0);
			VERIFY(date.SetTime(&time));
		}else{
			return;
		}
	}else{
		return;
	}
}

void CCtmEdit::ShowTip()
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

afx_msg LRESULT CCtmEdit::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CCtmEdit::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T("����"));
	return 0;
}

