
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_MAC_DOCK_BAR						(L"MacDockBar")

class _declspec(novtable) ICtrlMacDockBar : public ICtrlInterface
{
public:
	ICtrlMacDockBar(IUiFeatureKernel *pUiKernel);
	virtual bool AppendItem(LPCWSTR pszLocalImg, bool bRedraw) = 0;
};
