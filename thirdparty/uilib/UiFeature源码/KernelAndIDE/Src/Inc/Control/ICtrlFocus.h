
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_FOCUS_CTRL						(L"FocusControl")

class _declspec(novtable) ICtrlFocus : public ICtrlInterface
{
public:
	ICtrlFocus(IUiFeatureKernel *pUiKernel);
};
