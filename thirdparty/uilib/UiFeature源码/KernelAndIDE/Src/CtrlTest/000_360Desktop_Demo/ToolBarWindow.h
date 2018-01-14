#pragma once
#include "..\..\Inc\CUiFeatureWindow.h"
#include "..\..\Inc\Control\ICtrlImageBox.h"
#include "..\..\Inc\Control\ICtrlShadowButton.h"

class CToolBarWindow : public CUiFeatureWindow
{
public:
	CToolBarWindow();
	virtual ~CToolBarWindow();

	bool ShowToolBarWindow(DWORD dwMainThreadId);
	void UnInitialized();

	// �ؼ����͸����ڵ���Ϣ�ӿ�
	BEGIN_CTRL_COMMAND
	WIN32_WND_CTRL_COMMAND
		CTRL_COMMAND_HANDLER(m_pShowDirBtn, CM_BUTTON_UP, OnDirBtnClick)
	END_CTRL_COMMAND

protected:
	// �����ڵ���Ϣ������
	virtual LRESULT WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// WM_CREATE���Ի����ʼ��	
	virtual void OnCreate();
	LRESULT OnDirBtnClick(WPARAM wParam, LPARAM lParam);

private:
	DWORD m_dwMainThreadId;
	ICtrlImageBox* m_pDialogBkImgBox;
	ICtrlShadowButton* m_pShowDirBtn;
};
