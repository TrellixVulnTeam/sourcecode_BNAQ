//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

class IWindowBase;
class _declspec(novtable) IPropertyCursorBase : public IPropertyBase
{
public:
	IPropertyCursorBase(IUiFeatureKernel* pUiKernel);
	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData() = 0;
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode) = 0;

	// ����ϵͳ���
	virtual void SetSystemCursor(bool bIsSysCursor) = 0;
	// �Ƿ�Ϊϵͳ���
	virtual bool IsSystemCursor() = 0;

	// ���ù��ID
	virtual void SetCursorId(int nId) = 0;
	// �õ����id
	virtual int GetCursorId() = 0;
};
