
#include "StdAfx.h"
#include "ICtrlContextMenuImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"


ICtrlContextMenu::ICtrlContextMenu(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlContextMenuImpl::ICtrlContextMenuImpl(IUiFeatureKernel *pUiKernel) : ICtrlContextMenu(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_CONTEXTMENU);

	m_MenuWndVec.clear();
	m_pContextMenuWnd = NULL;
	m_pPropMenuPanelName = NULL;

	m_pPropItemHeight = NULL;
	m_pPropSeparatorHeight = NULL;

	m_pPropItemLeftSpace = NULL;
	m_pPropItemRightSpace = NULL;
	m_pPropItemTopSpace = NULL;
	m_pPropItemBottomSpace = NULL;
	m_pPropItemSpace = NULL;
	m_pPropPanelSpace = NULL;

	m_pNewNormalFont = NULL;
	m_pNewHoverFont = NULL;
	m_pNewDisableFont = NULL;
	m_wpTrackMenuParam = NULL;
}

ICtrlContextMenuImpl::~ICtrlContextMenuImpl()
{
	SAFE_DELETE(m_pContextMenuWnd);
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlContextMenuImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropMenuPanelName = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "WindowObjectName", "Ҫ��ʾ�Ĳ˵���Builder�е�Window��ObjectName");

	m_pPropItemHeight = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "ItemHeight", "�˵���ĸ߶�");
	m_pPropSeparatorHeight = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "SeparatorHeight", "�˵��ָ��ߵĸ߶�");
	m_pPropSkinPassword = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "SkinPassword", "�˵�����Ƥ����������");

	m_pPropItemLeftSpace = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "LeftSpace", "�˵������˵�������߾�");
	m_pPropItemRightSpace = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "RightSpace", "�˵������˵�����Ҳ�߾�");
	m_pPropItemTopSpace = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "TopSpace", "�˵������˵���嶥���߾�");
	m_pPropItemBottomSpace = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "BottomSpace", "�˵������˵����ײ��߾�");
	m_pPropItemSpace = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "ItemSpace", "�˵���֮��ľ���");
	m_pPropPanelSpace = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "PanelSpace", "�˵����֮������ҵļ��");

	if (bIsNewCtrl)
	{
		// �޻��ƿؼ�
		this->PP_SetNoDrawControl(true);
	}

	return true;
}

// �˵���ĸ߶�
int ICtrlContextMenuImpl::GetItemHeight()
{
	if (m_pPropItemHeight == NULL)
		return 0;

	return m_pPropItemHeight->GetValue();
}

// �˵��ָ��ߵĸ߶�
int ICtrlContextMenuImpl::GetSeparatorHeight()
{
	if (m_pPropSeparatorHeight == NULL)
		return 0;

	return m_pPropSeparatorHeight->GetValue();
}

// �˵������˵�������߾�
int ICtrlContextMenuImpl::GetLeftSpace()
{
	if (m_pPropItemLeftSpace == NULL)
		return 0;

	return m_pPropItemLeftSpace->GetValue();
}

// �˵������˵�����Ҳ�߾�
int ICtrlContextMenuImpl::GetRightSpace()
{
	if (m_pPropItemRightSpace == NULL)
		return 0;

	return m_pPropItemRightSpace->GetValue();
}

// �˵������˵���嶥���߾�
int ICtrlContextMenuImpl::GetTopSpace()
{
	if (m_pPropItemTopSpace == NULL)
		return 0;

	return m_pPropItemTopSpace->GetValue();
}

// �˵������˵����ײ��߾�
int ICtrlContextMenuImpl::GetBottomSpace()
{
	if (m_pPropItemBottomSpace == NULL)
		return 0;

	return m_pPropItemBottomSpace->GetValue();
}

// �˵���֮��ľ���
int ICtrlContextMenuImpl::GetItemSpace()
{
	if (m_pPropItemSpace == NULL)
		return 0;

	return m_pPropItemSpace->GetValue();
}

// �˵����֮������ҵļ��
int ICtrlContextMenuImpl::GetPanelSpace()
{
	if (m_pPropPanelSpace == NULL)
		return 0;

	return m_pPropPanelSpace->GetValue();
}


