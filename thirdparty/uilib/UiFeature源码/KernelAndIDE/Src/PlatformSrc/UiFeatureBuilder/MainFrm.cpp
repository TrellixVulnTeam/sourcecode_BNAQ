
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "MainFrm.h"
#include "UiFeatureDefs.h"
#include "CreateNewSkinProject.h"
#include "UiFeatureBuilderDoc.h"
#include "UiFeatureBuilderView.h"
//#include "..\UiFeatureKernel\UiFeatureAes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_FILE_NEW, &CMainFrame::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CMainFrame::OnFileSave)
	ON_COMMAND(ID_FILE_CLOSE, &CMainFrame::OnFileClose)
	ON_COMMAND(ID_APP_EXIT, &CMainFrame::OnAppExit)
	ON_COMMAND(IDTB_RUN_TEST, &CMainFrame::OnRunTest)
	ON_COMMAND(IDM_SET_PASSWORD, &CMainFrame::OnSetPassword)
	ON_MESSAGE(OPEN_SKIN_BY_DB_CLICK, OnOpenSkinByDbClick)
	ON_UPDATE_COMMAND_UI(IDTB_RUN_TEST, &CMainFrame::OnUpdateRunTest)
	ON_WM_SETCURSOR()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_SILVER);
	theApp.InitShellManager();

	m_hClassViewIcon = NULL;
	m_hPropertiesBarIcon = NULL;

	m_pView = NULL;
	m_hKernelDll = NULL;
	m_pUiKernel = NULL;
	m_pSkinMgr = NULL;
	m_hControlDll = NULL;
	m_pRegControlMap = NULL;
	m_bInitOk = false;
	m_bNeedSave = false;
	m_nViewCursor = -1;
	m_bProjectInitState = false;

	m_strCurSkinDir = _T("");
	m_strCurSkinName = _T("");
	m_strCurUfpPath = _T("");

	m_strNewUfpPath = _T("");
	m_strNewSkinDir = _T("");
	m_strNewSkinName = _T("");
	m_strUserPassword = _T("");
	m_pSkinFileItem = NULL;

	//CUiFeatureAes keytest1, keytest2, keytest3;

	//string strKeyFrom = "abcdef1kerutdfvvljdefrgthyujkio2abcdef1kerutdfvvljdefrgthyujkio2abcdef1kerutdfvvljdefrgthyujkio2abcdef1kerutdfvvljdefrgthyujkio2";
	//BYTE *pOutKey = NULL;
	//int nOutLen = 0;
	//keytest1.CreateAesPassword((char*)strKeyFrom.c_str(), &pOutKey, nOutLen);

	//string strKey = "";
	//keytest2.GetUserPassword(pOutKey, nOutLen, strKey);

	//if (keytest3.Compare(pOutKey, nOutLen, "abcdef1kerutdfvvljdefrgthyujkio2abcdef1kerutdfvvljdefrgthyujkio2abcdef1kerutdfvvljdefrgthyujkio2abcdef1kerutdfvvljdefrgthyujkio2"))
	//{
	//	int nR = 0;
	//}
	//int ne = 0;
}

CMainFrame::~CMainFrame()
{
	SAFE_FREE_LIBRARY(m_hControlDll);
	SAFE_FREE_LIBRARY(m_hKernelDll);
}

// 设置属性发生变化，需要保存
void CMainFrame::SetPropetryChange()
{
	m_bNeedSave = true;
}

