//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

// Group �е������б�
typedef CTList				GROUP_PROP_VEC;

class _declspec(novtable) IPropertyGroup : public IPropertyBase
{
public:
	IPropertyGroup(IUiFeatureKernel* pUiKernel);
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode) = 0;

	// ׷��һ������
	virtual void AppendProperty(IPropertyBase* pProperty) = 0;

	// ȡ��Group�µ������б�
	virtual GROUP_PROP_VEC* GetPropVec() = 0;
};
