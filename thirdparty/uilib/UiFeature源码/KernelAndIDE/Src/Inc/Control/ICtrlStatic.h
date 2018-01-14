
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_STATIC						(L"Static")

class _declspec(novtable) ICtrlStatic : public ICtrlInterface
{
public:
	ICtrlStatic(IUiFeatureKernel *pUiKernel);
	// ���ÿؼ����ı�
	virtual bool SetText(LPCWSTR pszText) = 0;
	virtual LPCWSTR GetText() = 0;
};
