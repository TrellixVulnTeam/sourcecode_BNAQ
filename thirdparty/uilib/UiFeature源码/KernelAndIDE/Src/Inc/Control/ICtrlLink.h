
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_LINK							(L"Link")

// �����ؼ��򴰿ڷ��͵���Ϣ
enum CTRL_MSG_LINK
{
	// LINK_LABLE��ϢBase������Ϣֵ���������ͣ�ֻ����Ϊ������Ϣֵ��Base
	CM_LINK_BASE	= 0x10004000,
	// LINK_LABLE Down��Ϣ
	CM_LINK_DOWN,
	// LINK_LABLE Up��Ϣ
	CM_LINK_UP
};

class _declspec(novtable) ICtrlLink : public ICtrlInterface
{
public:
	ICtrlLink(IUiFeatureKernel *pUiKernel);
	// ����Link����
	virtual void SetLinkText(LPCWSTR pText, bool bRedraw) = 0;
	// ����Link���ӵ�ַURL
	virtual void SetLinkUrl(LPCWSTR pUrl) = 0;
	// ȡ��Link���ӵ�ַURL
	virtual LPCWSTR GetLinkUrl() = 0;
};
