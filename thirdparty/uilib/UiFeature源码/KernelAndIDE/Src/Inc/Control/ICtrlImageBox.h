
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_IMAGE_BOX						(L"ImageBox")

// �滻ͼƬ��ʱ��Ķ���
enum IMAGE_BOX_ANIMATION
{
	// �޶���
	IBA_NONE		= 0,
	// ��������
	IBA_JYJX
};

class _declspec(novtable) ICtrlImageBox : public ICtrlInterface
{
public:
	ICtrlImageBox(IUiFeatureKernel *pUiKernel);
	virtual IPropertyImageBase* GetBackgroundImage() = 0;
	// ���ñ���ͼ
	virtual bool SetBackgroundImage(LPCWSTR pszImagePath) = 0;
	virtual bool SetBackgroundImage(IPropertyImageBase* pNewImageBase) = 0;
	// ���ö�������
	virtual void SetImageAnimation(IMAGE_BOX_ANIMATION paType) = 0;
	// ȡ�õ�ǰ��ͼ�Ķ���
	virtual IMAGE_BOX_ANIMATION GetImageAnimation() = 0;
};
