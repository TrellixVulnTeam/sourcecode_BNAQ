
#pragma once
#include "IFeatureObject.h"
#include "IPropertySkinManager.h"
#include "IPropertyImageBase.h"
#include "IPropertyBase.h"
#include "IWindowBase.h"

// ���ԡ�����������󳤶�
#ifndef STATIC_LEN
#define STATIC_LEN							(33)
#endif

// ��output�������debug��Ϣ����ʹ�ú� DEBUG_INFO �����
void DebugInfoOutput(char *pszFormat, ...);
#ifndef _DEBUG
#define DEBUG_INFO
#else
#define DEBUG_INFO				DebugInfoOutput
#endif

// ���ݵ�ǰ���е�exe�ľ���Ŀ¼�����ϲ���Ŀ¼���õ�������·��
const char* PathHelper(char *pszFileName);
const WCHAR* PathHelperW(LPCWSTR pszFileName);
// �������������ַ����õ��������͵�IDֵ
OBJECT_TYPE_ID PropStringToType(const WCHAR* strPropType);
// ������������IDֵ�õ����������ַ���
const WCHAR* PropTypeToString(OBJECT_TYPE_ID propType);
// ����һ�����ԣ������������� group ���Ѿ����ˣ��ͷ���������ԣ����û�о��½�һ������
IPropertyBase* CreateResourcePropetry(SKIN_FILE_ITEM* pSkinFileItem, IFeatureObject *pOwnerObj, IPropertySkinManager* pSkinPropMgr,
									  IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo, bool bNotExistCreate);
// �ж�ָ���ļ��Ƿ����
bool FileExists(const char *pszFilePath);
bool FileExistsW(LPCWSTR pszFilePath);
// ��һ��xml�ڵ����һ��int����
void AddIntAttrToNode(xml_node* pNode, const WCHAR* pszAttrName, int nInt);
void AddStringAttrToNode(xml_node* pNode, const WCHAR* pszAttrName, const WCHAR* pszData);
// ��һ���������в�����Ϊ "@Object_Name" ������
IPropertyString* FindObjectNameProperty(IPropertyGroup *pGroupProp);

void RectScreenToClient(HWND hWnd, RECT& rct);
void RectClientToScreen(HWND hWnd, RECT& rct);
void InitPropImageBase(IMAGE_BASE_PROP *pImgBaseProp);

// ������Ե��������ĸ��ؼ�/���ڵ���Ϣ
void ClearGroupPropertyOwner(IPropertyGroup *pPropGroup);

// ͼƬ�ٱߣ�MarkDrawBoard ͼƬ�к�ɫ���ֽ���� DstDrawBoard �пٳ�
bool ClipImageWithBlack(CDrawingBoard &MarkDrawBoard, CDrawingBoard &DstDrawBoard);
// ��ԭͼ�е� Alpha ֵ���Ƶ�Ŀ��λͼ�е� Alpha ֵ
bool ClipImageWithAlpha(CDrawingBoard &MarkDrawBoard, CDrawingBoard &DstDrawBoard);
// ������nPixelCtns �ܹ�������ֵ
bool ClipImageWithAlpha(BYTE* pBitsSrc, BYTE* pBitsDes, int nPixelCtns);
// ��ȡ��ͨ��Text��С�ļ�
bool ReadTextFile(LPCWSTR pszFilePath, string &strOutData);
// �Ƿ�Ϊͬһ���͵�����
bool IsSameTypePropetry(IPropertyBase* pPropBase, IPropertyBase* pComPropBase);
// ��xml��ȡ��ָ��node��ָ��attr
const WCHAR * XmlGetAttrValue(xml_node* pXmlNode, const WCHAR* pwszAttrName);
// �������ݵ��ļ�
bool SaveDataToFile(LPCWSTR pszFilePath, BYTE *pData, int nDataLen);
// ȡ�� GUID
const WCHAR * GetGuidString();
// ȡ�ÿؼ�ָ��
IControlBase* GetSubControlByName(char *pszCtrlName, CHILD_CTRLS_VEC &ChildCtrlsVec);
IControlBase* GetSubControlByName(LPCWSTR pszCtrlName, CHILD_CTRLS_VEC &ChildCtrlsVec);
IControlBase* GetSubControlByName(WCHAR *pszCtrlName, CHILD_CTRLS_VEC &ChildCtrlsVec);
bool GetControlByNameFromVec(CHILD_CTRLS_VEC *pCtrlVec, LPCWSTR pszCtrlName, IControlBase **ppCtrl);
// ȡ�ÿؼ�ָ��
IControlBase* GetSubControlByObjectId(DWORD dwObjId, CHILD_CTRLS_VEC &ChildCtrlsVec);
bool GetControlByObjectIdFromVec(CHILD_CTRLS_VEC *pCtrlVec, DWORD dwObjId, IControlBase **ppCtrl);
