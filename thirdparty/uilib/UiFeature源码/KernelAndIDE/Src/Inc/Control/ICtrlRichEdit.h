
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_RICH_EDIT						(L"RichEdit")

class _declspec(novtable) ICtrlRichEdit : public ICtrlInterface
{
public:
	ICtrlRichEdit(IUiFeatureKernel *pUiKernel);
};
