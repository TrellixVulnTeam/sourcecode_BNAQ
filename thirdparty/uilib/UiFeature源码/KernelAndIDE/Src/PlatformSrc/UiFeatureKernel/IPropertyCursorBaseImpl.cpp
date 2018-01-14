
#include "stdafx.h"
#include "IPropertyCursorBaseImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\IWindowBase.h"

IPropertyCursorBaseImpl::IPropertyCursorBaseImpl(IUiFeatureKernel* pUiKernel) : IPropertyCursorBase(pUiKernel)
{
	SetObjectType(_T(PROP_TYPE_CURSOR_BASE_NAME));

	m_bIsActiveProp = true;
	// �Ƿ���ϵͳĬ�Ϲ��
	m_bIsSysCursor = true;
	// ���ID
	m_nCursorId = 0;
}

IPropertyCursorBaseImpl::~IPropertyCursorBaseImpl()
{

}

bool IPropertyCursorBaseImpl::IsRightData()
{
	return (m_nCursorId > 0);
}

bool IPropertyCursorBaseImpl::ReadPropertyFromXmlNode(xml_node* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	const WCHAR * psz_id = XmlGetAttrValue(pXmlNode, _T(SKIN_OBJECT_ID));
	const WCHAR * psz_name = XmlGetAttrValue(pXmlNode, L"name");
	const WCHAR * psz_issyscursor = XmlGetAttrValue(pXmlNode, L"issyscursor");
	const WCHAR * psz_cursorid = XmlGetAttrValue(pXmlNode, L"cursorid");
	if (psz_id == NULL || psz_name == NULL || psz_issyscursor == NULL || psz_cursorid == NULL)
		return false;

	SetObjectId(_wtoi(psz_id));
	SetObjectName(psz_name);

	m_bIsSysCursor = (psz_issyscursor[0] == '1');
	m_nCursorId = _wtoi(psz_cursorid);
	return true;
}

// д��xml
bool IPropertyCursorBaseImpl::AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode)
{
	// �������Ч���ԣ���д��XML
	if (!GetActivePropetry())
		return true;

	if (pParentXmlNode == NULL)
		return false;

	xml_node PropNode = pParentXmlNode->append_child(L"item");
	if (!PropNode)
		return false;

	AddIntAttrToNode(&PropNode, _T(SKIN_OBJECT_ID), (int)GetObjectId());
	AddStringAttrToNode(&PropNode, L"name", GetObjectName());
	AddStringAttrToNode(&PropNode, L"issyscursor", (m_bIsSysCursor ? L"1" : L"0"));
	AddIntAttrToNode(&PropNode, L"cursorid", m_nCursorId);

	return true;
}

// �Ƿ�Ϊϵͳ���
bool IPropertyCursorBaseImpl::IsSystemCursor()
{
	return m_bIsSysCursor;
}

// ����ϵͳ���
void IPropertyCursorBaseImpl::SetSystemCursor(bool bIsSysCursor)
{
	m_bIsSysCursor = bIsSysCursor;
}

// ���ù��ID
void IPropertyCursorBaseImpl::SetCursorId(int nId)
{
	m_nCursorId = nId;
}

// �õ����id
int IPropertyCursorBaseImpl::GetCursorId()
{
	return m_nCursorId;
}

// ����һ�����Կ�¡
bool IPropertyCursorBaseImpl::Clone(IPropertyBase* pFromPropBase)
{
	if (!IsSameTypePropetry(dynamic_cast<IPropertyBase*>(this), pFromPropBase))
		return false;

	IPropertyCursorBaseImpl* pFromProp = dynamic_cast<IPropertyCursorBaseImpl*>(pFromPropBase);
	if (pFromProp == NULL)
		return false;

	m_bIsSysCursor = pFromProp->m_bIsSysCursor;
	m_nCursorId = pFromProp->m_nCursorId;
	return true;
}
