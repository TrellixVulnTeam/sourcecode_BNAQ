#include "DMSpyAfx.h"
#include "MainWnd.h"
#include "DUIFindBtn.h"

BEGIN_MSG_MAP(CMainWnd)
	MSG_WM_INITDIALOG(OnInitDialog)
	MSG_WM_SIZE(OnSize)

	CHAIN_MSG_MAP(DMHWnd)
END_MSG_MAP()

BEGIN_EVENT_MAP(CMainWnd)
	EVENT_NAME_COMMAND(L"btn_close",OnClose)
	EVENT_NAME_COMMAND(L"btn_max", OnMaximize)
	EVENT_ID_COMMAND(10, OnRestore)
	EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
	EVENT_NAME_COMMAND(L"btn_skin",OnSkin)
	EVENT_NAME_HANDLER(L"findbtn",DMSpyInitArgs::EventID,OnSpyInitEvent)
	EVENT_NAME_HANDLER(L"wnd_tree",DMEventTCSelChangedArgs::EventID,OnTreeSelChanged)
END_EVENT_MAP()

CMainWnd::CMainWnd()
{
	m_pTreeCtrl = NULL;
	m_pTreeEdit = NULL;
	m_pSearchSta= NULL;
	m_hRootWnd  = NULL;
	m_bDraw     = false;
	m_bHittest  = false;
	m_bInit     = false;
	m_pSpyEnum  = new DMSpyEnum;
	memset(m_pSpyEnum,0,sizeof(DMSpyEnum));
}

CMainWnd::~CMainWnd()
{
	DM_DELETE(m_pSpyEnum);
}

BOOL CMainWnd::OnInitDialog(HWND wndFocus, LPARAM lInitParam)
{
	m_pTreeCtrl  = FindChildByNameT<DUITreeCtrl>(L"wnd_tree");
	m_pTreeEdit  = FindChildByNameT<DUIRichEdit>(L"rich_edit");
	m_pSearchSta = FindChildByNameT<DUIStatic>(L"search_sta");
	m_pSearchSta->DV_SetWindowText(L"���϶�����ָ�뵽��Ҫ�鿴�Ĵ���/�ؼ����ͷ�");
	DMASSERT(m_pTreeCtrl);DMASSERT(m_pTreeEdit);DMASSERT(m_pSearchSta);
	return TRUE;
}

void CMainWnd::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);  // ��DMHWnd��������
	if (0 == size.cx||0 == size.cy)
	{
		return;
	}
	if (SIZE_MAXIMIZED == nType)
	{
		DUIWindow*pMaxWnd     = FindChildByName(L"btn_max");
		DUIWindow*pRestoreWnd = FindChildById(10);
		if (pMaxWnd&&pRestoreWnd)
		{
			pMaxWnd->DM_SetVisible(false);
			pRestoreWnd->DM_SetVisible(true);
		}
	}
	else if (SIZE_RESTORED == nType)
	{
		DUIWindow*pMaxWnd     = FindChildByName(L"btn_max");
		DUIWindow*pRestoreWnd = FindChildById(10);
		if (pMaxWnd&&pRestoreWnd)
		{
			pMaxWnd->DM_SetVisible(true);
			pRestoreWnd->DM_SetVisible(false);
		}
	}
}

DMCode CMainWnd::OnClose()
{
	DM_KillTimer(10);
	if (m_pSkinWnd&&m_pSkinWnd->IsWindow())
	{
		m_pSkinWnd->DestroyWindow();
	}
	DM_AnimateWindow(400,AW_HOR_POSITIVE|AW_HIDE);
	DestroyWindow();
	return DM_ECODE_OK;
}

DMCode CMainWnd::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
	return DM_ECODE_OK;
}

DMCode CMainWnd::OnRestore()
{
	SendMessage(WM_SYSCOMMAND,SC_RESTORE);
	return DM_ECODE_OK;
}

DMCode CMainWnd::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND,SC_MINIMIZE);
	return DM_ECODE_OK;
}

DMCode CMainWnd::OnSkin()
{
	if (m_pSkinWnd&&m_pSkinWnd->IsWindow())
	{
		return DM_ECODE_OK;
	}
	m_pSkinWnd.Release();

	m_pSkinWnd.Attach(new CSkinWnd());
	m_pSkinWnd->DM_CreateWindow(L"dui_skin");				// ����������
	m_pSkinWnd->SendMessage(WM_INITDIALOG);
	m_pSkinWnd->CenterWindow();
	CRect rcWindow = m_rcWindow;
	ClientToScreen(rcWindow);
	m_pSkinWnd->SetWindowPos(HWND_TOPMOST, rcWindow.right-m_pSkinWnd->m_rcWindow.Width()-10,rcWindow.top+10,0, 0, SWP_NOSIZE);
	m_pSkinWnd->ShowWindow(SW_SHOW);
	g_pDMApp->Run(m_pSkinWnd->GetSafeHwnd());
	return DM_ECODE_OK;
}

