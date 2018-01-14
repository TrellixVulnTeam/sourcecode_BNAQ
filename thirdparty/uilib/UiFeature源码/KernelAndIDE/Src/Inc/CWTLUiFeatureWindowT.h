////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��Ҫ˵��
// ��ͷ�ļ���ʾ�����ʹ��WTL����UiFeature�����Ի���������ʾ����Ҳ����Ȼ�ܷ�ʹ��MFC�������ķ�ʽֱ�ӵ���UiFeature�ں��ˡ�
// WTL���ڵ�ʹ�����ӿ��Բο�Demo��005_WTLWindowAnimation

#pragma once
#include "UiFeatureDefs.h"
#include "UiFeatureWindowDefs.h"
#include "IWindowBase.h"
#include "IControlBase.h"
#include "IUiFeatureKernel.h"
#include "ICommonFun.h"
#include <assert.h>

#include <atlbase.h>
#include <atlapp.h>
#include <atlwin.h>
#include <atlframe.h>
#include <atlcrack.h>

#include <string>
#include <map>
#include <vector>
using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class CWTLUiFeatureWindowT : public CWindowImpl<T>,
							 public CUpdateUI<T>,
							 public CMessageFilter,
							 public CIdleHandler,
							 public IControlMessage
{
public:
	// ���� CreateWTLFeatureWindow ���� CreateWTLFeatureWindowByKernel ��������������ϵĻص�����
	// �����ڴ˺�����ȡ�ÿؼ�ָ��
	virtual VOID OnWTLWindowCreate() = 0;
	// �ؼ����͵���Ϣ�����͵��˺���
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam) = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	CWTLUiFeatureWindowT()
	{
		m_hWnd = NULL;
		m_pModule = NULL;

		m_hKernelDll = NULL;
		m_pSkinManager = NULL;
		m_pWindowBase = NULL;

		m_strKernelDllPath = "";
		m_strSkinPath = "";
		m_strSkinWndName = "";

		INIT_RECT(m_rctCreate);
	}

	~CWTLUiFeatureWindowT()
	{
		SAFE_FREE_LIBRARY(m_hKernelDll);
	}

	virtual BOOL CreateWTLFeatureWindow(CAppModule *_pModule, LPCWSTR pszKernelDllPath, LPCWSTR pszSkinPath, LPCWSTR pszSkinWndName, char *pszPassword, 
		HWND hWndParent, RECT wndRct, int nShow, DWORD dwStyle = 0, DWORD dwExStyle = 0, LPVOID lpCreateParam = NULL)
	{
		if (_pModule == NULL || m_hWnd != NULL || pszKernelDllPath == NULL || pszSkinPath == NULL || pszSkinWndName == NULL ||
			wcslen(pszKernelDllPath) <= 0 || wcslen(pszSkinPath) <= 0 || wcslen(pszSkinWndName) <= 0)
			return FALSE;

		m_rctCreate = wndRct;
		m_pModule = _pModule;

		m_strKernelDllPath = pszKernelDllPath;
		m_strSkinPath = pszSkinPath;
		m_strSkinWndName = pszSkinWndName;

		// ����UiFeatureKernel.dll
		m_hKernelDll = ::LoadLibraryW(pszKernelDllPath);
		if (m_hKernelDll == NULL)
		{
			DWORD dwErr = ::GetLastError();
			return FALSE;
		}

		// ȡ��UiFeatureKernel���ں˽ӿ�
		GETUIKERNELINTERFACE GetKernel = (GETUIKERNELINTERFACE)::GetProcAddress(m_hKernelDll, "GetUiKernelInterface");
		if (GetKernel == NULL)
		{
			DWORD dwErr = ::GetLastError();
			SAFE_FREE_LIBRARY(m_hKernelDll);
			return FALSE;
		}

		m_pUiKernel = GetKernel();
		if (m_pUiKernel == NULL)
		{
			DWORD dwErr = ::GetLastError();
			SAFE_FREE_LIBRARY(m_hKernelDll);
			return false;
		}

		// ȡ��Ƥ����������
		m_pSkinManager = m_pUiKernel->GetSkinManager();
		if (m_pSkinManager == NULL)
		{
			m_pUiKernel = NULL;
			SAFE_FREE_LIBRARY(m_hKernelDll);
			return false;
		}

		// ��������ʼ������
		return InitUiFeatureInstance(pszPassword, hWndParent, wndRct, nShow, dwStyle, dwExStyle, lpCreateParam);
	}

	virtual BOOL CreateWTLFeatureWindowByKernel(CAppModule *_pModule, IUiFeatureKernel* pUiKernel, char* pszSkinPath, char *pszSkinWndName, char *pszPassword, 
		HWND hWndParent, RECT wndRct, int nShow, DWORD dwStyle = 0, DWORD dwExStyle = 0, LPVOID lpCreateParam = NULL)
	{
		if (_pModule == NULL || pUiKernel == NULL || pszSkinPath == NULL || strlen(pszSkinPath) <= 0 ||
			pszSkinWndName == NULL || strlen(pszSkinWndName) <= 0)
			return FALSE;

		m_rctCreate = wndRct;
		m_pModule = _pModule;
		m_pUiKernel = pUiKernel;
		m_strSkinPath = pszSkinPath;
		m_strSkinWndName = pszSkinWndName;

		m_pSkinManager = m_pUiKernel->GetSkinManager();
		if (m_pSkinManager == NULL)
		{
			m_pUiKernel = NULL;
			return FALSE;
		}

		return InitUiFeatureInstance(pszPassword, hWndParent, wndRct, nShow, dwStyle, dwExStyle, lpCreateParam);
	}

	BEGIN_UPDATE_UI_MAP(CWTLUiFeatureWindowT)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CWTLUiFeatureWindowT)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	END_MSG_MAP()

