#pragma once
#include "..\..\Inc\CUiFeatureWindow.h"
#include "..\..\Inc\Control\ICtrlImageBox.h"
#include "..\..\Inc\Control\ICtrlShadowButton.h"
#include "..\..\Inc\Control\ICtrlWindowTitleBar.h"

class CUiFeatureTestWindow : public CUiFeatureWindow
{
public:
	CUiFeatureTestWindow();
	virtual ~CUiFeatureTestWindow();

	bool ShowUiFeatureTestWindow(DWORD dwMainThreadId);
	void UnInitialized();

	// 控件发送给窗口的消息接口
	BEGIN_CTRL_COMMAND
	WIN32_WND_CTRL_COMMAND
		CTRL_COMMAND_HANDLER(m_pCloneBtn, CM_BUTTON_UP, OnCloneBtn)
		KERNEL_COMMAND_HANDLER(KCM_SYS_COMMAND_CLOSE, OnSysCommandClose)
	END_CTRL_COMMAND

	BEGIN_WNDPROC_MESSAGE
	END_WNDPROC_MESSAGE

protected:
	// WM_CREATE：对话框初始化	
	virtual void OnCreate();

	virtual void OnKeyDown(int nVirtKey, int nFlag);

	LRESULT OnCloneBtn(WPARAM wParam, LPARAM lParam);
	LRESULT OnSysCommandClose(WPARAM wParam, LPARAM lParam);

private:
	DWORD m_dwMainThreadId;
	ICtrlShadowButton* m_pCloneBtn;
	ICtrlWindowTitleBar* m_pTitleBar;
	int m_nAddHeight;
};
