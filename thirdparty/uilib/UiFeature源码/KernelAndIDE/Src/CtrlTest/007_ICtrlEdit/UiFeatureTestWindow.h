#pragma once
#include "..\..\Inc\CUiFeatureWindow.h"
#include "..\..\Inc\Control\ICtrlImageBox.h"
#include "..\..\Inc\Control\ICtrlShadowButton.h"
#include "..\..\Inc\Control\ICtrlEdit.h"

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
		CTRL_COMMAND_HANDLER(m_pShowDirBtn, CM_BUTTON_UP, OnDirBtnClick)
		KERNEL_COMMAND_HANDLER(KCM_SYS_COMMAND_CLOSE, OnSysCommandClose)
	END_CTRL_COMMAND

protected:
	// 本窗口的消息处理函数
	virtual LRESULT WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// WM_CREATE：对话框初始化	
	virtual void OnCreate();

	virtual void OnKeyDown(int nVirtKey, int nFlag);

	LRESULT OnDirBtnClick(WPARAM wParam, LPARAM lParam);
	LRESULT OnSysCommandClose(WPARAM wParam, LPARAM lParam);

private:
	CStringW OnOpenDir();

private:
	DWORD m_dwMainThreadId;
	ICtrlShadowButton* m_pShowDirBtn;
	ICtrlEdit* m_pDirEdit;
};
