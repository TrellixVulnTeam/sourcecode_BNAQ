
#pragma once
#include "..\..\Inc\Control\ICtrlAndroidList.h"

class ICtrlAndroidListImpl : public ICtrlAndroidList
{
public:
	ICtrlAndroidListImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlAndroidListImpl();

	// ���� ListItem �е�һ���ӿؼ������ڳ�����ؼ��ĵط�
	virtual void Gone(IControlBase* pGoneCtrl);
	// ����/��ʾ ListItem �е�һ���ӿؼ����� gone �Ŀؼ�Ҳ������ʾ����������ռ��ԭ�����ڳ����Ŀռ�
	virtual void Visible(IControlBase* pCtrl, bool bVisible);
	// �� UiFeatureBuilder ����Ƴ����� ListItem ��ģ�壬������ʱ̬һ��Ҫ��ʾ���ٸ�
	virtual int GetTempletColumnCount();
	// �����б��Ƿ�Ϊ��
	virtual bool IsEmpty();

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
	// ��һ���ؼ������������ӿؼ���ʱ��ϵͳ�ᷢ�ʹ���������ӿؼ�����Ϣ
	virtual void OnCreateSubControl(bool bIsCreate);
};
