
#include "StdAfx.h"
#include "ICtrlContextMenuItemImpl.h"
#include "..\..\Inc\Control\ICtrlContextMenu.h"
#include "..\..\Inc\UiFeatureDefs.h"

// ��갴�±�־
#define MOUSE_FLAG_DOWN								(0x0000001UL)
ICtrlContextMenuItem::ICtrlContextMenuItem(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlContextMenuItemImpl::ICtrlContextMenuItemImpl(IUiFeatureKernel *pUiKernel) : ICtrlContextMenuItem(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_CONTEXTMENUITEM);

	m_pSubContextMenuWnd = NULL;
	m_pPropEnabled = NULL;
	m_pPropIsSeparator = NULL;
	m_pPropImageSeparator = NULL;
	m_pPropText = NULL;
	m_pPropIndex = NULL;
	m_pContextMenu = NULL;
	m_pPropMenuPanelName = NULL;
	m_enumMenuItemState = MeunItemStateNormal;

	for (int i = 0; i < MeunItemStateNum; i++)
	{
		m_pPropImages[i] = NULL;
		m_pPropIcons[i] = NULL;
		m_pPropFonts[i] = NULL;
		m_pPropArrows[i] = NULL;
	}
	for(int i = 0; i< 2 ;i++)
	{
		m_pPropIconPosition[i] = 0;
		m_pPropIconSize[i] = 0;

		m_pPropArrowPosition[i] = 0;
		m_pPropArrowSize[i] = 0;

		m_pPropSeparatorPosition[i] = 0;
		m_pPropSeparatorSize[i] = 0;

	}

	for(int i = 0; i< PaddingNum ;i++)
	{
		m_pPropTextPadding[i] = 0;
	}

	m_mouseFlag = 0;
}

