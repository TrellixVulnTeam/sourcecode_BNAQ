#pragma once
#include "..\..\Inc\CUiFeatureWindow.h"
#include "..\..\Inc\Control\ICtrlPanel.h"
#include "..\..\Inc\Control\ICtrlShadowButton.h"
#include "..\..\Inc\Control\ICtrlWindowTitleBar.h"
#include "..\..\Inc\Control\ICtrlImageBox.h"

class CUiFeatureTestWindow : public CUiFeatureWindow
{
public:
	CUiFeatureTestWindow();
	virtual ~CUiFeatureTestWindow();

	bool ShowUiFeatureTestWindow(DWORD dwMainThreadId);
	void UnInitialized();

protected:
	// �ؼ����͸����ڵ���Ϣ�ӿ�
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam);
	// �����ڵ���Ϣ������
	virtual LRESULT WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// WM_CREATE���Ի����ʼ��	
	virtual void OnCreate();

	virtual void OnKeyDown(int nVirtKey, int nFlag);

private:
	void EndDialog();
	void SetWindowAnimation();

private:
	DWORD m_dwMainThreadId;
	int m_nWndAnimationId;

	ICtrlImageBox* m_pAnimationPanel;
	ICtrlShadowButton* m_pBeginBtn;
};
