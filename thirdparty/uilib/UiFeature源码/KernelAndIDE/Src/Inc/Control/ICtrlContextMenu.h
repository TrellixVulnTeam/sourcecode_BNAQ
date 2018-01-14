
#pragma once
#include "..\ICtrlInterface.h"
#include ".\..\IPropertyFontBase.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_CONTEXTMENU						(L"ContextMenu")

class ICtrlContextMenu;
class ICtrlContextMenuItemImpl;
class ICtrlContextMenuItem;
class CContextMenuWnd;

// һ���˵����ڵ���Ϣ
struct MENU_WND_ITEM
{
	ICtrlContextMenuItem* pMenuItem;
	// �ڲ��˵����ڶԻ���ָ��
	CContextMenuWnd* pMenuWnd;
};
typedef vector<MENU_WND_ITEM>	MENN_WND_VEC;

// һ���˵������󷢳�����Ϣ����
struct MENU_PARAM_DATA
{
	ICtrlContextMenu* pContextMenu;
	ICtrlContextMenuItem* pMenuItem;
};

class _declspec(novtable) ICtrlContextMenu : public ICtrlInterface
{
	friend class CContextMenuWnd;
	friend class ICtrlContextMenuItemImpl;

public:
	ICtrlContextMenu(IUiFeatureKernel *pUiKernel);
	// �����˵����
	virtual bool CreatePopupMenu() = 0;
	// ��ʾ�˵���壬����������ᵼ��wait
	virtual bool TrackPopupMenu(POINT pt, WPARAM wMenuParam = NULL) = 0;
	// ���ٲ˵�
	virtual bool DestroyMenu() = 0;

	// �˵���ĸ߶�
	virtual int GetItemHeight() = 0;
	// �˵��ָ��ߵĸ߶�
	virtual int GetSeparatorHeight() = 0;

	// �˵������˵�������߾�
	virtual int GetLeftSpace() = 0;
	// �˵������˵�����Ҳ�߾�
	virtual int GetRightSpace() = 0;
	// �˵������˵���嶥���߾�
	virtual int GetTopSpace() = 0;
	// �˵������˵����ײ��߾�
	virtual int GetBottomSpace() = 0;
	// �˵���֮��ľ���
	virtual int GetItemSpace() = 0;
	// �˵����֮������ҵļ��
	virtual int GetPanelSpace() = 0;

	// ���ò˵���������
	virtual void SetMenuFont(IPropertyFontBase* pNormalFont, IPropertyFontBase* pHoverFont, IPropertyFontBase* pDisableFont) = 0;

	// ȡ�ò˵����Ĳ���
	virtual WPARAM GetPopupMenuParam() = 0;

	// ȡ��ָ���Ӳ˵���item
	virtual ICtrlContextMenuItem* GetMenuItem(WCHAR * pszMenuItemName) = 0;

protected:
	// �����˵�����Ӳ˵�
	virtual void PopupSubMenu(ICtrlContextMenuItem* pMenuItem, CContextMenuWnd* pMenuWnd) = 0;
	// ���ٲ˵�����Ӳ˵�
	virtual void DestroySubMenu(ICtrlContextMenuItem* pMenuItem) = 0;

	// �˵�����Ϣ�ɷ�
	virtual void OnMenuItemMessage(IControlBase* pMenuItem, int nMsgId, int nMenuId) = 0;
	// ȡ�ò˵��Ի����б�
	virtual MENN_WND_VEC* GetMenuWindowList() = 0;
	// ȡ�ò˵���������
	virtual void GetMenuFont(IPropertyFontBase** ppNormalFont, IPropertyFontBase** ppHoverFont, IPropertyFontBase** ppDisableFont) = 0;
};
