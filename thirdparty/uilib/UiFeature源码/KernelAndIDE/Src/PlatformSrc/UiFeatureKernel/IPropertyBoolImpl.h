//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "..\..\Inc\IPropertyBool.h"

class IPropertyBoolImpl : public IPropertyBool
{
public:
	IPropertyBoolImpl(IUiFeatureKernel* pUiKernel);
	virtual ~IPropertyBoolImpl();

	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode);

	virtual void SetValue(bool bBoolData);
	virtual bool GetValue();
	// ����һ�����Կ�¡
	virtual bool Clone(IPropertyBase* pFromPropBase);

private:
	bool m_bBoolData;
};
