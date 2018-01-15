// Download.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SchoolJoy.h"
#include "Download.h"
#include "afxdialogex.h"
#include "SchoolJoyDlg.h"


// CDownload �Ի���

IMPLEMENT_DYNAMIC(CDownload, CDialogEx)

CDownload::CDownload(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDownload::IDD, pParent)
{

}

CDownload::~CDownload()
{
}

void CDownload::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LIST_Download, m_List_Download);
	DDX_Control(pDX, IDC_TAB_Download, m_tab_download);
}


BEGIN_MESSAGE_MAP(CDownload, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_Download, &CDownload::OnSelchangeTabDownload)
	ON_BN_CLICKED(IDC_BUTTON_StartDownload, &CDownload::OnBnClickedButtonStartdownload)
END_MESSAGE_MAP()


// CDownload ��Ϣ�������


BOOL CDownload::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	InitDownload();
	return 0;
}


void CDownload::InitDownload(void)
{
	CRect tabRect;   // ��ǩ�ؼ��ͻ�����λ�úʹ�С    
    m_tab_download.InsertItem(0, _T("��������"));         // �����һ����ǩ����  
	m_download_downloading.Create(IDD_DIALOG_Download_Downloading, &m_tab_download);    // ������һ����ǩҳ
    m_tab_download.InsertItem(1, _T("���������"));  // ����ڶ�����ǩ����
	m_download_downloaded.Create(IDD_DIALOG_Download_Downloaded, &m_tab_download); // �����ڶ�����ǩҳ 
	m_tab_download.InsertItem(2, _T("��������"));   
	m_download_alldownloaded.Create(IDD_DIALOG_Download_AllDownloaded, &m_tab_download); 
 
    m_tab_download.GetClientRect(&tabRect);    // ��ȡ��ǩ�ؼ��ͻ���Rect    
    // ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ    
    tabRect.left += 1;                   
    tabRect.right -= 1;    
    tabRect.top += 25;    
    tabRect.bottom -= 1;    
    // ���ݵ����õ�tabRect����m_jzmDlg�ӶԻ��򣬲�����Ϊ��ʾ    
    m_download_downloading.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);    
    // ���ݵ����õ�tabRect����m_androidDlg�ӶԻ��򣬲�����Ϊ����    
    m_download_downloaded.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
	m_download_alldownloaded.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 

	//Add by wqdnan ���ڳ�ʼ������Tab�ؼ�������ʾ������Tab������Downloading��Downloaded��AllDownload�����Ի�����й���

}


void CDownload::OnSelchangeTabDownload(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect    
 
    // ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ    
    m_tab_download.GetClientRect(&tabRect);    
    tabRect.left += 1;    
    tabRect.right -= 1;    
    tabRect.top += 25;    
    tabRect.bottom -= 1;    
 
    switch (m_tab_download.GetCurSel())    
    {    
    // �����ǩ�ؼ���ǰѡ���ǩΪ���������ء�������ʾDownloading�Ի�������Downloaded��AllDownload�Ի���    
    case 0:    
        m_download_downloading.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		//m_download_downloading.InsertFile()
        m_download_downloaded.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_download_alldownloaded.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
        break;    
    // �����ǩ�ؼ���ǰѡ���ǩΪ����������ء�������ʾDownloaded�Ի�������Downloading��AllDownload�Ի���     
    case 1:    
        m_download_downloading.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);    
        m_download_downloaded.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW); 
		m_download_alldownloaded.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
        break;   
	// �����ǩ�ؼ���ǰѡ���ǩΪ���������ء�������ʾAllDownload�Ի�������Downloaded��Downloading�Ի��� 
	case 2:
		m_download_downloading.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);    
        m_download_downloaded.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
		m_download_alldownloaded.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
    default:    
        break;    
    }    

}


void CDownload::OnBnClickedButtonStartdownload()
{
	this->m_download_downloading.StratToDownLoad();
}
