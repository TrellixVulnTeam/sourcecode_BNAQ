// OrderContentProp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "OrderContent.h"
#include "afxdialogex.h"


// COrderContent �Ի���

IMPLEMENT_DYNAMIC(COrderContent, CDialogEx)

COrderContent::COrderContent(CWnd* pParent /*=NULL*/)
	: CDialogEx(COrderContent::IDD, pParent)
	, m_accessory_filepath(_T(""))
	, m_baseinfo_ps(_T(""))
	, m_charge_name(_T(""))
	, m_contract_NO(_T(""))
	, m_contract_total_price(0)
	, m_ctm_addr(_T(""))
	, m_ctm_call(_T(""))
	, m_ctm_name(_T(""))
	, m_ctm_phone(_T(""))
	, m_ctm_ps(_T(""))
	, m_persion1_discuss(_T(""))
	, m_person2_discuss(_T(""))
	, m_person_earlyStageModify(_T(""))
	, m_person_exact_measure(_T(""))
	, m_factory_choose(_T(""))
	, m_person_install(_T(""))
	, m_problems_install(_T(""))
	, m_money_already_take(0)
	, m_order_NO(_T(""))
	, m_person_budget(_T(""))
	, m_person_out_order(_T(""))
	, m_persion_first_test(_T(""))
	, m_persion_first_design(_T(""))
{
	m_ulCurTotal = 0;
}

COrderContent::~COrderContent()
{
	
}

void COrderContent::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CTM_FROM, m_ctmFrom);
	DDX_Control(pDX, IDC_STATIC_INTR_NAME, m_staticIntrName);
	DDX_Control(pDX, IDC_STATIC_INTR_PHONE, m_staticIntrPhone);
	DDX_Control(pDX, IDC_STATIC_SERV_PERSON, m_staticServPersonNM);
	DDX_Control(pDX, IDC_EDIT_INTR_NM, m_intrName);
	DDX_Control(pDX, IDC_EDIT_INTR_PHONE, m_intrPhone);
	DDX_Control(pDX, IDC_EDIT_SERV_PERSON, m_servPerson);
	DDX_Control(pDX, IDC_STATIC_EMP_DONE, m_static_emp_done);
	DDX_Control(pDX, IDC_EDIT_EMP_NAME, m_empName);
	DDX_Control(pDX, IDC_COMBO_BUSINESS_PROG, m_businessProg);
	DDX_Control(pDX, IDC_COMBO_PAY_DEAL_CHOOSE, m_payDealChoose);
	DDX_Control(pDX, IDC_COMBO_ORDER_DISCUSS_TYPE, m_orderDiscussType);
	DDX_Control(pDX, IDC_COMBO_EARLY_STAGE_TYPE, m_earlyStageType);
	DDX_Control(pDX, IDC_DATETIME_BOOK, m_date_book);
	DDX_Control(pDX, IDC_DATETIME_FINAL_SCHEME, m_date_final_scheme);
	DDX_Control(pDX, IDC_DATETIME_FIRST_TEST, m_date_firsttest);
	DDX_Control(pDX, IDC_DATETIME_INSTALL_BOOK, m_date_installBOOK);
	DDX_Control(pDX, IDC_DATETIME_ORDER_ACCEPT, m_date_orderaccept);
	DDX_Control(pDX, IDC_DATETIME_ORDER_FINISHED, m_order_orderfinished);
	DDX_Control(pDX, IDC_DATETIME_OUT_ORDER_BOOK, m_date_out_order_book);
	DDX_Text(pDX, IDC_EDIT_ACCESSORY_FILE_PATH, m_accessory_filepath);
	DDX_Text(pDX, IDC_EDIT_BASEINFO_PS, m_baseinfo_ps);
	DDX_Text(pDX, IDC_EDIT_CHARGE_NM, m_charge_name);
	DDX_Text(pDX, IDC_EDIT_CONTRACT_NO, m_contract_NO);
	DDX_Text(pDX, IDC_EDIT_CONTRACT_TOTAL_PRICE, m_contract_total_price);
	DDX_Text(pDX, IDC_EDIT_CTM_ADDR, m_ctm_addr);
	DDX_Text(pDX, IDC_EDIT_CTM_CALL, m_ctm_call);
	DDX_Text(pDX, IDC_EDIT_CTM_NAME, m_ctm_name);
	DDX_Text(pDX, IDC_EDIT_CTM_PHONE, m_ctm_phone);
	DDX_Text(pDX, IDC_EDIT_CTM_PS, m_ctm_ps);
	DDX_Text(pDX, IDC_EDIT_DEAL_DISCUSS_PERSON1, m_persion1_discuss);
	DDX_Text(pDX, IDC_EDIT_DEAL_DISCUSS_PERSON2, m_person2_discuss);
	DDX_Text(pDX, IDC_EDIT_EARLY_STAGE_MODIFY_PERSON, m_person_earlyStageModify);
	DDX_Text(pDX, IDC_EDIT_EXACT_MEASURE_PERSON, m_person_exact_measure);
	DDX_Text(pDX, IDC_EDIT_FCTORY_CHOOSE, m_factory_choose);
	DDX_Text(pDX, IDC_EDIT_INSTALL_PERSON, m_person_install);
	DDX_Text(pDX, IDC_EDIT_INSTALL_PROBLEMS, m_problems_install);
	DDX_Text(pDX, IDC_EDIT_MONEY_ALREADY_TAKE, m_money_already_take);
	DDX_Text(pDX, IDC_EDIT_ORDER_NO, m_order_NO);
	DDX_Text(pDX, IDC_EDIT_PERSON_BUDGET, m_person_budget);
	DDX_Text(pDX, IDC_EDIT_PERSON_OUT_ORDER, m_person_out_order);
	DDX_Control(pDX, IDC_PROGRESS_STATUS, m_progressCtrl);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
	DDX_Text(pDX, IDC_EDIT_PERDON_FIRST_TEST, m_persion_first_test);
	DDX_Text(pDX, IDC_EDIT_PERSION_FIRST_DESIGN, m_persion_first_design);
	DDX_Control(pDX, IDC_STATIC_UPLOAD_STATUS, m_static_upload_status);
}


