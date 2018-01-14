
#include "StdAfx.h"
#include "ICtrlLinkImpl.h"
#include "..\..\Inc\IControlManager.h"


ICtrlLink::ICtrlLink(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlLinkImpl::ICtrlLinkImpl(IUiFeatureKernel *pUiKernel) : ICtrlLink(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_LINK);

	m_bIsLButtonDown = false;

	m_pPropLinkText = NULL;
	m_pPropLinkUrl = NULL;
	m_pPropCursor = NULL;
	m_PropFontGroup = NULL;
	m_pPropFontNormal = NULL;
	m_pPropFontHover = NULL;
	m_pPropFontDown = NULL;
}

ICtrlLinkImpl::~ICtrlLinkImpl()
{
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlLinkImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// ��ʼ���ؼ�
void ICtrlLinkImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlLinkImpl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlLinkImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlLinkImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (m_pPropLinkText == NULL || m_pPropLinkText->GetLength() <= 0)
		return;

	IPropertyFont* pPropFont = m_pPropFontDown;
	if (!m_bIsLButtonDown)
	{
		if (IsMousehover())
			pPropFont = m_pPropFontHover;
		else
			pPropFont = m_pPropFontNormal;
	}

	if (pPropFont != NULL)
		pPropFont->DrawFontText(DrawBoard, m_pPropLinkText->GetString(), GetClientRect());
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlLinkImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropLinkText = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "LinkText", "��������ʾ������");
	m_pPropLinkUrl = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "LinkUrl", "������ָ��ĵ�ַ");
	m_pPropCursor = (IPropertyCursor*)CreatePropetry(NULL, OTID_CURSOR, "CursorStyle", "�����ӵ��������");
	m_PropFontGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "FontGroup", "��������ʾ����������");
	m_pPropFontNormal = (IPropertyFont*)CreatePropetry(m_PropFontGroup, OTID_FONT, "Normal", "����״̬��ʾ����������");
	m_pPropFontHover = (IPropertyFont*)CreatePropetry(m_PropFontGroup, OTID_FONT, "MouseHover", "���Hover״̬��ʾ����������");
	m_pPropFontDown = (IPropertyFont*)CreatePropetry(m_PropFontGroup, OTID_FONT, "MouseDown", "��갴��״̬��ʾ����������");

	return true;
}

// ������̧��
void ICtrlLinkImpl::OnLButtonUp(POINT pt)
{
	m_bIsLButtonDown = false;
	this->RedrawControl(true);

	if (m_pWindowBase == NULL || m_pPropLinkUrl == NULL || m_pPropLinkUrl->GetLength() <= 0)
		return;

	m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_LINK_UP, (WPARAM)m_pPropLinkUrl->GetString(), NULL);
}

// ���ÿؼ����
IPropertyCursor* ICtrlLinkImpl::OnSetCursor(POINT pt)
{
	return m_pPropCursor;
}

// ���������
void ICtrlLinkImpl::OnLButtonDown(POINT pt)
{
	m_bIsLButtonDown = true;
	this->RedrawControl(true);

	if (m_pWindowBase == NULL || m_pPropLinkUrl == NULL || m_pPropLinkUrl->GetLength() <= 0)
		return;

	m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_LINK_DOWN, (WPARAM)m_pPropLinkUrl->GetString(), NULL);
}

// ����Link����
void ICtrlLinkImpl::SetLinkText(LPCWSTR pText, bool bRedraw)
{
	if (pText == NULL)
		return;

	if (m_pPropLinkText == NULL)
		m_pPropLinkText = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "LinkText", "��������ʾ������", true);

	if (m_pPropLinkText == NULL)
		return;

	m_pPropLinkText->SetString(pText);
	this->RedrawControl(bRedraw);
}

// ����Link���ӵ�ַURL
void ICtrlLinkImpl::SetLinkUrl(LPCWSTR pUrl)
{
	if (pUrl == NULL)
		return;

	if (m_pPropLinkUrl == NULL)
		m_pPropLinkUrl = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "LinkUrl", "������ָ��ĵ�ַ", true);

	if (m_pPropLinkUrl == NULL)
		return;

	m_pPropLinkUrl->SetString(pUrl);
}

// ������
void ICtrlLinkImpl::OnMouseEnter(POINT pt)
{
	this->RedrawControl(true);
}

// ����Ƴ�
void ICtrlLinkImpl::OnMouseLeave(POINT pt)
{
	this->RedrawControl(true);
}

// ȡ��Link���ӵ�ַURL
LPCWSTR ICtrlLinkImpl::GetLinkUrl()
{
	if (m_pPropLinkUrl == NULL)
		return NULL;

	return m_pPropLinkUrl->GetString();
}
