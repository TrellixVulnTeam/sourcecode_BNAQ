#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_CHECK_BOX							(L"CheckBox")

// �����ؼ��򴰿ڷ��͵���Ϣ
enum CTRL_MSG_CHECK_BOX
{
	// CHECK_BOX��ϢBase������Ϣֵ���������ͣ�ֻ����Ϊ��Ϣֵ��Base
	CM_CHECK_BOX_BASE	= 0x10009000,
	// CHECK_BOX Down��Ϣ
	CM_CHECK_BOX_DOWN,
	// CHECK_BOX Up��Ϣ
	CM_CHECK_BOX_UP
};

class _declspec(novtable) ICtrlCheckBox : public ICtrlInterface
{
public:
	ICtrlCheckBox(IUiFeatureKernel *pUiKernel);
	// ����CheckBox����
	virtual void SetText(LPCWSTR pText, bool bRedraw) = 0;
	// ����ѡ������
	virtual void SetCheck(bool bCheck) = 0;
	// ȡ��ѡ������
	virtual bool GetCheck() = 0;
};