ICtrlContextMenuItemImpl::~ICtrlContextMenuItemImpl()
{
	SAFE_DELETE(m_pSubContextMenuWnd);
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlContextMenuItemImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlContextMenuItemImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropMenuPanelName = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "SubMenuWndObjName", "�Ӳ˵��Ĵ������ƣ�Builder�е�Window��ObjectName");
	m_pPropEnabled			= (IPropertyBool*)CreatePropetry(NULL, OTID_BOOL, "Enabled", "�Ƿ�����");
	m_pPropIsSeparator		= (IPropertyBool*)CreatePropetry(NULL, OTID_BOOL, "IsSeparator", "�Ƿ�ָ���");
	m_pPropText = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "Text", "MenuItem����ʾ������");
	if (m_pPropText != NULL && bIsNewCtrl)
		m_pPropText->SetString(L"��ʾ���ı�");
	m_pPropIndex = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "Order", "�˵���˳���(��0��ʼ)");

	//����MenuItem����ͼƬ
	IPropertyGroup* pImagePropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Image", "MenuItem�ı���ͼƬGroup");
	m_pPropImages[MeunItemStateNormal] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "NormalImage", "Normal״̬��MenuItem�ı���ͼƬ");
	m_pPropImages[MeunItemStateHover] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "HoverImage", "Hover״̬��MenuItem�ı���ͼƬ");
	m_pPropImages[MeunItemStateDisable] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "DisableImage", "����״̬��MenuItem�ı���ͼƬ");

	//����MenuItem��Icon
	IPropertyGroup* pIconPropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Icon", "Icon Group");
	m_pPropIcons[MeunItemStateNormal] = (IPropertyImage*)CreatePropetry(pIconPropGroup, OTID_IMAGE, "NormalIcon", "Normal״̬��MenuItem�ϵ�Icon");
	m_pPropIcons[MeunItemStateHover] = (IPropertyImage*)CreatePropetry(pIconPropGroup, OTID_IMAGE, "HoverIcon", "Hover״̬��MenuItem�ϵ�Icon");
	m_pPropIcons[MeunItemStateDisable] = (IPropertyImage*)CreatePropetry(pIconPropGroup, OTID_IMAGE, "DisableIcon", "����״̬��MenuItem�ϵ�Icon");
	m_pPropIconPosition[0] = (IPropertyInt*)CreatePropetry(pIconPropGroup, OTID_INT, "Top", "�ϱ߾�");
	m_pPropIconPosition[1] = (IPropertyInt*)CreatePropetry(pIconPropGroup, OTID_INT, "Left", "��߾�");
	m_pPropIconSize[0] = (IPropertyInt*)CreatePropetry(pIconPropGroup, OTID_INT, "Width", "��");
	m_pPropIconSize[1] = (IPropertyInt*)CreatePropetry(pIconPropGroup, OTID_INT, "Height", "��");


	//����MenuItem��Arrow
	IPropertyGroup* pArrowPropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Arrow", "MenuItem�ϵ�Arrow Group");
	m_pPropArrows[MeunItemStateNormal] = (IPropertyImage*)CreatePropetry(pArrowPropGroup, OTID_IMAGE, "NormalArrow", "Normal״̬��MenuItem�ϵ�Arrow");
	m_pPropArrows[MeunItemStateHover] = (IPropertyImage*)CreatePropetry(pArrowPropGroup, OTID_IMAGE, "HoverArrow", "Hover״̬��MenuItem�ϵ�Arrow");
	m_pPropArrows[MeunItemStateDisable] = (IPropertyImage*)CreatePropetry(pArrowPropGroup, OTID_IMAGE, "DisableArrow", "����״̬��MenuItem�ϵ�Arrow");
	m_pPropArrowPosition[0] = (IPropertyInt*)CreatePropetry(pArrowPropGroup, OTID_INT, "Top", "�ϱ߾�");
	m_pPropArrowPosition[1] = (IPropertyInt*)CreatePropetry(pArrowPropGroup, OTID_INT, "Right", "�ұ߾�");
	m_pPropArrowSize[0] = (IPropertyInt*)CreatePropetry(pArrowPropGroup, OTID_INT, "Width", "��");
	m_pPropArrowSize[1] = (IPropertyInt*)CreatePropetry(pArrowPropGroup, OTID_INT, "Height", "��");

	//����MenuItem�����Ե�����
	IPropertyGroup* pFontPropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Font", "MenuItem�����Ե����� Group");
	m_pPropFonts[MeunItemStateNormal] = (IPropertyFont*)CreatePropetry(pFontPropGroup, OTID_FONT, "NormalFont", "Normal״̬��MenuItem�ϵ����Ե�����");
	m_pPropFonts[MeunItemStateHover] = (IPropertyFont*)CreatePropetry(pFontPropGroup, OTID_FONT, "HoverFont", "Hover״̬��MenuItem�ϵ����Ե�����");
	m_pPropFonts[MeunItemStateDisable] = (IPropertyFont*)CreatePropetry(pFontPropGroup, OTID_FONT, "DisableFont", "����״̬��MenuItem�ϵ����Ե�����");
	m_pPropTextPadding[Top] = (IPropertyInt*)CreatePropetry(pFontPropGroup, OTID_INT, "Top", "�ϱ߾�");
	m_pPropTextPadding[Left] = (IPropertyInt*)CreatePropetry(pFontPropGroup, OTID_INT, "Left", "��߾�");
	m_pPropTextPadding[Bottom] = (IPropertyInt*)CreatePropetry(pFontPropGroup, OTID_INT, "Bottom", "�±߾�");
	m_pPropTextPadding[Right] = (IPropertyInt*)CreatePropetry(pFontPropGroup, OTID_INT, "Right", "�ұ߾�");

	//����Separator
	IPropertyGroup* pSeparatorPropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Separator", "Separator Group");
	m_pPropImageSeparator	= (IPropertyImage*)CreatePropetry(pSeparatorPropGroup, OTID_IMAGE, "SeparatorImage", "�ָ�������ͼ");
	m_pPropSeparatorPosition[0] = (IPropertyInt*)CreatePropetry(pSeparatorPropGroup, OTID_INT, "Top", "�ϱ߾�");
	m_pPropSeparatorPosition[1] = (IPropertyInt*)CreatePropetry(pSeparatorPropGroup, OTID_INT, "Left", "��߾�");
	m_pPropSeparatorSize[0] = (IPropertyInt*)CreatePropetry(pSeparatorPropGroup, OTID_INT, "Width", "��");
	m_pPropSeparatorSize[1] = (IPropertyInt*)CreatePropetry(pSeparatorPropGroup, OTID_INT, "Height", "��");

	return true;
}

// ��ʼ���ؼ�
void ICtrlContextMenuItemImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlContextMenuItemImpl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlContextMenuItemImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlContextMenuItemImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	//���Ʒָ���
	if(NULL != m_pPropIsSeparator)
	{
		if(m_pPropIsSeparator->GetValue())
		{
			if (NULL != m_pPropImageSeparator)
			{
				RECT rect = GetClientRect();
				rect.top += m_pPropSeparatorPosition[0]->GetValue();
				rect.left += m_pPropSeparatorPosition[1]->GetValue();
				rect.bottom = rect.top + m_pPropSeparatorSize[1]->GetValue();
				rect.right =rect.left + m_pPropSeparatorSize[0]->GetValue();
				m_pPropImageSeparator->DrawImage(DrawBoard, GetClientRect());
			}
			return;
		}
	}

	if (IsEnable()) 
	{
		if (m_enumMenuItemState == MeunItemStateDisable)
			m_enumMenuItemState = MeunItemStateNormal;
	}
	else
	{
		m_enumMenuItemState = MeunItemStateDisable;
	}


	//���Ʊ���ͼ
	if (NULL != m_pPropImages[m_enumMenuItemState])
		m_pPropImages[m_enumMenuItemState]->DrawImage(DrawBoard, GetClientRect());

	//��������icon
	if (NULL != m_pPropIcons[m_enumMenuItemState])
	{
		RECT rect = GetClientRect();
		rect.top += m_pPropIconPosition[0]->GetValue();
		rect.left += m_pPropIconPosition[1]->GetValue();
		rect.bottom = rect.top + m_pPropIconSize[1]->GetValue();
		rect.right =rect.left + m_pPropIconSize[0]->GetValue();
		m_pPropIcons[m_enumMenuItemState]->DrawImage(DrawBoard, rect);
	}

	//�����м������
	if (NULL != m_pPropFonts[m_enumMenuItemState])
	{
		RECT rect = GetClientRect();
		rect.top += m_pPropTextPadding[Top]->GetValue();
		rect.left += m_pPropTextPadding[Left]->GetValue();
		rect.bottom -= m_pPropTextPadding[Bottom]->GetValue();
		rect.right -= m_pPropTextPadding[Right]->GetValue();
		m_pPropFonts[m_enumMenuItemState]->DrawFontText(DrawBoard, m_pPropText->GetString(), rect);
	}

	//�����Ҳ�ļ�ͷ
	if(HaveSubMenu())
	{
		if (NULL != m_pPropArrows[m_enumMenuItemState])
		{
			RECT rect = GetClientRect();
			rect.top += m_pPropArrowPosition[0]->GetValue();
			rect.right -= m_pPropIconPosition[1]->GetValue();
			rect.bottom = rect.top + m_pPropArrowSize[1]->GetValue();
			rect.left =rect.right - m_pPropArrowSize[0]->GetValue();
			m_pPropArrows[m_enumMenuItemState]->DrawImage(DrawBoard, rect);
		}
	}
}

