
#pragma once
#include "..\ICtrlInterface.h"
#include "ICtrlShadowButton.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_WINDOW_TITLE_BAR						(L"WindowTitleBar")

// �ؼ��򴰿ڷ��͵���Ϣ
enum CTRL_MSG_WND_TITLEBAR
{
	CM_TITLEBAR_BASE	= 0x10008000,
	// ���ô��ڵ�RGN������Ҫ�����ڵ�rgn������ᵼ�´��ڱ������쳣
	// ���������� WS_CAPTION ���ԣ�����Ҫͨ������RGN������ϵͳ�Դ���RGN�����ԶԻ������Ҫ���������Ϣ
	// Ҳ����ֱ�����ÿؼ��� UseDefaultRgn ����Ϊtrue��ʹ�ÿؼ��ڲ��ṩ��Ĭ�Ͼ���rgn�������Ͳ���Ҫ���������Ϣ��
	CM_TITLEBAR_SET_WND_RGN,
	// Up��Ϣ˫���˱�����
	CM_TITLEBAR_DBCLICK,
	// �����˹رնԻ���ť
	CM_TITLEBAR_CLOSEBTN_CLICK,
	// ��������С����ť
	CM_TITLEBAR_MINIMIZEBTN_CLICK,
	// ��������󻯰�ť
	CM_TITLEBAR_MAXIMIZEBTN_CLICK,
	// �����˻�ԭ��ť
	CM_TITLEBAR_RESTOREBTN_CLICK,
	// ���ڽ������
	CM_TITLEBAR_WILL_MAXIMIZE,
	// ���ڽ��ỹԭ
	CM_TITLEBAR_WILL_RESTOREBTN,
};

class _declspec(novtable) ICtrlWindowTitleBar : public ICtrlInterface
{
public:
	ICtrlWindowTitleBar(IUiFeatureKernel *pUiKernel);
	virtual ICtrlShadowButton* GetMinimizeButton() = 0;
	virtual ICtrlShadowButton* GetMaximizeButton() = 0;
	virtual ICtrlShadowButton* GetRestoreButton() = 0;
	virtual ICtrlShadowButton* GetClostButton() = 0;
	virtual bool UseDefaultRgn() = 0;
};