// ��ʼ���ؼ�
void ICtrlContextMenuImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlContextMenuImpl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlContextMenuImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlContextMenuImpl::OnPaint(CDrawingBoard &DrawBoard)
{
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlContextMenuImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// ȡ�ò˵��Ի����б�
MENN_WND_VEC* ICtrlContextMenuImpl::GetMenuWindowList()
{
	return &m_MenuWndVec;
}

// ȡ�ò˵����Ĳ���
WPARAM ICtrlContextMenuImpl::GetPopupMenuParam()
{
	return m_wpTrackMenuParam;
}

// �˵�����Ϣ�ɷ�
void ICtrlContextMenuImpl::OnMenuItemMessage(IControlBase* pMenuItem, int nMsgId, int nMenuId)
{
	if (nMsgId == CM_MENU_ITEM_UP && m_pWindowBase != NULL)
	{
		MENU_PARAM_DATA menuParam;
		menuParam.pContextMenu = dynamic_cast<ICtrlContextMenu*>(this);
		menuParam.pMenuItem = dynamic_cast<ICtrlContextMenuItem*>(pMenuItem);

		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), nMsgId, (WPARAM)nMenuId, (LPARAM)&menuParam);
		this->PostMessage(WM_MENU_DESTROY, (WPARAM)this, NULL);
	}
}

bool ICtrlContextMenuImpl::CreatePopupMenu()
{
	if (m_pWindowBase == NULL || m_pWindowBase->GetUiKernel() == NULL || m_pPropMenuPanelName == NULL || m_pPropMenuPanelName->GetString() == NULL || wcslen(m_pPropMenuPanelName->GetString()) <= 0 || m_pPropSkinPassword == NULL)
		return false;

	if (m_pContextMenuWnd == NULL)
		m_pContextMenuWnd = new CContextMenuWnd;

	if (m_pContextMenuWnd == NULL)
		return false;

	if (IS_SAFE_HANDLE(m_pContextMenuWnd->GetSafeHandle()) || m_MenuWndVec.size() > 0)
		return false;

	m_pContextMenuWnd->SetMenuLevel(1);

	CStringA  strPassword = m_pPropSkinPassword->GetString();
	
	bool bRet = m_pContextMenuWnd->CreateContextMenuWnd(dynamic_cast<ICtrlContextMenu*>(this), m_pWindowBase->GetSkinFileItem()->strSkinFilePath, m_pPropMenuPanelName->GetString(), m_pWindowBase->GetUiKernel(), strPassword.GetBuffer(), m_pWindowBase->GetSafeHandle());
	strPassword.ReleaseBuffer();

	MENU_WND_ITEM MenuItem;
	MenuItem.pMenuItem = NULL;
	MenuItem.pMenuWnd = m_pContextMenuWnd;
	m_MenuWndVec.push_back(MenuItem);
	DEBUG_INFO("m_MenuWndVec.push_back");

	if (bRet)
	{
		this->RegisterControlMessage(WM_MENU_DESTROY);
	}
	else
	{
		DestroyMenu();
	}

	return bRet;
}

bool ICtrlContextMenuImpl::TrackPopupMenu(POINT pt, WPARAM wMenuParam)
{
	m_wpTrackMenuParam = wMenuParam;
	if (m_pContextMenuWnd == NULL)
		return false;

	if (!m_pContextMenuWnd->PostMessage(WM_MENU_TRACK, MAKEWPARAM(pt.x,pt.y), NULL))
	{
		// �˴��п��ܷ�����Ϣʧ�ܣ�ԭ���Ǵ���û����ȫ��������
		DestroyMenu();
		return false;
	}

	return true;
}

bool ICtrlContextMenuImpl::DestroyMenu()
{
	return OnDestroyMenuMessage();
//	return this->PostMessage(WM_MENU_DESTROY, (WPARAM)this, NULL);
}