DMCode CMainWnd::OnSpyInitEvent(DMEventArgs *pEvt)
{
	DMSpyInitArgs *pInitEvt = (DMSpyInitArgs*)pEvt;
	do 
	{
		if (!pInitEvt
			||!pInitEvt->m_hwnd)
		{
			break;
		}
		if (pInitEvt->m_hwnd == m_hRootWnd&&m_bInit)
		{
			break;
		}
		m_pTreeCtrl->RemoveAllItems();
		DM_KillTimer(10);
		m_bDraw = false;
		m_bInit = false;
		m_pTreeEdit->SetWindowText(L"");
		m_pSearchSta->DV_SetWindowText(L"���϶�����ָ�뵽��Ҫ�鿴�Ĵ���/�ؼ����ͷ�");
		// Ĭ��wparam��ʲô����ʲô
		LRESULT lr  = ::SendMessage(pInitEvt->m_hwnd,WM_DMSPY,DMSPY_INIT,(LPARAM)m_hWnd);
		if (DMSPY_INIT!=lr)
		{
			break;
		}

		m_hRootWnd = pInitEvt->m_hwnd;
		DMSpyTool::ReleaseSharedMemory();
		DMSpyTool::CreateSharedMemory(sizeof(DMSpyEnum));

		// ��ʼ����pInitEvt->m_hwndΪroot��ö������DUI����
		InitTreeCtrl(pInitEvt->m_hwnd);

	} while (false);
	return DM_ECODE_OK;
}

DMCode CMainWnd::OnTreeSelChanged(DMEventArgs *pEvt)
{
	if (m_bHittest)// ����pt���ң�pt���������Լ���
	{
		return DM_ECODE_OK;
	}
	DMEventTCSelChangedArgs *pSelEvt = (DMEventTCSelChangedArgs*)pEvt;
	HDMTREEITEM hSelItem = pSelEvt->m_hNewSel;
	if (hSelItem)
	{
		DUIWND hDUIWnd = m_pTreeCtrl->GetItemData(hSelItem);
		if (hDUIWnd)
		{
			m_pSpyEnum->iCode   = GDW_FIRSTCHILD;
			m_pSpyEnum->hDUIWnd = hDUIWnd;
			DMSpyTool::WriteShareMemory(m_pSpyEnum,sizeof(DMSpyEnum));
			if (DMSPY_INFO == ::SendMessage(m_hRootWnd, WM_DMSPY, DMSPY_INFO, 0))
			{
				ReflashEditInfo();
				m_bDraw = true;
				m_rcDraw = m_pSpyEnum->info.rcWindow;
				::BringWindowToTop(m_hRootWnd);
				DM_SetTimer(10,10);
			}
		}
		else
		{
			m_bDraw = false;
			DM_KillTimer(10);
		}
	}
	return DM_ECODE_OK;
}

void CMainWnd::InitTreeCtrl(HWND hRootWnd)
{
	do 
	{
		CStringW strRoot;
		strRoot.Format(L"���� %08x-(root)",hRootWnd);
		HDMTREEITEM hRootTree = m_pTreeCtrl->InsertItem(strRoot,0,0,(LPARAM)-1);

		// ���xml�б�
		wchar_t szXmlPath[MAX_PATH] = {0};
		DM::GetRootFullPath(L".\\DMSpyTree.xml",szXmlPath,MAX_PATH);
		DMSpyTool::WriteShareMemory(szXmlPath,MAX_PATH);
		HRESULT hr = ::SendMessage(hRootWnd, WM_DMSPY, DMSPY_ENUM, 0);
		if (DMSPY_ENUM != hr)
		{
			break;
		}
		DMXmlDocument doc;
		if (!doc.LoadFromFile(szXmlPath))
		{
			break;
		}

		// �������οؼ�
		DMXmlNode XmlNode = doc.Root();
		if (!XmlNode.IsValid())
		{
			break;
		}
		InsertTreeItem(XmlNode,hRootTree);
		m_pTreeCtrl->Expand(hRootTree,TVE_COLLAPSE);
	} while (false);

	int nCount = m_pTreeCtrl->GetCount();
	if (nCount>1)
	{
		m_bInit = true;
		m_pSearchSta->DV_SetWindowText(L"DUI��ʼ�����,���϶�����ָ��鿴DUI����/�ؼ�");
	}
	else
	{
		m_bInit = false;
		m_pSearchSta->DV_SetWindowText(L"���϶�����ָ�뵽��Ҫ�鿴�Ĵ���/�ؼ����ͷ�");
	}
}

