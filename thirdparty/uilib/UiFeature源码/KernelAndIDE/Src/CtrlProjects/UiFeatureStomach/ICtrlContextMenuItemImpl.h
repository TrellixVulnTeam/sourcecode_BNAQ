
#pragma once
#include "..\..\Inc\Control\ICtrlContextMenuItem.h"
#include "ContextMenuWnd.h"

class ICtrlContextMenuItemImpl : public ICtrlContextMenuItem
{
public:
	ICtrlContextMenuItemImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlContextMenuItemImpl();

protected:
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
	// ������
	virtual void OnMouseEnter(POINT pt);
	// ����Ƴ�
	virtual void OnMouseLeave(POINT pt);
	// ���������
	virtual void OnLButtonDown(POINT pt);
	// ������̧��
	virtual void OnLButtonUp(POINT pt);
	// ���������ؼ�
	virtual void SetContextMenu(ICtrlContextMenu* pContextMenu);
	// ���ò˵���������
	virtual void SetMenuFont(IPropertyFontBase* pNormalFont, IPropertyFontBase* pHoverFont, IPropertyFontBase* pDisableFont);
	// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
	virtual LRESULT ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam);
private:
	typedef enum enumMeunItemState
	{
		MeunItemStateInvalid = -1,
		MeunItemStateNormal,
		MeunItemStateHover,
		MeunItemStateDisable,
		//�ڴ�֮ǰ����MeunItem��״̬
		MeunItemStateNum
	}MENUITEMSTATE;

	typedef enum enumPadding
	{
		Invalid = -1,
		Top,
		Left,
		Bottom,
		Right,
		PaddingNum
	}PADDING;

private:
	// ���MenuITem��ʾ�ķ��
	void ChangeMenuItemStyle(MENUITEMSTATE state);
	bool HaveSubMenu();

private:
	// �Ӳ˵���崰��
	CContextMenuWnd*	m_pSubContextMenuWnd;

	// ��������
	IPropertyString*	m_pPropMenuPanelName;
	// �Ƿ�����
	IPropertyBool*		m_pPropEnabled;
	// �Ƿ�ָ���
	IPropertyBool*		m_pPropIsSeparator;
	// �ָ�������ͼ
	IPropertyImage*		m_pPropImageSeparator;
	// �Ƿ����Ӳ˵�
	IPropertyBool*		m_pPropHasChild;
	// �˵����ͼ
	IPropertyImage*		m_pPropImages[MeunItemStateNum];
	// �˵���Iconͼ��
	IPropertyImage*		m_pPropIcons[MeunItemStateNum];
	// �˵����������
	IPropertyFont*		m_pPropFonts[MeunItemStateNum];
	// �˵����ͷͼ��
	IPropertyImage*		m_pPropArrows[MeunItemStateNum];
	// �˵���Icon��λ��
	IPropertyInt*		m_pPropArrowPosition[2];
	// �˵���Icon�Ĵ�С
	IPropertyInt*		m_pPropArrowSize[2];
	// �˵������Եı߾�
	IPropertyInt*		m_pPropTextPadding[PaddingNum];
	// �˵���Arrow��λ��
	IPropertyInt*		m_pPropIconPosition[2];
	// �˵���Arrow�Ĵ�С
	IPropertyInt*		m_pPropIconSize[2];

	IPropertyInt*		m_pPropSeparatorPosition[2];
	IPropertyInt*		m_pPropSeparatorSize[2]; 


	// �˵���˳���(��0��ʼ)
	IPropertyInt*		m_pPropIndex;
	// �˵������
	IPropertyString*	m_pPropText;
	// �Ӳ˵�
	ICtrlContextMenu*	m_pContextMenu;

	MENUITEMSTATE		m_enumMenuItemState;
	ULONG				m_mouseFlag;
};
