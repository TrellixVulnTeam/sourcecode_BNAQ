
// SchoolJoyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SchoolJoy.h"
#include "SchoolJoyDlg.h"
#include "afxdialogex.h"
#include "ThreadOperate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define  WM_TRAY WM_USER+1    //����;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSchoolJoyDlg �Ի���


CSchoolJoyDlg::CSchoolJoyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSchoolJoyDlg::IDD, pParent)
//	, m_edit_main_show(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSchoolJoyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_Main, m_tab_main);
//	  DDX_Control(pDX, IDC_EDIT_Main_Show, m_Edit_Main_Show);
//	DDX_Text(pDX, IDC_EDIT_Main_Show, m_edit_main_show);
	DDX_Control(pDX, IDC_BUTTON_Download, m_button_download);
	DDX_Control(pDX, IDC_BUTTON_Upload, m_button_upload);
}

BEGIN_MESSAGE_MAP(CSchoolJoyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Search, &CSchoolJoyDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_Download, &CSchoolJoyDlg::OnBnClickedButtonDownload)
	ON_BN_CLICKED(IDC_BUTTON_Upload, &CSchoolJoyDlg::OnBnClickedButtonUpload)
	ON_BN_CLICKED(IDC_BUTTON_LogIn, &CSchoolJoyDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_Set, &CSchoolJoyDlg::OnBnClickedButtonSet)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_Main, &CSchoolJoyDlg::OnTcnSelchangeTabMain)
	ON_MESSAGE(WM_TRAY,OnTray)
END_MESSAGE_MAP()


// CSchoolJoyDlg ��Ϣ�������

BOOL CSchoolJoyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	UpdateData(TRUE);
	//m_edit_main_show = "δ��¼�����ȵ�¼";
	UpdateData(FALSE);

	 ShowTray();   //������ʾ    
	//����Tab��ǩ
	m_tab_main.InsertItem(0, _T("����"));         // �����һ����ǩ����    
	m_search.Create(IDD_DIALOG_Search, &m_tab_main);    // ������һ����ǩҳ 
	m_search.SetBackgroundColor(RGB(139,134,130));


	m_tab_main.InsertItem(1, _T("����"));  // ����ڶ�����ǩ����
	m_download.Create(IDD_DIALOG_Download, &m_tab_main);// �����ڶ�����ǩҳ
	m_download.SetBackgroundColor(RGB(139,134,130));  

	m_tab_main.InsertItem(2, _T("�ϴ�"));
	m_upload.Create(IDD_DIALOG_Upload, &m_tab_main); 
	m_upload.SetBackgroundColor(RGB(139,134,130));

	

	
    // ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ    
    CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect 
	m_tab_main.GetClientRect(&tabRect);    
    tabRect.left += 1;    
    tabRect.right -= 1;    
    tabRect.top += 25;    
    tabRect.bottom -= 1;

	m_search.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);    
	m_upload.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
    m_download.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	ThreadOperate mainThread;//�������߳�
	void* dialog=(void*)this;////////////////
	mainThread.startMainThread(dialog);//////

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSchoolJoyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSchoolJoyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{ 
		
          CPaintDC   dc(this);   
          CRect   rect;   
          GetClientRect(&rect);   
          CDC   dcMem;   
          dcMem.CreateCompatibleDC(&dc);   
          CBitmap   bmpBackground;   
          bmpBackground.LoadBitmap(IDB_BITMAP_background3);   //IDB_BITMAP_background3 �����Լ���ͼ��Ӧ��ID  
                                                                             
                  
          BITMAP   bitmap;   
          bmpBackground.GetBitmap(&bitmap);   
          CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
          dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
         bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);   
	}
	   HBITMAP hBitmap;                          
       hBitmap = (HBITMAP)::LoadImage(NULL,".\\res\\download.bmp",
		       IMAGE_BITMAP,80,80,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	   ((CButton *)GetDlgItem(IDC_BUTTON_Download))->SetBitmap(hBitmap); 
	   hBitmap = (HBITMAP)::LoadImage(NULL,".\\res\\set.bmp",
		       IMAGE_BITMAP,80,80,LR_LOADFROMFILE|LR_CREATEDIBSECTION);      
	   ((CButton *)GetDlgItem(IDC_BUTTON_Set))->SetBitmap(hBitmap);
	    hBitmap = (HBITMAP)::LoadImage(NULL,".\\res\\upload.bmp",              //����BUTTON��ͼ��
		       IMAGE_BITMAP,80,80,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	   ((CButton *)GetDlgItem(IDC_BUTTON_Upload))->SetBitmap(hBitmap);
	    hBitmap = (HBITMAP)::LoadImage(NULL,".\\res\\user.bmp",
		       IMAGE_BITMAP,80,80,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	   ((CButton *)GetDlgItem(IDC_BUTTON_LogIn))->SetBitmap(hBitmap);
	    hBitmap = (HBITMAP)::LoadImage(NULL,".\\res\\search.bmp",
		       IMAGE_BITMAP,80,80,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	   ((CButton *)GetDlgItem(IDC_BUTTON_Search))->SetBitmap(hBitmap);
	  
	   
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSchoolJoyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSchoolJoyDlg::OnBnClickedButtonSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect 
    // ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ   
    m_tab_main.GetClientRect(&tabRect);    
    tabRect.left += 1;    
    tabRect.right -= 1;    
    tabRect.top += 25;    
    tabRect.bottom -= 1;
	// �����ǩ�ؼ���ǰѡ���ǩΪ�������������ء����ء����ϴ���    
    m_search.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);    
    m_download.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_upload.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	int Label = m_tab_main.SetCurSel(0);

}


void CSchoolJoyDlg::OnBnClickedButtonDownload()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect    
    // ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ    
    m_tab_main.GetClientRect(&tabRect);    
    tabRect.left += 1;    
    tabRect.right -= 1;    
    tabRect.top += 25;    
    tabRect.bottom -= 1;
	
	// �����ǩ�ؼ���ǰѡ���ǩΪ�����ء������ء����������ϴ���    
    m_download.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	m_search.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);    
	m_upload.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	int Label = m_tab_main.SetCurSel(1);

}


