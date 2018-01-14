//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "..\..\Inc\IPropertyCursorBase.h"

class IWindowBase;
class IPropertyCursorBaseImpl : public IPropertyCursorBase
{
public:
	IPropertyCursorBaseImpl(IUiFeatureKernel* pUiKernel);
	virtual ~IPropertyCursorBaseImpl();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode);

	// ����ϵͳ���
	virtual void SetSystemCursor(bool bIsSysCursor);
	// �Ƿ�Ϊϵͳ���
	virtual bool IsSystemCursor();

	// ���ù��ID
	virtual void SetCursorId(int nId);
	// �õ����id
	virtual int GetCursorId();
	// ����һ�����Կ�¡
	virtual bool Clone(IPropertyBase* pFromPropBase);

private:
	// �Ƿ���ϵͳĬ�Ϲ��
	bool m_bIsSysCursor;
	// ���ID
	int m_nCursorId;
};
