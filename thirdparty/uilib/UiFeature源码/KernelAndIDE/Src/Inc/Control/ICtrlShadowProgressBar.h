
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_SHADOW_PROGRESS_BAR				(L"ShadowProgressBar")

class _declspec(novtable) ICtrlShadowProgressBar : public ICtrlInterface
{
public:
	ICtrlShadowProgressBar(IUiFeatureKernel *pUiKernel);
	// ���õ�ǰ���ȣ�ֵ��0-100
	virtual void SetProgressBarPos(int nPos, bool bRedraw = true) = 0;
	// ��ȡ��ǰֵ
	virtual int GetProgressBarPos() = 0;
	// ʹ�þ���ķ�ʽ���ƹ��������������Ƶ�ָ����dc��ָ������
	virtual bool MirrorDraw(CDrawingBoard &DrawBoard, RECT DstRect, int nPos) = 0;
};
