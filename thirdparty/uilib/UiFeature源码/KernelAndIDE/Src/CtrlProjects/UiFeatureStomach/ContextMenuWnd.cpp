
#include "StdAfx.h"
#include <windowsx.h>
#include "ContextMenuWnd.h"
#include "..\..\Inc\Control\ICtrlContextMenu.h"
#include "..\..\Inc\Control\ICtrlContextMenuItem.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"

CContextMenuWnd::CContextMenuWnd()
{
	m_nMenuLevel = 0;
	m_pContextMenuCtrl = NULL;
	m_bHideDonotDestroy = FALSE;
	m_MenuItemList.clear();
}

CContextMenuWnd::~CContextMenuWnd()
{
}

// ���ò˵�����
void CContextMenuWnd::SetMenuLevel(int nLevel)
{
	m_nMenuLevel = nLevel;
}

// ȡ�ò˵�����
int CContextMenuWnd::GetMenuLevel()
{
	return m_nMenuLevel;
}

bool CContextMenuWnd::CreateContextMenuWnd(ICtrlContextMenu* pContextMenuCtrl, const WCHAR* pszSkinPath, const WCHAR* pszWindowName, IUiFeatureKernel* pUiKernel, char * pszPassword, HWND hWnd)
{
	if (IS_SAFE_HANDLE(m_hWnd) || pContextMenuCtrl == NULL || pszWindowName == NULL || wcslen(pszWindowName) <= 0 || pUiKernel == NULL)
		return false;

	m_pContextMenuCtrl = pContextMenuCtrl;
	RECT WndRct = {0, 0, 0, 0};

	bool bNewThread = (m_nMenuLevel == 1);

	return CreateFeatureWindowByKernel(pszPassword, pUiKernel, pszSkinPath, pszWindowName, hWnd, WndRct, SW_HIDE, WS_POPUP, (LPARAM)this);
}

// ����/ȡ�ò˵����Ĵ�С
SIZE CContextMenuWnd::GetMenuWindowSize()
{
	SIZE menuSize;
	menuSize.cx = menuSize.cy = 0;
	if (m_pWindowBase == NULL)
		return menuSize;

	menuSize = m_pWindowBase->PP_GetWindowPropSize();
	return menuSize;
}

bool CContextMenuWnd::TrackPopupMenu(POINT pt)
{
	SIZE menuSize = GetMenuWindowSize();
	if (IS_INVALID_HANDLE(m_hWnd) || m_pWindowBase == NULL || menuSize.cx <= 0 || menuSize.cy <= 0)
		return false;

	RECT ScreenRect;
	INIT_RECT(ScreenRect);

	// �õ���Ļ��С
	ScreenRect.right = GetSystemMetrics(SM_CXSCREEN);
	ScreenRect.bottom = GetSystemMetrics(SM_CYSCREEN);

	// ȡ�ö���������Ⱥ͸߶�
	int nCtns = GetSystemMetrics(SM_CMONITORS);
	if (nCtns > 1)
	{
		// ������������Ͻ����
		ScreenRect.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
		ScreenRect.top = GetSystemMetrics(SM_YVIRTUALSCREEN);

		// ������Ļ����һ��Ĵ�С
		ScreenRect.right = ScreenRect.left + GetSystemMetrics(SM_CXVIRTUALSCREEN);
		ScreenRect.bottom = ScreenRect.top + GetSystemMetrics(SM_CYVIRTUALSCREEN);
	}

	// �˵����ܳ�����Ļ�Ҳ�
	if ((pt.x + menuSize.cx) > ScreenRect.right)
		pt.x -= menuSize.cx;

	// �˵����ܳ�����Ļ�·�
	if ((pt.y + menuSize.cy) > ScreenRect.bottom)
		pt.y -= menuSize.cy;

	// �˵����ܳ�����Ļ���
	if (pt.x < ScreenRect.left)
		pt.x = ScreenRect.left;

	// �˵����ܳ�����Ļ�Ϸ�
	if (pt.y < ScreenRect.top)
		pt.y = ScreenRect.top;

	RECT wndRct = {pt.x, pt.y, pt.x + menuSize.cx, pt.y + menuSize.cy};
	this->MoveWindow(wndRct);
	this->ShowWindow(SW_SHOW);
	return true;
}

// �����ڵ���Ϣ������
LRESULT CContextMenuWnd::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	// ��������
	if (WM_MENU_TRACK == nMsgId)
	{
		POINT pt;
		pt.x = GET_X_LPARAM(wParam);
		pt.y = GET_Y_LPARAM(wParam);
		this->TrackPopupMenu(pt);
		return 0;
	}

	return CUiFeatureWindow::WndProc(nMsgId, wParam, lParam);
}

void CContextMenuWnd::OnKeyDown(int nVirtKey, int nFlag)
{
	if (nVirtKey == VK_ESCAPE && m_pContextMenuCtrl != NULL)
	{
		m_pContextMenuCtrl->DestroyMenu();
	}
}

// ���ٲ˵�
void CContextMenuWnd::DestroyMenu()
{
	if (IS_INVALID_HANDLE(m_hWnd))
		return;

	this->CloseWindow();

	m_nMenuLevel = 0;
	m_pContextMenuCtrl = NULL;
	m_MenuItemList.clear();
}

