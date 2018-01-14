
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_STRAIGHTLINE_FLY_IMAGE					(L"StraightLineFlyImage")

class _declspec(novtable) ICtrlStraightLineFlyImage : public ICtrlInterface
{
public:
	ICtrlStraightLineFlyImage(IUiFeatureKernel *pUiKernel);
	// ��ʼһ�����������ö�����ʼ�ͽ�����λ�ã�����ֵ�Ƕ�����һ��KEY
	virtual VOID* StartFly(RECT rctBegin, RECT rctEnd) = 0;
	// �õ�Ƥ���������õķ���λ��
	virtual void GetFlyPostion(RECT &rctBegin, RECT &rctEnd) = 0;
};
