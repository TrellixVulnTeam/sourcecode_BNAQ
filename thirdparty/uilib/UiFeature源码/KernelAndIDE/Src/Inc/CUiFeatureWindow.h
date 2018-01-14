// ˵����UiFeature�ĸ����ܻ����Ի���

#pragma once
#include <Windows.h>
#include "IWindowBase.h"
#include "IControlBase.h"
#include "IUiFeatureKernel.h"
#include "CWin32Window.h"
#include "UiFeatureWindowDefs.h"
#include <atlstr.h>
using namespace ATL;


class CUiFeatureWindow : public CWin32Window, public IControlMessage
{
public:
	CUiFeatureWindow();
	virtual ~CUiFeatureWindow();

	// ����һ�����ڣ�������
	// char* pszPassword��Ƥ��������
	// LPCWSTR pszDllDir��UiFeatureKernel.dll��ȫ·��
	// LPCWSTR pszSkinPath��*.ufdƤ���ļ���ȫ·��
	// LPCWSTR pszWndName��*.ufdƤ���ļ��жԻ��������
	// HWND hParent��������
	// RECT WndRect��������ʾλ�ã�����Ϊ��Ļλ��
	// int nShow����ʾģʽ���磺SW_SHOW��SW_HIDE
	// LPARAM lParam����������ʱ����Ĳ���������ͨ�� GetCreateWindowParam ����ȡ��
	virtual bool CreateFeatureWindow(char* pszPassword, LPCWSTR pszKernelDllPath, LPCWSTR pszSkinPath, LPCWSTR pszSkinWndName, HWND hParent, RECT WndRect, int nShow, int nStyle = WS_OVERLAPPED | WS_THICKFRAME, LPARAM lParam = NULL);
	virtual bool CreateFeatureWindowByKernel(char* pszPassword, IUiFeatureKernel* pUiKernel, LPCWSTR pszSkinPath, LPCWSTR pszSkinWndName, HWND hParent, RECT WndRect, int nShow, int nStyle = WS_OVERLAPPED | WS_THICKFRAME, LPARAM lParam = NULL);

	// �����ڵ���Ϣ������
	virtual LRESULT WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// ȡ��
	IWindowBase* GetUiFeatureWindow();
	// ���ô��ڱ�������
	void SetWindowText(char* pstrWndText);
	// ��ʼ���Ի������
	virtual void OnInitWindowEnd(int nErrorCode);

	virtual bool CreateWin32Window(HWND hParent, RECT WndRect, LPCWSTR pszWndText, int nShow, int nStyle = WS_OVERLAPPED | WS_THICKFRAME, LPARAM lParam = NULL);

	// ���öԻ���������ʱ��Ķ����ؼ�
	void ShowWindowWithAnimation(IControlBase* pAnimationCtrl);
	// ���ŹرնԻ��򶯻������رմ���
	bool CloseWindowWithAnimation(IControlBase* pAnimationCtrl);
	LPCWSTR GetSkinPath();

	// �ؼ����͸����ڵ���Ϣ�ӿ�
	BEGIN_CTRL_COMMAND
		CTRL_COMMAND_HANDLER(m_pEndAnimationCtrl, CMB_ANIMATION_END, OnCloseWindowWithAnimation);
	END_CTRL_COMMAND

protected:
	virtual bool InitInstance();
	// ��ʾ����
	virtual void OnShowWindow(bool bIsShow, int nShowStatus);
	virtual void OnCreateEnd();
	
	LRESULT OnCloseWindowWithAnimation(WPARAM wParam, LPARAM lParam);

protected:
	HMODULE m_hKernelDll;
	IUiFeatureKernel* m_pUiKernel;
	IPropertySkinManager* m_pSkinManager;
	// UiFeature����ĶԻ�����Դָ��
	IWindowBase* m_pWindowBase;
	CStringW m_strSkinPath;
	CStringW m_strSkinWndName;
	string m_strUserPassword;

	// �Ƿ��ǶԻ����������ʱ����ʾ�ġ�
	bool m_bIsStartShow;
	IControlBase* m_pStartAnimationCtrl;
	IControlBase* m_pEndAnimationCtrl;
};