//	Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
//	LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
//	LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return FALSE;
	}

	virtual BOOL OnIdle()
	{
		return FALSE;
	}

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (m_pModule == NULL)
			return -1;

		CMessageLoop* pLoop = m_pModule->GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (m_pModule == NULL)
			return -1;

		CMessageLoop* pLoop = m_pModule->GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->RemoveMessageFilter(this);
		pLoop->RemoveIdleHandler(this);
		bHandled = FALSE;
		return 0;
	}

private:
	BOOL InitUiFeatureInstance(char *pszPassword, HWND hWndParent, RECT wndRct, int nShow, DWORD dwStyle = 0, DWORD dwExStyle = 0, LPVOID lpCreateParam = NULL)
	{
		if (m_pModule == NULL)
			return FALSE;

		// WTL �ķ�ʽ��������
		this->Create(hWndParent, &wndRct, _T("WtlUiFeatureWindow"), dwStyle, dwExStyle, 0U, lpCreateParam);
		if (IS_INVALID_HANDLE(m_hWnd))
			return FALSE;

		IControlMessage *pCtrlMsg = dynamic_cast<IControlMessage*>(this);
		if (pCtrlMsg == NULL)
		{
			assert(false);
			return FALSE;
		}

		// ʹ��UiFeature�ں˴����Ի���
		m_pWindowBase = m_pUiKernel->PG_InitFeatureSkin(m_hWnd, m_strSkinPath, m_strSkinWndName, pszPassword);
		if (m_pWindowBase == NULL)
		{
			assert(false);
			return FALSE;
		}

		// ���ÿؼ��ص�
		m_pWindowBase->SetCtrlMsgCallBack(pCtrlMsg);
		if (IS_RECT_EMPTY(m_rctCreate))
		{
			SIZE WndSize = m_pWindowBase->PP_GetWindowPropSize();
			INIT_RECT(m_rctCreate);
			m_rctCreate.right = WndSize.cx;
			m_rctCreate.bottom = WndSize.cy;
			this->MoveWindow(&m_rctCreate);
			this->CenterWindow();
		}
		else
		{
			this->MoveWindow(&m_rctCreate);
		}

		// ���ڴ������
		OnWTLWindowCreate();
		::ShowWindow(m_hWnd, nShow);
		return IS_SAFE_HANDLE(m_hWnd);
	}

protected:
	CAppModule*				m_pModule;
	// UiFeature DLL ���
	HMODULE					m_hKernelDll;
	// UiFeature �ں�ָ��
	IUiFeatureKernel*		m_pUiKernel;
	// Ƥ����������
	IPropertySkinManager*	m_pSkinManager;
	// UiFeature �Ĵ���ָ��
	IWindowBase*			m_pWindowBase;
	// UiFeatureKernel.dll ��·��
	CStringW				m_strKernelDllPath;
	// ��ǰ�Ի����Ӧ��Ƥ������·��
	CStringW				m_strSkinPath;
	// ��ǰ�Ի������Ƥ�����еĴ�������
	CStringW				m_strSkinWndName;
	// ��ǰ�Ի��򴴽�ʱ�Ĵ��ڴ�С
	RECT					m_rctCreate;
};
