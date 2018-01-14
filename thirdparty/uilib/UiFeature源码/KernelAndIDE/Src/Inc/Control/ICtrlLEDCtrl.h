#pragma once
#include "..\ICtrlInterface.h"	//�����ؼ��ӿ��ļ�

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_LEDCTRL							(L"LEDCtrl")

class _declspec(novtable) ICtrlLEDCtrl : public ICtrlInterface
{
public:
	ICtrlLEDCtrl(IUiFeatureKernel *pUiKernel);

	virtual void SetText(LPCWSTR pText, bool bRedraw) = 0;
	virtual void SetIndexMap(LPCWSTR pText) = 0;
	virtual SIZE GetAutoSize() = 0;

};
