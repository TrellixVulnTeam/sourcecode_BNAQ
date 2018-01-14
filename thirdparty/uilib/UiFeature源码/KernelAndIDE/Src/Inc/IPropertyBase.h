//////////////////////////////////////////////////////////////////////////
// ����

#pragma once

#define PUGIXML_WCHAR_MODE
#include "PugiXml\pugixml.hpp"
using namespace pugi;

#include "IFeatureObject.h"
#include "IPropertyBuilderCtrl.h"
#include "CTList.h"
#include <atlstr.h>
using namespace ATL;

class IPropertyBase;
class IUiFeatureKernel;


// һ�����ԵĶ��У��磺font��string��image�ȣ�KEY��ObjectId
// һ�ֿؼ������Զ��У��磺Button��CheckBox�ȣ�KEY��ObjectId
// һ�ִ��ڵ����Զ��У�KEY��ObjectId
typedef map<DWORD, IPropertyBase*>						IPropertyBaseMap;

// ������������ԵĶ��У�KEY�������������ƣ��磺font
// ���пؼ���������ԵĶ��У�KEY���ؼ��������ƣ��磺Button
// KEY:ObjectId�����д��ڵĹ�����map
typedef map<CStringW, IPropertyBaseMap*>					IPropertyBaseMapMap;

class IUiFeatureKernel;
class IPropertyBase : public IFeatureObject, public ListObj
{
public:
	IPropertyBase(IUiFeatureKernel *pUiKernel);
	virtual ~IPropertyBase();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode);

	// ������������
	virtual const WCHAR* GetRelevancyPropName();
	virtual void SetRelevancyPropName(WCHAR *pszPropName);

	const char* GetObjectInfo();
	void SetObjectInfo(const char* pszObjInfo);

	// ��������
	virtual IPropertyBase* GetRelevancyProp();
	virtual void SetRelevancyProp(IPropertyBase *pszProp);
	
	// ��Builder�н���
	virtual void EnableInBuilder(bool bEnable);
	virtual bool IsEnableInBuilder();
	virtual void SetPropBuilderCtrl(IPropertyBuilderCtrl* pBuilderCtrl);

	// ����һ�����Կ�¡
	virtual bool Clone(IPropertyBase* pFromPropBase) = 0;

private:
	char *m_pszObjInfo;
	// �����������ƣ����Ȳ�������30�ֽ�
	WCHAR *m_pszRelevancyPropName;
	// ��������
	IPropertyBase *m_pRelevancyProp;
	IPropertyBuilderCtrl* m_pBuilderCtrl;
	bool m_bIsEnableInBuilder;
};
