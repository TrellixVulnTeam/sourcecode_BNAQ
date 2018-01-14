// ServModify.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "ServModify.h"
#include "afxdialogex.h"


// CServModify �Ի���

IMPLEMENT_DYNAMIC(CServModify, CDialogEx)

CServModify::CServModify(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServModify::IDD, pParent)
	, m_addr(_T(""))
	, m_charge(0)
	, m_clientNM(_T(""))
	, m_ctmNM(_T(""))
	, m_phone(_T(""))
	, m_ps(_T(""))
	, m_servContent(_T(""))
	, m_servNM(_T(""))
	, m_servNO(_T(""))
	, m_servPhone(_T(""))
	, m_servType(_T(""))
{

}

CServModify::~CServModify()
{
}

void CServModify::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CTM_SEX, m_ctmSex);
	DDX_Control(pDX, IDC_COMBO_CTM_TYPE, m_ctmType);
	DDX_Control(pDX, IDC_COMBO_PROG, m_prog);
	DDX_Control(pDX, IDC_DATETIME_DELAY, m_dateDelay);
	DDX_Control(pDX, IDC_DATETIME_REQ, m_dateReq);
	DDX_Text(pDX, IDC_EDIT_ADDR, m_addr);
	DDX_Text(pDX, IDC_EDIT_CHARGE, m_charge);
	DDX_Text(pDX, IDC_EDIT_CLIENT_NM, m_clientNM);
	DDX_Text(pDX, IDC_EDIT_CTM_NM, m_ctmNM);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_phone);
	DDX_Text(pDX, IDC_EDIT_PS, m_ps);
	DDX_Text(pDX, IDC_EDIT_SERV_CONTENT, m_servContent);
	DDX_Text(pDX, IDC_EDIT_SERV_NM, m_servNM);
	DDX_Text(pDX, IDC_EDIT_SERV_NO, m_servNO);
	DDX_Text(pDX, IDC_EDIT_SERV_PHONE, m_servPhone);
	DDX_Text(pDX, IDC_EDIT_SERV_TYPE, m_servType);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
}


BEGIN_MESSAGE_MAP(CServModify, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_STARTTASK_ServModify, &CServModify::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_ServModify, &CServModify::OnEndTask)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CServModify::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CServModify::OnBnClickedBtnSave)
END_MESSAGE_MAP()


// CServModify ��Ϣ�������


HBRUSH CServModify::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

BOOL CServModify::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InitTipCtrl();
	InitComb();

	m_dateDelay.SetFormat(_T("yyyy-MM-dd"));
	m_dateReq.SetFormat(_T("yyyy-MM-dd"));
	LoadDate(m_strDateReq,m_dateReq);
	LoadDate(m_strDateDelay,m_dateDelay);
	return TRUE;
}

void CServModify::OnTimer(UINT_PTR nIDEvent)
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

void CServModify::InitComb()
{
	//�Ա�������Ͽ�
	m_ctmSex.AddString(_T("��"));
	m_ctmSex.AddString(_T("Ů"));
	if(_T("��") == m_strCtmSex)
	{
		m_ctmSex.SetCurSel(0);
	}else{
		m_ctmSex.SetCurSel(1);
	}
	CString         m_strCtmType;
	CString         m_strProg;
	//�ͻ�������Ͽ�
	m_ctmType.AddString(_T("�Ͽͻ�����"));
	m_ctmType.AddString(_T("�Ͽͻ����ζ���"));
	m_ctmType.AddString(_T("�¿ͻ�"));
	m_ctmType.AddString(_T("װ�깫˾����"));
	m_ctmType.AddString(_T("ҵ��Ա�ܵ�"));
	if(!m_strCtmType.IsEmpty())
	{
		int index = m_ctmType.FindStringExact(0,m_strCtmType);
		if(index != CB_ERR)
		{
			m_ctmType.SetCurSel(index);
		}else{
			m_ctmType.SetCurSel(2);
		}
	}else{
		m_ctmType.SetCurSel(2);
	}
	//������
	m_prog.AddString(_T("ԤԼ"));
	m_prog.AddString(_T("���"));
	m_prog.AddString(_T("����"));
	if(!m_strProg.IsEmpty())
	{
		int index = m_ctmType.FindStringExact(0,m_strProg);
		if(index != CB_ERR)
		{
			m_prog.SetCurSel(index);
		}else{
			m_prog.SetCurSel(0);
		}
	}else{
		m_prog.SetCurSel(0);
	}
}

