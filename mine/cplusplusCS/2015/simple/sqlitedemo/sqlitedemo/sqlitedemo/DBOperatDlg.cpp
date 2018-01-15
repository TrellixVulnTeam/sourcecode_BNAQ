// DBOperatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "sqlitedemo.h"
#include "DBOperatDlg.h"
#include "ChildView.h"

// CDBOperatDlg �Ի���

IMPLEMENT_DYNAMIC(CDBOperatDlg, CDialog)

CDBOperatDlg::CDBOperatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBOperatDlg::IDD, pParent)
{

}

CDBOperatDlg::~CDBOperatDlg()
{
}

void CDBOperatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_COMPANY, m_companyName);
	DDX_Control(pDX, IDC_EDIT_DEPARTMENT, m_departmentName);
	DDX_Control(pDX, IDC_EDIT_EMPLOY, m_employName);
}


BEGIN_MESSAGE_MAP(CDBOperatDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_NEW_COMPANY, &CDBOperatDlg::OnBnClickedBtnNewCompany)
	ON_BN_CLICKED(IDC_BTN_NEW_DEPARTMENT, &CDBOperatDlg::OnBnClickedBtnNewDepartment)
	ON_BN_CLICKED(IDC_BTN_NEW_EMPLOY, &CDBOperatDlg::OnBnClickedBtnNewEmploy)
	ON_BN_CLICKED(IDC_BTN_DELETE_COMPANY, &CDBOperatDlg::OnBnClickedBtnDeleteCompany)
	ON_BN_CLICKED(IDC_BTN_DELETE_DEPARTMENT, &CDBOperatDlg::OnBnClickedBtnDeleteDepartment)
	ON_BN_CLICKED(IDC_BTN_DELETE_EMPLOY, &CDBOperatDlg::OnBnClickedBtnDeleteEmploy)
END_MESSAGE_MAP()


// CDBOperatDlg ��Ϣ�������

void CDBOperatDlg::OnBnClickedBtnNewCompany()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sCompany;
	m_companyName.GetWindowText(sCompany);
	if(sCompany.GetLength() == 0)
	{
		MessageBox(_T("��˾���ֲ���Ϊ�գ�"));
		return;
	}
	CChildView* pView = (CChildView*)GetParent();
	pView->m_dbOperation.commandID = ENUM_COMMAND_NEW_COMPANY;
    pView->m_dbOperation.sComanyName = sCompany;
	
	return OnOK();
}

void CDBOperatDlg::OnBnClickedBtnNewDepartment()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sCompany;
	CString sDepartment;
	m_companyName.GetWindowText(sCompany);
	m_departmentName.GetWindowText(sDepartment);
	if(sCompany.GetLength() == 0 )
	{
		MessageBox(_T("��˾���ֲ���Ϊ�գ�"));
		return;
	}
	if(sDepartment.GetLength() == 0)
	{
		MessageBox(_T("�������ֲ���Ϊ�գ�"));
		return;
	}
	CChildView* pView = (CChildView*)GetParent();
	pView->m_dbOperation.commandID = ENUM_COMMAND_NEW_DEPARTMENT;
	pView->m_dbOperation.sDepartmentName = sDepartment;
    pView->m_dbOperation.sComanyName = sCompany;

	return OnOK();
}

void CDBOperatDlg::OnBnClickedBtnNewEmploy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sCompany;
	CString sDepartment;
	CString sEmployName;
	m_companyName.GetWindowText(sCompany);
	m_departmentName.GetWindowText(sDepartment);
	m_employName.GetWindowText(sEmployName);
	if(sCompany.GetLength() == 0 )
	{
		MessageBox(_T("��˾���ֲ���Ϊ�գ�"));
		return;
	}
	if(sDepartment.GetLength() == 0)
	{
		MessageBox(_T("�������ֲ���Ϊ�գ�"));
		return;
	}
	if(sEmployName.GetLength() == 0)
	{
		MessageBox(_T("Ա�����ֲ���Ϊ�գ�"));
		return;
	}
	CChildView* pView = (CChildView*)GetParent();
	pView->m_dbOperation = DB_Operation(ENUM_COMMAND_NEW_EMPLOY,sCompany,sDepartment,sEmployName);

	return OnOK();
}

void CDBOperatDlg::OnBnClickedBtnDeleteCompany()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sCompany;
	m_companyName.GetWindowText(sCompany);
	if(sCompany.GetLength() == 0 )
	{
		MessageBox(_T("��˾���ֲ���Ϊ�գ�"));
		return;
	}
	CChildView* pView = (CChildView*)GetParent();
	pView->m_dbOperation = DB_Operation(ENUM_COMMAND_DELETE_COMPANY,sCompany,_T(""),_T(""));

	return OnOK();
}

void CDBOperatDlg::OnBnClickedBtnDeleteDepartment()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sCompany;
	CString sDepartment;
	m_companyName.GetWindowText(sCompany);
	m_departmentName.GetWindowText(sDepartment);
	if(sCompany.GetLength() == 0 )
	{
		MessageBox(_T("��˾���ֲ���Ϊ�գ�"));
		return;
	}
	if(sDepartment.GetLength() == 0)
	{
		MessageBox(_T("�������ֲ���Ϊ�գ�"));
		return;
	}
	CChildView* pView = (CChildView*)GetParent();
	pView->m_dbOperation = DB_Operation(ENUM_COMMAND_DELETE_DEPARTMENT,sCompany,sDepartment,_T(""));

	return OnOK();
}

void CDBOperatDlg::OnBnClickedBtnDeleteEmploy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sCompany;
	CString sDepartment;
	CString sEmployName;
	m_companyName.GetWindowText(sCompany);
	m_departmentName.GetWindowText(sDepartment);
	m_employName.GetWindowText(sEmployName);
	if(sCompany.GetLength() == 0 )
	{
		MessageBox(_T("��˾���ֲ���Ϊ�գ�"));
		return;
	}
	if(sDepartment.GetLength() == 0)
	{
		MessageBox(_T("�������ֲ���Ϊ�գ�"));
		return;
	}
	if(sEmployName.GetLength() == 0)
	{
		MessageBox(_T("Ա�����ֲ���Ϊ�գ�"));
		return;
	}
	CChildView* pView = (CChildView*)GetParent();
	pView->m_dbOperation = DB_Operation(ENUM_COMMAND_DELETE_EMPLOY,sCompany,sDepartment,sEmployName);

	return OnOK();
}
