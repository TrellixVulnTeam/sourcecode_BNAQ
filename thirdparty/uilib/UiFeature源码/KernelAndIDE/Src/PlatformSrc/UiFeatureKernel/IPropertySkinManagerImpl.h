
#pragma once

#define PUGIXML_WCHAR_MODE
#include "..\..\Inc\PugiXml\pugixml.hpp"
using namespace pugi;

#include "..\..\Inc\IPropertySkinManager.h"
#include "IPropertyWindowImpl.h"
#include "IZipFileImpl.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\IWindowBase.h"
#include "SkinFileManager.h"

class CLocalImageList;
//////////////////////////////////////////////////////////////////////////
// ��Դ���Զ���

// ����ͼƬmap
typedef map<CStringW, IPropertyImageBase*>	LOCAL_IMAGE_MAP;

class IPropertySkinManagerImpl : public IPropertySkinManager
{
	friend class CUiFeatureSkinMergerDlg;

public:
	IPropertySkinManagerImpl();
	virtual ~IPropertySkinManagerImpl();

	// ȡ��Ƥ�����汾��
	virtual SKIN_VERSION GetSkinFileVersion(LPCWSTR pZipFilePath, int &nPasswordLen);
	// ��֤�û�Ƥ��������
	virtual bool ChekUserPassword(const char *pUserPassword, LPCWSTR pZipFilePath);

	// ��ʼ�������������
	virtual bool InitCursorBasePropetry(SKIN_FILE_ITEM* pSkinFileItem);
	// ���ر���ͼƬ
	virtual IPropertyImageBase* LoadLocalImage(LPCWSTR pszLocalImgPath, bool bReLoad = false);
	virtual IPropertyImageBase* LoadImageFromHBITMAP(HBITMAP hBmp);
	virtual IPropertyImageBase* LoadImageFromHICON(HICON hIcon);
	// ������ڴ��ʽΪ DIB 32 λ�����ݡ�
	virtual IPropertyImageBase* LoadImage(int nWidth, int nHeight, BYTE* pScan0);

	// ɾ������ͼƬ
	virtual bool DeleteLocalImageBase(IPropertyImageBase *pPropImgBase);
	// ɾ��ͼƬ
	virtual bool DeleteImageBase(SKIN_FILE_ITEM* pSkinFileItem, IPropertyImageBase *pPropImgBase);

	// ȡ��ָ���������
	virtual IPropertyBaseMap* GetIPropertyBaseMap(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pPropGroupName, bool bIsCreate = false);

	// ������Զ���
	virtual void ReleaseSkinManagerPropetry();
	// ɾ��һ���ؼ�����������
	virtual bool DeleteControlPropetry(IControlBase* pCtrl);
	// ɾ������
	virtual bool DeletePropetryBaseProp(SKIN_FILE_ITEM* pSkinFileItem, IPropertyBase *pPropBase);
	// �ӿؼ����Զ�����ɾ��һ���ؼ���������ɾ���ؼ��Ľڵ㣬�ؼ��ľ������Բ�û��ɾ��
	virtual bool DeleteControlPropetryFromCtrlPropMap(IControlBase* pCtrl);

	// ��ָ��Ƥ�����ļ����ҵ�ָ���ļ�
	virtual bool FindUnZipFile(LPCWSTR pszSkinFilePath, LPCWSTR pFileName, BYTE **ppOutBuffer, int *pnFileLen, ZIP_FILE **ppFindZipFile = NULL);

//////////////////////////////////////////////////////////////////////////
	// ��ʼ��WindowƤ��
	virtual IPropertyWindow* PG_InitWindowSkin(LPCWSTR pszSkinPath, LPCWSTR pszWndName);
	// ����ָ��������
	virtual IPropertyBase* FindBasePropertyByPropId(SKIN_FILE_ITEM *pSkinFileItem, OBJECT_TYPE_ID propType, DWORD dwObjId);
	virtual IPropertyBase* FindBasePropertyByPropId(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pszPropType, DWORD dwObjId);
	// ����ָ��������
	virtual IPropertyBase* FindBasePropertyByPropName(SKIN_FILE_ITEM *pSkinFileItem, OBJECT_TYPE_ID propType, LPCWSTR pszPropName);
	virtual IPropertyBase* FindBasePropertyByPropName(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pszPropType, LPCWSTR pszPropName);
	// ������ʾ����������
	virtual void SetArea(AREA_TYPE areaType);
	// ����һ�����ԣ����������Է������
	virtual IPropertyBase* CreateEmptyBaseProp(SKIN_FILE_ITEM *pSkinFileItem, OBJECT_TYPE_ID propType, DWORD *pdwObjectId = NULL);

	// ɾ��һ������
	void ReleaseBaseProp(IPropertyBase *pCtrlProp);

	// ȡ����������Ĭ�ϵ�������Ϣ
	virtual IPropertyFontBase* GetDefaultFontBase(SKIN_FILE_ITEM* pSkinFileItem);

