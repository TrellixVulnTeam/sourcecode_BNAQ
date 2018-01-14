//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "..\..\Inc\IPropertyComboBox.h"


class IPropertyComboBoxImpl : public IPropertyComboBox
{
public:
	IPropertyComboBoxImpl(IUiFeatureKernel* pUiKernel);
	virtual ~IPropertyComboBoxImpl();

	virtual void Clear();
	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode);

	// ����ѡ����
	virtual void SetSelect(int nSel);
	virtual void SetSelectString(LPCWSTR pszSelString);
	virtual int GetSelect();
	virtual int GetDataCounts();
	// ���б������һ������
	virtual bool AppendString(LPCWSTR pszString);
	// ����һ�����Կ�¡
	virtual bool Clone(IPropertyBase* pFromPropBase);

protected:
	virtual COMBOBOX_PROP* GetComboBoxData();

private:
	COMBOBOX_PROP m_ComboBoxPro;
};
