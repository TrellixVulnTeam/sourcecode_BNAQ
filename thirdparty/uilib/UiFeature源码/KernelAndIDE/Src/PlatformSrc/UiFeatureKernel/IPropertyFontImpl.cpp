
#include "stdafx.h"
#include "IPropertyFontImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\ICommonFun.h"

IPropertyFontImpl::IPropertyFontImpl(IUiFeatureKernel* pUiKernel) : IPropertyFont(pUiKernel)
{
	SetObjectType(_T(PROP_TYPE_FONT_NAME));
}

IPropertyFontImpl::~IPropertyFontImpl()
{

}

const WCHAR * IPropertyFontImpl::GetFontBaseName()
{
	return GetRelevancyPropName();
}

bool IPropertyFontImpl::IsRightData()
{
	return (GetRelevancyProp() != NULL);
}

IPropertyFontBase* IPropertyFontImpl::GetFontBaseProp()
{
	return dynamic_cast<IPropertyFontBase*>(GetRelevancyProp());
}

void IPropertyFontImpl::SetNeedRedraw()
{
	if (GetOwnerObject() == NULL)
		return;

	IControlBase *pCtrlBase = dynamic_cast<IControlBase*>(GetOwnerObject());
	if (pCtrlBase == NULL)
		return;

	pCtrlBase->RedrawControl();
}

void IPropertyFontImpl::SetFontBaseProp(IPropertyFontBase *pFontProp)
{
	if (pFontProp == NULL)
	{
		SetRelevancyProp(NULL);
		SetNeedRedraw();
		return;
	}

	IPropertyBase* pPropBase = dynamic_cast<IPropertyBase*>(pFontProp);
	SetRelevancyProp(pPropBase);
	SetNeedRedraw();
}

bool IPropertyFontImpl::ReadPropertyFromXmlNode(xml_node* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	const WCHAR * psz_id = XmlGetAttrValue(pXmlNode, _T(SKIN_OBJECT_ID));
	const WCHAR * psz_name = XmlGetAttrValue(pXmlNode, L"name");
	const WCHAR * psz_fontbasename = XmlGetAttrValue(pXmlNode, L"fontbasename");
	if (psz_id == NULL || psz_name == NULL || psz_fontbasename == NULL)
		return false;

	SetObjectId(_wtoi(psz_id));
	SetObjectName(psz_name);

	SetRelevancyPropName((WCHAR*)psz_fontbasename);
	return true;
}

// д��xml
bool IPropertyFontImpl::AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode)
{
	// �������Ч���ԣ���д��XML
	if (!GetActivePropetry())
		return true;

	if (pParentXmlNode == NULL)
		return false;

	// ���û�����ݣ��Ͳ�����xml
	if (GetRelevancyPropName() == NULL || wcslen(GetRelevancyPropName()) <= 0)
		return true;

	xml_node PropNode = pParentXmlNode->append_child(L"item");
	if (!PropNode)
		return false;

	AddIntAttrToNode(&PropNode, _T(SKIN_OBJECT_ID), (int)GetObjectId());
	AddStringAttrToNode(&PropNode, L"name", GetObjectName());
	AddStringAttrToNode(&PropNode, L"fontbasename", GetRelevancyPropName());
	return true;
}

// ��������
bool IPropertyFontImpl::DrawFontText(CDrawingBoard &DstDc, LPCWSTR pszOutText, RECT DstRct)
{
	IPropertyFontBase* pPropBase = dynamic_cast<IPropertyFontBase*>(this->GetRelevancyProp());
	if (pPropBase == NULL)
		return false;

	return pPropBase->DrawFontText(DstDc, pszOutText, DstRct);
}

// ����ͼƬ�����ػ��־��������ɺ󣬽����´λ��Ƶ�ʱ�����´���ͼƬ����
void IPropertyFontImpl::SetPictureTextRedrawSign()
{
	IPropertyFontBase* pPropBase = dynamic_cast<IPropertyFontBase*>(this->GetRelevancyProp());
	if (pPropBase == NULL)
		return;

	return pPropBase->SetPictureTextRedrawSign();
}


// ȡ�û������ֵľ��δ�С
bool IPropertyFontImpl::GetTextDrawRect(CDrawingBoard* pDstBoard, LPCWSTR pszDrawText, RECT &DrawRect, RECT &RectInDc)
{
	if (pszDrawText == NULL || wcslen(pszDrawText) <= 0)
		return false;

	IPropertyFontBase* pPropBase = dynamic_cast<IPropertyFontBase*>(this->GetRelevancyProp());
	if (pPropBase == NULL)
		return false;

	return pPropBase->GetTextDrawRect(pDstBoard, pszDrawText, DrawRect, RectInDc);
}

// ����һ�����Կ�¡
bool IPropertyFontImpl::Clone(IPropertyBase* pFromPropBase)
{
	if (!IsSameTypePropetry(dynamic_cast<IPropertyBase*>(this), pFromPropBase))
		return false;

	IPropertyFontImpl* pFromProp = dynamic_cast<IPropertyFontImpl*>(pFromPropBase);
	if (pFromProp == NULL)
		return false;

//	SetRelevancyProp(NULL);
//	SetRelevancyPropName((WCHAR*)pFromProp->GetRelevancyPropName());

	SetRelevancyProp(pFromProp->GetRelevancyProp());
	return true;
}
