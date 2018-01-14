//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "..\..\Inc\IPropertyInt.h"

// int ��Builder�е�ֵ��Χ��-(0x7FFFFFFF), 0x7FFFFFFF
class IPropertyIntImpl : public IPropertyInt
{
public:
	IPropertyIntImpl(IUiFeatureKernel* pUiKernel);
	virtual ~IPropertyIntImpl();

	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode);

	virtual void SetValue(int nValue);
	virtual int GetValue();
	// ����һ�����Կ�¡
	virtual bool Clone(IPropertyBase* pFromPropBase);

private:
	int m_nIntData;
};