void CSchoolJoyDlg::OnBnClickedButtonUpload()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect 
    // ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ    
    m_tab_main.GetClientRect(&tabRect);    
    tabRect.left += 1;    
    tabRect.right -= 1;    
    tabRect.top += 25;    
    tabRect.bottom -= 1;
	// �����ǩ�ؼ���ǰѡ���ǩΪ���ϴ��������ء����ء���������    
	m_upload.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
    m_search.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);    
    m_download.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	int Label = m_tab_main.SetCurSel(2);
	
}


void CSchoolJoyDlg::OnBnClickedButtonLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CLogIn logIn;
	logIn.SetBackgroundColor(RGB(95,158,160));   //���ñ���ɫ
	INT_PTR nResponse = logIn.DoModal();
}


void CSchoolJoyDlg::OnBnClickedButtonSet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSet set;
	set.SetBackgroundColor(RGB(95,158,160));
	//set.ReadSet();
	INT_PTR nResponse = set.DoModal();
	
}
 
void CSchoolJoyDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect 
    // ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ    
    m_tab_main.GetClientRect(&tabRect);    
    tabRect.left += 1;    
    tabRect.right -= 1;    
    tabRect.top += 25;    
    tabRect.bottom -= 1;

	switch(m_tab_main.GetCurSel())
	{
		case 0:
			m_upload.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_search.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);    
			m_download.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			break;

		case 1:
			m_upload.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_search.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);    
			m_download.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
			break;

		case 2:
			m_upload.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
			m_search.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);    
			m_download.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			break;

		default:
			break;


	}
}


//----------------------------------------������ʾ
void CSchoolJoyDlg::ShowTray(){  
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.uCallbackMessage = WM_TRAY;    //WM_TRAYΪ�Զ�����ϢWM_USER+103
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	//wcscpy_s(p,_T("У԰����"));
	::Shell_NotifyIcon(NIM_ADD, &nid);
	this->ShowWindow(SW_HIDE); //����������
}

//--------------------------------------������Ϣ����
LRESULT CSchoolJoyDlg::OnTray(WPARAM wParam, LPARAM lParam){
	if(wParam!=IDR_MAINFRAME)
		return 1;
	switch (lParam){
	case WM_RBUTTONDOWN:     //��갴���Ҽ�ʱ�Ĵ���
		{
			LPPOINT Ipoint=new tagPOINT;
			::GetCursorPos(Ipoint);  //�õ����λ��
			CMenu menu;
			menu.CreatePopupMenu();  //����һ�������˵� 
			//menu.AppendMenuW(MF_POPUP,(UINT_PTR)menu.m_hMenu,_T("�ر�"));//����Ӳ˵���
			menu.AppendMenu(MF_STRING,WM_DESTROY,_T("�ر�"));//���Ӳ˵���رա������������ϢWM_DESTROY�������ڣ������أ��������������
			menu.TrackPopupMenu(TPM_LEFTALIGN,Ipoint->x,Ipoint->y,this);//���ص����˵�
			HMENU hmenu=menu.Detach();
			menu.DestroyMenu();
			delete Ipoint;
		}
		break;
	case WM_LBUTTONDOWN:  //��갴�����ʱ�Ĵ���
		{
			this->ShowWindow(SW_SHOWNORMAL);  //��ʾ������
		}
		break;
	}
	return 0;
}