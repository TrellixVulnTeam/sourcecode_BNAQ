#pragma once
#include "..\..\Inc\CUiFeatureWindow.h"
#include "..\..\Inc\Control\ICtrlImageBox.h"
#include "..\..\Inc\Control\ICtrlShadowButton.h"
#include "..\..\Inc\Control\ICtrlLEDCtrl.h"

#define IDC_Timer                       101

class CUiFeatureTestWindow : public CUiFeatureWindow
{
public:
	CUiFeatureTestWindow();
	virtual ~CUiFeatureTestWindow();

	bool ShowUiFeatureTestWindow(DWORD dwMainThreadId);
	void UnInitialized();

	// �ؼ����͸����ڵ���Ϣ�ӿ�
	BEGIN_CTRL_COMMAND
	WIN32_WND_CTRL_COMMAND
		KERNEL_COMMAND_HANDLER(KCM_SYS_COMMAND_CLOSE, OnSysCommandClose)
	END_CTRL_COMMAND

	BEGIN_WNDPROC_MESSAGE
		WNDPROC_MESSAGE_HANDLER(WM_TIMER, OnTimer)
	END_WNDPROC_MESSAGE

protected:
	// WM_CREATE���Ի����ʼ��	
	virtual void OnCreate();

	virtual void OnKeyDown(int nVirtKey, int nFlag);

	LRESULT OnSysCommandClose(WPARAM wParam, LPARAM lParam);
	LRESULT OnTimer(WPARAM wParam, LPARAM lParam, BOOL bContinue);

private:
	DWORD m_dwMainThreadId;
	ICtrlLEDCtrl* m_pShowTime;
};