bool ICtrlContextMenuImpl::OnDestroyMenuMessage()
{
	if (m_pContextMenuWnd == NULL)
		return false;

	for (int i = (int)m_MenuWndVec.size() - 1; i >= 0; i--)
	{
		MENU_WND_ITEM &WndItem = m_MenuWndVec[i];
		if (WndItem.pMenuWnd == NULL)
			continue;

		WndItem.pMenuWnd->CloseWindow();
		//WndItem.pMenuWnd->SendMessage(WM_CLOSE, NULL, NULL);
	}
	m_MenuWndVec.clear();
	DEBUG_INFO("OnDestroyMenuMessage m_MenuWndVec.clear();");

	return true;
}

// �ؼ���Ҫ�����һЩ�Զ������Ϣ����Ϣ�����ϻ��ɶԻ�����������ؼ�����
int ICtrlContextMenuImpl::OnCtrlNotify(int nMsgId, WPARAM wParam, LPARAM lParam)
{
	if (WM_MENU_DESTROY == nMsgId && wParam == (WPARAM)this)
		OnDestroyMenuMessage();

	return S_OK;
}

// �����˵�����Ӳ˵�
void ICtrlContextMenuImpl::PopupSubMenu(ICtrlContextMenuItem* pMenuItem, CContextMenuWnd* pMenuWnd)
{
	if (pMenuItem == NULL || pMenuWnd == NULL)
		return;

	for (int i = 0 ; i < (int)m_MenuWndVec.size(); i++)
	{
		MENU_WND_ITEM &WndItem = m_MenuWndVec[i];
		if (WndItem.pMenuItem == pMenuItem || WndItem.pMenuWnd == pMenuWnd)
			return;
	}

	MENU_WND_ITEM WndItem;
	WndItem.pMenuItem = pMenuItem;
	WndItem.pMenuWnd = pMenuWnd;

	m_MenuWndVec.push_back(WndItem);
	DEBUG_INFO("m_MenuWndVec.push_back(WndItem);");
}

// ���ٲ˵�����Ӳ˵�
void ICtrlContextMenuImpl::DestroySubMenu(ICtrlContextMenuItem* pMenuItem)
{
	if (pMenuItem == NULL)
		return;

	for (MENN_WND_VEC::iterator pWndItem = m_MenuWndVec.begin(); pWndItem != m_MenuWndVec.end(); pWndItem++)
	{
		MENU_WND_ITEM &WndItem = *pWndItem;
		if (WndItem.pMenuItem == pMenuItem)
		{
			WndItem.pMenuWnd->CloseWindow();
			break;
		}
	}
}

// ���ò˵���������
void ICtrlContextMenuImpl::SetMenuFont(IPropertyFontBase* pNormalFont, IPropertyFontBase* pHoverFont, IPropertyFontBase* pDisableFont)
{
	m_pNewNormalFont = pNormalFont;
	m_pNewHoverFont = pHoverFont;
	m_pNewDisableFont = pDisableFont;
}

// ȡ�ò˵���������
void ICtrlContextMenuImpl::GetMenuFont(IPropertyFontBase** ppNormalFont, IPropertyFontBase** ppHoverFont, IPropertyFontBase** ppDisableFont)
{
	if (ppNormalFont != NULL)
		*ppNormalFont = m_pNewNormalFont;

	if (ppHoverFont != NULL)
		*ppHoverFont = m_pNewHoverFont;

	if (ppDisableFont != NULL)
		*ppDisableFont = m_pNewDisableFont;
}

// ȡ��ָ���Ӳ˵���item
ICtrlContextMenuItem* ICtrlContextMenuImpl::GetMenuItem(WCHAR * pszMenuItemName)
{
	if (pszMenuItemName == NULL || wcslen(pszMenuItemName) <= 0)
		return NULL;

	for (MENN_WND_VEC::iterator pWndItem = m_MenuWndVec.begin(); pWndItem != m_MenuWndVec.end(); pWndItem++)
	{
		MENU_WND_ITEM &WndItem = *pWndItem;
		if (WndItem.pMenuWnd == NULL)
			continue;

		ICtrlContextMenuItem* pMenuItem = WndItem.pMenuWnd->GetMenuItem(pszMenuItemName);
		if (pMenuItem != NULL)
			return pMenuItem;
	}

	return NULL;
}
