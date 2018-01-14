
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_BASE_PANEL						(L"Panel")

// �ؼ��򴰿ڷ��͵���Ϣ
enum CTRL_MSG_PANEL
{
	// ��ϢBase������Ϣֵ���������ͣ�ֻ����Ϊ�ؼ���Ϣֵ��Base
	CM_PANEL_BASE	= 0x10001000,
	// Down��Ϣ
	CM_PANEL_DOWN,
	// Up��Ϣ
	CM_PANEL_UP,
	// ���� 
	CM_PANEL_ENTER,
	// �뿪
	CM_PANEL_LEAVE,
	// ˫��
	CM_PANEL_DBCLICK,
	// Button �Ҽ�������Ϣ
	CM_PANEL_R_BTN_DOWN
};


// �滻ͼƬ�Ķ�������
enum PANEL_ANIMATION
{
	// �޶���
	PA_NONE		= 0,
	// ��������
	PA_JYJX
};

class _declspec(novtable) ICtrlPanel : public ICtrlInterface
{
public:
	ICtrlPanel(IUiFeatureKernel *pUiKernel);
	// ���ñ���ͼ
	virtual bool SetBackgroundImage(LPCWSTR pszImagePath, bool bReload) = 0;
	// ���ö�������
	virtual void SetImageAnimation(PANEL_ANIMATION paType) = 0;
	virtual PANEL_ANIMATION GetImageAnimation() = 0;
	// �ظ���Ƥ�����е�ͼƬ
	virtual void SetToDefault(bool bRedraw, bool bDeleteOld = true) = 0;
	// �Ƿ���ʾ����ָ�뿪��
	virtual void SetIsShowCursor(bool bIsShow) = 0;
	// ���ñ���ͼ
	virtual bool SetBackgroundImage(HBITMAP hbmp, bool bReload) = 0;
	// get����ͼ
	virtual IPropertyImageBase* GetBackgroundImage() = 0;
	// ���ñ���ͼ
	virtual bool SetBackgroundImage(IPropertyImageBase* pNewImageBase) = 0;
	// ���ùؼ��֣�������������ʱ��������
	virtual void SetKey(LPCWSTR key) = 0;
	// getkey
	virtual LPCWSTR GetKey() = 0;
};
