
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_GRADUAL_LIGHT						(L"GradualLight")

class _declspec(novtable) ICtrlGradualLight : public ICtrlInterface
{
public:
	ICtrlGradualLight(IUiFeatureKernel *pUiKernel);
	virtual void Play() = 0;
	virtual void Stop(bool bIsKillTimer) = 0;
};