	// ����Ƥ����
	virtual bool BD_SaveSkinFile(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pszSkinDir, LPCWSTR pszSkinName, char *pszPassword);
	// ��ؼ��������һ���ؼ�
	virtual bool BD_AppendControlToVec(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pszCtrlType, IPropertyGroup* pCtrlPropGroup);
	// ���ÿ��Ա������Ч����
	virtual void BD_SetWindowPropetryActiveProp(IWindowBase *pWndBase, bool bActive);
	void BD_SetChildVecActiveMark(CHILD_CTRLS_VEC* pChildCtrlVec, bool bActive);
	void BD_SetGroupPropActiveMark(IPropertyGroup *pPropGroup, bool bActive);
	// ɾ��һ��ͼƬ
	virtual bool BD_DeleteZipImage(SKIN_FILE_ITEM* pSkinFileItem, ZIP_FILE* pZipImage);

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
	// ȡ��Ƥ���ļ�
	virtual SKIN_FILE_ITEM* GetSkinFileItem(LPCWSTR pszFilePath, bool bNew = false);
	// �ڴ��Ż���Ҫ��ֻ����Ҫ�õ�zip�е�ͼƬ��ʱ��ż���ͼƬ
	virtual bool ReadSkinFileItem(ZIP_FILE* pZipItem);
	// ����һ���յ�Ƥ���ļ�
	virtual SKIN_FILE_ITEM* CreateEmptySkinFileItem(LPCWSTR pszFilePath);
	// �ͷ�һ�����Ե��ڴ�ռ�
	virtual void ReleaseIPropertyBase(SKIN_FILE_ITEM* pSkinFileItem, IPropertyBase *pCtrlProp);

//////////////////////////////////////////////////////////////////////////
	// ����ؼ�Ƥ����Ĭ���ļ���
	virtual bool SaveControlDefaultSkin(LPCWSTR pszSaveDir, LPCWSTR pszCtrlName, IPropertyGroup* pPublicGroup, IPropertyGroup* pPrivateGroup);
	// ����Ĭ��Ƥ��
	virtual bool SetControlDefaultSkin(SKIN_FILE_ITEM* pSkinFileItem, IControlBase *pControl, LPCWSTR pszDefSkinDir);
//////////////////////////////////////////////////////////////////////////

protected:
	//////////////////////////////////////////////////////////////////////////
	// ��һ��Ƥ����ʱ����Ҫ��ȡƤ�������ļ�
	// �޸���������
	virtual bool BD_ModifyPropetryName(SKIN_FILE_ITEM* pSkinFileItem, IPropertyBase *pPropBase, LPCWSTR pszNewPropName);

	// ����ͼƬʹ�õ�zip�ļ�
	virtual SKIN_FILE_ITEM * GetLocalImageSkinFileItem();

//////////////////////////////////////////////////////////////////////////
	// �ڴ����
	virtual ZIP_FILE* MEM_CreateZipFile(SKIN_FILE_ITEM* pSkinFileItem, int nFileBufLen, BYTE byFileType, LPCWSTR pszFileName);
	virtual void MEM_DeleteZipFileByCom(SKIN_FILE_ITEM* pSkinFileItem, ZIP_FILE *pComZipFile);

private:
//////////////////////////////////////////////////////////////////////////
	// ���ҹ��
	IPropertyCursorBase* FindCursorBasePropetry(SKIN_FILE_ITEM* pSkinFileItem, int nCursorId);
	// ����һ�������ʰ
	bool AddCursorBasePropetry(SKIN_FILE_ITEM* pSkinFileItem, bool bSysCursor, int nCursorId);
	// ���ù�����Ե�����
	void SetCursorObjectName(IPropertyCursorBase *pCursorBase);

//////////////////////////////////////////////////////////////////////////
	// Layout.xml ���

	bool DeleteImageBaseProp(SKIN_FILE_ITEM* pSkinFileItem, IPropertyImageBase *pImgBaseProp);
	bool DeleteFontBaseProp(SKIN_FILE_ITEM* pSkinFileItem, IPropertyFontBase *pFontBaseProp);

	IPropertyImageBase* LoadImageFromHANDLE(HBITMAP hBmp, HICON hIcon);

	bool SaveControlDefaultSkin_ControlXml(LPCWSTR pszSaveDir, LPCWSTR pszCtrlName, IPropertyGroup* pPublicGroup, IPropertyGroup* pPrivateGroup);
	bool SaveControlDefaultSkin_ResourceXml(LPCWSTR pszSaveDir, LPCWSTR pszCtrlName, IPropertyGroup* pPublicGroup, IPropertyGroup* pPrivateGroup);
	bool SaveCtrlGroupProp_ResXml(xml_document &XmlStrObj, xml_node* pParentNode, IPropertyGroup *pPropGroup, LPCWSTR pszSaveDir);
	bool SaveCtrlGroupProp_CtrlXml(xml_document &XmlStrObj, xml_node* pParentNode, IPropertyGroup *pPropGroup);


	// �����ؼ��Զ���Ƥ����Resource.xml
	bool ReadCtrlDftSkinXml(SKIN_FILE_ITEM* pSkinFileItem, IControlBase *pControl, LPCWSTR pszDefSkinDir, SKIN_FILE_ITEM &DftSkinFileItem);
	bool SetControlDefaultSkinToCtrl(SKIN_FILE_ITEM &DftSkinFileItem, SKIN_FILE_ITEM* pCtrlSkinFileItem, IPropertyGroup* pCtrlPrivateGroup, IControlBase *pControl, LPCWSTR pszDefSkinDir);
	bool CopyPropetry(SKIN_FILE_ITEM &DftSkinFileItem, SKIN_FILE_ITEM* pCtrlSkinFileItem, IPropertyGroup* pFromGroup, IPropertyGroup* pCopyToGroup, IControlBase *pControl, LPCWSTR pszDefSkinDir);

private:
	// ����ͼƬ��map
	LOCAL_IMAGE_MAP m_LocalImgMap;

	// ����Ƥ�����ļ�������
	CSkinFileManager m_SkinFile;
};
