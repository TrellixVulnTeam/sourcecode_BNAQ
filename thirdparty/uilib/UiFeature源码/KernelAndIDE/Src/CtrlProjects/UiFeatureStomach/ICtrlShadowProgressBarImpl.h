
#pragma once
#include "..\..\Inc\Control\ICtrlShadowProgressBar.h"

// ����������
enum PROGRESS_BAR_TYPE
{
	// ˮƽ
	PBT_H = 0,
	// ��ֱ
	PBT_V,
};

class ICtrlShadowProgressBarImpl : public ICtrlShadowProgressBar, public IControlMessage
{
public:
	ICtrlShadowProgressBarImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlShadowProgressBarImpl();

	// ʹ�þ���ķ�ʽ���ƹ��������������Ƶ�ָ����dc��ָ������
	virtual bool MirrorDraw(CDrawingBoard &DrawBoard, RECT DstRect, int nPos);

	// ���õ�ǰ���ȣ�ֵ��0-100
	virtual void SetProgressBarPos(int nPos, bool bRedraw = true);

	virtual int GetProgressBarPos();

protected:
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam);

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

	// ��ʱ��
	virtual void OnTimer(UINT nTimerId);

	// �ƶ������ÿؼ�λ��
	virtual void OnSize();
	// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
	virtual LRESULT ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam);

	// �ɼ�����
	void SetVisible(bool bVisible);

	bool IsVisible();

	virtual void SetRectInOwner(RECT ctrlRectInOwner);

private:
	IPropertyComboBox* m_pPropProgressType;
	// �м���ʾ����������
	IPropertyFont* m_pPropFont;

	// ����ͼƬ
	IPropertyImage* m_pPropBkImg;
	// ���ڽ������ϵ�����ͼƬ
	IPropertyImage* m_pPropMaskImg;
	// �������߽��ȵ�ͼƬ
	IPropertyImage* m_pPropProgressImg;

	IPropertyGroup* m_pPropSpaceGroup;
	// ��������ʼ�߽��Ⱦ���ؼ�����ƫ��
	IPropertyInt* m_pPropLeftSpace;
	// ��������ʼ�߽��Ⱦ���ؼ��Ҳ��ƫ��
	IPropertyInt* m_pPropRightSpace;
	// ��������ʼ�߽��Ⱦ���ؼ��Ϸ���ƫ��
	IPropertyInt* m_pPropTopSpace;
	// ��������ʼ�߽��Ⱦ���ؼ��·���ƫ��
	IPropertyInt* m_pPropBottomSpace;
	// �ɼ�
	bool m_bIsVisible;
	// rect
	RECT m_CtrlRectInOwner;
	// ��ǰλ��
	int m_nCurPos;
};
