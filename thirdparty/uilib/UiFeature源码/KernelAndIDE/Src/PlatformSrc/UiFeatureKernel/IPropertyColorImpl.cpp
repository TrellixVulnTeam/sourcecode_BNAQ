
#include "stdafx.h"
#include "IPropertyColorImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyColorImpl::IPropertyColorImpl(IUiFeatureKernel* pUiKernel) : IPropertyColor(pUiKernel)
{
	SetObjectType(_T(PROP_TYPE_COLOR_NAME));
}

IPropertyColorImpl::~IPropertyColorImpl()
{

}

bool IPropertyColorImpl::IsRightData()
{
	return false;
}

bool IPropertyColorImpl::ReadPropertyFromXmlNode(xml_node* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	return true;
}

// ����һ�����Կ�¡
bool IPropertyColorImpl::Clone(IPropertyBase* pFromPropBase)
{
	return false;
}
