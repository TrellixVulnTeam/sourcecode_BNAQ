// ˵����Win32�Ļ����Ի���

#pragma once
#include <Windows.h>
#include <atlstr.h>
using namespace ATL;

// ��ǰ��ʾ�Ĵ���map
class CWin32Window;
typedef map<HWND, CWin32Window*> W32_Wnd_MAP;

class CWin32Window
{
public:
	CWin32Window();
	virtual ~CWin32Window();

	// ����һ�����ڣ�������
	// HWND hParent��������
	// RECT WndRect��������ʾλ�ã�����Ϊ��Ļλ��
	// char *pszWndText�����ڱ���
	// int nShow����ʾģʽ���磺SW_SHOW��SW_HIDE
	// LPARAM lParam����������ʱ����Ĳ���������ͨ�� GetCreateWindowParam ����ȡ��
	virtual bool CreateWin32Window(HWND hParent, RECT WndRect, LPCWSTR pszWndText, int nShow, int nStyle = WS_OVERLAPPED | WS_THICKFRAME, LPARAM lParam = NULL);

	// �����ڵ���Ϣ������
	virtual LRESULT WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam);

	// ȡ�ô��ڱ�������
	LPCWSTR GetWindowText();
	// ���ô��ڱ�������
	void SetWindowText(LPCWSTR pstrWndText);
	// ȡ�ô��ھ��
	HWND GetSafeHandle();
	// �õ�������Ļ����
	RECT GetWindowRect();
	// �õ��ͻ������꣬[0,0]����ϵ
	RECT GetClientRect();
	// ͬAPI�� IsWindow
	bool IsWindow();
	// �������Ƶ���Ļ����
	void CenterWindow();
	// ���ö�ʱ��
	void SetTimer(int nId, UINT uElapse);
	// ȡ����ʱ��
	void KillTimer(int nId);
	// ���öԻ���λ��
	void MoveWindow(RECT MoveRect, BOOL bRepaint = TRUE);
	// ��ʾ/���ش��ڣ�����ΪSW_SHOW֮��
	void ShowWindow(int nShow);
	// �����ػ�����
	void InvalidateRect(RECT *pInvRect);
	// ���´��ڣ��������л���
	void UpdateWindow();
	// �����ػ洰��
	void RedrawWindow(RECT *pDrawRect = NULL);
	// ������Ϣ:Send��ʽ
	LRESULT SendMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// ������Ϣ:Post��ʽ
	bool PostMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// ���ô���֧��͸��ģʽ
	void SetWindowTransparence(bool bIsTrans);
	// ȡ�ô����Ի���Ĳ���
	LPARAM GetCreateWindowParam();
	// �����Ƿ�����
	bool IsWindowEnd();
	// ���ٴ���
	void CloseWindow();
	// ֹͣ���ƴ���
	void StopDrawWin32Window(bool bStop);

	// ȡ�����湤�������С
	RECT GetWorkAreaRect();
	// ����������ͼ��
	void SetDialogIcon(int nIconId);

protected:

	//�̶߳�������
	static LRESULT CALLBACK Win32WndProc(HWND hWnd, UINT nMsgId, WPARAM wParam, LPARAM lParam);

	// ����Windows��Ϣ���������أ�����Ҫ���ø����ԭ���� /////////////////////////////////////////////////////
	// �����Ҫ���ص���Ϣ�����������к����У�����ϵ��ؿ�����Ա //////////////////////////////////////////////
	virtual void OnKeyDown(int nVirtKey, int nFlag);
	virtual void OnCreate();
	// WM_TIMER����ʱ��	
	virtual void OnTimer(UINT nTimerId);
	// WM_DESTROY�����ٴ���
	virtual void OnDestroy();
	virtual void OnKillFocus();
	virtual void OnSetFocus();
	virtual void OnSize(UINT nType, int cx, int cy);
	// WM_ENTERSIZEMOVE�������ƶ������촰�ڲ���
	virtual void OnEnterSizeMove();
	// WM_EXITSIZEMOVE���˳��ƶ������촰�ڲ���
	virtual void OnExitSizeMove();
	virtual bool OnEraseBkgnd(HDC hDc);
	virtual void OnPaint(HDC hDc);
	// ����MFC��PreTranslateMessage��������ص���true�����ټ��������ɷ���Ϣ
	virtual bool PreTranslateMessage(MSG msg);
	// ��ʾ����
	virtual void OnShowWindow(bool bIsShow, int nShowStatus);

	// ���ô����Ի���Ĳ���
	void SetCreateWindowParam(LPARAM lParam);

	// Win32 �Ի���ע�ᴴ������
	ATOM RegisterClass();
	virtual bool InitInstance();
	VOID SetClassName(LPCWSTR pszClassName);

	// �������������������ڰ�ť
	void HideInTaskbar();
//////////////////////////////////////////////////////////////////////////
	// ���º���ԭ���ϲ������ⲿ������ã�ֻ�ṩ���ڲ�ʹ��

public:
	// ���ô��ھ��
	void SetSafeHandle(HWND hWnd);
	void WaitWindowThreadEnd();

protected:
	// �Ƿ�ֹͣ���л��ƴ���
	bool m_bStopDrawWindow;
	bool m_bIsCreateWithThread;
	// ���ھ��
	HWND m_hWnd;
	// ���ڱ�������
	CStringW m_strWndText;
	// �����ھ��
	HWND m_hParentWnd;
	// �����Ի���Ĳ������������ͨ��������������
	LPARAM m_lParam;
	int m_nCreateStyle;

	RECT m_rctCreate;
	int m_nCreateShow;
	HICON m_hDlgIcon;
	CStringW m_strClassName;

private:
	// ��Ϣ�������໯
	static W32_Wnd_MAP ms_Win32WndMap;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �����Լ�ע�����Ϣ����������������ɷ������ں���ֱ�ӷ������ֵ����
#define DEF_MSG_NOT_PASS_ON					(0x1234ABCD)
#define BEGIN_WND_PROC															\
public:																			\
	virtual LRESULT WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam){			\

// int OnMyMsgGoon(WPARAM wParam, LPARAM lParam);
#define WND_MSG_HANDLER(MsgId, Func_name)										\
	if (MsgId == nMsgId){if(Func_name(wParam, lParam)==DEF_MSG_NOT_PASS_ON)return S_OK;}

#define END_WND_PROC(ParentClass)												\
	return ParentClass::WndProc(nMsgId, wParam, lParam);}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
