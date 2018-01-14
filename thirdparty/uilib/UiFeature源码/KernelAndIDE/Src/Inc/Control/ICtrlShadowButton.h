
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_SHADOW_BUTTON						(L"ShadowButton")

// �����ؼ��򴰿ڷ��͵���Ϣ
enum CTRL_MSG_BUTTON
{
	// Button��ϢBase������Ϣֵ���������ͣ�ֻ����Ϊ�ؼ���Ϣֵ��Base
	CM_BUTTON_BASE	= 0x10002000,
	// Button Down��Ϣ
	CM_BUTTON_DOWN,
	// Button Up��Ϣ
	CM_BUTTON_UP,
	// ���� Button 
	CM_BUTTON_ENTER,
	// �뿪 Button
	CM_BUTTON_LEAVE,
	// Button �Ҽ�������Ϣ
	CM_BUTTON_R_BTN_DOWN
};

class _declspec(novtable) ICtrlShadowButton : public ICtrlInterface
{
public:
	ICtrlShadowButton(IUiFeatureKernel *pUiKernel);
	// ����Button����
	virtual	void SetButtonText(LPCWSTR pszText) = 0;
	// ��ȡButton����
	virtual	LPCWSTR GetButtonText() = 0;

	// check button ģʽ��
	virtual void SetCheck(bool bIsCheck, bool bRedraw) = 0;
	virtual bool IsCheck() = 0;
	virtual IControlBase* GetCheckPanel() = 0;
};