void CMainFrame::SetView(CUiFeatureBuilderView *pView)
{
	m_pView = pView;
	if (m_pView != NULL)
	{
		m_pView->Init(m_pUiKernel, m_wndControls.GetControlList(), m_wndWindowView.GetViewTreeCtrl(), m_wndProperties.GetPropetryCtrl());
		m_wndControls.GetControlList()->SetBuilderView(m_pView);
		m_wndWindowView.GetViewTreeCtrl()->SetBuilderView(m_pView);
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("未能创建菜单栏\n");
		return -1;      // 未能创建
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// 防止菜单栏在激活时获得焦点
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// 允许用户定义的工具栏操作:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果您不希望工具栏和菜单栏可停靠，请删除这五行
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);

//////////////////////////////////////////////////////////////////////////
	if (!m_wndTestRunToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), ID_RUN_TOOL_BAR) ||
		!m_wndTestRunToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_RUN_TEST_TOOLBAR : IDR_MAINFRAME))
	{
		TRACE0("未能创建测试工具栏\n");
		return -1;
	}

	m_wndTestRunToolBar.SetWindowText(_T("运行窗口"));
	m_wndTestRunToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndTestRunToolBar);

//////////////////////////////////////////////////////////////////////////


	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 加载菜单项图像(不在任何标准工具栏上):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// 创建停靠窗口
	if (!CreateDockingWindows())
	{
		TRACE0("未能创建停靠窗口\n");
		return -1;
	}

//	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndWindowView.EnableDocking(CBRS_ALIGN_ANY);
//	DockPane(&m_wndFileView);
	CDockablePane* pTabbedBar = NULL;
//	m_wndWindowView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	DockPane(&m_wndWindowView);

	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);

	m_wndControls.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndControls);

	// 启用工具栏和停靠窗口菜单替换
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// 启用快速(按住 Alt 拖动)工具栏自定义
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// 加载用户定义的工具栏图像
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			m_UserImages.SetImageSize(CSize(16, 16), FALSE);
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// 启用菜单个性化(最近使用的命令)
	// TODO: 定义您自己的基本命令，确保每个下拉菜单至少有一个基本命令。
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_SORTING_SORTALPHABETIC);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYTYPE);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYACCESS);
	lstBasicCommands.AddTail(ID_SORTING_GROUPBYTYPE);

	// 让菜单完全的显示出来，需要注释此代码
//	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	// 设置界面显示的默认字体
	LOGFONT logfont = {0};
	::SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LOGFONT), &logfont, 0);
	afxGlobalData.SetMenuFont(&logfont, true);

	// 改文档名称
	this->SetWindowText(_T("UiFeatureBuilder"));
//////////////////////////////////////////////////////////////////////////
	InitUiFeatureKernel();
//////////////////////////////////////////////////////////////////////////

	// 双击直接打开的操作
	this->PostMessage(OPEN_SKIN_BY_DB_CLICK, NULL, NULL);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// 把cs.style中的FWS_ADDTOTITLE风格去掉
	cs.style &= ~FWS_ADDTOTITLE;

	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;

	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// 创建Dui窗口视图
	CString strWindowView;
	bNameValid = strWindowView.LoadString(IDS_WINDOW_VIEW);
	ASSERT(bNameValid);
	if (!m_wndWindowView.Create(strWindowView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_WINDOW_VIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“Dui窗口视图”窗口\n");
		return FALSE; // 未能创建
	}

	// 创建资源视图
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	//if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_RES_VIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	//{
	//	TRACE0("未能创建“资源视图”窗口\n");
	//	return FALSE; // 未能创建
	//}

	// 创建属性视图窗口
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“属性视图”窗口\n");
		return FALSE; // 未能创建
	}

	// 创建控件视图窗口
	if (!m_wndControls.Create(_T("控件视图"), this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CONTROLSWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“控件”窗口\n");
		return FALSE; // 未能创建
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
//	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
//	m_wndFileView.SetIcon(hFileViewIcon, FALSE);

	m_hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndWindowView.SetIcon(m_hClassViewIcon, FALSE);

	m_hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(m_hPropertiesBarIcon, FALSE);
	m_wndControls.SetIcon(m_hPropertiesBarIcon, FALSE);
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 扫描菜单*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// 基类将执行真正的工作

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// 为所有用户工具栏启用自定义按钮
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}

BOOL CMainFrame::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (m_nViewCursor != -1)
	{
		CUiFeatureBuilderView *pView = (CUiFeatureBuilderView*)this->GetActiveView();
		if (pView != NULL)
		{
			POINT pt;
			::GetCursorPos(&pt);

			RECT ViewRct;
			pView->GetWindowRect(&ViewRct);

			if (PtInRect(&ViewRct, pt))
			{
				int nCur = m_nViewCursor;
				if (m_nViewCursor == UF_IDC_CROSS)
				{
					// 只有需要创建新控件，鼠标进入窗口范围，才显示十字架
					pView->ScreenToClient(&pt);
					if (!pView->PtInWindow(pt))
						nCur = UF_IDC_ARROW;
				}

				HCURSOR hCursor = ::LoadCursor(NULL, MAKEINTRESOURCE(nCur));
				if (hCursor != NULL)
				{
					HCURSOR hSetCur = ::SetCursor(hCursor);
					if (hSetCur != NULL)
						return TRUE;
				}
			}
		}
	}

	return CFrameWndEx::OnSetCursor(pWnd, nHitTest, message);
}

