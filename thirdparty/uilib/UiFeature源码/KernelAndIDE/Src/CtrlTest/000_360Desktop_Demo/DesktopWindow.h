#pragma once
#include "..\..\Inc\CUiFeatureWindow.h"
#include "..\..\Inc\Control\ICtrlImageBox.h"
#include "..\..\Inc\Control\ICtrlShadowButton.h"
#include "DockBarWindow.h"
#include "ToolBarWindow.h"
#include "360DesktopDemoDefs.h"

class CDesktopWindow : public CUiFeatureWindow
{
public:
	CDesktopWindow();
	virtual ~CDesktopWindow();

	bool ShowDesktopWindow(DWORD dwMainThreadId);
	void UnInitialized();

//////////////////////////////////////////////////////////////////////////
	// �ؼ����͸����ڵ���Ϣ�ӿ�
	BEGIN_CTRL_COMMAND
	WIN32_WND_CTRL_COMMAND
	//
	END_CTRL_COMMAND
//////////////////////////////////////////////////////////////////////////
	// �����ڵ���Ϣ������
	BEGIN_WND_PROC
		WND_MSG_HANDLER(WM_UIF_CRATE_SUB_WINDOW, OnCreateSubWnd)
	END_WND_PROC(CUiFeatureWindow)
//////////////////////////////////////////////////////////////////////////

protected:
	// WM_CREATE���Ի����ʼ��	
	virtual void OnCreate();
	virtual void OnKeyDown(int nVirtKey, int nFlag);

	int OnCreateSubWnd(WPARAM wParam, LPARAM lParam);

private:
	CDockBarWindow m_DockBarWnd;
	CToolBarWindow m_ToolBarWnd;
	DWORD m_dwMainThreadId;
	ICtrlImageBox* m_pDialogBkImgBox;
};
