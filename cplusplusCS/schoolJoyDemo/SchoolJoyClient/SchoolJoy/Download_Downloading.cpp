// Download_Downloading.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SchoolJoy.h"
#include "Download_Downloading.h"
#include "afxdialogex.h"
#include "ThreadOperate.h"


// CDownload_Downloading �Ի���

IMPLEMENT_DYNAMIC(CDownload_Downloading, CDialogEx)

CDownload_Downloading::CDownload_Downloading(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDownload_Downloading::IDD, pParent)
{
	m_filename=_T("");
	m_filepath=_T("");
}

CDownload_Downloading::~CDownload_Downloading()
{
}

void CDownload_Downloading::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Download_Downloading, m_Download_Downloading);
}


BEGIN_MESSAGE_MAP(CDownload_Downloading, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON1, &CDownload_Downloading::OnBnClickedButton1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_Download_Downloading, &CDownload_Downloading::OnDblclkListDownloadDownloading)
	ON_WM_TIMER()
//	ON_MESSAGE(WM_OKSEARCH, &CDownload_Downloading::OnOkSearch)
END_MESSAGE_MAP()


// CDownload_Downloading ��Ϣ�������

//Add by wqdnan ���ڴ����б�ĸ�ʽ��д���ʼֵ
void CDownload_Downloading::InitDownload_Downloading(void)
{
	CRect rect;    
 
    // ��ȡ��������б���ͼ�ؼ���λ�úʹ�С    
    m_Download_Downloading.GetClientRect(&rect);    
 
    // Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����    
    m_Download_Downloading.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);   

	m_Download_Downloading.SetTextColor(RGB(139, 90, 43));

	m_Download_Downloading.SetTextBkColor(RGB(255, 236, 139));
 

	m_Download_Downloading.InsertColumn(0, _T("�ļ���"), LVCFMT_LEFT, 100);    
    m_Download_Downloading.InsertColumn(1, _T("�ļ�����"), LVCFMT_LEFT, 100);
	m_Download_Downloading.InsertColumn(2, _T("�ļ���С"), LVCFMT_LEFT, 100);
    m_Download_Downloading.InsertColumn(3, _T("ԭ�ļ�·��"), LVCFMT_LEFT, 150);
	m_Download_Downloading.InsertColumn(4, _T("���ؽ���"), LVCFMT_LEFT, 100);
	m_Download_Downloading.InsertColumn(5, _T("�����ٶ�"), LVCFMT_LEFT, 100);    
    m_Download_Downloading.InsertColumn(6, _T("����״̬"), LVCFMT_LEFT, 100);


}

//Add by wqdnan ���ڵ��ó�ʼ���б�����ֵ
BOOL CDownload_Downloading::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	InitDownload_Downloading();
	return 0;
}

void CDownload_Downloading::NewDownLoad(CString &filename,CString &filetype,CString &filesize,CString &filepath,int &j)
{
	CDownload_Downloading *dlg=(CDownload_Downloading *)this;
	dlg->m_Download_Downloading.InsertItem(j,NULL);
	dlg->m_Download_Downloading.SetItemText(j,0,filename);
	dlg->m_Download_Downloading.SetItemText(j,1,filetype);
	dlg->m_Download_Downloading.SetItemText(j,2,filesize);
	dlg->m_Download_Downloading.SetItemText(j,3,filepath);
	dlg->m_Download_Downloading.SetItemText(j,4,_T(""));
	dlg->m_Download_Downloading.SetItemText(j,5,_T(""));
	dlg->m_Download_Downloading.SetItemText(j,6,_T("�ȴ�����"));
}




void CDownload_Downloading::OnDblclkListDownloadDownloading(NMHDR *pNMHDR, LRESULT *pResult)
{
	 //˫��listctrl�е�ѡ���п�ʼ����
	StratToDownLoad();
}
void CDownload_Downloading::StratToDownLoad(void)    //������ʼ���ذ�ť����Ӧ�������������ط�ʽ
{
	for(int i=0; i<m_Download_Downloading.GetItemCount(); i++)
	{
		if( m_Download_Downloading.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{	
			m_filename=m_Download_Downloading.GetItemText(i,0);
			m_filepath=m_Download_Downloading.GetItemText(i,3);
			this->m_Download_Downloading.SetItemText(i,6,_T("����������"));
			this->m_NUMDownloading=i;//��¼�������صĵڼ���
			ThreadOperate downloadThread;//ת�������߳�  ���غ�����ʾ��
			void* dialog=(void*)this;////////////////
			downloadThread.startRequireInfoThread(dialog);//////
			Sleep(1000);//�������һ�룬��ѡ�ж���������ʱ�򣬷�ֹ����ִ��̫������ֵ���ݶ�ʧ
		}
	}
}

void CDownload_Downloading::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	switch (nIDEvent)
	{
	case TIMER_SPEED:
		_pthreadoperate->UpdateSpeed(this);
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

