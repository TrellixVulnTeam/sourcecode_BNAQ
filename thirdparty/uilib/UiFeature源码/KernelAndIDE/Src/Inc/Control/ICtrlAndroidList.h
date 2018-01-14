
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_ANDROID_LIST						(L"AndroidList")


// �����ؼ��򴰿ڷ��͵���Ϣ
enum CTRL_MSG_ANDROID_LIST
{
	CM_ANDROID_LIST_BASE				= 0x10027000,
	// �б����ݷ����仯
	CM_ANDROID_LIST_DATA_SET_CHANGED,
	// ListItem �����ӿؼ�������
	CM_ANDROID_LIST_L_BUTTON_DOWN,
	// ListItem �����ӿؼ������º�̧��
	CM_ANDROID_LIST_L_BUTTON_UP,
	// ListItem �����ӿؼ�item�����ѡ��
	CM_ANDROID_LIST_MOUSE_MOVE,
};


class _declspec(novtable) ICtrlAndroidList : public ICtrlInterface
{
public:
	ICtrlAndroidList(IUiFeatureKernel *pUiKernel);

	// ���� ListItem �е�һ���ӿؼ������ڳ�����ؼ��ĵط�
	virtual void Gone(IControlBase* pGoneCtrl) = 0;
	// ����/��ʾ ListItem �е�һ���ӿؼ����� gone �Ŀؼ�Ҳ������ʾ����������ռ��ԭ�����ڳ����Ŀռ�
	virtual void Visible(IControlBase* pCtrl, bool bVisible) = 0;
	// �� UiFeatureBuilder ����Ƴ����� ListItem ��ģ�壬������ʱ̬һ��Ҫ��ʾ���ٸ�
	virtual int GetTempletColumnCount() = 0;
	// �����б��Ƿ�Ϊ��
	virtual bool IsEmpty() = 0;
};