BEGIN_MESSAGE_MAP(COrderContent, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_CTM_FROM, &COrderContent::OnCbnSelchangeComboCtmFrom)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_CANCLE, &COrderContent::OnBnClickedBtnCancle)
	ON_BN_CLICKED(IDC_BTN_NEW, &COrderContent::OnBnClickedBtnNew)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_STARTTASK_OrderContent, &COrderContent::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_OrderContent, &COrderContent::OnEndTask)
	ON_BN_CLICKED(IDC_BTN_ACCESSORY_CHOOSE, &COrderContent::OnBnClickedBtnAccessoryChoose)
	ON_BN_CLICKED(IDC_BTN_ACCESSORY_CHECK, &COrderContent::OnBnClickedBtnAccessoryCheck)
	ON_MESSAGE(WM_STARTUPLOADFILE_OrderContent, &COrderContent::OnStartUploadFile)
	ON_MESSAGE(WM_CONFIRMUPLOADFILE_OrderContent, &COrderContent::OnConfirmUploadFile)
	ON_MESSAGE(WM_RESETUPLOAD_OrderContent, &COrderContent::OnResetUpload)
	ON_BN_CLICKED(IDC_BTN_FILE_UPLOAD, &COrderContent::OnBnClickedBtnFileUpload)
END_MESSAGE_MAP()


// COrderContent ��Ϣ�������

void COrderContent::InitCtmFromComb()
{
	m_ctmFrom.AddString(_T("�Ͽͻ�����"));
	m_ctmFrom.AddString(_T("�Ͽͻ����ζ���"));
	m_ctmFrom.AddString(_T("�¿ͻ�"));
	m_ctmFrom.AddString(_T("װ�깫˾����"));
	m_ctmFrom.AddString(_T("ҵ��Ա�ܵ�"));

	m_ctmFrom.SetCurSel(0);
}

BOOL COrderContent::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InitCtmFromComb();
	InitBusinessProgComb();
	InitEarlyStageTypeComb();
	InitTipCtrl();
	InitPayDealChooseComb();
	InitOrderDiscussTypeComb();
	m_date_book.SetFormat(_T("yyyy-MM-dd"));
	m_date_final_scheme.SetFormat(_T("yyyy-MM-dd"));
	m_date_firsttest.SetFormat(_T("yyyy-MM-dd"));
	m_date_installBOOK.SetFormat(_T("yyyy-MM-dd"));
	m_date_orderaccept.SetFormat(_T("yyyy-MM-dd"));
	m_order_orderfinished.SetFormat(_T("yyyy-MM-dd"));
	m_date_out_order_book.SetFormat(_T("yyyy-MM-dd"));
	return TRUE;
}