void CMainFrame::OnClose()
{
	if (m_bNeedSave)
	{
		int nRetId = AfxMessageBox(_T("当前工程的设置已经被改变，保存修改吗？"), MB_YESNOCANCEL | MB_ICONINFORMATION);
		if (nRetId == IDCANCEL)
		{
			return;
		}
		else if (nRetId == IDYES)
		{
			OnFileSave();
		}
	}

//	SAFE_CLOSE_HANDLE(m_hClassViewIcon);
//	SAFE_CLOSE_HANDLE(m_hPropertiesBarIcon);
	CFrameWndEx::OnClose();
}

void CMainFrame::OnUpdateRunTest(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

LRESULT CMainFrame::OnOpenSkinByDbClick(WPARAM wParam, LPARAM lParam)
{
	// szArglist就是保存参数的数组
	// nArgs是数组中参数的个数
	// 数组的第一个元素表示进程的path，也就是szArglist[0]，其他的元素依次是输入参数

	AutoOpenSkin();

	int nArgs = 0;
	LPWSTR *szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if (NULL == szArglist || nArgs <= 1)
		return -1;

	CStringW strSkinPath = szArglist[1];

	int nDirFind = strSkinPath.ReverseFind('\\');
	nDirFind++;
	m_strNewSkinDir = strSkinPath.Left(nDirFind);

	int nDotFind = strSkinPath.ReverseFind('.');
	m_strNewSkinName = strSkinPath.Mid(nDirFind, nDotFind - nDirFind);

	m_strNewUfpPath.Format(_T("%s%s%s"), m_strNewSkinDir, m_strNewSkinName, _T(NAME_SKIN_PROJ_EX_NAME));

	OpenSkinProject(false, m_strNewSkinDir, m_strNewSkinName);

	return 0;
}

// 自动关联并可以打开皮肤包文件
void CMainFrame::AutoOpenSkin()
{
	WCHAR szPath[MAX_PATH * 2 + 1] = {0};
	DWORD dwSize = sizeof(szPath);
	DWORD dwType = REG_SZ;
	SHGetValue(HKEY_CLASSES_ROOT, L"ufp_auto_file\\shell\\open\\command", L"", &dwType, szPath, &dwSize);

	if (wcslen(szPath) <= 0)
	{
		memset(szPath, 0, sizeof(szPath));
		::GetModuleFileNameW(NULL, szPath, MAX_PATH);

		CStringW strPath = L"\"";
		strPath += szPath;
		strPath += "\" \"%1\"";
		SHSetValue(HKEY_CLASSES_ROOT, L"ufp_auto_file\\shell\\open\\command", L"", REG_SZ, strPath.LockBuffer(), strPath.GetLength() * sizeof(WCHAR));
		strPath.UnlockBuffer();
	}
}
