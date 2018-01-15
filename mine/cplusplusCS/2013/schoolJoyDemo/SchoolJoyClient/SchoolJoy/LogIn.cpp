// LogIn.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SchoolJoy.h"
#include "LogIn.h"
#include "afxdialogex.h"
#include "Register.h"
#include "ADOConn.h"
#include "ThreadOperate.h"
#include "ConnectSet.h"


// CLogIn �Ի���
CString m_usernameShow;//������ȫ�ַ�Χ��ʹ��
CString CLogIn::username=_T("");
CString CLogIn::password=_T("");

IMPLEMENT_DYNAMIC(CLogIn, CDialogEx)

CLogIn::CLogIn(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogIn::IDD, pParent)
	, m_edit_username(_T(""))
	, m_edit_password(_T(""))
//	, m_usernameShow(_T(""))
{

	m_loginstatus = LogInWrong;
}

CLogIn::~CLogIn()
{
}

void CLogIn::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Username, m_edit_username);
	DDX_Text(pDX, IDC_EDIT_Password, m_edit_password);
}


BEGIN_MESSAGE_MAP(CLogIn, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLogIn::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_LogIn, &CLogIn::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_Register, &CLogIn::OnBnClickedButtonRegister)
	ON_BN_CLICKED(IDC_BUTTON_AdvancedSet, &CLogIn::OnBnClickedButtonAdvancedset)
	ON_BN_CLICKED(IDC_BUTTON_Quit, &CLogIn::OnBnClickedButtonQuit)
END_MESSAGE_MAP()


// CLogIn ��Ϣ�������


void CLogIn::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CDialogEx::OnOK();
}


void CLogIn::OnBnClickedButtonLogin()
{

	UpdateData(TRUE);
	if (""==m_edit_username)
	{
		MessageBox(_T("�û�������Ϊ��"),_T("����"),MB_ICONWARNING|MB_OK);
	return;	
	}
	if (""==m_edit_password)
	{
		MessageBox(_T("���벻��Ϊ��"),_T("����"),MB_ICONWARNING|MB_OK);
		return;	
	}
	username=m_edit_username;
	password=m_edit_password;
	ThreadOperate loginThread;
	void *dialog=this;
	loginThread.StartLoginThread(dialog);	
	CDialogEx::OnOK();
	return;
}

int CLogIn::GetLogInStatus(void)
{
	return m_loginstatus;
}


void CLogIn::OnBnClickedButtonRegister()
{
	CRegister  cregister;
	cregister.SetBackgroundColor(RGB(95,158,160));
	cregister.DoModal();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}


CString CLogIn::GetUsername(void)
{
	return m_edit_username;
}


void CLogIn::OnBnClickedButtonAdvancedset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CConnectSet connectset;
	connectset.SetBackgroundColor(RGB(95,158,160));
	connectset.DoModal();
}


void CLogIn::OnBnClickedButtonQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ThreadOperate QuitThread;
	void *dialog=this;
	QuitThread.StartQuitThread(dialog);	
	//CDialogEx::OnOK();
	return;
}