void COrderContent::InitTipCtrl()
{
	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	m_static_upload_status.SetFont(&font);
	font.Detach();
}

void COrderContent::InitOrderDiscussTypeComb()
{
	m_orderDiscussType.AddString(_T("��ѡ�����̸��"));
	m_orderDiscussType.AddString(_T("���˺���̸��"));
	m_orderDiscussType.SetCurSel(0);
}
void COrderContent::InitPayDealChooseComb()
{
	m_payDealChoose.AddString(_T("�Ѹ�"));
	m_payDealChoose.AddString(_T("δ��"));
	m_payDealChoose.AddString(_T("�ۻ�"));
	m_payDealChoose.SetCurSel(0);
}
void COrderContent::InitEarlyStageTypeComb()
{
	m_earlyStageType.AddString(_T("�ڲ��޸�"));
	m_earlyStageType.AddString(_T("�ͻ���ͨ�޸�"));
	m_earlyStageType.SetCurSel(0);

}

void COrderContent::InitBusinessProgComb()
{
	m_businessProg.AddString(_T("����ͻ�"));
	m_businessProg.AddString(_T("�Ѷ���"));
	m_businessProg.AddString(_T("�ѳ���"));
	m_businessProg.AddString(_T("��ǩ��ͬ"));
	m_businessProg.AddString(_T("��ȷ�����շ���"));
	m_businessProg.AddString(_T("�ѷ�������"));
	m_businessProg.AddString(_T("�ѷ���"));
	m_businessProg.AddString(_T("�ѻص�"));
	m_businessProg.AddString(_T("�Ѱ�װ"));
	m_businessProg.AddString(_T("�����"));
	m_businessProg.SetCurSel(0);
}
void COrderContent::OnCbnSelchangeComboCtmFrom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int curSel = m_ctmFrom.GetCurSel();
	CString strTemp = _T("");
	m_ctmFrom.GetLBText(curSel,strTemp);

	if("�¿ͻ�" == strTemp){
		m_staticServPersonNM.ShowWindow(SW_SHOW);
		m_servPerson.ShowWindow(SW_SHOW);

		m_staticIntrName.ShowWindow(SW_HIDE);
		m_intrName.ShowWindow(SW_HIDE);

		m_staticIntrPhone.ShowWindow(SW_HIDE);
		m_intrPhone.ShowWindow(SW_HIDE);

		m_static_emp_done.ShowWindow(SW_HIDE);
		m_empName.ShowWindow(SW_HIDE);
	}else if("�Ͽͻ����ζ���" == strTemp){
		m_staticServPersonNM.ShowWindow(SW_HIDE);
		m_servPerson.ShowWindow(SW_HIDE);

		m_staticIntrName.ShowWindow(SW_HIDE);
		m_intrName.ShowWindow(SW_HIDE);

		m_staticIntrPhone.ShowWindow(SW_HIDE);
		m_intrPhone.ShowWindow(SW_HIDE);

		m_static_emp_done.ShowWindow(SW_HIDE);
		m_empName.ShowWindow(SW_HIDE);
	}else if("�Ͽͻ�����" == strTemp){
		m_staticServPersonNM.ShowWindow(SW_HIDE);
		m_servPerson.ShowWindow(SW_HIDE);

		m_staticIntrName.ShowWindow(SW_SHOW);
		m_intrName.ShowWindow(SW_SHOW);

		m_staticIntrPhone.ShowWindow(SW_SHOW);
		m_intrPhone.ShowWindow(SW_SHOW);

		m_static_emp_done.ShowWindow(SW_HIDE);
		m_empName.ShowWindow(SW_HIDE);
	}else if("װ�깫˾����" == strTemp){
		m_staticServPersonNM.ShowWindow(SW_HIDE);
		m_servPerson.ShowWindow(SW_HIDE);

		m_staticIntrName.ShowWindow(SW_SHOW);
		m_intrName.ShowWindow(SW_SHOW);

		m_staticIntrPhone.ShowWindow(SW_SHOW);
		m_intrPhone.ShowWindow(SW_SHOW);

		m_static_emp_done.ShowWindow(SW_HIDE);
		m_empName.ShowWindow(SW_HIDE);
	}else if("ҵ��Ա�ܵ�" == strTemp){
		m_staticServPersonNM.ShowWindow(SW_HIDE);
		m_servPerson.ShowWindow(SW_HIDE);

		m_staticIntrName.ShowWindow(SW_HIDE);
		m_intrName.ShowWindow(SW_HIDE);

		m_staticIntrPhone.ShowWindow(SW_HIDE);
		m_intrPhone.ShowWindow(SW_HIDE);

		m_static_emp_done.ShowWindow(SW_SHOW);
		m_empName.ShowWindow(SW_SHOW);
	}else{
		return;	
	}
}


