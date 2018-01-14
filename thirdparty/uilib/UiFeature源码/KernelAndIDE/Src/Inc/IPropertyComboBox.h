//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

class CPropertyViewCtrl;

// string ����
typedef vector<CStringW>									STRING_VEC;
// ComboBox����
struct COMBOBOX_PROP
{
	int nSelect;
	STRING_VEC DataVec;
};

class _declspec(novtable) IPropertyComboBox : public IPropertyBase
{
	friend class CPropertyViewCtrl;

public:
	IPropertyComboBox(IUiFeatureKernel* pUiKernel);
	virtual void Clear() = 0;
	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData() = 0;
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode) = 0;

	// ����ѡ����
	virtual void SetSelectString(LPCWSTR pszSelString) = 0;
	virtual void SetSelect(int nSel) = 0;
	virtual int GetSelect() = 0;
	virtual int GetDataCounts() = 0;
	// ���б������һ������
	virtual bool AppendString(LPCWSTR pszString) = 0;

protected:
	virtual COMBOBOX_PROP* GetComboBoxData() = 0;
};
