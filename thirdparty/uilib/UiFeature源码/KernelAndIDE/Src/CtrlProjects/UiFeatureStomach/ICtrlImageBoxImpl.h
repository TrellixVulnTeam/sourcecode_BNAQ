
#pragma once
#include "..\..\Inc\Control\ICtrlImageBox.h"

class ICtrlImageBoxImpl : public ICtrlImageBox
{
public:
	ICtrlImageBoxImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlImageBoxImpl();

	virtual IPropertyImageBase* GetBackgroundImage();
	// ���ñ���ͼ
	virtual bool SetBackgroundImage(LPCWSTR pszImagePath);
	virtual bool SetBackgroundImage(IPropertyImageBase* pNewImageBase);
	// ���ö�������
	virtual void SetImageAnimation(IMAGE_BOX_ANIMATION paType);
	virtual IMAGE_BOX_ANIMATION GetImageAnimation();

protected:
	// �����ؼ����ڴ��������Լ��Ŀؼ�����
	// bIsNewCtrl��trueʱ˵����Builder���ã��´���һ���ؼ�����Ҫ��ʼ�����Եĸ���Ĭ��ֵ
	// false��˵������Ƥ�����Ѿ���ʼ����ϣ����Դ�����ϵ�ʱ�򣬴�xml�ж�ȡ������ֵ�Ѿ���ֵ����ˣ������ٳ�ʼ��������xml�е�ֵ�ᱻ���
	virtual bool CreateControlPropetry(bool bIsNewCtrl);
	// ��ʼ���ؼ�
	virtual void OnCreate();
	// �ؼ���ʼ�����
	virtual void OnFinalCreate();
	// ���ٿؼ�
	virtual void OnDestroy();
	// ���ƿؼ�
	virtual void OnPaint(CDrawingBoard &DrawBoard);
	// ���ƿؼ��Ķ����������Ҫ����ˢ�½��棬����true�����򷵻�false
	// �˺����ɶ�ʱ��������ÿ100���봥��һ��
	virtual bool OnDrawAnimation();
	// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
	virtual LRESULT ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam);

private:
	IPropertyImage* m_pPropImage;
	IPropertyComboBox* m_pChangeImgAnimation;

	IPropertyImageBase* m_pOldImgBase;
	IPropertyImageBase* m_pNewImgBase;

	int m_nNewImgAlpha;
};
