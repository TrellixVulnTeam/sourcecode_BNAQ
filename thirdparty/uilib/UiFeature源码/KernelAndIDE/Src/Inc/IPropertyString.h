//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

// ��������
enum AREA_TYPE
{
	AT_NONE	= 0,
	// ���ļ���
	AT_CN		= 1,
	// ���ķ���
	AT_CN_TW	= 2,
	// Ӣ��
	AT_EN		= 3,
	// ����
	AT_JP		= 4,
	// ����
	AT_GE		= 5,
	AT_LAST		= 6
};

class _declspec(novtable) IPropertyString : public IPropertyBase
{
public:
	IPropertyString(IUiFeatureKernel* pUiKernel);
	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData() = 0;
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode) = 0;

	// Ĭ����ʾ����
	virtual WCHAR* GetString(AREA_TYPE areaType = AT_CN) = 0;
	virtual void SetString(const WCHAR* pszString, AREA_TYPE areaType = AT_CN) = 0;
	virtual int GetLength() = 0;

	virtual void SetArea(AREA_TYPE areaType) = 0;
};
