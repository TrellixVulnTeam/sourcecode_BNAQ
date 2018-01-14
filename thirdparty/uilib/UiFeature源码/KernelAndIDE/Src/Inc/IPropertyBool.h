//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

class _declspec(novtable) IPropertyBool : public IPropertyBase
{
public:
	IPropertyBool(IUiFeatureKernel* pUiKernel);
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode) = 0;

	virtual void SetValue(bool bBoolData) = 0;
	virtual bool GetValue() = 0;
};
