
#pragma once
#include "..\..\Inc\Control\ICtrlWindowTitleBar.h"
#include "..\..\Inc\Control\ICtrlShadowButton.h"
#include "..\..\Inc\IPropertyBool.h"

class ICtrlWindowTitleBarImpl : public ICtrlWindowTitleBar, public IControlMessage
{
public:
	ICtrlWindowTitleBarImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlWindowTitleBarImpl();

	virtual ICtrlShadowButton* GetMinimizeButton();
	virtual ICtrlShadowButton* GetMaximizeButton();
	virtual ICtrlShadowButton* GetRestoreButton();
	virtual ICtrlShadowButton* GetClostButton();
	virtual bool UseDefaultRgn();

	BEGIN_CTRL_COMMAND
		CTRL_COMMAND_HANDLER(m_pMinimizeBtn, CM_BUTTON_UP, OnMinimizeBtnClick)
		CTRL_COMMAND_HANDLER(m_pMaximizeBtn, CM_BUTTON_UP, OnMaximizeBtnClick)
		CTRL_COMMAND_HANDLER(m_pRestoreBtn, CM_BUTTON_UP, OnRestoreBtnClick)
		CTRL_COMMAND_HANDLER(m_pClostBtn, CM_BUTTON_UP, OnClostBtnClick)
	END_CTRL_COMMAND

	BEGIN_CTRL_NOTIFY
		// ��������Զ�����ϢĿ����Ϊ��֪ͨ���ڿ�������rgn������
		CTRL_NOTIFY_HANDLER(UI_FEATURE_KERNEL_MSG, OnSetWindowRgn)
		// ���������ϢĿ����Ϊ��������󻯡���ԭ��ť��״̬
		CTRL_NOTIFY_HANDLER(WM_WINDOWPOSCHANGED, OnWindowPosChanged)
		CTRL_NOTIFY_HANDLER(WM_SIZE, OnWindowSize)
	END_CTRL_NOTIFY

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
	// ����Ƿ������˿ؼ�ָ����RGN����Ĭ�Ϸ���true�������ؼ�����RGN����
	virtual bool OnCheckMouseInRgn(POINT pt, INT nMouseMsgId);
	// ������˫��
	virtual void OnLButtonDbClick(POINT pt);
	// ��һ���ؼ������������ӿؼ���ʱ��ϵͳ�ᷢ�ʹ���������ӿؼ�����Ϣ
	virtual void OnCreateSubControl(bool bIsCreate);
	// ����ӿڻ��������Ի����ʼ����ɵ�ʱ�����
	// �ؼ�ͨ����������ӿڣ�����������ӿں�����ͨ�������ؼ�������ȡ�õ�ǰ�Ի�����������ؼ���
	virtual void OnWindowFinalCreate();
	// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
	virtual LRESULT ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam);
	// pCloneCtrl �����տ�¡�����Ŀؼ��������������Ϣ��Ӧ�������ٿ�¡һЩ�ؼ�˽�е�����
	virtual void OnAfterClone(IControlBase* pCloneCtrl, WPARAM lParam);

	LRESULT OnMinimizeBtnClick(WPARAM wParam, LPARAM lParam);
	LRESULT OnMaximizeBtnClick(WPARAM wParam, LPARAM lParam);
	LRESULT OnRestoreBtnClick(WPARAM wParam, LPARAM lParam);
	LRESULT OnClostBtnClick(WPARAM wParam, LPARAM lParam);

	int OnSetWindowRgn(WPARAM wParam, LPARAM lParam);
	int OnWindowPosChanged(WPARAM wParam, LPARAM lParam);
	int OnWindowSize(WPARAM wParam, LPARAM lParam);

private:
	// ����Ƿ��������ӿؼ���Χ��
	BOOL PointInSubCtrl(POINT pt, IControlBase* pCtrlBase);
	bool HaveMaximizeButton();
	bool HaveMinimizeButton();
	// �Ƿ�ΪWin7�Ժ�Ĳ���ϵͳ
	bool IsWin7Later();
	void SetDefaultWindowRgn();
	void GetMaxWndRgnOffset(int &nCxOffset, int &nCyOffset);

private:
	ICtrlShadowButton* m_pMinimizeBtn;
	ICtrlShadowButton* m_pMaximizeBtn;
	ICtrlShadowButton* m_pRestoreBtn;
	ICtrlShadowButton* m_pClostBtn;
	IControlBase* m_pWndBasePanelCtrl;

	IPropertyBool* m_pPropNoMinimizeBtn;
	IPropertyBool* m_pPropNoMaximizeBtn;
	IPropertyString* m_pPropWndBasePanelName;
	IPropertyBool* m_pPropSetDftRgn;

	bool m_bOldFullScreenStyle;
};
