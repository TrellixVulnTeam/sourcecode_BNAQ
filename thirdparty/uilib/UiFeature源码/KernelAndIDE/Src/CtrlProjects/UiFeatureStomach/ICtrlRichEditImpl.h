
#pragma once
#include "..\..\Inc\Control\ICtrlRichEdit.h"
#include "RichEdit/IUiFeatureTextHost.h"

class ICtrlRichEditImpl : public ICtrlRichEdit, public CHostCallBack
{
public:
	ICtrlRichEditImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlRichEditImpl();

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
	// �ƶ������ÿؼ�λ��
	virtual void OnSize();
	// �ؼ�ȡ�ý��㣬ͨ��Tab����ת������ؼ�
	virtual void OnSetFocus();
	// �ؼ�ʧȥ����
	virtual void OnKillFocus();
	// �ؼ���Ҫ�����һЩ�Զ������Ϣ����Ϣ�����ϻ��ɶԻ�����������ؼ�����
	virtual int OnCtrlNotify(int nMsgId, WPARAM wParam, LPARAM lParam);

	//@cmember Notify host of events
	virtual HRESULT TxNotify(DWORD iNotify, void *pv);

protected:
	IUiFeatureTextHost* m_pTextHost;
};
