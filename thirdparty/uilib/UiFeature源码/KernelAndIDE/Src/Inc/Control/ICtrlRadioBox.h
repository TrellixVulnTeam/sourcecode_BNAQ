#pragma once
#include "..\ICtrlInterface.h"	//�����ؼ��ӿ��ļ�

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_RADIO_BOX							(L"RadioBox")

enum CTRL_MSG_RADIO_BOX
{
	// RADIO_BOX��ϢBase������Ϣֵ���������ͣ�ֻ����Ϊ��Ϣֵ��Base
	CM_RADIO_BOX_BASE	= 0x20009000,
	// RADIO_BOX Down��Ϣ
	CM_RADIO_BOX_DOWN,
	// RADIO_BOX Up��Ϣ
	CM_RADIO_BOX_UP
};


class _declspec(novtable) ICtrlRadioBox : public ICtrlInterface
{
public:
	ICtrlRadioBox(IUiFeatureKernel *pUiKernel);

	virtual void SetText(LPCWSTR pText, bool bRedraw) = 0;

	// ����ѡ������
	virtual void SetCheck(bool bCheck) = 0;

	// ȡ��ѡ������
	virtual bool GetCheck() = 0;

	//���÷���ID
	virtual void SetGroupID(int nGroupId);

	//��ȡ����ID
	virtual int GetGroupID();

};