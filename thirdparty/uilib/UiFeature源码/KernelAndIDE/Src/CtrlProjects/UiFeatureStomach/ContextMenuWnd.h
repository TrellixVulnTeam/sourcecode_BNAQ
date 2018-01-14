
#pragma once
#include "..\..\Inc\CUiFeatureWindow.h"
#include "..\..\Inc\Control\ICtrlContextMenuItem.h"

// �����˵�
#define WM_MENU_TRACK					(WM_APP + 0x0300 + 0x0181)
// ���ٲ˵�
#define WM_MENU_DESTROY					(WM_APP + 0x0300 + 0x0182)

typedef vector<ICtrlContextMenuItem*>			MENU_ITEM_CTRL_VEC;


class ICtrlContextMenu;
class CContextMenuWnd : public CUiFeatureWindow
{
public:
	CContextMenuWnd();
	virtual ~CContextMenuWnd();

	// �����˵����
	bool CreateContextMenuWnd(ICtrlContextMenu* pContextMenuCtrl, const WCHAR* pszSkinPath, const WCHAR* pszWindowName, IUiFeatureKernel* pUiKernel, char * pszPassword, HWND hWnd);
	// ���ٲ˵�
	void DestroyMenu();

	// ���ò˵�����
	void SetMenuLevel(int nLevel);
	// ȡ�ò˵�����
	int GetMenuLevel();
	// ȡ�ò˵����б�
	MENU_ITEM_CTRL_VEC* GetMenuItemList();

	// ��ʾ�˵���壬����������ᵼ��wait
	bool TrackPopupMenu(POINT pt);

	// ȡ��ָ���Ӳ˵���item
	ICtrlContextMenuItem* GetMenuItem(WCHAR * pszMenuItemName);

protected:
	// �ؼ����͸����ڵ���Ϣ�ӿ�
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam);
	// �����ڵ���Ϣ������
	virtual LRESULT WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	virtual void OnCreate();
	virtual void OnKeyDown(int nVirtKey, int nFlag);
	virtual void OnKillFocus();

private:
	// ����/ȡ�ò˵����Ĵ�С
	SIZE GetMenuWindowSize();
	void GetMenuItemVec(CHILD_CTRLS_VEC* pCtrlVEC);
	// ��������
	void SetMenuItemFont();

private:
	int m_nMenuLevel;
	ICtrlContextMenu* m_pContextMenuCtrl;
	MENU_ITEM_CTRL_VEC m_MenuItemList;
	BOOL				m_bHideDonotDestroy;
};
