
#pragma once
#include "..\..\Inc\Control\ICtrlContextMenu.h"
#include "ContextMenuWnd.h"
#include "..\..\Inc\Control\ICtrlContextMenuItem.h"

class ICtrlContextMenuImpl : public ICtrlContextMenu
{
public:
	ICtrlContextMenuImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlContextMenuImpl();

	// �����˵����
	virtual bool CreatePopupMenu();
	// ��ʾ�˵���壬����������ᵼ��wait
	virtual bool TrackPopupMenu(POINT pt, WPARAM wMenuParam = NULL);
	// ���ٲ˵�
	virtual bool DestroyMenu();

	// �˵���ĸ߶�
	virtual int GetItemHeight();
	// �˵��ָ��ߵĸ߶�
	virtual int GetSeparatorHeight();

	// �˵������˵�������߾�
	virtual int GetLeftSpace();
	// �˵������˵�����Ҳ�߾�
	virtual int GetRightSpace();
	// �˵������˵���嶥���߾�
	virtual int GetTopSpace();
	// �˵������˵����ײ��߾�
	virtual int GetBottomSpace();
	// �˵���֮��ľ���
	virtual int GetItemSpace();
	// �˵����֮������ҵļ��
	virtual int GetPanelSpace();
	// ȡ�ò˵����Ĳ���
	virtual WPARAM GetPopupMenuParam();

	// ���ò˵���������
	virtual void SetMenuFont(IPropertyFontBase* pNormalFont, IPropertyFontBase* pHoverFont, IPropertyFontBase* pDisableFont);

	// ȡ��ָ���Ӳ˵���item
	virtual ICtrlContextMenuItem* GetMenuItem(WCHAR * pszMenuItemName);

protected:
	// �����˵�����Ӳ˵�
	virtual void PopupSubMenu(ICtrlContextMenuItem* pMenuItem, CContextMenuWnd* pMenuWnd);
	// ���ٲ˵�����Ӳ˵�
	virtual void DestroySubMenu(ICtrlContextMenuItem* pMenuItem);

	// �˵�����Ϣ�ɷ�
	virtual void OnMenuItemMessage(IControlBase* pMenuItem, int nMsgId, int nMenuId);
	// ȡ�ò˵��Ի����б�
	virtual MENN_WND_VEC* GetMenuWindowList();

	// �����ؼ����ڴ��������Լ��Ŀؼ�����
	// bIsNewCtrl��trueʱ˵����Builder���ã��´���һ���ؼ�����Ҫ��ʼ�����Եĸ���Ĭ��ֵ
	// false��˵������Ƥ�����Ѿ���ʼ����ϣ����Դ�����ϵ�ʱ�򣬴�xml�ж�ȡ������ֵ�Ѿ���ֵ����ˣ������ٳ�ʼ��������xml�е�ֵ�ᱻ���
	virtual bool CreateControlPropetry(bool bIsNewCtrl);
	// ��ʼ���ؼ�
	virtual void OnCreate();
	// �ؼ���ʼ�����
	virtual void OnFinalCreate();
	// ���ٿؼ�
	virtual void OnDestroy();
	// ���ƿؼ�
	virtual void OnPaint(CDrawingBoard &DrawBoard);
	// �ؼ���Ҫ�����һЩ�Զ������Ϣ����Ϣ�����ϻ��ɶԻ�����������ؼ�����
	virtual int OnCtrlNotify(int nMsgId, WPARAM wParam, LPARAM lParam);
	// ȡ�ò˵���������
	virtual void GetMenuFont(IPropertyFontBase** ppNormalFont, IPropertyFontBase** ppHoverFont, IPropertyFontBase** ppDisableFont);

	// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
	virtual LRESULT ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam);
private:
	bool OnDestroyMenuMessage();

private:
	// �˵���崰��
	CContextMenuWnd *m_pContextMenuWnd;

	IPropertyString* m_pPropMenuPanelName;
	IPropertyInt* m_pPropItemLeftSpace;
	IPropertyInt* m_pPropItemRightSpace;
	IPropertyInt* m_pPropItemTopSpace;
	IPropertyInt* m_pPropItemBottomSpace;
	IPropertyInt* m_pPropItemSpace;
	IPropertyInt* m_pPropPanelSpace;

	IPropertyInt* m_pPropItemHeight;
	IPropertyInt* m_pPropSeparatorHeight;
	IPropertyString* m_pPropSkinPassword;					// Ƥ����������

	// ���в˵������б�
	MENN_WND_VEC m_MenuWndVec;

	IPropertyFontBase* m_pNewNormalFont;
	IPropertyFontBase* m_pNewHoverFont;
	IPropertyFontBase* m_pNewDisableFont;

	WPARAM m_wpTrackMenuParam;
};
