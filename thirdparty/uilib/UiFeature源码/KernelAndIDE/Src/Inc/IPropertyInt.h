//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

// int ��Builder�е�ֵ��Χ��-(0x7FFFFFFF), 0x7FFFFFFF
class _declspec(novtable) IPropertyInt : public IPropertyBase
{
public:
	IPropertyInt(IUiFeatureKernel* pUiKernel);
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode) = 0;

	virtual void SetValue(int nValue) = 0;
	virtual int GetValue() = 0;
};
