
#pragma once
#include "..\ICtrlInterface.h"
#include <atlstr.h>
using namespace ATL;

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_EDIT						(L"Edit")

// edit�򷢸������ؼ�����Ϣ
enum CTRL_MSG_EDIT
{
	// EDIT��ϢBase������Ϣֵ���������ͣ�ֻ����Ϊ������Ϣֵ��Base
	CM_NORMAL_EDIT_BASE	= 0x10007000,
	// EDIT�������
	CM_NORMAL_EDIT_CREATE,
	// EDIT����
	CM_NORMAL_EDIT_DESTROY,
	// EDIT��ʾ
	CM_NORMAL_EDIT_SHOW,
	// EDIT����
	CM_NORMAL_EDIT_HIDE,
	// EDIT�õ�����
	CM_NORMAL_EDIT_SET_FOCUS,
	// EDITʧȥ����
	CM_NORMAL_EDIT_KILL_FOCUS,
	// EDIT����������
	CM_NORMAL_EDIT_CHAR,
	CM_NORMAL_EDIT_KEY_DOWN,
	CM_NORMAL_EDIT_KEY_UP,
	CM_NORMAL_EDIT_MOUSE_MOVE,
	// ���¹��ܼ�
	CM_NORMAL_EDIT_FUNCTION_KEY_DOWN,
	CM_NORMAL_EDIT_MESSAGE_END = 0x10005FFF
};

class _declspec(novtable) ICtrlEdit : public ICtrlInterface
{
public:
	ICtrlEdit(IUiFeatureKernel *pUiKernel);
	virtual LPCWSTR GetEditText() = 0;
	virtual void SetEditText(LPCWSTR pszText) = 0;
	virtual void SetEditFocus() = 0;
	// �жϵ�ǰedit�Ƿ�õ����뽹��
	virtual bool IsForegroundWindow() = 0;
	// ȡ��Edit�йܴ��ڵľ��
	virtual HWND GetWindowHwnd() = 0;
	// ȡ��Edit���ڵľ��
	virtual HWND GetEditHwnd() = 0;
	virtual void EnableEditWindow(BOOL bEnable) = 0;
	virtual void SetReadOnly(BOOL bReadOnly) = 0;
	virtual void GetEditRemindText(CStringW &strText) = 0;
	virtual void SetEditRemindText(WCHAR *pszText) = 0;
	virtual void SetEditToRemindText() = 0;
	virtual void SetEditAutoVScroll(bool bVScroll) = 0;
	virtual void SetEditAutoHScroll(bool bHScroll) = 0;
	virtual void SetEditMultiLine(bool bMultiline = false) = 0;
};
