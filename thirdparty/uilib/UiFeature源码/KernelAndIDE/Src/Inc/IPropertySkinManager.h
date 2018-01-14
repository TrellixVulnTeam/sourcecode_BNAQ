//////////////////////////////////////////////////////////////////////////
// ��ǰƤ�����д��������пؼ������Թ�����

#pragma once
#include "IPropertyBase.h"
#include "IPropertyWindow.h"
#include "IZipFile.h"
#include "IPropertyFontBase.h"
#include "IPropertyImageBase.h"
#include "IPropertyString.h"

class IControlBase;
class _declspec(novtable) IPropertySkinManager
{
public:
//////////////////////////////////////////////////////////////////////////
	// Ƥ�������
	// ȡ��Ƥ�����汾��
	virtual SKIN_VERSION GetSkinFileVersion(LPCWSTR pZipFilePath, int &nPasswordLen) = 0;
	// ��֤�û�Ƥ��������
	virtual bool ChekUserPassword(const char *pUserPassword, LPCWSTR pZipFilePath) = 0;

//////////////////////////////////////////////////////////////////////////
	// ���4��xml�ļ������Զ���
	virtual void ReleaseSkinManagerPropetry() = 0;
	// �ӿؼ����Զ�����ɾ��һ���ؼ���������ɾ���ؼ��Ľڵ㣬�ؼ��ľ������Բ�û��ɾ��
	virtual bool DeleteControlPropetryFromCtrlPropMap(IControlBase* pCtrl) = 0;
	// ɾ��һ���ؼ�����������
	virtual bool DeleteControlPropetry(IControlBase* pCtrl) = 0;
	// ɾ�������е�Base���ԣ���ImageBase��FontBase
	virtual bool DeletePropetryBaseProp(SKIN_FILE_ITEM* pSkinFileItem, IPropertyBase *pPropBase) = 0;
	// ��ʼ�������������
	virtual bool InitCursorBasePropetry(SKIN_FILE_ITEM* pSkinFileItem) = 0;

	// ���ر���ͼƬ��������·����ͼƬ�Ѿ����ع��ˣ�����ԭ�еģ�ʹ�� DeleteLocalImageBase ɾ��ͼƬ
	virtual IPropertyImageBase* LoadLocalImage(LPCWSTR pszLocalImgPath, bool bReLoad = false) = 0;
	// ���� HBITAMP ����ͼƬ���� DeleteLocalImageBase ɾ��ͼƬ
	virtual IPropertyImageBase* LoadImageFromHBITMAP(HBITMAP hBmp) = 0;
	// ���� HICON ����ͼƬ���� DeleteLocalImageBase ɾ��ͼƬ
	virtual IPropertyImageBase* LoadImageFromHICON(HICON hIcon) = 0;
	// ������ڴ��ʽΪ DIB 32 λ�����ݡ�
	virtual IPropertyImageBase* LoadImage(int nWidth, int nHeight, BYTE* pScan0) = 0;

	// ɾ������ͼƬ
	virtual bool DeleteLocalImageBase(IPropertyImageBase *pPropImgBase) = 0;
	// ɾ��ͼƬ
	virtual bool DeleteImageBase(SKIN_FILE_ITEM* pSkinFileItem, IPropertyImageBase *pPropImgBase) = 0;

	// ��ָ��Ƥ�����ļ����ҵ�ָ���ļ�
	virtual bool FindUnZipFile(LPCWSTR pszSkinFilePath, LPCWSTR pFileName, BYTE **ppOutBuffer, int *pnFileLen, ZIP_FILE **ppFindZipFile = NULL) = 0;

//////////////////////////////////////////////////////////////////////////
	// ��ʼ��WindowƤ��
	virtual IPropertyWindow* PG_InitWindowSkin(LPCWSTR pszSkinPath, LPCWSTR pszWndName) = 0;
	// ������ʾ����������
	virtual void SetArea(AREA_TYPE areaType) = 0;
	// ����һ�����ԣ����������Է������
	virtual IPropertyBase* CreateEmptyBaseProp(SKIN_FILE_ITEM *pSkinFileItem, OBJECT_TYPE_ID propType, DWORD *pdwObjectId = NULL) = 0;
	// ȡ����������Ĭ�ϵ�������Ϣ
	virtual IPropertyFontBase* GetDefaultFontBase(SKIN_FILE_ITEM* pSkinFileItem) = 0;

