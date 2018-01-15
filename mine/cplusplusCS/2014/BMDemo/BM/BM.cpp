// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// BM.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "BM.h"
#include "MainFrm.h"

#include "BMDoc.h"
#include "BMView.h"
#include "DBConf.h"
#include "Login.h"
#include "MainFormView.h"


//#include "Sock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBMApp

BEGIN_MESSAGE_MAP(CBMApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CBMApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	
END_MESSAGE_MAP()


// CBMApp ����
HMODULE CBMApp::hMod = NULL;
CBMApp::CBMApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("BM.AppID.NoVersion"));
	hMod = LoadLibrary(_T("riched20.dll"));
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CBMApp ����

CBMApp theApp;


BOOL CBMApp::LoginInitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBMDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CMainFormView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	
	HICON hIcon=AfxGetApp()->LoadIcon(IDI_ICON_BMMAIN);
	m_pMainWnd->SetIcon(hIcon,TRUE);
	m_pMainWnd->SetIcon(hIcon,FALSE);
	
	


	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	CDBConf pdbconfDlg;
	pdbconfDlg.DoModal();
	//////////***********����Ϊ�ڴ�й¶��⺯��**********************////////////////////////////////
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	///////////**********����Ϊ�ڴ�й¶��⺯��***********************///////////////////////////////
	return TRUE;
}


// CBMApp ��ʼ��
BOOL CBMApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	
	hMod = LoadLibrary(_T("riched20.dll"));    //ʹ��rich edit control �ؼ�
	
	InitSocket();          //��ʼ���׽���	

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	LoginInitInstance();
	return TRUE;
}

int CBMApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);
	FreeLibrary(hMod);
	if(CSock::m_pPosAuthority != NULL)
	{
		delete CSock::m_pPosAuthority;
		CSock::m_pPosAuthority = NULL;
	}
	return CWinAppEx::ExitInstance();
}

// CBMApp ��Ϣ�������


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
public:
	afx_msg void OnBtnPerforMg();
	//afx_msg void OnUpdateIdsStatusPane2(CCmdUI *pCmdUI);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	//afx_msg LRESULT OnStartreqMt(WPARAM wParam, LPARAM lParam);
	//afx_msg LRESULT OnEndReqMt(WPARAM wParam, LPARAM lParam);
public:
	
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(ID_BTN_PERFORMENCEMG, &CAboutDlg::OnBtnPerforMg)
	//ON_UPDATE_COMMAND_UI(IDS_STATUS_PANE2, &CAboutDlg::OnUpdateIdsStatusPane2)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CBMApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CBMApp �Զ������/���淽��

void CBMApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CBMApp::LoadCustomState()
{
}

void CBMApp::SaveCustomState()
{
}

// CBMApp ��Ϣ�������


void CBMApp::InitSocket(void)
{
	
	WORD	wVersionRequested;			//����socket�汾
	WSADATA	wsaData;					//wsaData�ṹ
	int		nErrCode;					//����ֵ
	
	wVersionRequested = MAKEWORD( 2, 2 );//����windows Sockets 2.2�汾	
	nErrCode = WSAStartup( wVersionRequested, &wsaData );
	if ( 0 != nErrCode )
	{
		return;
	}
	
	//�����׽���
	m_sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_sHost)
	{
		AfxMessageBox(_T("�����׽���ʧ��"));
		return;
	}
	
	//����ϵͳ��������ΪĬ�ϵ�BUF_TIMES��
	unsigned int uiRcvBuf;
	int uiRcvBufLen = sizeof(uiRcvBuf);
	nErrCode= getsockopt(m_sHost, SOL_SOCKET, SO_RCVBUF,(char*)&uiRcvBuf, &uiRcvBufLen);
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("��ȡϵͳĬ�Ϸ������ݻ�����ʧ�ܣ�"));
		return;
	}
	uiRcvBuf *= BUF_TIMES;
	nErrCode = setsockopt(m_sHost, SOL_SOCKET, SO_RCVBUF,(char*)&uiRcvBuf, uiRcvBufLen);
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("�޸�ϵͳ�������ݻ�����ʧ�ܣ�"));
		return;
	}

	//�������ϵͳ�������ݻ������Ƿ�ɹ�
	unsigned int uiNewRcvBuf;
	getsockopt(m_sHost, SOL_SOCKET, SO_RCVBUF,(char*)&uiNewRcvBuf, &uiRcvBufLen);
	if (SOCKET_ERROR == nErrCode || uiNewRcvBuf != uiRcvBuf)
	{
		AfxMessageBox(_T("�޸�ϵͳ�������ݻ�����ʧ�ܣ�"));;
		return ;
	}

	return;
}


HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor == CTLCOLOR_DLG){
		pDC->SetTextColor(RGB(0,0,0)); 
		pDC->SetBkColor(RGB(185,211,255)); 
		HBRUSH b=CreateSolidBrush(RGB(185,211,255)); 
		return b;
	}
	return hbr;
}