bool ICtrlContextMenuItemImpl::HaveSubMenu()
{
	if (m_pPropMenuPanelName == NULL)
		return false;

	if (m_pPropMenuPanelName->GetString() == NULL)
		return false;

	if (wcslen(m_pPropMenuPanelName->GetString()) <= 0)
		return false;

	return true;
}

// ������
void ICtrlContextMenuItemImpl::OnMouseEnter(POINT pt)
{
	ChangeMenuItemStyle(MeunItemStateHover);
	if(NULL != m_pContextMenu && HaveSubMenu())
	{
		if (m_pSubContextMenuWnd == NULL)
			m_pSubContextMenuWnd = new CContextMenuWnd;

		m_pContextMenu->PopupSubMenu(this, m_pSubContextMenuWnd);
	}
}

// ����Ƴ�
void ICtrlContextMenuItemImpl::OnMouseLeave(POINT pt)
{
	ChangeMenuItemStyle(MeunItemStateNormal);
	if(NULL != m_pContextMenu && HaveSubMenu())
		m_pContextMenu->DestroySubMenu(this);

	if (m_mouseFlag & MOUSE_FLAG_DOWN)
	{
		m_pContextMenu->DestroyMenu();
	}

	m_mouseFlag &= ~MOUSE_FLAG_DOWN;
}

// ���������
void ICtrlContextMenuItemImpl::OnLButtonDown(POINT pt)
{
	if(IsEnable() && !m_pPropIsSeparator->GetValue())
	{
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_MENU_ITEM_DOWN, m_pPropIndex->GetValue(), NULL);
	}

	m_mouseFlag |= MOUSE_FLAG_DOWN;
}

// ������̧��
void ICtrlContextMenuItemImpl::OnLButtonUp(POINT pt)
{
	if(IsEnable() 
		&& ::PtInRect(&GetClientRect(),pt)
		&& !m_pPropIsSeparator->GetValue())
	{
		if(::PtInRect(&GetClientRect(),pt))
		{
			m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_MENU_ITEM_UP, m_pPropIndex->GetValue(), NULL);
		}
	}

	if (m_mouseFlag & MOUSE_FLAG_DOWN)
	{
		m_pContextMenu->DestroyMenu();
	}

	m_mouseFlag &= ~MOUSE_FLAG_DOWN;
}

// ���������ؼ�
void ICtrlContextMenuItemImpl::SetContextMenu(ICtrlContextMenu* pContextMenu)
{
	m_pContextMenu = pContextMenu;
}

// ���MenuITem��ʾ�ķ��
void ICtrlContextMenuItemImpl::ChangeMenuItemStyle(MENUITEMSTATE state)
{
	if(state != m_enumMenuItemState)
	{
		m_enumMenuItemState = state;
		RedrawControl(true);
	}
}

// ���ò˵���������
void ICtrlContextMenuItemImpl::SetMenuFont(IPropertyFontBase* pNormalFont, IPropertyFontBase* pHoverFont, IPropertyFontBase* pDisableFont)
{
	if (pNormalFont != NULL && m_pPropFonts[MeunItemStateNormal] != NULL)
		m_pPropFonts[MeunItemStateNormal]->SetRelevancyProp(dynamic_cast<IPropertyBase*>(pNormalFont));

	if (pHoverFont != NULL && m_pPropFonts[MeunItemStateHover] != NULL)
		m_pPropFonts[MeunItemStateHover]->SetRelevancyProp(dynamic_cast<IPropertyBase*>(pHoverFont));

	if (pDisableFont != NULL && m_pPropFonts[MeunItemStateDisable] != NULL)
		m_pPropFonts[MeunItemStateDisable]->SetRelevancyProp(dynamic_cast<IPropertyBase*>(pDisableFont));
}