HBRUSH COrderContent::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void COrderContent::OnBnClickedBtnCancle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(CSock::m_bUpLoading){
		if(IDYES == MessageBox(_T("��ǰ�����ϴ��ļ�����ȷ��ȡ����"),_T("����"),MB_YESNO))
		{
			CSock::m_bUpLoading = FALSE;
			CSock::m_pOrderContent = NULL;
			CDialogEx::OnCancel();
		}else{
			return;
		}
	}else{
		CSock::m_pOrderContent = NULL;
		CDialogEx::OnCancel();
	}
}


void COrderContent::OnBnClickedBtnNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	USES_CONVERSION;
	if(!IsItemValidity(m_order_NO,_T("�������"),TRUE,TRUE,FALSE,12,0))
	{
		return ;
	}
	
	memset(&m_orderInfo,0,sizeof(m_orderInfo));
	strcpy_s(m_orderInfo.NO_Order,T2A(m_order_NO));
	char *p = NULL;
	CTime timeTime;
	DWORD dwResult = m_date_orderaccept.GetTime(timeTime);   //�ӵ�����
	CString str;
	if (dwResult == GDT_VALID)
	{
		if ((m_date_orderaccept.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}else{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}
		p = T2A(str);
		strcpy_s(m_orderInfo.date_accept_order,p);
	}else
	{
		MessageBox(_T("��ѡ��ӵ�����"));
		return;
	}
	dwResult = m_order_orderfinished.GetTime(timeTime);   //�������
	if (dwResult == GDT_VALID)
	{
		if ((m_order_orderfinished.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}else{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}
		p = T2A(str);
		strcpy_s(m_orderInfo.date_finished_order,p);
	}else
	{
		MessageBox(_T("��ѡ���������"));
		return;
	}
	if(!IsItemValidity(m_charge_name,_T("����������"),FALSE,FALSE,FALSE,15,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.name_person_charge_order,T2A(m_charge_name));
	if(!IsItemValidity(m_baseinfo_ps,_T("������Ϣ��ע"),FALSE,FALSE,FALSE,180,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.base_ps_order,T2A(m_baseinfo_ps));

	if(!IsItemValidity(m_persion_first_design,_T("���������Ա"),FALSE,FALSE,FALSE,15,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.persion_first_design,T2A(m_persion_first_design));
	CString earlyStageType;
	m_earlyStageType.GetWindowText(earlyStageType);
	strcpy_s(m_orderInfo.type_early_modify,T2A(earlyStageType));


	if(!IsItemValidity(m_person_earlyStageModify,_T("ǰ���޸���Ա"),FALSE,FALSE,FALSE,15,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.persion_early_modify,T2A(m_person_earlyStageModify));

	dwResult = m_date_final_scheme.GetTime(timeTime);   //������������
	if (dwResult == GDT_VALID)
	{
		if ((m_date_final_scheme.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}else{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}
		p = T2A(str);
		strcpy_s(m_orderInfo.date_final_scheme,p);
	}else
	{
		MessageBox(_T("��ѡ�񷽰���������"));
		return;
	}

	CString intrname;   //����������
	m_intrName.GetWindowText(intrname);
	if(!IsItemValidity(intrname,_T("������"),FALSE,FALSE,FALSE,15,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.name_intr,T2A(intrname));
	
	CString intrphone;
	m_intrPhone.GetWindowText(intrphone);
	if(!IsItemValidity(intrphone,_T("�����˵绰"),FALSE,TRUE,FALSE,11,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.phone_intr,T2A(intrphone));
	CString servPersion;
	m_servPerson.GetWindowText(servPersion);
	if(!IsItemValidity(servPersion,_T("�Ӵ���"),FALSE,FALSE,FALSE,15,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.name_serv_persion,T2A(servPersion));

	CString empname;
	m_empName.GetWindowText(empname);
	if(!IsItemValidity(empname,_T("ҵ��Ա"),FALSE,FALSE,FALSE,15,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.name_emp,T2A(empname));

	if(!IsItemValidity(m_ctm_call,_T("�ͻ�����"),FALSE,FALSE,FALSE,15,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.call_ctm,T2A(m_ctm_call));

	if(!IsItemValidity(m_ctm_name,_T("�˿�����"),FALSE,FALSE,FALSE,15,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.name_ctm,T2A(m_ctm_name));
	if(!IsItemValidity(m_ctm_phone,_T("�˿͵绰"),FALSE,TRUE,FALSE,11,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.phone_ctm,T2A(m_ctm_phone));

	if(!IsItemValidity(m_ctm_ps,_T("�˿ͱ�ע"),FALSE,FALSE,FALSE,100,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.ps_ctm,T2A(m_ctm_ps));
	
	if(!IsItemValidity(m_ctm_addr,_T("�˿͵�ַ"),FALSE,FALSE,FALSE,50,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.addr_ctm,T2A(m_ctm_addr));

	if(!IsItemValidity(m_person_budget,_T("Ԥ����Ա"),FALSE,FALSE,FALSE,15,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.persion_budget,T2A(m_person_budget));
	
	CString temp;
	m_orderDiscussType.GetWindowText(temp);
	strcpy_s(m_orderInfo.type_discuss_order,T2A(temp));
	
	if(!IsItemValidity(m_persion1_discuss,_T("̸����Ա1"),FALSE,FALSE,FALSE,15,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.persion1_discuss_order,T2A(m_persion1_discuss));
	
	if(!IsItemValidity(m_person2_discuss,_T("̸����Ա2"),FALSE,FALSE,FALSE,15,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.persion2_discuss_order,T2A(m_person2_discuss));

	if(!IsItemValidity(m_contract_NO,_T("��ͬ����"),FALSE,TRUE,FALSE,15,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.NO_contract,T2A(m_contract_NO));

	m_businessProg.GetWindowText(temp);
	strcpy_s(m_orderInfo.prog_business,T2A(temp));
	temp.Format(_T("%.2f"),m_contract_total_price);
	strcpy_s(m_orderInfo.price_total_contract,T2A(temp));
	temp.Format(_T("%.2f"),m_money_already_take);
	strcpy_s(m_orderInfo.money_already_take,T2A(temp));

	dwResult = m_date_firsttest.GetTime(timeTime);   //����ԤԼʱ��
	if (dwResult == GDT_VALID)
	{
		if ((m_date_firsttest.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}else{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}
		p = T2A(str);
		strcpy_s(m_orderInfo.date_first_test_book,p);
	}else
	{
		MessageBox(_T("��ѡ�����ԤԼʱ��"));
		return;
	}
	
	if(!IsItemValidity(m_persion_first_test,_T("������Ա"),FALSE,FALSE,FALSE,15,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.persion_first_test,T2A(m_persion_first_test));
	

	dwResult = m_date_out_order_book.GetTime(timeTime);   //����ԤԼʱ��
	if (dwResult == GDT_VALID)
	{
		if ((m_date_out_order_book.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}else{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}
		p = T2A(str);
		strcpy_s(m_orderInfo.date_out_order_book,p);
	}else
	{
		MessageBox(_T("��ѡ�񷢵�ԤԼʱ��"));
		return;
	}
	
	if(!IsItemValidity(m_person_out_order,_T("������Ա"),FALSE,FALSE,FALSE,15,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.person_out_order,T2A(m_person_out_order));

	if(!IsItemValidity(m_factory_choose,_T("��λ"),FALSE,FALSE,FALSE,30,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.factory_choose,T2A(m_factory_choose));
	
	m_payDealChoose.GetWindowText(temp);
	strcpy_s(m_orderInfo.pay_deal_choice,T2A(temp));

	dwResult = m_date_book.GetTime(timeTime);   //����ԤԼʱ��
	if (dwResult == GDT_VALID)
	{
		if ((m_date_book.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}else{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}
		p = T2A(str);
		strcpy_s(m_orderInfo.date_book,p);
	}else
	{
		MessageBox(_T("��ѡ�����ԤԼʱ��"));
		return;
	}

	if(!IsItemValidity(m_person_exact_measure,_T("����������Ա"),FALSE,FALSE,FALSE,15,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.person_exact_measure,T2A(m_person_exact_measure));
	

	dwResult = m_date_installBOOK.GetTime(timeTime);   //����ԤԼʱ��
	if (dwResult == GDT_VALID)
	{
		if ((m_date_installBOOK.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}else{
			str = timeTime.Format(_T("%Y-%m-%d"));
		}
		p = T2A(str);
		strcpy_s(m_orderInfo.date_install_book,p);
	}else
	{
		MessageBox(_T("��ѡ��װԤԼʱ��"));
		return;
	}
	
	if(!IsItemValidity(m_person_install,_T("��װ��Ա"),FALSE,FALSE,FALSE,15,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.persion_install,T2A(m_person_install));
	if(!IsItemValidity(m_problems_install,_T("��װ����"),FALSE,FALSE,FALSE,100,0))
	{
		return ;
	}
	strcpy_s(m_orderInfo.problems_install,T2A(m_problems_install));
	
	CString ctmFrom;
	m_ctmFrom.GetWindowText(ctmFrom);
	strcpy_s(m_orderInfo.ctm_from,T2A(ctmFrom));
	CheckCtmFrom();
	CSock::StartReqOrderNew(this);
}

BOOL COrderContent::IsItemValidity(CString _source,CString _item_name,BOOL bCheckEmpty,BOOL bCheckNum,BOOL bCheckDateFormat,int str_len_max,int data_min_len,BOOL bCheckDot)
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

BOOL COrderContent::ContainsCharsRemain(CString str)     //����ַ����Ƿ�������ַ���
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

BOOL COrderContent::IsNum(CString str,BOOL bCheckDot)
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



void COrderContent::CheckCtmFrom()
{
	UpdateData(TRUE);
	CString strTemp;
	CString temp;
	m_ctmFrom.GetWindowText(strTemp);
	if("�¿ͻ�" == strTemp){
		memset(m_orderInfo.phone_intr,0,sizeof(m_orderInfo.phone_intr));
		memset(m_orderInfo.name_emp,0,sizeof(m_orderInfo.name_emp));
		memset(m_orderInfo.name_intr,0,sizeof(m_orderInfo.name_intr));
	}else if("�Ͽͻ����ζ���" == strTemp){
		memset(m_orderInfo.phone_intr,0,sizeof(m_orderInfo.phone_intr));
		memset(m_orderInfo.name_emp,0,sizeof(m_orderInfo.name_emp));
		memset(m_orderInfo.name_intr,0,sizeof(m_orderInfo.name_intr));
		memset(m_orderInfo.name_serv_persion,0,sizeof(m_orderInfo.name_serv_persion));
	}else if("�Ͽͻ�����" == strTemp){
		memset(m_orderInfo.name_emp,0,sizeof(m_orderInfo.name_emp));
		memset(m_orderInfo.name_serv_persion,0,sizeof(m_orderInfo.name_serv_persion));
	}else if("װ�깫˾����" == strTemp){
		memset(m_orderInfo.name_emp,0,sizeof(m_orderInfo.name_emp));
		memset(m_orderInfo.name_serv_persion,0,sizeof(m_orderInfo.name_serv_persion));
	}else if("ҵ��Ա�ܵ�" == strTemp){
		memset(m_orderInfo.name_emp,0,sizeof(m_orderInfo.name_emp));
		
	}else{
		return;	
	}
}

void COrderContent::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
		{
			ShowTip();
			ShowUploadStatus();
			break;
		}
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}
void COrderContent::ResetCurFileUpload()
{
	m_ulCurTotal = 0;
	m_progressCtrl.SetPos(0);
	m_static_upload_status.SetWindowText(_T(""));
	m_progressCtrl.ShowWindow(SW_HIDE);
}
void COrderContent::ShowUploadStatus()
{
	if (m_ulCurTotal > 0)//��ǰ�����ļ����ֽ���
	{
		int nPercent = (float)m_ulCurTotal / m_ulFileSize * 100;//�ٷֱ�
		m_progressCtrl.SetPos(nPercent);							//���ý�����λ��
		
		m_progressCtrl.ShowWindow(SW_SHOW);						//��ʾ������
		
		//��ʾ���ؽ�����Ϣ
		CString strProgInfor;
		strProgInfor.Format(_T("�����ϴ� %d%s"), nPercent,_T("%"));
		m_static_upload_status.SetWindowText(strProgInfor);
	}
}

void COrderContent::ShowTip()
{
	m_time_take++;
	CString time =NULL;
	time.Format(_T("��ʱ��%d��"),m_time_take);
	m_tip.SetWindowText(time);
}

void COrderContent::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(CSock::m_bUpLoading){
		if(IDYES == MessageBox(_T("��ǰ�����ϴ��ļ�����ȷ�Ϲر���"),_T("����"),MB_YESNO))
		{
			CSock::m_bUpLoading = FALSE;
			CSock::m_pOrderContent = NULL;
			CDialogEx::OnClose();
		}else{
			return;
		}
	}else{
		CSock::m_pOrderContent = NULL;
		CDialogEx::OnClose();
	}
}


afx_msg LRESULT COrderContent::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT COrderContent::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T("����"));
	(CButton*)GetDlgItem(IDC_BTN_NEW)->EnableWindow(TRUE);
	(CButton*)GetDlgItem(IDC_BTN_ACCESSORY_CHECK)->EnableWindow(TRUE);
	return 0;
}


void COrderContent::OnBnClickedBtnAccessoryChoose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CFileDialog fileDlg(TRUE);
	fileDlg.m_ofn.lpstrTitle = _T("ѡ�񸽼������ϴ�");
	fileDlg.m_ofn.lpstrFilter = _T("All Files(*.*)\0*.*\0\0");
	if(IDOK == fileDlg.DoModal())
	{
		CString pathName = fileDlg.GetPathName();
		CString fileExt = fileDlg.GetFileExt();
		m_accessory_filepath = pathName;
		m_filename = fileDlg.GetFileName();
		UpdateData(FALSE);
	}else{
		return;
	}
}


void COrderContent::OnBnClickedBtnAccessoryCheck()    //��ʼ�ϴ�����
{
	UpdateData(TRUE);
	USES_CONVERSION;
	if(m_order_NO.IsEmpty())
	{
		MessageBox(_T("������Ų���Ϊ��"));
		return;
	}else if(m_order_NO.GetLength()>12){
		MessageBox(_T("������ų��Ȳ��ܳ���12���ַ�"));
		return;
	}else{
		int len = m_order_NO.GetLength();
		char *p = T2A(m_order_NO);
		for(int i=0;i<len;i++)
		{
			if(p[i] < '0'||p[i] >'9')
			{
				MessageBox(_T("������ű���Ϊ����"));
				m_order_NO.Empty();
				UpdateData(FALSE);
				return;
			}
		}
	}
	if(m_accessory_filepath.IsEmpty())
	{
		MessageBox(_T("����ѡ��Ҫ�ϴ��ĸ���"));
		return ;
	}else if(m_accessory_filepath.GetLength()>MAX_PATH){
		MessageBox(_T("����·�����ܳ���260���ַ���������ѡ��"));
		return ;
	}
	CFileFind finder;
	BOOL isFind = finder.FindFile(m_accessory_filepath);
	if(isFind){ 
		m_ulFileSize = GetFileSize();
	}else{
		MessageBox(_T("Ҫ�ϴ����������ڣ������Ѿ���ɾ��"));
		return;
	}
	CString filesize = NULL;
	filesize.Format(_T("%u"),m_ulFileSize);
	memset(&m_orderInfo,0,sizeof(m_orderInfo));
	strcpy_s(m_orderInfo.NO_Order,T2A(m_order_NO));
	strcpy_s(m_orderInfo.filepath_accessory,T2A(m_filename));
	strcpy_s(m_orderInfo.filesize,T2A(filesize));
	(CButton*)GetDlgItem(IDC_BTN_NEW)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_BTN_ACCESSORY_CHECK)->EnableWindow(FALSE);
	
	CSock::StartCheckFileExist(this);
}

u_long COrderContent::GetFileSize()
{
	USES_CONVERSION;
	CString filepath = m_accessory_filepath;
	char* p = T2A(filepath);
	long retFileLen;//�ļ�����
	FILE *stream;	//�ļ�ָ��
	int err = fopen_s(&stream,p,"rb");
	if(err != 0)//���ļ�ʧ��
	{
		return 0;
	}
	fseek( stream, 0, SEEK_END);	//ָ���ƶ����ļ�β
	retFileLen = ftell( stream );	//��ȡ�ļ�����
	fclose( stream );				//�ر��ļ�
	return retFileLen;
}

afx_msg LRESULT COrderContent::OnStartUploadFile(WPARAM wParam, LPARAM lParam)
{
	if(IDYES == MessageBox(_T("�ö�����ʱû�и����������ϴ���������"),_T("��ʾ"),MB_YESNO))
	{
		CSock::StartUpLoadFile(this);
	}else{
		(CButton*)GetDlgItem(IDC_BTN_NEW)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_BTN_ACCESSORY_CHECK)->EnableWindow(TRUE);
		m_tip.SetWindowText(_T("����"));
		m_static_upload_status.SetWindowText(_T("�ö�����û�и���"));
	}
	return 0;
}


afx_msg LRESULT COrderContent::OnConfirmUploadFile(WPARAM wParam, LPARAM lParam)
{
	if(IDYES == MessageBox(_T("�ö�����һ��������ȷ���ϴ�������ԭ�и�����������"),_T("����"),MB_YESNO))
	{
		CSock::StartUpLoadFile(this);
	}else{
		(CButton*)GetDlgItem(IDC_BTN_NEW)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_BTN_ACCESSORY_CHECK)->EnableWindow(TRUE);
		m_tip.SetWindowText(_T("����"));
		m_static_upload_status.SetWindowText(_T("�ö������и���"));
	}
	return 0;
}


afx_msg LRESULT COrderContent::OnResetUpload(WPARAM wParam, LPARAM lParam)
{
	ResetCurFileUpload();
	return 0;
}


void COrderContent::OnBnClickedBtnFileUpload()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	USES_CONVERSION;
	if(m_order_NO.IsEmpty())
	{
		MessageBox(_T("������Ų���Ϊ��"));
		return;
	}else if(m_order_NO.GetLength()>12){
		MessageBox(_T("������ų��Ȳ��ܳ���12���ַ�"));
		return;
	}else{
		int len = m_order_NO.GetLength();
		char *p = T2A(m_order_NO);
		for(int i=0;i<len;i++)
		{
			if(p[i] < '0'||p[i] >'9')
			{
				MessageBox(_T("������ű���Ϊ����"));
				m_order_NO.Empty();
				UpdateData(FALSE);
				return;
			}
		}
	}
	if(m_accessory_filepath.IsEmpty())
	{
		MessageBox(_T("����ѡ��Ҫ�ϴ��ĸ���"));
		return ;
	}else if(m_accessory_filepath.GetLength()>MAX_PATH){
		MessageBox(_T("����·�����ܳ���260���ַ���������ѡ��"));
		return ;
	}
	CFileFind finder;
	BOOL isFind = finder.FindFile(m_accessory_filepath);
	if(isFind){ 
		m_ulFileSize = GetFileSize();
	}else{
		MessageBox(_T("Ҫ�ϴ����������ڣ������Ѿ���ɾ��"));
		return;
	}
	memset(&m_fileULInfo,0,sizeof(m_fileULInfo));
	strcpy_s(m_fileULInfo.order_NO,T2A(m_order_NO));
	strcpy_s(m_fileULInfo.filename,T2A(m_filename));
	m_fileULInfo.filesize = m_ulFileSize;
	(CButton*)GetDlgItem(IDC_BTN_NEW)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_BTN_ACCESSORY_CHECK)->EnableWindow(FALSE);

	CSock::StartUpLoadFile(this);
}
