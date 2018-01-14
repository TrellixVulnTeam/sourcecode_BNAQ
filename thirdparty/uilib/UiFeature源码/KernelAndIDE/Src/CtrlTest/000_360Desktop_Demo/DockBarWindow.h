#pragma once
#include "..\..\Inc\CUiFeatureWindow.h"
#include "..\..\Inc\Control\ICtrlImageBox.h"
#include "..\..\Inc\Control\ICtrlShadowButton.h"

class CDockBarWindow : public CUiFeatureWindow
{
public:
	CDockBarWindow();
	virtual ~CDockBarWindow();

	bool ShowDockBarWindow();

//////////////////////////////////////////////////////////////////////////
	// �ؼ����͸����ڵ���Ϣ�ӿ�
	BEGIN_CTRL_COMMAND
	WIN32_WND_CTRL_COMMAND
		CTRL_COMMAND_HANDLER(m_pShowDirBtn, CM_BUTTON_UP, OnDirBtnClick)
	END_CTRL_COMMAND
//////////////////////////////////////////////////////////////////////////
	// �����ڵ���Ϣ������
	BEGIN_WND_PROC
//	WND_MSG_HANDLER(WM_UIF_CRATE_SUB_WINDOW, OnCreateSubWnd)
	END_WND_PROC(CUiFeatureWindow)
//////////////////////////////////////////////////////////////////////////

protected:
	// WM_CREATE���Ի����ʼ��	
	virtual void OnCreate();

	LRESULT OnDirBtnClick(WPARAM wParam, LPARAM lParam);

private:
	ICtrlImageBox* m_pDialogBkImgBox;
	ICtrlShadowButton* m_pShowDirBtn;
};