	// ����ָ��������
	virtual IPropertyBase* FindBasePropertyByPropId(SKIN_FILE_ITEM *pSkinFileItem, OBJECT_TYPE_ID propType, DWORD dwObjId) = 0;
	virtual IPropertyBase* FindBasePropertyByPropId(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pszPropType, DWORD dwObjId) = 0;
	// ����ָ��������
	virtual IPropertyBase* FindBasePropertyByPropName(SKIN_FILE_ITEM *pSkinFileItem, OBJECT_TYPE_ID propType, LPCWSTR pszPropName) = 0;
	virtual IPropertyBase* FindBasePropertyByPropName(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pszPropType, LPCWSTR pszPropName) = 0;

	// �ڴ��Ż���Ҫ��ֻ����Ҫ�õ�zip�е�ͼƬ��ʱ��ż���ͼƬ
	virtual bool ReadSkinFileItem(ZIP_FILE* pZipItem) = 0;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
	// ȡ��Ƥ���ļ������� bNew�������ǰƤ�����б��в����ڴ�Ƥ���ļ����Ƿ�ӱ��ض�ȡ��Ƥ���ļ�
	virtual SKIN_FILE_ITEM* GetSkinFileItem(LPCWSTR pszFilePath, bool bNew = false) = 0;
	// ����һ���յ�Ƥ���ļ�
	virtual SKIN_FILE_ITEM* CreateEmptySkinFileItem(LPCWSTR pszFilePath) = 0;

//////////////////////////////////////////////////////////////////////////
	// ����ؼ�Ƥ����Ĭ���ļ���
	virtual bool SaveControlDefaultSkin(LPCWSTR pszSaveDir, LPCWSTR pszCtrlName, IPropertyGroup* pPublicGroup, IPropertyGroup* pPrivateGroup) = 0;
	// ����Ĭ��Ƥ��
	virtual bool SetControlDefaultSkin(SKIN_FILE_ITEM* pSkinFileItem, IControlBase *pControl, LPCWSTR pszDefSkinDir) = 0;
//////////////////////////////////////////////////////////////////////////

	// ����Ƥ����
	virtual bool BD_SaveSkinFile(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pszSkinDir, LPCWSTR pszSkinName, char *pszPassword) = 0;

	// �޸���������
	virtual bool BD_ModifyPropetryName(SKIN_FILE_ITEM* pSkinFileItem, IPropertyBase *pPropBase, LPCWSTR pszNewPropName) = 0;
	// ɾ��һ��ͼƬ
	virtual bool BD_DeleteZipImage(SKIN_FILE_ITEM* pSkinFileItem, ZIP_FILE* pZipImage) = 0;

	// ȡ��ָ���������
	virtual IPropertyBaseMap* GetIPropertyBaseMap(SKIN_FILE_ITEM *pSkinFileItem, LPCWSTR pPropGroupName, bool bIsCreate = false) = 0;
	
	// ����ͼƬʹ�õ�zip�ļ�
	virtual SKIN_FILE_ITEM * GetLocalImageSkinFileItem() = 0;
	// �ͷ�һ�����Ե��ڴ�ռ�
	virtual void ReleaseIPropertyBase(SKIN_FILE_ITEM* pSkinFileItem, IPropertyBase *pCtrlProp) = 0;

//////////////////////////////////////////////////////////////////////////
	// �ڴ����
	virtual ZIP_FILE* MEM_CreateZipFile(SKIN_FILE_ITEM* pSkinFileItem, int nFileBufLen, BYTE byFileType, LPCWSTR pszFileName) = 0;
	virtual void MEM_DeleteZipFileByCom(SKIN_FILE_ITEM* pSkinFileItem, ZIP_FILE *pComZipFile) = 0;
};
