// Download_Downloaded.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SchoolJoy.h"
#include "Download_Downloaded.h"
#include "afxdialogex.h"


// CDownload_Downloaded �Ի���

IMPLEMENT_DYNAMIC(CDownload_Downloaded, CDialogEx)

CDownload_Downloaded::CDownload_Downloaded(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDownload_Downloaded::IDD, pParent)
{

}

CDownload_Downloaded::~CDownload_Downloaded()
{
}

void CDownload_Downloaded::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Download_Downloaded, m_Download_Downloaded);
}


BEGIN_MESSAGE_MAP(CDownload_Downloaded, CDialogEx)
END_MESSAGE_MAP()


// CDownload_Downloaded ��Ϣ�������

//Add by wqdnan ���ڴ����б�ĸ�ʽ��д���ʼֵ
void CDownload_Downloaded::InitDownload_Downloaded(void)
{
	CRect rect;    
 
    // ��ȡ��������б���ͼ�ؼ���λ�úʹ�С    
    m_Download_Downloaded.GetClientRect(&rect);    
 
    // Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����    
    m_Download_Downloaded.SetExtendedStyle(m_Download_Downloaded.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);    
 
    // Ϊ�б���ͼ�ؼ��������    
    m_Download_Downloaded.InsertColumn(0, _T("�����ļ�"), LVCFMT_CENTER, rect.Width()/4, 0);    
    m_Download_Downloaded.InsertColumn(1, _T("�ļ���С"), LVCFMT_CENTER, rect.Width()/4, 1);    
    m_Download_Downloaded.InsertColumn(2, _T("�ļ�����"), LVCFMT_CENTER, rect.Width()/4, 2);    
	m_Download_Downloaded.InsertColumn(1, _T("���ʱ��"), LVCFMT_CENTER, rect.Width()/4, 3);    
 

    // ���б���ͼ�ؼ��в����б���������б������ı�    
    m_Download_Downloaded.InsertItem(0, _T("�ļ�һ"));    
    m_Download_Downloaded.SetItemText(0, 1, _T("0"));    
    m_Download_Downloaded.SetItemText(0, 2, _T("0"));    
    m_Download_Downloaded.SetItemText(0, 3, _T("0"));   
}


BOOL CDownload_Downloaded::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	InitDownload_Downloaded();
	return 0;
}