void CServModify::LoadDate(CString _strTime,CDateTimeCtrl &date)
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

void CServModify::InitTipCtrl()
{
	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	font.Detach();
}
void CServModify::ShowTip()
{
	m_time_take++;
	CString time = NULL;
	time.Format(_T("��ʱ��%d��"),m_time_take);
	m_tip.SetWindowText(time);
	if(m_time_take == 120)
	{
		OnEndTask(0,0);
		m_tip.SetWindowText(_T("����ʱ�������Ի����������ӷ�����"));
	}
}

void CServModify::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CSock::m_pServModify = NULL;
	CDialogEx::OnClose();
}


afx_msg LRESULT CServModify::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CServModify::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T("����"));
	return 0;
}


void CServModify::OnBnClickedBtnCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CServModify::OnBnClickedBtnSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	USES_CONVERSION;
	char *p = NULL;
	memset(&m_servInfo_struct,0,sizeof(m_servInfo_struct));
	if(m_servNO.IsEmpty())
	{
		MessageBox(_T("���񵥺Ų���Ϊ��"));
		return ;
	}else if(m_servNO.GetLength() > 10)
	{
		MessageBox(_T("���񵥺ų��Ȳ��ܴ���10���ַ�"));
		return ;
	}else {
		p = T2A(m_servNO);
		int len = m_servNO.GetLength();
		for(int i = 0;i < len;i++)
		{
			if(p[i] <'0'||p[i]>'9')
			{
				MessageBox(_T("���񵥺ű���Ϊ����"));
				return;
			}
		}
	}
	if(m_ctmNM.IsEmpty())
	{
		MessageBox(_T("�ͻ����Ʋ���Ϊ��"));
		return ;
	}else if(m_ctmNM.GetLength()>15)
	{
		MessageBox(_T("�ͻ����Ʋ��ܳ���15���ַ�"));
		return;
	}

	if(m_clientNM.IsEmpty())
	{
		MessageBox(_T("�˿���������Ϊ��"));
		return ;
	}else if(m_clientNM.GetLength()>15)
	{
		MessageBox(_T("�˿��������ܳ���15���ַ�"));
		return;
	}

	if(m_phone.IsEmpty())
	{
		if(IDYES == MessageBox(_T("�˿͵绰Ϊ�գ�ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO))
		{
			m_phone = _T("");
		}else{
			return ;
		}
	}else {
		p = T2A(m_phone);
		int len = m_phone.GetLength();
		if(len>11){
			MessageBox(_T("�˿͵绰���ܳ���11���ַ�"));
			return;
		}
		for(int i = 0; i<len;i++)
		{
			if(p[i] < '0'||p[i] >'9')
			{
				MessageBox(_T("�˿͵绰����Ϊ����"));
				return;
			}
		}
	}

	if(m_addr.IsEmpty())
	{
		if(IDYES == MessageBox(_T("��ַΪ�գ�ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO))
		{
			m_addr = _T("");
		}else{
			return ;
		}
	}else if(m_addr.GetLength()>25){
		MessageBox(_T("��ַ���ܳ���25���ַ�"));
		return;
	}

	if(m_servContent.IsEmpty())
	{
		if(IDYES == MessageBox(_T("��������Ϊ�գ�ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO))
		{
			m_servContent = _T("");
		}else{
			return ;
		}
	}else if(m_servContent.GetLength()>30)
	{
		MessageBox(_T("�������ݲ��ܳ���30���ַ�"));
		return;
	}
	if(m_servNM.IsEmpty())
	{
		if(IDYES == MessageBox(_T("������Ա����Ϊ�գ�ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO))
		{
			m_servNM = _T("");
		}else{
			return ;
		}
	}else if(m_servNM.GetLength()>10)
	{
		MessageBox(_T("������Ա�������ܳ���10���ַ�"));
		return;
	}
	if(m_ps.IsEmpty())
	{
		if(IDYES == MessageBox(_T("��עΪ�գ�ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO))
		{
			m_ps = _T("");
		}else{
			return ;
		}
	}else if(m_ps.GetLength()>100)
	{
		MessageBox(_T("��ע���ܳ���100���ַ�"));
		return;
	}
	if(m_servType.IsEmpty())
	{
		if(IDYES == MessageBox(_T("��������Ϊ�գ�ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO))
		{
			m_servType = _T("");
		}else{
			return ;
		}
	}else if(m_servType.GetLength()>15)
	{
		MessageBox(_T("��ע���ܳ���15���ַ�"));
		return;
	}
	
	if(m_servPhone.IsEmpty())
	{
		if(IDYES == MessageBox(_T("������Ա�绰Ϊ�գ�ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO))
		{
			m_servPhone = _T("");
		}else{
			return ;
		}
	}else{
		p = T2A(m_servPhone);
		int len = m_servPhone.GetLength();
		if(len>11){
			MessageBox(_T("������Ա�绰���ܳ���11���ַ�"));
			return;
		}
		for(int i = 0; i<len;i++)
		{
			if(p[i] < '0'||p[i] >'9')
			{
				MessageBox(_T("������Ա�绰����Ϊ����"));
				return;
			}
		}
	}

	if(m_addr.IsEmpty())
	{
		if(IDYES == MessageBox(_T("��ַΪ�գ�ȷ�ϼ�����"),_T("��ʾ"),MB_YESNO))
		{
			m_addr = _T("");
		}else{
			return ;
		}
	}else if(m_addr.GetLength()>25)
	{
		MessageBox(_T("�����ַ���ܳ���25���ַ�"));
		return;
	}
	p = T2A(m_servNO);
	strcpy_s(m_servInfo_struct.serv_NO,p);
	CString ctmType = NULL;
	m_ctmType.GetWindowText(ctmType);
	p = T2A(ctmType);
	strcpy_s(m_servInfo_struct.client_type,p);
	p = T2A(m_ctmNM);
	strcpy_s(m_servInfo_struct.ctm_name,p);
	p = T2A(m_clientNM);
	strcpy_s(m_servInfo_struct.client_name,p);
	CString sex = NULL;
	m_ctmSex.GetWindowText(sex);
	p = T2A(sex);
	strcpy_s(m_servInfo_struct.ctm_sex,p);
	p = T2A(m_phone);
	strcpy_s(m_servInfo_struct.client_phone,p);
	p = T2A(m_addr);
	strcpy_s(m_servInfo_struct.addr,p);
	p = T2A(m_ps);
	strcpy_s(m_servInfo_struct.ps,p);
	p = T2A(m_servContent);
	strcpy_s(m_servInfo_struct.serv_content,p);

	CTime timeTime;
	DWORD dwResult = m_dateReq.GetTime(timeTime);
	CString str;
	if (dwResult == GDT_VALID)
	{
		if ((m_dateReq.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}else{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}
		p = T2A(str);
		strcpy_s(m_servInfo_struct.req_serv_date,p);
	}else
	{
		MessageBox(_T("��ѡ��Ҫ���������"));
		return;
	}

	p = T2A(m_servNM);
	strcpy_s(m_servInfo_struct.serv_name,p);
	p = T2A(m_servPhone);
	strcpy_s(m_servInfo_struct.serv_phone,p);
	CString prog = NULL;
	m_prog.GetWindowText(prog);
	p = T2A(prog);
	strcpy_s(m_servInfo_struct.prog,p);

	dwResult = m_dateDelay.GetTime(timeTime);
	if (dwResult == GDT_VALID)
	{
		if ((m_dateDelay.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}else{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}
		p = T2A(str);
		strcpy_s(m_servInfo_struct.delay_date,p);
	}else
	{
		MessageBox(_T("��ѡ����������"));
		return;
	}
	CString charge = NULL;
	charge.Format(_T("%.2f"),m_charge);
	p = T2A(charge);
	strcpy_s(m_servInfo_struct.charge,p);
	p = T2A(m_servType);
	strcpy_s(m_servInfo_struct.serv_type,T2A(m_servType));

	CSock::StartReqServModify(this);
}
