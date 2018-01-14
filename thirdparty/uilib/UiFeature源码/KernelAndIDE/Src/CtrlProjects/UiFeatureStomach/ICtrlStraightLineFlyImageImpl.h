
#pragma once
#include "..\..\Inc\Control\ICtrlStraightLineFlyImage.h"
#include "FlyWindowManager.h"

class ICtrlStraightLineFlyImageImpl : public ICtrlStraightLineFlyImage
{
public:
	ICtrlStraightLineFlyImageImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlStraightLineFlyImageImpl();

	// ��ʼһ�����������ö�����ʼ�ͽ�����λ�ã�����ֵ�Ƕ�����һ��KEY
	virtual VOID* StartFly(RECT rctBegin, RECT rctEnd);
	virtual void GetFlyPostion(RECT &rctBegin, RECT &rctEnd);

protected:
	// �����ؼ����ڴ��������Լ��Ŀؼ�����
	// bIsNewCtrl��trueʱ˵����Builder���ã��´���һ���ؼ�����Ҫ��ʼ�����Եĸ���Ĭ��ֵ
	// false��˵������Ƥ�����Ѿ���ʼ����ϣ����Դ�����ϵ�ʱ�򣬴�xml�ж�ȡ������ֵ�Ѿ���ֵ����ˣ������ٳ�ʼ��������xml�е�ֵ�ᱻ���
	virtual bool CreateControlPropetry(bool bIsNewCtrl);
	// ��ʼ���ؼ�
	virtual void OnCreate();
	// �ؼ���ʼ�����
	virtual void OnFinalCreate();
	// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
	virtual LRESULT ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam);
	// ���ٿؼ�
	virtual void OnDestroy();
	// ���ƿؼ�
	virtual void OnPaint(CDrawingBoard &DrawBoard);
	// ��ʱ��
	virtual void OnTimer(UINT nTimerId);

private:
	CFlyWindowManager m_FlyWindowMgr;

	// ������ʾ���ƶ�ͼƬ
	IPropertyImage* m_pPropFlyImage;
	IPropertyInt* m_pPropFlyAlpha;
	IPropertyInt* m_pPropFlyTime;

	// ���
	IPropertyInt* m_pPropBeginRctLeft;
	IPropertyInt* m_pPropBeginRctTop;
	IPropertyInt* m_pPropBeginWidth;
	IPropertyInt* m_pPropBeginHeight;

	// �ص�
	IPropertyInt* m_pPropEndRctLeft;
	IPropertyInt* m_pPropEndRctTop;
	IPropertyInt* m_pPropEndWidth;
	IPropertyInt* m_pPropEndHeight;
};
