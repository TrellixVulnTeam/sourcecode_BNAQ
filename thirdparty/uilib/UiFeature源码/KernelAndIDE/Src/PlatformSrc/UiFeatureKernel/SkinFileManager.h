
#pragma once

#define PUGIXML_WCHAR_MODE
#include "..\..\Inc\PugiXml\pugixml.hpp"
using namespace pugi;

#include "..\..\Inc\IPropertySkinManager.h"
#include "IPropertyWindowImpl.h"
#include "IZipFileImpl.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\IWindowBase.h"


class CSkinFileManager
{
public:
	CSkinFileManager();
	~CSkinFileManager();

	// ������ʾ����������
	virtual void SetArea(AREA_TYPE areaType);

	// ��ȡһ��Ƥ������Ϣ
	SKIN_FILE_ITEM* ReadSkinFile(LPCWSTR pszSkinPath);

	// ɾ�����е�Ƥ�����ļ�
	void ReleaseAllSkinFile();
	// ɾ������һ��Ƥ�����ļ�
	void ReleaseSkinFile(LPCWSTR pszSkinPath);
	// ɾ��һ������
	void ReleaseBaseProp(IPropertyBase *pCtrlProp);
	// ȡ��Ƥ���ļ�
	SKIN_FILE_ITEM* GetSkinFileItem(LPCWSTR pszSkinPath, bool bNew = false);
	// ����һ���յ�Ƥ���ļ�
	SKIN_FILE_ITEM* CreateEmptySkinFileItem(LPCWSTR pszSkinPath);

	// ȡ��ָ���������
	IPropertyBaseMap* GetIPropertyBaseMap(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pszPropGroupName, bool bIsCreate);

	// ����ָ��������
	IPropertyBase* FindBasePropertyByPropId(SKIN_FILE_ITEM *pSkinFileItem, OBJECT_TYPE_ID propType, DWORD dwObjId);
	IPropertyBase* FindBasePropertyByPropId(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pszPropType, DWORD dwObjId);
	// ����ָ��������
	IPropertyBase* FindBasePropertyByPropName(SKIN_FILE_ITEM *pSkinFileItem, OBJECT_TYPE_ID propType, LPCWSTR pszPropName);
	IPropertyBase* FindBasePropertyByPropName(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pszPropType, LPCWSTR pszPropName);

	// �ӿؼ����Զ�����ɾ��һ���ؼ���������ɾ���ؼ��Ľڵ㣬�ؼ��ľ������Բ�û��ɾ��
	bool DeleteControlPropetryFromCtrlPropMap(IControlBase* pCtrl);
	// �ڴ��Ż���Ҫ��ֻ����Ҫ�õ�zip�е�ͼƬ��ʱ��ż���ͼƬ
	bool ReadSkinFileItem(IZipFile *pZipFileMgr, ZIP_FILE* pZipItem);

	// ����Ƥ����
	bool SaveSkinFileItem(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pszSkinDir, LPCWSTR pszSkinName, char *pszPassword);

	// ����һ�����ԣ����������Է������
	IPropertyBase* CreateEmptyBaseProp(SKIN_FILE_ITEM *pSkinFileItem, OBJECT_TYPE_ID propType, DWORD *pdwObjectId = NULL);

	// ����ͼƬʹ�õ�zip�ļ�
	SKIN_FILE_ITEM * GetLocalImageSkinFileItem();
	// ȡ������Ƥ����Ĭ�ϵ�������Ϣ
	IPropertyFontBase* GetDefaultFontBase(SKIN_FILE_ITEM* pSkinFileItem);

	// ɾ��һ���ؼ�����������
	bool DeleteControlPropetry(IControlBase* pCtrl);

	// ɾ�������е�Base���ԣ���ImageBase��FontBase
	bool DeletePropetryBaseProp(SKIN_FILE_ITEM* pSkinFileItem, IPropertyBase *pPropBase);
	bool DeleteFontBaseProp(SKIN_FILE_ITEM* pSkinFileItem, IPropertyFontBase *pFontBaseProp);
	bool ModifyFontBaseProp(SKIN_FILE_ITEM* pSkinFileItem, IPropertyFontBase *pFontBaseProp, LPCWSTR pszNewPropName);

