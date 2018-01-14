// CtmNew.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "CtmNew.h"
#include "afxdialogex.h"


// CCtmNew �Ի���

IMPLEMENT_DYNAMIC(CCtmNew, CDialogEx)

CCtmNew::CCtmNew(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCtmNew::IDD, pParent)
	, m_ctmcall(_T(""))
	, m_ctmNM(_T(""))	
	, m_ps(_T(""))
	, m_times(0)
	, m_price(0)
	, m_ctmNO(0)
	, m_phone(_T(""))
{

}

CCtmNew::CCtmNew(CCtmInfo *pdlg,CWnd* pParent /*=NULL*/)
	: CDialogEx(CCtmNew::IDD, pParent)
	, m_ctmcall(_T(""))
	, m_ctmNM(_T(""))	
	, m_price(0)
	, m_ps(_T(""))
	, m_times(0)
	, m_ctmNO(0)
{
	m_pParentDlg = pdlg;
}

CCtmNew::~CCtmNew()
{
	m_pParentDlg = NULL;
}

void CCtmNew::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CTMSEX, m_comboxSex);
	DDX_Control(pDX, IDC_DATE_FIRST, m_dateFist);
	DDX_Control(pDX, IDC_DATE_LAST, m_dateLast);
	DDX_Text(pDX, IDC_EDIT_CTMCALL, m_ctmcall);
	DDX_Text(pDX, IDC_EDIT_CTMNM, m_ctmNM);
	DDX_Text(pDX, IDC_EDIT_PS, m_ps);
	DDX_Text(pDX, IDC_EDIT_TIMES, m_times);
	DDV_MinMaxInt(pDX, m_times, 0, 10000);
	//  DDX_Text(pDX, IDC_EDIT_PRICE, m_price);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
	DDX_Text(pDX, IDC_EDIT_CTMNO, m_ctmNO);
	DDV_MinMaxInt(pDX, m_ctmNO, 0, 100000000);
	DDX_Text(pDX, IDC_EDIT_PHONENO, m_phone);
	DDX_Text(pDX, IDC_EDIT_PRICE, m_price);
}


BEGIN_MESSAGE_MAP(CCtmNew, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_STARTTASK_CtmNew, &CCtmNew::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_CtmNew, &CCtmNew::OnEndTask)
	ON_BN_CLICKED(IDC_BTN_CANCLE, &CCtmNew::OnBnClickedBtnCancle)
	ON_BN_CLICKED(IDC_BTN_NEW, &CCtmNew::OnBnClickedBtnNew)
END_MESSAGE_MAP()


// CCtmNew ��Ϣ�������


HBRUSH CCtmNew::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CCtmNew::OnTimer(UINT_PTR nIDEvent)
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


void CCtmNew::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CSock::m_pCtmNew = NULL;
	CDialogEx::OnClose();
}


afx_msg LRESULT CCtmNew::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}

void CCtmNew::ShowTip()
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

afx_msg LRESULT CCtmNew::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T("����"));
	return 0;
}



void CCtmNew::OnBnClickedBtnCancle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CCtmNew::OnBnClickedBtnNew()
{
	UpdateData(TRUE);
	if(!IsItemValidity(m_ctmNM,_T("�˿�����"),TRUE,FALSE,FALSE,15,0))
	{
		return;
	}
	if(!IsItemValidity(m_ctmcall,_T("�ͻ�����"),FALSE,FALSE,FALSE,24,0))
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
	memset(&m_ctmNewStruct,0,sizeof(CtmInfo));
	char *p = NULL;
	CTime timeTime;
	DWORD dwResult = m_dateFist.GetTime(timeTime);
	CString str;
	if (dwResult == GDT_VALID)
	{
		if ((m_dateFist.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}else{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}
		p = T2A(str);
		strcpy_s(m_ctmNewStruct.first_pay_time,p);
	}else
	{
		MessageBox(_T("��ѡ���״�����ʱ��"));
		return;
	}


	dwResult = m_dateLast.GetTime(timeTime);
	if (dwResult == GDT_VALID)
	{
		if ((m_dateLast.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}else{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}
		p = T2A(str);
		strcpy_s(m_ctmNewStruct.late_pay_time,p);
	}else{
		MessageBox(_T("��ѡ���������ʱ��"));
		return;
	}

	CString temp ;
	temp.Format(_T("%d"),m_ctmNO);
	p = T2A(temp);
	strcpy_s(m_ctmNewStruct.NO,p);
	p = T2A(m_ctmcall);
	strcpy_s(m_ctmNewStruct.call_ctm,p);
	p = T2A(m_ctmNM);
	strcpy_s(m_ctmNewStruct.name,p);
	int sel = m_comboxSex.GetCurSel();
	m_comboxSex.GetLBText(sel,temp);
	p = T2A(temp);
	strcpy_s(m_ctmNewStruct.sex,p);
	p = T2A(m_phone);
	strcpy_s(m_ctmNewStruct.phone,p);
	temp.Format(_T("%d"),m_times);
	p = T2A(temp);
	strcpy_s(m_ctmNewStruct.pay_times,p);
	temp.Format(_T("%.2f"),m_price);
	p = T2A(temp);
	strcpy_s(m_ctmNewStruct.pay_total,p);
	p = T2A(m_ps);
	strcpy_s(m_ctmNewStruct.ps,p);

	CSock::StartReqCtmNew(this);
}

BOOL CCtmNew::IsItemValidity(CString _source,CString _item_name,BOOL bCheckEmpty,BOOL bCheckNum,BOOL bCheckDateFormat,int str_len_max,int data_min_len,BOOL bCheckDot)
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

BOOL CCtmNew::ContainsCharsRemain(CString str)     //����ַ����Ƿ�������ַ���
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

BOOL CCtmNew::IsNum(CString str,BOOL bCheckDot)
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


BOOL  CCtmNew::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	font.Detach();

	InitCombSex();

	m_dateFist.SetFormat(_T("yyyy-MM-dd"));
	m_dateLast.SetFormat(_T("yyyy-MM-dd"));
	return TRUE;
}

void CCtmNew::InitCombSex()
{
	m_comboxSex.AddString(_T("��"));
	m_comboxSex.AddString(_T("Ů"));
	m_comboxSex.SetCurSel(0);
}