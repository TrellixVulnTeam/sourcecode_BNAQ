
#pragma once

// �� UiFeatureBuilder ���ܹ��༭�����Ե�����
enum OBJECT_TYPE_ID 
{
	// �Ƿ�����ID
	OTID_NONE	= 0,
	// bool����
	OTID_BOOL	= 1,
	// ��ɫ����
	OTID_COLOR,
	// ��ɫ���Ե��ӽڵ㣬�洢�˾������ɫ��Ϣ
	OTID_COLOR_BASE,
	// ����������
	OTID_COMBOBOX,
	// �����������
	OTID_CURSOR,
	// ����������Ե��ӽڵ㣬�洢�˾�������������Ϣ
	OTID_CURSOR_BASE,
	// ��������
	OTID_FONT,
	// �������Ե��ӽڵ㣬�洢�˾����������Ϣ
	OTID_FONT_BASE,
	// ͼƬ����
	OTID_IMAGE,
	// ͼƬ���Ե��ӽڵ㣬�洢�˾����ͼƬ��Ϣ
	OTID_IMAGE_BASE,
	// ��������
	OTID_INT,
	// �ַ�������
	OTID_STRING,
	// ���������ԣ����¿��Դ洢һ������
	OTID_GROUP,
	// �ؼ������Խ��
	OTID_CONTROL,
	// ���ڵ����Խ��
	OTID_WINDOW,
	// ���Ե����һ��ö��ֵ�����ڼ���
	OTID_LAST
};

#define PROP_TYPE_BOOL_NAME						"bool"
#define PROP_TYPE_COLOR_NAME					"color"
#define PROP_TYPE_COLOR_BASE_NAME				"colorbase"
#define PROP_TYPE_COMBOBOX_NAME					"combobox"
#define PROP_TYPE_CURSOR_NAME					"cursor"
#define PROP_TYPE_CURSOR_BASE_NAME				"cursorbase"
#define PROP_TYPE_FONT_NAME						"font"
#define PROP_TYPE_FONT_BASE_NAME				"fontbase"
#define PROP_TYPE_IMAGE_NAME					"image"
#define PROP_TYPE_IMAGE_BASE_NAME				"imagebase"
#define PROP_TYPE_INT_NAME						"int"
#define PROP_TYPE_STRING_NAME					"string"
#define PROP_TYPE_GROUP_NAME					"group"
#define PROP_TYPE_CONTROL_NAME					"control"
#define PROP_TYPE_WINDOW_NAME					"window"

#define ERROR_OBJECT_ID							(0)

class IUiFeatureKernel;
class IFeatureObject
{
public:
	IFeatureObject(IUiFeatureKernel *pUiKernel);
	virtual ~IFeatureObject();

	DWORD GetObjectId();
	void SetObjectId(DWORD dwObjId);

	const WCHAR* GetObjectType();
	void SetObjectType(const WCHAR* pszObjType);
	OBJECT_TYPE_ID GetObjectTypeId();

	const WCHAR* GetObjectName();
	void SetObjectName(const WCHAR* pszObjName);

	virtual void SetActivePropetry(bool bIsActive);
	virtual bool GetActivePropetry();

	// ���ؼ�/������
	IFeatureObject* GetOwnerObject();
	void SetOwnerObject(IFeatureObject* pOwnerObj);

	// ���� ObjectName���������޸�ObjectName
	void LockName(bool bLock);
	bool IsLockName();

	void SetUiKernel(IUiFeatureKernel* pUiKernel);
	IUiFeatureKernel *GetUiKernel();

protected:
	IUiFeatureKernel *m_pUiKernel;
	// �Ƿ�Ϊ��Ч���ԣ���Builder��������ʱ�ж�ʹ�á�
	bool m_bIsActiveProp;

private:
	bool m_bIsLockName;
	// ID��Ψһ��ʶ��id
	DWORD m_dwObjId;
	// ����
	WCHAR *m_pszObjType;
	// ����
	WCHAR *m_pszObjName;
	IFeatureObject *m_pOwnerObj;
};
