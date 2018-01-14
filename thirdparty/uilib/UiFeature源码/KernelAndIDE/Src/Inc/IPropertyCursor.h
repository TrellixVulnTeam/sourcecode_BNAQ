//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"
#include "IPropertyCursorBase.h"

class IWindowBase;
class _declspec(novtable) IPropertyCursor : public IPropertyBase
{
public:
	IPropertyCursor(IUiFeatureKernel* pUiKernel);
	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData() = 0;
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode) = 0;

	virtual const WCHAR * GetCursorBaseName() = 0;

	// ���������Ϣ
	virtual void SetCursorBaseProp(IPropertyCursorBase *pCursorProp) = 0;
	virtual IPropertyCursorBase* GetCursorBaseProp() = 0;
};
