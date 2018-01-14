// ConnectSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SchoolJoy.h"
#include "ConnectSet.h"
#include "afxdialogex.h"


// CConnectSet �Ի���
#define SERVERPORT 12344
#define SERVERIP   "10.6.8.16" 
CString CConnectSet::ServerIP=SERVERIP;
int CConnectSet::ServerPort=SERVERPORT;


IMPLEMENT_DYNAMIC(CConnectSet, CDialogEx)

CConnectSet::CConnectSet(CWnd* pParent /*=NULL*/): CDialogEx(CConnectSet::IDD, pParent)

{
	m_serverIp=SERVERIP;
	m_serverPort=SERVERPORT;
}

CConnectSet::~CConnectSet()
{
}

void CConnectSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ServerIp, m_serverIp);
	DDX_Text(pDX, IDC_EDIT_ServerPort, m_serverPort);
}


BEGIN_MESSAGE_MAP(CConnectSet, CDialogEx)
//	ON_BN_CLICKED(IDC_BUTTON1, &CConnectSet::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_Cancel, &CConnectSet::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CConnectSet::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CConnectSet ��Ϣ�������


//void CConnectSet::OnBnClickedButton1()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}
void CConnectSet::OnOK()
{
}
void CConnectSet::OnCancel()
{
}

void CConnectSet::OnBnClickedButtonCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}



void CConnectSet::OnBnClickedButtonOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	ServerIP=m_serverIp;
	ServerPort=m_serverPort;
	CDialog::OnOK();
}