	bool DeleteImageBaseProp(SKIN_FILE_ITEM* pSkinFileItem, IPropertyImageBase *pImgBaseProp);
	bool ModifyImageBaseProp(SKIN_FILE_ITEM* pSkinFileItem, IPropertyImageBase *pImgBaseProp, LPCWSTR pszNewPropName);

//////////////////////////////////////////////////////////////////////////
	// ����Resource.xml
	bool TranslateResourceXml(SKIN_FILE_ITEM *pSkinFileItem, ZIP_FILE *pResurceXml);
	// Controls.xml ���
	bool TranslateControlsXml(SKIN_FILE_ITEM *pSkinFileItem, ZIP_FILE *pControlsXml);
	void ReleaseSkinFileItem(SKIN_FILE_ITEM *pSkinFile);
	void SetPropRelevancy(IPropertyBaseMap* pFromMap, IPropertyBaseMap* pToMap);
//////////////////////////////////////////////////////////////////////////

	void ReleaseIPropertyBase(IPropertyBase *pCtrlProp);

private:

	bool DeleteControlPropetryFromCtrlPropMapByVec(PROP_CONTROL_VEC* pVec, IPropertyControl* pCtrlProp);
	bool DeleteControlPropetryByGroup(IPropertyGroup *pGroup, SKIN_FILE_ITEM* pSkinItem);
	void ReleaseLayoutMap(IPropertyBaseMap &LayoutWindowMap);
	void ReleaseLayoutMapPropControlVec(PROP_CONTROL_VEC* pCtrlVec);
	void ReleasePropMap(IPropertyBaseMapMap &PropMap, bool bReleaseChild);
	void ReleasePropMapItem(IPropertyBaseMap* pPropMapItem);

	bool GeneralCreateSubProp(SKIN_FILE_ITEM *pSkinFileItem, xml_node* pXmlNode, IPropertyBaseMap* pCtrlPropMap);
	bool AppendBasePropToGroup(SKIN_FILE_ITEM *pSkinFileItem, IPropertyGroup *pGroup, xml_node* pXmlNode);

	// ����Windows.xml
	bool TranslateWindowsXml(SKIN_FILE_ITEM *pSkinFileItem, ZIP_FILE *pWindowsXml);

	// Layout.xml ���
	bool TranslateLayoutXml(SKIN_FILE_ITEM *pSkinFileItem, ZIP_FILE *pLayoutXml);
	bool GeneralCreateWindowLayoutProp(SKIN_FILE_ITEM *pSkinFileItem, xml_node* pXmlNode, PROP_CONTROL_VEC* pChildCtrlVec, IPropertyControl* pParentProp);

	// ͨ�õĴ���Դxml�д�������
	bool GeneralCreateBaseProp(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pPropType, xml_node* pXmlNode, IPropertyBaseMap* pPropMap);

	// ����������base���ԵĹ���
	void SetPropetryBaseRelevancy(SKIN_FILE_ITEM *pSkinFileItem);
	// ����imagebase���Ժ�ͼƬ�Ĺ���
	bool SetImageFileRelevancy(SKIN_FILE_ITEM *pSkinFileItem);

	IPropertyGroup* FindControlPropGroup(SKIN_FILE_ITEM *pSkinFileItem, DWORD dwObjId, CStringW &strCtrlType);

	// ���� IPropertyImageBase �����е� IMAGE_BASE_PROP �� pszSkinFilePath
	void SetImageBaseSkinPath(SKIN_FILE_ITEM *pSkinFileItem);

//////////////////////////////////////////////////////////////////////////
	// ����Ƥ����
	bool SaveLayoutXml(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pszSavePath);
	bool SaveLayoutXml_ChildCtrl(xml_document &XmlStrObj, xml_node* pNode, PROP_CONTROL_VEC* pWndChildVec);
	bool SaveResourceXml(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pszSavePath);
	bool SaveControlsXml(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pszSavePath);
	bool SaveXml_GroupProp(xml_document &XmlStrObj, xml_node* pParentNode, IPropertyGroup *pPropGroup);
	bool SaveWindowsXml(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pszSavePath);

private:
	AREA_TYPE m_AreaType;
	// ����Ƥ���ļ���map
	SKIN_FILE_MAP m_SkinFileMap;
	// ����ͼƬʹ�õ�zip�ļ�
	SKIN_FILE_ITEM m_LocalImageSkinFileItem;
};
