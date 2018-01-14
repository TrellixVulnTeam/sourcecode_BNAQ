
#pragma once
#include "..\ICtrlInterface.h"
#include ".\..\IPropertyFontBase.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_CONTEXTMENUITEM						(L"ContextMenuItem")

enum CTRL_MSG_MENU_ITEM
{
	// MenuItem��ϢBase������Ϣֵ���������ͣ�ֻ����Ϊ��Ϣֵ��Base
	CM_MENU_ITEM_BASE	= 0x10012000,
	// MenuItem Down��Ϣ
	CM_MENU_ITEM_DOWN,
	// MenuItem Up��Ϣ
	CM_MENU_ITEM_UP
};

class ICtrlContextMenu;

class _declspec(novtable) ICtrlContextMenuItem : public ICtrlInterface
{
public:
	ICtrlContextMenuItem(IUiFeatureKernel *pUiKernel);
	// ���������ؼ�
	virtual void SetContextMenu(ICtrlContextMenu* pContextMenu) = 0;
	// ���ò˵���������
	virtual void SetMenuFont(IPropertyFontBase* pNormalFont, IPropertyFontBase* pHoverFont, IPropertyFontBase* pDisableFont) = 0;
};