void CContextMenuWnd::OnCreate()
{
	if (m_pWindowBase == NULL || m_pContextMenuCtrl == NULL)
		return;

	CHILD_CTRLS_VEC* pChildCtrlVEC = m_pWindowBase->GetChildControlsVec();
	if (pChildCtrlVEC == NULL)
		return;

	m_MenuItemList.clear();
	GetMenuItemVec(pChildCtrlVEC);
	SetMenuItemFont();
}

// ��������
void CContextMenuWnd::SetMenuItemFont()
{
	if (m_pContextMenuCtrl == NULL)
		return;

	IPropertyFontBase* pNormalFont = NULL;
	IPropertyFontBase* pHoverFont = NULL;
	IPropertyFontBase* pDisableFont = NULL;
	m_pContextMenuCtrl->GetMenuFont(&pNormalFont, &pHoverFont, &pDisableFont);

	for (MENU_ITEM_CTRL_VEC::iterator pCtrlItem = m_MenuItemList.begin(); pCtrlItem != m_MenuItemList.end(); pCtrlItem++)
	{
		ICtrlContextMenuItem* pMenuItem = *pCtrlItem;
		if (pMenuItem == NULL)
			continue;

		pMenuItem->SetMenuFont(pNormalFont, pHoverFont, pDisableFont);
	}
}

// ȡ��ָ���Ӳ˵���item
ICtrlContextMenuItem* CContextMenuWnd::GetMenuItem(WCHAR * pszMenuItemName)
{
	if (pszMenuItemName == NULL || wcslen(pszMenuItemName) <= 0)
		return NULL;

	for (MENU_ITEM_CTRL_VEC::iterator pCtrlItem = m_MenuItemList.begin(); pCtrlItem != m_MenuItemList.end(); pCtrlItem++)
	{
		ICtrlContextMenuItem* pMenuItem = *pCtrlItem;
		if (pMenuItem == NULL)
			continue;

		if (lstrcmpi(pMenuItem->GetObjectName(), pszMenuItemName) == 0)
			return pMenuItem;
	}

	return NULL;
}

void CContextMenuWnd::GetMenuItemVec(CHILD_CTRLS_VEC* pCtrlVEC)
{
	if (pCtrlVEC == NULL || m_pContextMenuCtrl == NULL)
		return;

	ListObj* pNext = NULL;
	for (ListObj* pItem = pCtrlVEC->TopObj(); pItem != NULL; pItem = pNext)
	{
		pNext = pCtrlVEC->NextObj(pItem);
		IControlBase* pCtrl = (IControlBase *)pItem;
		if (pCtrl == NULL)
			continue;

		if (lstrcmpi(pCtrl->GetObjectType(), CTRL_NAME_CONTEXTMENUITEM) == 0)
		{
			ICtrlContextMenuItem *pMenuItem = dynamic_cast<ICtrlContextMenuItem*>(pCtrl);
			if (pMenuItem == NULL)
				continue;

			pMenuItem->SetContextMenu(m_pContextMenuCtrl);

			// �˵�Item
			m_MenuItemList.push_back(pMenuItem);
			continue;
		}

		CHILD_CTRLS_VEC* pChildCtrlVEC = pCtrl->GetChildControlsVec();
		if (pChildCtrlVEC == NULL)
			continue;

		GetMenuItemVec(pChildCtrlVEC);
	}
}

// ȡ�ò˵����б�
MENU_ITEM_CTRL_VEC* CContextMenuWnd::GetMenuItemList()
{
	return &m_MenuItemList;
}

// �ؼ����͸����ڵ���Ϣ�ӿ�
LRESULT CContextMenuWnd::OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam)
{
	if ((nMsgId == CM_MENU_ITEM_DOWN || nMsgId == CM_MENU_ITEM_UP) && m_pContextMenuCtrl != NULL)
	{
		m_bHideDonotDestroy = TRUE;
		ShowWindow(SW_HIDE);
		m_bHideDonotDestroy = FALSE;

		m_pContextMenuCtrl->OnMenuItemMessage(pCtrl, nMsgId, (int)wParam);
		
		return 0;
	}

	return CUiFeatureWindow::OnCtrlMessage(pCtrl, nMsgId, wParam, lParam);
}

void CContextMenuWnd::OnKillFocus()
{
	if (m_pContextMenuCtrl == NULL || m_bHideDonotDestroy)
		return;

	MENN_WND_VEC* pWndVec = m_pContextMenuCtrl->GetMenuWindowList();
	if (pWndVec == NULL)
		return;

	// ʧȥ�Ľ�����������ڲ˵��ϣ������ٴ���
	HWND hActWnd = ::GetActiveWindow();

	for (MENN_WND_VEC::iterator pWndItem = pWndVec->begin(); pWndItem != pWndVec->end(); pWndItem++)
	{
		MENU_WND_ITEM& wndItem = *pWndItem;
		if (wndItem.pMenuWnd == NULL)
			continue;

		// ʧȥ�Ľ����ڲ˵��ϣ������ٴ���
		if (hActWnd == wndItem.pMenuWnd->GetSafeHandle())
			return;
	}

	m_pContextMenuCtrl->DestroyMenu();

	m_nMenuLevel = 0;
	m_pContextMenuCtrl = NULL;
	m_MenuItemList.clear();
}
