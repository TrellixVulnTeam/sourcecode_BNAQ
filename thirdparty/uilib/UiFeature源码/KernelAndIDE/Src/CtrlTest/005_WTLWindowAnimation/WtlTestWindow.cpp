#include "StdAfx.h"
#include "WtlTestWindow.h"
#include <assert.h>
#include "..\..\Inc\UiFeatureDefs.h"
#include <Shellapi.h>
#include <windows.h>
#include "resource.h"

CWtlTestWindow::CWtlTestWindow()
{
	m_dwMainThreadId = 0;
	m_pWindowbkPanel = NULL;

	m_pAnimationBtn = NULL;
	m_nWndAnimationId = 1;
	m_pModule = NULL;
	m_DlgIcon = NULL;
}

CWtlTestWindow::~CWtlTestWindow()
{
}

bool CWtlTestWindow::ShowWtlTestWindow(CAppModule *_pModule, DWORD dwMainThreadId)
{
	m_dwMainThreadId = dwMainThreadId;
	m_pModule = _pModule;

	CStringW strKernelDllPath = PathHelperW(_T(NAME_KERNEL_DLL));

	// ȡ��Ƥ������·��
	CStringW strSkinPath = PathHelperW(_T("..\\SkinPackage\\005_WTLWindowAnimation\\005_WTLWindowAnimation.ufd"));

	// ʹ��Ƥ�����еĶԻ���Ƥ����Ϣ��ʼ����ǰ�ĶԻ���
	RECT WndRct = {0, 0, 0, 0};
	return (CreateWTLFeatureWindow(m_pModule, strKernelDllPath, strSkinPath, L"TestWindow", NULL,
		NULL, WndRct, SW_SHOW, WS_OVERLAPPED | WS_THICKFRAME, 0, NULL) == TRUE);
}

LRESULT CWtlTestWindow::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nVirtKey = (int)wParam;

	// ����esc�˳�����
	if (nVirtKey == VK_ESCAPE)
		CloseTestWindow();

	return 0;
}

// �ؼ����͸����ڵ���Ϣ�ӿ�
LRESULT CWtlTestWindow::OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam)
{
	if (nMsgId == CM_LINK_UP)
	{
		// �����˳����ӿؼ�
		ICtrlLink* pLinkCtrl = dynamic_cast<ICtrlLink*>(pCtrl);
		if (pLinkCtrl == NULL)
			return -1;

		// ȡ�ó����ӵ����ӵ�ַ
		CStringW strUrl = (WCHAR*)wParam;
		if (strUrl.GetLength() <= 0)
			return -1;

		// ����ҳ
		HINSTANCE hOpen = ::ShellExecute(NULL, _T("open"), strUrl, NULL, NULL, SW_SHOWNORMAL);
		if (hOpen == NULL)
			return -1;
	}
	else if (m_pAnimationBtn != NULL && nMsgId == CM_BUTTON_UP && m_pAnimationBtn->CompareControl(pCtrl))
	{
		// ���¿�ʼ������ť
		SetWindowAnimation();
	}
	else if (nMsgId == KCM_SYS_COMMAND_CLOSE)
	{
		::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
	}

	return 0;
}

void CWtlTestWindow::CloseTestWindow()
{
	// �رմ���
	this->PostMessage(WM_CLOSE);
	// �˳����߳�
	::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
}

LRESULT CWtlTestWindow::OnUiFeatureMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (UI_FEATURE_KERNEL_MSG == uMsg && WID_ANIMATION_THREAD_END == wParam)
	{
		// ���ڽ��ܵ������߳̽�������Ϣ
		// ��Ϊ����72����������Ҫ��ÿһ������������ʱ�������һ������
		SetWindowAnimation();
	}

	return 0;
}

// �Ի����ʼ��	
VOID CWtlTestWindow::OnWTLWindowCreate()
{
//////////////////////////////////////////////////////////////////////////
	// ����������ͼ��
	m_DlgIcon = ::LoadIcon(::GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_UIFEATURERUN));
	if (m_DlgIcon != NULL)
		this->SetIcon(m_DlgIcon);
//////////////////////////////////////////////////////////////////////////

	if (m_pWindowBase == NULL)
		return;

	GET_CONTROL_EX(m_pWindowbkPanel, ICtrlImageBox, "DlgInBk");
	GET_CONTROL_EX(m_pAnimationBtn, ICtrlShadowButton, "BeginBtn");
	if (m_pWindowbkPanel == NULL || m_pAnimationBtn == NULL)
	{
		assert(false);
		return;
	}
}

void CWtlTestWindow::UnInitialized()
{
	if (m_pUiKernel != NULL)
		m_pUiKernel->UnInitialized();
}

void CWtlTestWindow::SetWindowAnimation()
{
	if (m_pWindowbkPanel == NULL || m_pWindowBase == NULL)
		return;

	if (m_nWndAnimationId > 81)
	{
		m_nWndAnimationId = 1;
		::MessageBox(m_hWnd, _T("�ף��Ѿ�Ϊ��������79��������"), _T("�ף��������ˣ�"), MB_OK);
		return;
	}

	// ����Ƕ������͵�ID��֧�ִ� 2-73
	m_nWndAnimationId++;

	// ���ÿؼ���������
	m_pWindowbkPanel->PP_SetCtrlAnimationType(m_nWndAnimationId);

	// �򴰿ڼ��붯��Ԫ��
	m_pWindowBase->AppendAnimationControl(m_pWindowbkPanel);

	// ��ʼ����
	m_pWindowBase->DoControlAnimation();
}
