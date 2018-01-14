#pragma once
#include "..\..\inc\CUiFeatureWindow.h"

#include <winuser.h>
#include <atlstr.h>
using namespace ATL;

class CSoftware : public CUiFeatureWindow
{
public:
	CSoftware();
	virtual ~CSoftware();

	bool CreateUIWindow(HWND hParent);

protected:
	// �ؼ����͸����ڵ���Ϣ�ӿ�
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam);
	// �����ڵ���Ϣ������
	virtual LRESULT WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// WM_CREATE���Ի����ʼ��	
	virtual void OnCreate();

	virtual void OnKeyDown(int nVirtKey, int nFlag);
};