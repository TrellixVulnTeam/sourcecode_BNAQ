
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_BASE_PANEL						(L"Panel")

class _declspec(novtable) ICtrl_XXXX_ : public ICtrlInterface
{
public:
	ICtrl_XXXX_(IUiFeatureKernel *pUiKernel);
};