void CMainWnd::InsertTreeItem(DMXmlNode &XmlNode,HDMTREEITEM hParentItem)
{
	int duiwnd = XmlNode.AttributeInt(L"duiwnd");
	int bsee = XmlNode.AttributeInt(L"bsee");
	int bPanel = XmlNode.AttributeInt(L"bpanel");
	CStringW classname = XmlNode.Attribute(L"classname");
	CStringW name = XmlNode.Attribute(L"name");
	CStringW id = XmlNode.Attribute(L"id");
	CStringW level = XmlNode.Attribute(L"level");

	CStringW strTree;
	if (1 == bPanel)
	{
		strTree.Format(L"(panel)����level(%s) ID:%d Name:%s ����:%s",level,duiwnd,name,classname);
	}
	else
	{
		strTree.Format(L"����level(%s) ID:%d Name:%s ����:%s",level,duiwnd,name,classname);
	}
	int iIcon = bsee?1:0;
	HDMTREEITEM hChildItem = m_pTreeCtrl->InsertItem(strTree,iIcon,iIcon,(LPARAM)duiwnd,hParentItem);
	for (DMXmlNode XmlChildNode = XmlNode.FirstChild(); XmlChildNode.IsValid(); XmlChildNode=XmlChildNode.NextSibling())
	{
		InsertTreeItem(XmlChildNode,hChildItem);
	}
}

void CMainWnd::ReflashEditInfo()
{
	DMSpyTool::ReadShareMemory(m_pSpyEnum,sizeof(DMSpyEnum));
	CStringW strWnd;
	strWnd.Format(L"��������:left:%d,top:%d,wid:%d,hei:%d\r\n",m_pSpyEnum->info.rcWindow.left,m_pSpyEnum->info.rcWindow.top,m_pSpyEnum->info.rcWindow.Width(),m_pSpyEnum->info.rcWindow.Height());
	CStringW strClient;
	strClient.Format(L"�ͻ�����:left:%d,top:%d,wid:%d,hei:%d\r\n",m_pSpyEnum->info.rcClient.left,m_pSpyEnum->info.rcClient.top,m_pSpyEnum->info.rcClient.Width(),m_pSpyEnum->info.rcClient.Height());
	CStringW strInfo =strWnd + strClient;
	strInfo += L"XML:\r\n";
	strInfo += m_pSpyEnum->info.szXml;
	m_pTreeEdit->SetWindowText(strInfo);
}

bool CMainWnd::HitTest(RECT &rc)
{
	bool bRet = false;
	do 
	{
		if (!m_bInit||0==m_pTreeCtrl->GetCount()||NULL==m_hRootWnd)
		{
			break;
		}
		POINT pnnt;
		::GetCursorPos(&pnnt);
		::ScreenToClient(m_hRootWnd,&pnnt);
		m_pSpyEnum->hDUIWnd = DMSPY_ENUM_BEGIN;
		m_pSpyEnum->pt = pnnt;
		DMSpyTool::WriteShareMemory(m_pSpyEnum,sizeof(DMSpyEnum));
		HRESULT hr = ::SendMessage(m_hRootWnd, WM_DMSPY, DMSPY_POINT, 0);
		DMSpyTool::ReadShareMemory(m_pSpyEnum,sizeof(DMSpyEnum));
		if (DMSPY_POINT == hr&&m_pSpyEnum->hNextDUIWnd)
		{
			// ����ѡ��tree
			HDMTREEITEM hItem = m_pTreeCtrl->GetRootItem();
			while (hItem)
			{
				DUIWND hDUIWnd = m_pTreeCtrl->GetItemData(hItem);
				if (m_pSpyEnum->hNextDUIWnd == hDUIWnd)
				{
					m_bHittest = true;
					rc = m_pSpyEnum->info.rcWindow;
					m_pTreeCtrl->SelectItem(hItem, TRUE);
					ReflashEditInfo();
					m_bHittest = false;
					bRet = true;
					break;
				}
				hItem = m_pTreeCtrl->GetNextItem(hItem);
			}
		}
	
	} while (false);
	return bRet;
}

void CMainWnd::OnDUITimer(char id)
{
	DMHWnd::OnDUITimer(id);
	if (10 == id&&m_bDraw)
	{
		static int ncount = 40;
		ncount--;
		if (ncount!=1)
		{
			return;
		}
		HWND DeskHwnd = ::GetDesktopWindow();//ȡ��������
		HDC DeskDC    = ::GetWindowDC(DeskHwnd);
		int oldRop2   = SetROP2(DeskDC, R2_NOTXORPEN);
		RECT rc = m_rcDraw;
		HPEN newPen = ::CreatePen(PS_DASHDOTDOT, 1, RGB(125, 0, 125));
		HGDIOBJ oldPen = ::SelectObject(DeskDC, newPen);
		::Rectangle(DeskDC, rc.left, rc.top,rc.right, rc.bottom);
		Sleep(200); //������˸ʱ����
		::Rectangle(DeskDC, rc.left, rc.top,rc.right, rc.bottom);

		::SetROP2(DeskDC, oldRop2);
		::SelectObject(DeskDC, oldPen);
		::DeleteObject(newPen);
		::ReleaseDC(DeskHwnd, DeskDC);
		DeskDC = NULL;
		ncount = 40;
	}
}



