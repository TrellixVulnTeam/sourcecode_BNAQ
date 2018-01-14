
#pragma once
#include "..\..\Inc\Control\ICtrlFocus.h"

class ICtrlFocusImpl : public ICtrlFocus
{
public:
	ICtrlFocusImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlFocusImpl();

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
	// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
	virtual LRESULT ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam);
	// ��һ���ؼ���TabOrder���Ա�������֮��ͬʱ�˿ؼ��õ����㣬���ڻὫ����Ϣ
	// ͨ������������͸�ע������Ҫȡ�ý�����Ϣ�Ŀؼ�
	virtual void OnContrlFocusChange(IControlBase* pFocusCtrl);
	virtual void OnMoveAnimationDraw();

private:
	bool IsUseAnimation();
	bool SetMoveRect(int nAnimationTime, int nPropMoveTime);
	void DoAnimation(CDrawingImage &WndMemDc, HDC &hWndDc, BLENDFUNCTION &Blend);

private:
	RECT m_BeginRct;
	RECT m_EndRct;
	RECT m_MoveRct;
	bool m_bIsInAnimation;

	IPropertyInt* m_pPropFrameSpace;
	IControlBase* m_pFocusCtrl;
	IPropertyImage *m_pPropFrameImage;
	IPropertyBool* m_pPropUseAnimation;
	IPropertyInt* m_pPropAnimationTime;
};
