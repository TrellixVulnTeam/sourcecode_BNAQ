
#pragma once
#include "..\..\Inc\CWin32Window.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\IPropertyImage.h"
#include "..\..\Inc\CDrawingImage.h"
#include <atlstr.h>
using namespace ATL;

// ����EDIT��Ϣ
#define CREATE_EDIT_MSG							(WM_APP + 0x0100)
// ����edit���õ����뽹��
#define CREATE_ACTIVE_EDIT_MSG					(CREATE_EDIT_MSG + 1)
#define	WM_CAL_SCROLL_BAR						(WM_USER + 0X32)

class CEditWindow : public CWin32Window
{
public:
	CEditWindow();
	virtual ~CEditWindow();

	// ����Edit���ڵ����ԣ��ڿؼ��� CreateControlPropetry �����е���
	bool CreateEditPropetry(IControlBase* pOwnerCtrl, bool bIsNewCtrl);
	// ����EDIT���ڣ��ڿؼ��� OnCreate �����е���
	bool CreateEditWindow(RECT ctrlRectInOwner, int nShow);
	// EDIT�����Զ�����Ϣ�����ڿؼ� OnCtrlNotify �����е���
	void OnEditNotify(int nMsgId, WPARAM wParam, LPARAM lParam);

	void GetEditText(CStringW &strText);
	void SetEditText(LPCWSTR pszText);
	void GetEditRemindText(CStringW &strText);
	void SetEditRemindText(WCHAR *pszText);
	void SetEditToRemindText();
	void SetEditAutoVScroll(bool bVScroll);
	void SetEditAutoHScroll(bool bHScroll);
	void SetEditMultiLine(bool bMultiline = false);
	// ����edit����edit�õ����뽹��
	void PostActiveMessage();
	// �жϵ�ǰedit�Ƿ�õ����뽹��
	bool IsForegroundWindow();

	virtual void SetRectInOwner(RECT ctrlRectInOwner);

	// ȡ��Edit�йܴ��ڵľ��
	HWND GetWindowHwnd();
	// ȡ��Edit���ڵľ��
	HWND GetEditHwnd();
	void EnableEditWindow(BOOL bEnable);
	void SetReadOnly(BOOL bReadOnly);

protected:
	// �����ڵ���Ϣ������
	virtual LRESULT WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	virtual bool CreateWindowWithNewThread(HWND hParent, RECT WndRect, char *pszWndText, int nShow, int nStyle = WS_OVERLAPPED | WS_THICKFRAME, LPARAM lParam = NULL);
	virtual bool CreateWindowWithoutThread(HWND hParent, RECT WndRect, char *pszWndText, int nShow, int nStyle = WS_OVERLAPPED | WS_THICKFRAME, LPARAM lParam = NULL);
	virtual void OnCreate();
	virtual void OnSize(UINT nType, int cx, int cy);
	virtual void OnKeyDown(int nVirtKey, int nFlag);
	// ϵͳ��Ϣ������true˵������Ҫ���ظ����ü�������
	virtual bool OnEditSysCommand(WPARAM wParam, LPARAM lParam);

private:
	// �����ϵ�EDIT�ؼ��ı�������
	LRESULT OnCtlColorEdit(WPARAM wParam, LPARAM lParam);
	// ֻ��״̬�µı��������塢��ɫ����
	LRESULT OnCtlColorStatic(WPARAM wParam, LPARAM lParam);
	void OnEditCreateMesage();
	bool OnEditEraseBkgnd(HDC hDc);
	void SetEditFocus();
	int GetColorValue(IPropertyInt* pPropColor);
	void SetEditFont(HFONT hFont);

public:
	LRESULT EditProc(UINT nMsgId, WPARAM wParam, LPARAM lParam);

private:
	IWindowBase* m_pWindowBase;
	CDrawingImage m_EditBkMemDc;
	IControlBase* m_pOwnerCtrl;
	HWND m_hEdit;
	WNDPROC m_defEditWndProc;
	RECT m_CtrlRectInOwner;
	int m_nShow;

	HBRUSH m_hReadOnlyColorBrush;
	HBRUSH m_hColorBrush;
	HFONT m_hEditRemindFont;

	HFONT m_hEditFont;
	IPropertyGroup* m_pPropEditGroup;
	IPropertyImage* m_pPropEditBkImg;
	IPropertyFont* m_pPropEditFont;
	IPropertyString* m_pPropEditRemindInfo;
	IPropertyFont* m_pPropEditRemindFont;
	IPropertyBool* m_pPropReadOnly;

	IPropertyGroup* m_pPropBkColorGroup;
	IPropertyBool* m_pPropShowBkColor;
	IPropertyInt* m_pPropR;
	IPropertyInt* m_pPropG;
	IPropertyInt* m_pPropB;


	IPropertyFont* m_pPropReadOnlyEditFont;
	IPropertyGroup* m_pPropReadOnlyBkColorGroup;
	IPropertyBool* m_pPropReadOnlyShowBkColor;
	IPropertyInt* m_pPropReadOnlyR;
	IPropertyInt* m_pPropReadOnlyG;
	IPropertyInt* m_pPropReadOnlyB;

	RECT m_OldEditRct;
	DWORD		 m_dwStyle;
	int  m_nMaxLineCount;
	BOOL m_isReminding;
};
