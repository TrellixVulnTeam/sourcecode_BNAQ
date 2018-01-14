//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "..\..\Inc\IPropertyColor.h"

class IPropertyColorImpl : public IPropertyColor
{
public:
	IPropertyColorImpl(IUiFeatureKernel* pUiKernel);
	virtual ~IPropertyColorImpl();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode);
	// ����һ�����Կ�¡
	virtual bool Clone(IPropertyBase* pFromPropBase);

};
