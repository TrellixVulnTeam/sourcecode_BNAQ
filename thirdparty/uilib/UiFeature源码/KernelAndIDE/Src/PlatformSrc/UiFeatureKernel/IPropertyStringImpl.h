//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "..\..\Inc\IPropertyString.h"
#include <atlstr.h>
using namespace ATL;

typedef map<AREA_TYPE, WCHAR*>		STRING_MAP;
// String����
struct STRING_PROP
{
	// ��������
	WCHAR* pstrDefaultString;
	AREA_TYPE nDefaultArea;
	STRING_MAP StringMap;
};

class IPropertyStringImpl : public IPropertyString
{
public:
	IPropertyStringImpl(IUiFeatureKernel* pUiKernel);
	virtual ~IPropertyStringImpl();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode);

	// Ĭ����ʾ����
	virtual WCHAR* GetString(AREA_TYPE areaType = AT_CN);
	virtual void SetString(const WCHAR* pszString, AREA_TYPE areaType = AT_CN);
	virtual int GetLength();

	virtual void SetArea(AREA_TYPE areaType);
	// ����һ�����Կ�¡
	virtual bool Clone(IPropertyBase* pFromPropBase);

private:
	void Clear();
	void ResetDefaultString();

private:
	STRING_PROP m_StringProp;
};
