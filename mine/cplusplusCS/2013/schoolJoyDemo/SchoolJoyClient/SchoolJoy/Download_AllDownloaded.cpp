// Download_AllDownloaded.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SchoolJoy.h"
#include "Download_AllDownloaded.h"
#include "afxdialogex.h"


// CDownload_AllDownloaded �Ի���

IMPLEMENT_DYNAMIC(CDownload_AllDownloaded, CDialogEx)

CDownload_AllDownloaded::CDownload_AllDownloaded(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDownload_AllDownloaded::IDD, pParent)
{

}

CDownload_AllDownloaded::~CDownload_AllDownloaded()
{
}

void CDownload_AllDownloaded::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Download_AllDownloaded, m_List_Download_AllDownloaded);
}


BEGIN_MESSAGE_MAP(CDownload_AllDownloaded, CDialogEx)
END_MESSAGE_MAP()


// CDownload_AllDownloaded ��Ϣ�������

//Add by wqdnan ���ڴ����б�ĸ�ʽ��д���ʼֵ
void CDownload_AllDownloaded::InitDownload_AllDownloaded(void)
{
	CRect rect;    
 
    // ��ȡ��������б���ͼ�ؼ���λ�úʹ�С    
    m_List_Download_AllDownloaded.GetClientRect(&rect);    
 
    // Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����    
    m_List_Download_AllDownloaded.SetExtendedStyle(m_List_Download_AllDownloaded.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   

	m_List_Download_AllDownloaded.SetTextColor(RGB(126, 192, 238));

	m_List_Download_AllDownloaded.SetTextBkColor(RGB(47, 79, 79));
 
    // Ϊ�б���ͼ�ؼ��������    
    m_List_Download_AllDownloaded.InsertColumn(0, _T("�����ļ�"), LVCFMT_CENTER, rect.Width()/4, 0);    
    m_List_Download_AllDownloaded.InsertColumn(1, _T("�ļ���С"), LVCFMT_CENTER, rect.Width()/4, 1);    
    m_List_Download_AllDownloaded.InsertColumn(2, _T("�ļ�����"), LVCFMT_CENTER, rect.Width()/4, 2);    
	m_List_Download_AllDownloaded.InsertColumn(1, _T("���ʱ��"), LVCFMT_CENTER, rect.Width()/4, 3);    
 

    // ���б���ͼ�ؼ��в����б���������б������ı�    
    m_List_Download_AllDownloaded.InsertItem(0, _T("�ļ�һ"));    
    m_List_Download_AllDownloaded.SetItemText(0, 1, _T("0"));    
    m_List_Download_AllDownloaded.SetItemText(0, 2, _T("0"));    
    m_List_Download_AllDownloaded.SetItemText(0, 3, _T("0"));  
	m_List_Download_AllDownloaded.InsertItem(1, _T("�ļ���"));    
    m_List_Download_AllDownloaded.SetItemText(1, 1, _T("0"));    
    m_List_Download_AllDownloaded.SetItemText(1, 2, _T("0"));    
    m_List_Download_AllDownloaded.SetItemText(1, 3, _T("0"));  
}

//Add by wqdnan ���ڵ��ó�ʼ���б�����ֵ
BOOL CDownload_AllDownloaded::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	InitDownload_AllDownloaded();
	return 0;
}
