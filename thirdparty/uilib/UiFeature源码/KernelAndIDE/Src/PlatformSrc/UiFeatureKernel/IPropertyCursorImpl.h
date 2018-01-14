//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "..\..\Inc\IPropertyCursor.h"
#include "..\..\Inc\IPropertyCursorBase.h"

class IWindowBase;
class IPropertyCursorImpl : public IPropertyCursor
{
public:
	IPropertyCursorImpl(IUiFeatureKernel *pUiKernel);
	virtual ~IPropertyCursorImpl();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode);

	virtual const WCHAR * GetCursorBaseName();

	// ���������Ϣ
	virtual void SetCursorBaseProp(IPropertyCursorBase *pCursorProp);
	virtual IPropertyCursorBase* GetCursorBaseProp();
	// ����һ�����Կ�¡
	virtual bool Clone(IPropertyBase* pFromPropBase);
};
