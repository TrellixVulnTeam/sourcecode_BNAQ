// OrderContentProp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "OrderContentProp.h"
#include "afxdialogex.h"


// COrderContentProp �Ի���

IMPLEMENT_DYNAMIC(COrderContentProp, CPropertyPage)

COrderContentProp::COrderContentProp()
	: CPropertyPage(COrderContentProp::IDD)
	//, m_intrNM(_T(""))
	//, m_intrPhone(0)
	//, m_servPersonName(_T(""))
{

}

COrderContentProp::~COrderContentProp()
{
}

void COrderContentProp::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CTM_FROM, m_ctmFrom);
	//  DDX_Text(pDX, IDC_EDIT_INTR_NM, m_intrNM);
	//  DDX_Text(pDX, IDC_EDIT_INTR_PHONE, m_intrPhone);
	DDX_Control(pDX, IDC_STATIC_INTR_NAME, m_staticIntrName);
	DDX_Control(pDX, IDC_STATIC_INTR_PHONE, m_staticIntrPhone);
	DDX_Control(pDX, IDC_STATIC_SERV_PERSON, m_staticServPersonNM);
	//  DDX_Text(pDX, IDC_EDIT_SERV_PERSON, m_servPersonName);
	DDX_Control(pDX, IDC_EDIT_INTR_NM, m_intrName);
	DDX_Control(pDX, IDC_EDIT_INTR_PHONE, m_intrPhone);
	DDX_Control(pDX, IDC_EDIT_SERV_PERSON, m_servPerson);
	DDX_Control(pDX, IDC_STATIC_EMP_DONE, m_static_emp_done);
	DDX_Control(pDX, IDC_EDIT_EMP_NAME, m_empName);
	DDX_Control(pDX, IDC_COMBO_BUSINESS_PROG, m_businessProg);
	DDX_Control(pDX, IDC_COMBO_PAY_DEAL_CHOOSE, m_payDealChoose);
	DDX_Control(pDX, IDC_COMBO_ORDER_DISCUSS_TYPE, m_orderDiscussType);
	DDX_Control(pDX, IDC_COMBO_EARLY_STAGE_TYPE, m_earlyStageType);
}


BEGIN_MESSAGE_MAP(COrderContentProp, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO_CTM_FROM, &COrderContentProp::OnCbnSelchangeComboCtmFrom)
	//ON_EN_CHANGE(IDC_EDIT_ACCESSORY_FILE_PATH, &COrderContentProp::OnEnChangeEditAccessoryFilePath)
END_MESSAGE_MAP()


// COrderContentProp ��Ϣ�������

void COrderContentProp::InitCtmFromComb()
{
	m_ctmFrom.AddString(_T("�Ͽͻ�����"));
	m_ctmFrom.AddString(_T("�Ͽͻ����ζ���"));
	m_ctmFrom.AddString(_T("�¿ͻ�"));
	m_ctmFrom.AddString(_T("װ�깫˾����"));
	m_ctmFrom.AddString(_T("ҵ��Ա�ܵ�"));

	m_ctmFrom.SetCurSel(0);

	

}

BOOL COrderContentProp::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	InitCtmFromComb();
	InitBusinessProgComb();
	InitEarlyStageTypeComb();
	
	InitPayDealChooseComb();
	InitOrderDiscussTypeComb();

	return TRUE;
}

void COrderContentProp::InitOrderDiscussTypeComb()
{
	m_orderDiscussType.AddString(_T("��ѡ�����̸��"));
	m_orderDiscussType.AddString(_T("���˺���̸��"));
	m_orderDiscussType.SetCurSel(0);
}
void COrderContentProp::InitPayDealChooseComb()
{
	m_payDealChoose.AddString(_T("�Ѹ�"));
	m_payDealChoose.AddString(_T("δ��"));
	m_payDealChoose.AddString(_T("�ۻ�"));
	m_payDealChoose.SetCurSel(0);

}
void COrderContentProp::InitEarlyStageTypeComb()
{
	m_earlyStageType.AddString(_T("�ڲ��޸�"));
	m_earlyStageType.AddString(_T("�ͻ���ͨ�޸�"));
	m_earlyStageType.SetCurSel(0);

}

void COrderContentProp::InitBusinessProgComb()
{
	m_businessProg.AddString(_T("����ͻ�"));
	m_businessProg.AddString(_T("�Ѷ���"));
	m_businessProg.AddString(_T("�ѳ���"));
	m_businessProg.AddString(_T("�Ѷ���"));
	m_businessProg.AddString(_T("��ǩ��ͬ"));
	m_businessProg.AddString(_T("��ȷ�����շ���"));
	m_businessProg.AddString(_T("�ѷ�������"));
	m_businessProg.AddString(_T("�ѷ���"));
	m_businessProg.AddString(_T("�ѻص�"));
	m_businessProg.AddString(_T("�Ѱ�װ"));
	m_businessProg.AddString(_T("�����"));
	m_businessProg.SetCurSel(0);
}
void COrderContentProp::OnCbnSelchangeComboCtmFrom()
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



