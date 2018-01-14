//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "..\..\Inc\IPropertyGroup.h"

class IPropertyGroupImpl : public IPropertyGroup
{
public:
	IPropertyGroupImpl(IUiFeatureKernel* pUiKernel);
	virtual ~IPropertyGroupImpl();

	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode);

	// ׷��һ������
	virtual void AppendProperty(IPropertyBase* pProperty);
	// ȡ��Group�µ������б�
	virtual GROUP_PROP_VEC* GetPropVec();
	// ����һ�����Կ�¡
	virtual bool Clone(IPropertyBase* pFromPropBase);

private:
	GROUP_PROP_VEC m_PropVec;
};
